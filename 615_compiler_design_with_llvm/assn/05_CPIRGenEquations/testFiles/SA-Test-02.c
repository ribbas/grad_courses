/* Functions declared void must not return values */

void func(int x)
{
    int A;
    int B;
    int C;
    A = (B = (C = 0) + 1) - 1;
    return;
}

void main(void)
{
    int x;
    x = 0;
    func(x);
}
