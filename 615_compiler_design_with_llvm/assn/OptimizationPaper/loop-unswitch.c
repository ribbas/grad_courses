int main() {

    int i, w, x[1000], y[1000];
    for (i = 0; i < 1000; i++) {
        x[i] += y[i];
        if (w){
            y[i] = 0;
        }
    }

    return 0;
}
