// While loop cannot accept variable declaration as expression by C-Minus grammar

// Decrementing variable is not supported

void main(void) {

    int x = 10;

    while(int y = 10;)

    {

        x = y;

        y--;

    }

}