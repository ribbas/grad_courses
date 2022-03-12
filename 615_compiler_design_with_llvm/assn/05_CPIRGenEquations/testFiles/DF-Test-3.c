/* pg. 495 the only l-values are given by the var syntax... Thus, pointer arithmetic is forbidden. */

int x[10];

void main(void) 
{
    int i;
    x[1] = 2;
    i = (x + 1)[0];
}