#include <stdio.h>

char upper_case(char);

char lower_case(char);

int toInt(char*);

char upper_case(char integer) {

    return (integer & ~0x20);

}

char lower_case(char integer) {

    return (integer | 0x20);

}

int toInt(char* inputNumber) {
  int retval = 0;
  for (int c = 0; inputNumber[c] != '\0'; c++) {
    retval *= 10;
    retval += (inputNumber[c] - '0');
  }
  return retval;
}

int main() {

    printf("%c\n", upper_case('z'));
    printf("%c\n", lower_case('Z'));
    printf("%c\n", upper_case('Z'));
    printf("%c\n", lower_case('z'));
    char* lol = "5749835";
    printf("%d\n", toInt(lol));
    return 0;

}
