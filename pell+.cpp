// Solving x^2 - y^2 N = 1
#include <iostream>
#include <cmath>     // floor, pow
#include <vector>
#include <algorithm> 


std::vector<long long> sqrtCF(long long D) {
    // sqrt(D) may be slightly off for large D.
    // If large D are expected, a correction for R is needed.
    long long R = floor(sqrt(D));
    std::vector<long long> f;
    f.push_back(R);
    if (R*R == D) {
        // Oops, a square
        return f;
    }
    long long a = R, P = 0, Q = 1;
    do {
        P = a*Q - P;
        Q = (D - P*P)/Q;
        a = (R + P)/Q;
        f.push_back(a);
    }while(Q != 1);
    return f;
}

std::pair<long long, long long> get_Cn(std::vector<long long> v)  {

    // We add 2 elements to each array to compensate
    int size = v.size() + 2;
    long long p[size], q[size], a[size];
    int i;
    std::pair<long long, long long> C;

 
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

 i = 2;
 for(std::vector<long long>::iterator it = v.begin(); it != v.end(); ++it)
 {
	a[i] = *it;
    i++;
}

 std::cout << "\ncf: convergent\n___________________\n";
  //The rest of the convergents (and continued fraction)
  for(i = 2; i < size; i++) {
    p[i] = a[i]*p[i-1] + p[i-2];
    q[i] = a[i]*q[i-1] + q[i-2];
    std::cout << a[i] << ":  " << p[i] << "/" << q[i] << "\n";
  }
  std::cout << "\n\n";

  C = std::make_pair( p[size-2], q[size-2] );
  return C;

}
long double Factorial(long double nValue)
   {
       long double result = nValue;
       long double result_next;
       long double pc = nValue;
       do
       {
           result_next = result*(pc-1);
           result = result_next;
           pc--;
       }while(pc>2);
       nValue = result;
       return nValue;
   }
 
long double nCk(long double n, long double k)
   {
       k -= 1;
       if (std::abs(n - k) < 1e-7 || k  < 1e-7) return 1.0;
       if( std::abs(k-1.0) < 1e-7 || std::abs(k - (n-1)) < 1e-7)return n;
       return Factorial(n) /(Factorial(k)*Factorial((n - k)));
   }
 

int main(int argc, char *argv[])  {

  std::vector<long long> cf;
  std::pair<long long, long long> Cn;
  long long p, q;
  char sols = 'Y';
  int n = 0;
  int irr_pow;
  long double Monster, Irrational = 0.0;
  long long x, y;

  

  if (argc!= 2)  {
	  std::cout << "[USE] : " << argv[0] << " D for sqrt(D)";
    std::cout << "\nYou cannot have " << argc - 1 << " parameters.\n\n";
	  return -1;
  }
   long long N = atoi(argv[1]);
   cf = sqrtCF(N);
   std::cout << "\nsqrt(" << N << ") = [";
        for (std::vector<long long>::const_iterator i = cf.begin(); i != cf.end(); ++i)
        {
           if ( i == cf.begin() ) std::cout << *i << ", [";
           else if ( i == cf.end() - 1 ) std::cout << *i << ']';
                else std::cout << *i << ", "; 
        }
        std::cout << "]\n\n";

    Cn = get_Cn(cf);
    p = Cn.first;
    q = Cn.second;

    std::cout << "(" << p << ")^2 - (" << N << ")(" << q << ")^2 = "
              << p*p << " - (" << N << ")(" << q*q << ") = "
              << p*p << " - " << N*q*q << " = " << p*p - N*q*q
              << "\n\nHence, x = " << p << ", y = " << q 
              << " is a particular solution of x^2 - " << N 
              << "*y^2 = " << p*p - N*q*q << "\n\n";
    
    std::cout << "Do you wish to find other solutions? <Y/N>: ";
    std::cin >> sols;

    while ( (sols == 'Y') || (sols == 'y') )  {
        Irrational = 0;
        std::cout << "Enter value of n: ";
        std::cin >> n;
        Monster = std::pow( (p + q*sqrt(N)), n);
        int terms = n + 1;
        irr_pow = n;

        for (int i = 1; i <= terms; i++) {
           if (irr_pow%2 == 1) {
               Irrational += nCk(n, i)*sqrt(std::pow(N, irr_pow)) \
                             *std::pow(q, irr_pow)*std::pow(p, n - irr_pow); 
           }
           irr_pow--;
        }

        x = floor(Monster - Irrational + 0.5);       
        y = floor( (Monster - x)/sqrt(N) + 0.5 );

        std::cout << "\n\nSince (" << x << ")^2 - " << N << "*("
                  << y << ")^2 = " << x*x << " - " << N << "("
                  << y*y << ")\n\n\t\t\t\t = " << x*x << " - " << N*y*y 
                  << " = " << x*x - N*y*y << ", \nx_" << n
                  << " = " << x << ", y_" << n << " = " << y
                  << "\n\n";

        std::cout << "\nWould you like to find another solution? <Y/N> : ";
        std::cin >> sols;
    }
}