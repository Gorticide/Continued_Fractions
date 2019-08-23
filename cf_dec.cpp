#include <iostream>
#include <cmath>     // floor
#include <cstdlib>   // atof
#include <sstream>  // for stringstream in numbers_after_decimal_point
#include <iomanip>  // for setprecision
# include <string>  // for line

int* GetSeriesExpansion(double, int);
int numbers_after_decimal_point(double);
std::string line (int);

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
        n = numbers_after_decimal_point(-decimal) + 3;
        n++;
        cf = GetSeriesExpansion(-decimal, n);
        for (int i = n-1; i > 2; i--)
           cf[i] = cf[i-1];
        cf[2] = cf[1] - 1;
        cf[1] = 1;
        cf[0] = -cf[0]-1;
      }
      else {
        n = numbers_after_decimal_point(decimal) + 3;
        cf = GetSeriesExpansion(decimal, n);
      }
      std::cout << "\n" << decimal << " = \n";
      int m = n;
      int s;

      for (int i = 0; i < n; i++)  {
        if (cf[i] <= 0) s = -1;
        else s = floor(std::log10(cf[i]));
        if (cf[i+1] > 0)  {
         if (i != n-1)  {
           std::cout << std::string(ceil((6*n - m)/2) + 2*i, ' ')
                     << "1\n" << std::string(5*i - s, ' ') << cf[i]
                     << " + " << line(2*(n+m)-3*i+1) << "\n";
          }
          else std::cout << "\n"
                   << std::string(ceil((6*n - m)/2) + 2*i, ' ')
                   << cf[i];
      }
      else {
        std::cout << std::string(ceil((6*n - m)/2) + 2*i-2, ' ')
                  << cf[i];
        n--;
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

std::string line (int len)  {
  std::string L = "";

  L += std::string(len, '-');

  return L;
}
