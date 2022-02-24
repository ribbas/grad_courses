/* Functions declared void must not return values */

void func(int x)
{
    x = x + 1;
    return x;
}

void main(void)
{
    int x;
    x = 0;
    func(x);
}
