
int callee(const int& X) {
    return X + 1;
}

int main() {

    if (callee(4) == 5) {
        return 0;
    } else {
        return -1;
    }
}
