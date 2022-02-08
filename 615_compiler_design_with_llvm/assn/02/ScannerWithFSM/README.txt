# Homework 2: Scanner with FSM

For this portion of Homework 2, modifications were made to the provided Hw1-ScannerWithFSM files to add support for scanning the following tokens as SYMBOLS:

+ - * / < <= == >= > = ( ) # " // /* */

## Modifications

The following modifications were made to achieve the requirements:

1. Logic was added in the `getSymbol` function in getSymbol.cpp. Similarly to `getKeyword`, the scanning function follows an FSM logic utilizing the states declared in `ASCII_SYM.h`.

2. `ASCII_SYM.h` was added. The file is similar to `ASCII_KW.h` as it consists of its own versions of the variables defined for the keyword FSM. The ASCII indices are modified to capture the following characters: ", #, (, ), *, +, -, /, <, =, and >. The array of states consist of 19 states.

3. A minor update to `Token.cpp` was added, where the following line:
```
if (*c == '\n') {
```
was replaced with
```
if (*c == '\n' || *c == '\r') {
```
to account for the different line feeds on my development operating system.

4. The contents of `HW1-Input.txt` was replaced with the following:
+ - * / < <= == >= > = ( ) # " // /* */

This change is also reflected on the output that gets saved into `HW1-Output.txt`.

## Compilation

The attached CMakeLists.txt was used to compile the assignment files. The following are the version numbers of the tools used:

| Tool    | Version |
| ------- | ------- |
| Clang++ | 13.0.0  |
| CMake   | 3.22.2  |

The target machine used was an Ubuntu 20.04 64-bit virtual machine. The Linux kernel version is 5.13.0-28-generic. The following is a snippet of the output generated from `uname -a`:

```
Linux ribbas-virtual-machine 5.13.0-28-generic #31~20.04.1-Ubuntu SMP Wed Jan 19 14:08:10 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
```
