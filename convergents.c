#include <math.h>
#include <stdio.h>
#include <stdlib.h> 

#define eps 1e-9

int main(int argc, char *argv[]) {
    // We add 2 elements to each array
    // (argc - 1) + 2 = argc + 1
    int size = argc + 1;

    long p[size], q[size], a[size];
    int i;
 
  //The first two convergents are 0/1 and 1/0
  // In CD Olds book, p[-1] = 0, p[0] = 1, q[-1] = 1, q[0] = 0
  // but since we cannot start array at -1,
  // p[0] <---| p[-1] = 0
  // p[1] <---| p[0] = 1
  // q[0] <---| q[-1] = 1
  // q[1] <---| q[0] = 0
  
  // -1 ---> 0
  // 0 ---> 1
  // 1 ---> 2  Hence, a1, which is normally a[0] now must be a[2]

  p[0] = 0; q[0] = 1;
  p[1] = 1; q[1] = 0;

  a[0] = -1;  // NOT USING !
  a[1] = -1;  // NOT USING !

 for (i = 2; i < size; i++)  {
      a[i] = atoi(argv[i-1]);
 }
 printf("\ncf: convergent\n___________________\n");
  //The rest of the convergents (and continued fraction)
  for(i = 2; i < size; i++) {
    p[i] = a[i]*p[i-1] + p[i-2];
    q[i] = a[i]*q[i-1] + q[i-2];
    printf("%ld:  %ld/%ld\n", a[i], p[i], q[i]);
  }
  printf("\n\n");
  return 0;
}