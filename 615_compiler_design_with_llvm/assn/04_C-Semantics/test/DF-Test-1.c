/* Pg. 494 Functions not declared void must return values. Functions declared void must not return values. */

void func1(void) {
    return 9;
}

int func2(void) {
    
}

void main(void)
{
    func1();
    func2();
}