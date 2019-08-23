#include <iostream>
#include <utility>
#include <cmath>     // ceil, log10
#include <cstdlib>   // atof
#include <iomanip>  // for setprecision

std::pair<int, int> getFraction(int a[], int size)
{
   int r = 1;
   int q = a[size-1];
   //std::cout << "\nsize = " << size << "\n";
   std::cout << "\nr = " << r << ", q = " << q << "\n";

   for(int i = size - 2; i >= 0; i--)
   {
      int dividend = q*a[i] + r;
      std::cout << dividend << " = (" << q << ")*(" << a[i]
                << ") + " << r << "\n\n";
      r = q;
      q = dividend;
      std::cout << "\nr = " << r << ", q = " << q << "\n";
   }

   // When we are done, q is the numerator and r is the denominator.
   return std::make_pair(q, r);
}

int main(int argc, char *argv[])  {
  char answer = 'N';

  if (argc == 1)  {
    std::cout << "[USE] : " << argv[0] << " <decimal number> ";
    std::cout << "\nYou cannot have " << argc - 1 << " parameters.\n\n";
    return -1;
 }
   int *a = NULL;
   a = new int[argc-1];

   for (int i = 0; i < argc - 1; i++)
     a[i] = 0;

   for (int i = 0; i < argc - 1; i++)
     a[i] = atoi(argv[i+1]);

std::cout << "\n\n[";
    for (int i = 0; i < argc - 1; i++) {
        std::cout << a[i];
        if (i < argc - 2)
          std::cout << ", ";
        else
          std::cout << "] = \n\n";
     }

  // int size = sizeof(a)/sizeof(a[0]);
  // std::cout << "\nsize = " << size << "\n";
   std::pair<int, int> f = getFraction(a, argc - 1);
   std::cout
      << "\n " << f.first << "\n"
      << "--------\n"
      << " " << f.second << std::endl;
    std::cout << "\nDo you want the decimal approximation? <Y/N>: ";
    std::cin >> answer;
    if ( (answer == 'Y') || (answer == 'y') ) {
      int p = ceil(log10(f.first));
      std::cout << "\n\n"  << std::setprecision(p)
                << double(f.first)/double(f.second) << "\n\n";
      std::cout << "\nIs that close enough? <Y/N> ";
      std::cin >> answer;

      if ( (answer == 'N') || (answer == 'n') ) {
        std::cout << "\nEnter number of decimal places: ";
        std::cin >> p;
        std::cout << "\n"  << std::setprecision(p+1)
                  << double(f.first)/double(f.second) << "\n\n";
        }

    }

    delete [] a;
    a = NULL;
    return 0;
}
