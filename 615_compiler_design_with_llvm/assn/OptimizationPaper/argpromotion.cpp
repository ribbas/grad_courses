

int callee(int& x) {
    return x; // load
}

int caller() {
    int T; // on stack
    T = 2; // store
    return callee(T);
}

int main() {

    caller();
    return 0;
}
