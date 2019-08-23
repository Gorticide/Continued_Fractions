#include <iostream>
#include <cmath>     // floor
#include <cstdlib>   // atof
#include <sstream>  // for stringstream in numbers_after_decimal_point
#include <iomanip>  // for setprecision
# include <string>  // for line

int* GetSeriesExpansion(double, int);
int numbers_after_decimal_point(double);
int* GetRationalExpansion(int , int , int);
std::string line (int);
int gcf(int, int);
void normalize(int&, int&);
int gcd_count(int, int);

int main(int argc, char *argv[])  {
 int negative = 0;
 int* cf;

      if (argc!= 2)  {
	std::cout << "[USE] : " << argv[0] << " <decimal>";
  std::cout << "\nYou cannot have " << argc - 1 << " parameters.\n\n";
	return -1;
     }
      double decimal = atof(argv[1]);
      int n;

      if (decimal < 0)  {
        negative = 1;
        int dp = numbers_after_decimal_point(-decimal);
        int Znum = decimal*pow(10, dp);
        int Zden = pow(10, dp);
        normalize(Znum, Zden);

        int new_num = (-floor(double(Znum)/double(Zden))*Zden + Znum);
        int new_a1 = floor(double(Znum)/double(Zden));
        n = gcd_count(Zden, new_num);
        //std::cout << "\ngcd_count returns " << n << "\n";
        n++;
        //std::cout << "Adjusted array size to n = " << n;
        cf = GetRationalExpansion(Zden, new_num, n);

        for (int i = n-1; i > 0; i--)
           cf[i] = cf[i-1];

        cf[0] = new_a1;
      }
      else {
        n = numbers_after_decimal_point(decimal) + 3;
        cf = GetSeriesExpansion(decimal, n);
      }
      for (int i = 1; i < n; i++)
        if (cf[i] <= 0) n = i;

      std::cout << "\n" << decimal << " = \n";
      int m = n;
      int s;
      int scale;
      if (n < 3) scale = 8;
      else scale = 6;

      for (int i = 0; i < n; i++)  {
        if (cf[i] <= 0) s = -1;
        else s = floor(std::log10(cf[i]));
        if (cf[i+1] > 0)  {
         if (i != n-1)  {
           std::cout << std::string(ceil((scale*n - m)/2) + 2*i, ' ')
                     << "1\n" << std::string(5*i - s, ' ') << cf[i]
                     << " + " << line(2*(n+m)-3*i+1) << "\n";
          }
          else std::cout << "\n"
                   << std::string(ceil((6*n - m)/2) + 2*i-2, ' ')
                   << cf[i];
      }
      else {
        if (n < 3) std::cout << std::string(ceil((6*n - m)/2) + 2*i, ' ');
        else std::cout << std::string(ceil((6*n - m)/2) + 2*i-2, ' ');
        std::cout << cf[i];
      //  n--;
      }
        m--;
      }

      std::cout << "\n\n" << decimal << " = [" << cf[0] << "; ";
      for (int i = 1; i < n; i++)  {
        std::cout << cf[i];
        if (i != n-1) std::cout << ", ";
        else std::cout << "]\n\n";
      }
      delete [] cf;
      cf = NULL;
      return 0;
}


int* GetSeriesExpansion(double input, int NrFraction)  {

    double intput = input;
    int *a = NULL;
    a = new int[NrFraction];

    for (int i = 0; i < NrFraction; i++)
      a[i] = 0;

    int temp_dec;

    for (int i = 0; i < NrFraction; i++)  {
        temp_dec = int(floor(intput));
        //std::cout << "\nt = " << temp_dec << "\n";
        a[i] = temp_dec;
        intput = intput - floor(intput);
        //std::cout << "\nintput = " << intput << "\n";
        if (intput != 0)  {
            intput = 1 / intput;
            //std::cout << "\nintput = " << intput << "\n";
          }
        else
           {
            intput = 0;
            //std::cout << "\nintput = " << intput << "\n";
          }

    }

    return a;
    delete [] a;
    a = NULL;

}


/***********************************************************************/

int numbers_after_decimal_point(double x)  {
  double acceptedDiff = 2e-13;
  if (x - 0.0 < acceptedDiff) return 0;     // acceptedDiff = 2.27898e-13;
   std::stringstream sso;
   sso << std::setprecision(9) << std::showpoint << std::fixed
       << std::abs( x - (int)x );   // 27.44 - 27 ---> 0.44
   std::string Zahl;
   sso >> Zahl;
   size_t end = Zahl.find_last_not_of( '0' ) + 1 ;
   Zahl.erase(end);
   int result;

   if ( std::abs( x - (int)x ) == 0) return 0;
  // if (x > 0.1)
    result = Zahl.length() - 2;  // We don't want to count 0 and .
   //else result = Zahl.length();

   if (result < 0) return 0;
   else return result;

 }
/***********************************************************************/

int* GetRationalExpansion(int numer, int denom, int NrFraction)  {

    int p = numer;
    int q = denom;
    int *a = NULL;
    //std::cout << "\narray created with "  << NrFraction << " elements?\n";
    a = new int[NrFraction];

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

//*************************************************************************

std::string line (int len)  {
  std::string L = "";

  L += std::string(len, '-');

  return L;
}

void normalize(int& num, int& den)
{
     if (den == 0 || num == 0)
     {
          num = 0;
          den = 1;
     }

     if (den < 0)
     {
          num *= -1;
          den *= -1;
     }

     int n = gcf(num, den);
     num = num/n;
     den = den/n;
}

int gcf(int a, int b)
{
    if (a % b == 0)
       return abs(b);
    else
       return gcf(b, a % b);
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
