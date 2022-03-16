// https://llvm.org/docs/LoopTerminology.html#loop-terminology-loop-rotate

int main() {

    int j = 0;
    for (int i = 0; i < 10; i++) {
        j += 1;
        if (i == j) {
            j = 0;
        }
    }
    return 0;
}
