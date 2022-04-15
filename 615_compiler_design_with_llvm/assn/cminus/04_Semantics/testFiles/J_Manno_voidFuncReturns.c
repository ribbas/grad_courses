/* Void function should not have return value. pg 493 rule 9 */

void newFunc(void) {
    return 3;
}

void main(void){
    int x;
    x = 7;
}