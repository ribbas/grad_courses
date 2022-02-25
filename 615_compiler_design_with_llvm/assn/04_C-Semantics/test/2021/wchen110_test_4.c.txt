/* This program copies the selection sort program, but moves minloc to be after
   sort, even though sort depends on minloc. Functions which another function
   depends on must be declared prior to that function, so this program would
   be invalid. */

void sort( int a[], int low, int high)
{ int i; int k;
  i = low;
  while (i < high-1)
    { int t;
      k = minloc(a,i,high);
	  t = a[k];
	  a[k] = a[i];
	  a[i] = t;
	  i = i + 1;
    }
}

int minloc ( int a[], int low, int high )
{ int i; int x; int k;
  k = low;
  x = a[low];
  i = low + 1;
  while (i < high)
    { if (a[i] < x)
        { x = a[i];
          k = i; }
      i = i + 1;
    }
  return k;
}

void main(void)
{ int i;
  i = 0;
  while (i < 10)
    { x[i] = input();
      i = i + 1; }
  sort(x,0,10);
  i = 0;
  while (i < 10)
    { output(x[i]);
	  i = i + 1; }
}