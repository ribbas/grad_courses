/* The number of parameters in a function call must equal the number of
arguments in its declaration */

void func(int a, int b)
{
    a + b;
}

void main(void)
{
    int x;
    int y;
    x = 1;
    y = func(x);
}
