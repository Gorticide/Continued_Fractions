#include <iostream>
#include <cmath>     // floor
#include <cstdlib>   // atof
#include <iomanip>  // for setprecision
# include <string>  // for line

long* GetRationalExpansion(int, int, int);
int gcd_count(int, int);
std::string line (int);
void convergents(long*, int); 

int main(int argc, char *argv[])  {

  int type = 0;
  int n, m;
  long* cf;

  if (argc!= 3)  {
	  std::cout << "[USE] : " << argv[0] << " <numerator> <denominator>";
    std::cout << "\nYou cannot have " << argc - 1 << " parameters.\n\n";
	  return -1;
  }
   int numerator = atoi(argv[1]);
   int denominator = atoi(argv[2]);

   if (double(numerator)/double(denominator) < 0)  {
    type = 2;
    int new_num = (-floor(double(numerator)/double(denominator))  \
                   *denominator + numerator);
    int new_a1 = floor(double(numerator)/double(denominator));
    n = gcd_count(denominator, new_num);
    //std::cout << "\ngcd_count returns " << n << "\n";
    n++;
    //std::cout << "Adjusted array size to n = " << n;
    cf = GetRationalExpansion(denominator, new_num, n);
    
    for (int i = n-1; i > 0; i--)
       cf[i] = cf[i-1];

    cf[0] = new_a1;


  }
  else {
      if (numerator < denominator)  {
        type = 1;
        n = gcd_count(denominator, numerator);
        //std::cout << "\ngcd_count returns " << n << "\n";
        n++;
        //std::cout << "\nadjustment made to n = " << n << "\n";
        cf = GetRationalExpansion(denominator, numerator, n);

        for (int i = n-1; i > 0; i--)
           cf[i] = cf[i-1];

        cf[0] = 0;
      }
      else {
        n = gcd_count(numerator, denominator);
        //std::cout << "\ngcd_count returns " << n << "\n";
        cf = GetRationalExpansion(numerator, denominator, n);

      }


  }

      std::cout << "\n" << numerator << "/" << denominator << " = \n";
      m = n;
      int s;

      for (int i = 0; i < n; i++)  {
        if ( (cf[i] <= 0) || (i == 0) ) s = -1;
        else s = floor(std::log10(cf[i]));

        if (i != n-1)  {
          std::cout << std::string(ceil((6*n - m)/2) + 2*i, ' ')
                    << "1\n" << std::string(5*i - s, ' ') << cf[i]
                    << " + " << line(2*(n+m)-3*i+1) << "\n";
          }
          else std::cout << "\n" << std::string(5*i, ' ') << cf[i];

        m--;
      }

      std::cout << "\n\n" << numerator << "/" << denominator
                << " = [" << cf[0] << "; ";
      for (int i = 1; i < n; i++)  {
        std::cout << cf[i];
        if (i != n-1) std::cout << ", ";
        else std::cout << "]\n\n";
      }
      convergents(cf, n);
      delete [] cf;
      cf = NULL;
      return 0;
}


long* GetRationalExpansion(int numer, int denom, int NrFraction)  {

    int p = numer;
    int q = denom;
    long *a = NULL;
    //std::cout << "\narray created with "  << NrFraction << " elements?\n";
    a = new long[NrFraction];

    for (int i = 0; i < NrFraction; i++)
      a[i] = 0;

    int t;
    int itr = 0;
    while (p)
      {
        t = p;
        p = q%p;
        q = t;
        if (p != 0) a[itr] = q/p;
        itr++;
      }


    return a;
    delete [] a;
    a = NULL;

}

std::string line (int len)  {
  std::string L = "";

  L += std::string(len, '-');

  return L;
}

int gcd_count(int a, int b)    {

  int t;
  int count = 0;
  while (a)
    {
      t = a;
      a = b%a;
      b = t;
      count++;
    }
    count--;

  return count;
}

void convergents(long* arr, int size)  {

    // We add 2 elements to each array to compensate
    int new_size = size + 2;
    long p[new_size], q[new_size], a[new_size];
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

 for (i = 2; i < new_size; i++)  {
      a[i] = arr[i-2];
 }

 std::cout << "\ncf: convergent\n___________________\n";
  //The rest of the convergents (and continued fraction)
  for(i = 2; i < new_size; i++) {
    p[i] = a[i]*p[i-1] + p[i-2];
    q[i] = a[i]*q[i-1] + q[i-2];
    std::cout << a[i] << ":  " << p[i] << "/" << q[i] << "\n";
  }
  std::cout << "\n\n";

}