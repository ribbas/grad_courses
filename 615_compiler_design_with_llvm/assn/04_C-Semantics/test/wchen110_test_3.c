/* A program to test semantics. C- semantics do not permit nested assignation
   to occur, so the below code is invalid. */

void main(void)
{
    int x;
    int y;
    int z;
    x = input();
    y = input();
    z = (x = (y = 0) + 1);
}
