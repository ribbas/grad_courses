/* In a variable declaration, only the type specifier int may be used */

int testi(void)
{
  int a;
  return a;
}

int testii(void)
{
  int b;
  return;
}

void testv(void)
{
  int c;
  return c;
}

void testvv(void)
{
  int c;
  return;
}

void main(void)
{
    /* do nothing */
}
