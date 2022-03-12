/* pg. 493 The last declaration in a program must be a function declaration of the form void main(void). */

void main(void) 
{
    errorBecauseLastIsNotMain();
}

void errorBecauseLastIsNotMain(void) { }