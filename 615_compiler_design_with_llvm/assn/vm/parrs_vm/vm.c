// vm.c
// by Professor Terrance Parr

#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

typedef struct {
    char name[8];
    int nargs;
} VM_INSTRUCTION;

static VM_INSTRUCTION vm_instructions[] = {
    {"noop", 0},   // 0
    {"iadd", 0},   // 1
    {"isub", 0},   // 2
    {"imul", 0},   // 3
    {"ilt", 0},    // 4
    {"ieq", 0},    // 5
    {"br", 1},     // 6
    {"brt", 1},    // 7
    {"brf", 1},    // 8
    {"iconst", 1}, // 9
    {"load", 1},   // 10
    {"gload", 1},  // 11
    {"store", 1},  // 12
    {"gstore", 1}, // 13
    {"print", 0},  // 14
    {"pop", 0},    // 15
    {"call", 3},   // 16
    {"ret", 0},    // 17
    {"halt", 0}    // 18
};

static void vm_context_init(Context* ctx, int ip, int nlocals);

void vm_init(VM* vm, int* code, int code_size, int nglobals) {
    vm->code = code;
    vm->code_size = code_size;
    vm->globals = calloc(nglobals, sizeof(int));
    vm->nglobals = nglobals;
}

void vm_free(VM* vm) {
    free(vm->globals);
    free(vm);
}

VM* vm_create(int* code, int code_size, int nglobals) {
    VM* vm = calloc(1, sizeof(VM));
    vm_init(vm, code, code_size, nglobals);
    return vm;
}

