/* A program to test semantics. C- semantics do not permit a void function to
   return a value or a non-void function to not return a value, so the below
   code is invalid. */

int ifunc (int u, int v)
{
    int a;
    a = u * v;
    return;
}

void vfunc (int u, int v)
{
    int a;
    a = u + v;
    return a;
}

void main(void)
{
    int x; int y; int z;

    z = ifunc(x, y);

    vfunc(x, z);
}