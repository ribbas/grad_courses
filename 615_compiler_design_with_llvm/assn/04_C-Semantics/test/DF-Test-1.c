/* Pg. 494 Functions not declared void must return values. Functions declared void must not return values. */

void funca(void) {
    return 9;
}

int funcb(void) {
    
}

void main(void)
{
    funca();
    funcb();
}