void vm_exec_goto(VM* vm, int startip, bool trace) {

    static void* dispatch_table[] = {
        &&DO_NOOP, &&DO_IADD,  &&DO_ISUB,  &&DO_IMUL,   &&DO_ILT,
        &&DO_IEQ,  &&DO_BR,    &&DO_BRT,   &&DO_BRF,    &&DO_ICONST,
        &&DO_LOAD, &&DO_GLOAD, &&DO_STORE, &&DO_GSTORE, &&DO_PRINT,
        &&DO_POP,  &&DO_CALL,  &&DO_RET,   &&DO_HALT};

    // registers
    int ip;     // instruction pointer register
    int sp;     // stack pointer register
    int callsp; // call stack pointer register

    int a = 0;
    int b = 0;
    int addr = 0;
    int offset = 0;

    ip = startip;
    sp = -1;
    callsp = -1;

    goto* dispatch_table[vm->code[ip++]];
    while (true) {

    DO_NOOP : { goto* dispatch_table[vm->code[ip++]]; }
    DO_IADD : {

        b = vm->stack[sp--];     // 2nd opnd at top of stack
        a = vm->stack[sp--];     // 1st opnd 1 below top
        vm->stack[++sp] = a + b; // push result

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_ISUB : {

        b = vm->stack[sp--];
        a = vm->stack[sp--];
        vm->stack[++sp] = a - b;

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_IMUL : {

        b = vm->stack[sp--];
        a = vm->stack[sp--];
        vm->stack[++sp] = a * b;

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_ILT : {

        b = vm->stack[sp--];
        a = vm->stack[sp--];
        vm->stack[++sp] = (a < b);

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_IEQ : {

        b = vm->stack[sp--];
        a = vm->stack[sp--];
        vm->stack[++sp] = (a == b);

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_BR : {

        ip = vm->code[ip];

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_BRT : {

        addr = vm->code[ip++];
        if (vm->stack[sp--] == true) {
            ip = addr;
        }

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_BRF : {

        addr = vm->code[ip++];
        if (vm->stack[sp--] == false) {
            ip = addr;
        }

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_ICONST : {

        vm->stack[++sp] = vm->code[ip++]; // push operand

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_LOAD : { // load local or arg

        offset = vm->code[ip++];
        vm->stack[++sp] = vm->call_stack[callsp].locals[offset];

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_GLOAD : { // load from global memory

        addr = vm->code[ip++];
        vm->stack[++sp] = vm->globals[addr];

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_STORE : {

        offset = vm->code[ip++];
        vm->call_stack[callsp].locals[offset] = vm->stack[sp--];

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_GSTORE : {

        addr = vm->code[ip++];
        vm->globals[addr] = vm->stack[sp--];

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_PRINT : {

        printf("%d\n", vm->stack[sp--]);
        goto* dispatch_table[vm->code[ip++]];
    }
    DO_POP : {

        --sp;
        goto* dispatch_table[vm->code[ip++]];
    }
    DO_CALL : {

        // expects all args on stack
        addr = vm->code[ip++];        // index of target function
        int nargs = vm->code[ip++];   // how many args got pushed
        int nlocals = vm->code[ip++]; // how many locals to allocate
        ++callsp; // bump stack pointer to reveal space for this call
        vm_context_init(&vm->call_stack[callsp], ip, nargs + nlocals);
        // copy args into new context
        for (int i = 0; i < nargs; i++) {
            vm->call_stack[callsp].locals[i] = vm->stack[sp - i];
        }
        sp -= nargs;
        ip = addr; // jump to function

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_RET : {

        ip = vm->call_stack[callsp].returnip;
        callsp--; // pop context

        goto* dispatch_table[vm->code[ip++]];
    }
    DO_HALT : { break; }
    }

    if (trace) {
        vm_print_data(vm->globals, vm->nglobals);
    }
}

void vm_exec(VM* vm, int startip, bool trace) {
    // registers
    int ip;     // instruction pointer register
    int sp;     // stack pointer register
    int callsp; // call stack pointer register

    int a = 0;
    int b = 0;
    int addr = 0;
    int offset = 0;

    ip = startip;
    sp = -1;
    callsp = -1;
    int opcode = vm->code[ip];

    while (opcode != HALT && ip < vm->code_size) {
        if (trace) {
            vm_print_instr(vm->code, ip);
        }
        ip++; // jump to next instruction or to operand
        switch (opcode) {
            case IADD: {
                b = vm->stack[sp--];     // 2nd opnd at top of stack
                a = vm->stack[sp--];     // 1st opnd 1 below top
                vm->stack[++sp] = a + b; // push result
                break;
            }
            case ISUB: {
                b = vm->stack[sp--];
                a = vm->stack[sp--];
                vm->stack[++sp] = a - b;
                break;
            }
            case IMUL: {
                b = vm->stack[sp--];
                a = vm->stack[sp--];
                vm->stack[++sp] = a * b;
                break;
            }
            case ILT: {
                b = vm->stack[sp--];
                a = vm->stack[sp--];
                vm->stack[++sp] = (a < b) ? true : false;
                break;
            }
            case IEQ: {
                b = vm->stack[sp--];
                a = vm->stack[sp--];
                vm->stack[++sp] = (a == b) ? true : false;
                break;
            }
            case BR: {
                ip = vm->code[ip];
                break;
            }
            case BRT: {
                addr = vm->code[ip++];
                if (vm->stack[sp--] == true) {
                    ip = addr;
                }
                break;
            }
            case BRF: {
                addr = vm->code[ip++];
                if (vm->stack[sp--] == false) {
                    ip = addr;
                }
                break;
            }
            case ICONST: {
                vm->stack[++sp] = vm->code[ip++]; // push operand
                break;
            }
            case LOAD: { // load local or arg
                offset = vm->code[ip++];
                vm->stack[++sp] = vm->call_stack[callsp].locals[offset];
                break;
            }
            case GLOAD: { // load from global memory
                addr = vm->code[ip++];
                vm->stack[++sp] = vm->globals[addr];
                break;
            }
            case STORE: {
                offset = vm->code[ip++];
                vm->call_stack[callsp].locals[offset] = vm->stack[sp--];
                break;
            }
            case GSTORE: {
                addr = vm->code[ip++];
                vm->globals[addr] = vm->stack[sp--];
                break;
            }
            case PRINT: {
                printf("%d\n", vm->stack[sp--]);
                break;
            }
            case POP: {
                --sp;
                break;
            }
            case CALL: {
                // expects all args on stack
                addr = vm->code[ip++];        // index of target function
                int nargs = vm->code[ip++];   // how many args got pushed
                int nlocals = vm->code[ip++]; // how many locals to allocate
                ++callsp; // bump stack pointer to reveal space for this
                          // call
                vm_context_init(&vm->call_stack[callsp], ip, nargs + nlocals);
                // copy args into new context
                for (int i = 0; i < nargs; i++) {
                    vm->call_stack[callsp].locals[i] = vm->stack[sp - i];
                }
                sp -= nargs;
                ip = addr; // jump to function
                break;
            }
            case RET: {
                ip = vm->call_stack[callsp].returnip;
                callsp--; // pop context
                break;
            }
            default: {
                printf("invalid opcode: %d at ip=%d\n", opcode, (ip - 1));
                exit(1);
            }
        }
        if (trace) {
            vm_print_stack(vm->stack, sp);
        }
        opcode = vm->code[ip];
    }
    if (trace) {
        vm_print_data(vm->globals, vm->nglobals);
    }
}

static void vm_context_init(Context* ctx, int ip, int nlocals) {
    if (nlocals > DEFAULT_NUM_LOCALS) {
        fprintf(stderr, "too many locals requested: %d\n", nlocals);
    }
    ctx->returnip = ip;
}

void vm_print_instr(int* code, int ip) {
    int opcode = code[ip];
    VM_INSTRUCTION* inst = &vm_instructions[opcode];
    switch (inst->nargs) {
        case 0: {
            printf("%04d:  %-20s", ip, inst->name);
            break;
        }
        case 1: {
            printf("%04d:  %-10s%-10d", ip, inst->name, code[ip + 1]);
            break;
        }
        case 2: {
            printf("%04d:  %-10s%d,%10d", ip, inst->name, code[ip + 1],
                   code[ip + 2]);
            break;
        }
        case 3: {
            printf("%04d:  %-10s%d,%d,%-6d", ip, inst->name, code[ip + 1],
                   code[ip + 2], code[ip + 3]);
            break;
        }
    }
}

void vm_print_stack(int* stack, int count) {
    printf("stack=[");
    for (int i = 0; i <= count; i++) {
        printf(" %d", stack[i]);
    }
    printf(" ]\n");
}

void vm_print_data(int* globals, int count) {
    printf("Data memory:\n");
    for (int i = 0; i < count; i++) {
        printf("%04d: %d\n", i, globals[i]);
    }
}
