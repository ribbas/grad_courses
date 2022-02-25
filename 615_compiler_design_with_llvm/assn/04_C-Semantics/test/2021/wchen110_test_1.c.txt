/* A program to test semantics. C- semantics do not permit assignment within
   the scope of an if-else or while conditional, as in if (x = 2) or while (x <5 ), even
   though it evaluates correctly, so the below code is invalid. */

void main(void)
{
    int x;
    int y;
    int z;
    x = input();
    y = input();
    if (x = y) {
        z = 1;
    } else {
        z = 0;
    }
}
