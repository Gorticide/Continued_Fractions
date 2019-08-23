// Solving x^2 - y^2 N = 1
#include <iostream>
#include <cmath>     // floor
#include <vector>
#include <algorithm> 


std::vector<unsigned long> sqrtCF(unsigned long D) {
    // sqrt(D) may be slightly off for large D.
    // If large D are expected, a correction for R is needed.
    unsigned long R = floor(sqrt(D));
    std::vector<unsigned long> f;
    f.push_back(R);
    if (R*R == D) {
        // Oops, a square
        return f;
    }
    unsigned long a = R, P = 0, Q = 1;
    do {
        P = a*Q - P;
        Q = (D - P*P)/Q;
        a = (R + P)/Q;
        f.push_back(a);
    }while(Q != 1);
    return f;
}

std::pair<unsigned long, unsigned long> get_Cn(std::vector<unsigned long> v)  {

    // We add 2 elements to each array to compensate
    int size = v.size() + 2;
    long p[size], q[size], a[size];
    int i;
    std::pair<unsigned long, unsigned long> C;

 
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
 for(std::vector<unsigned long>::iterator it = v.begin(); it != v.end(); ++it)
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

int main(int argc, char *argv[])  {

  std::vector<unsigned long> cf;
  std::pair<unsigned long, unsigned long> Cn;
  unsigned long p, q;
  int flag = 1;

  if (argc!= 2)  {
	  std::cout << "[USE] : " << argv[0] << " D for sqrt(D)";
    std::cout << "\nYou cannot have " << argc - 1 << " parameters.\n\n";
	  return -1;
  }
   unsigned long N = atoi(argv[1]);
   cf = sqrtCF(N);
   std::cout << "\nsqrt(" << N << ") = [";
        for (std::vector<unsigned long>::const_iterator i = cf.begin(); i != cf.end(); ++i)
        {
           if ( i == cf.begin() ) std::cout << *i << ", [";
           else if ( i == cf.end() - 1 ) std::cout << *i << ']';
                else std::cout << *i << ", "; 
        }
        std::cout << "]\n\n";
    if (cf.size()%2 == 0) { // if number of partial quotients is even
                            // then element n before 2*a1 is odd
      // We will want to get_Cn of element 2n, where n = 2*(cf.size() - 1)
      // New size of cf will be 2*cf.size() - 1
      // Example: if cf.size() is 6, n = 5, new size is 11
      // And we will want to retrieve element 10  
      flag = -1;
      int old_size = cf.size();
      for (int i = 0; i < old_size - 1; i++)  {
          cf.push_back(cf[i+1]);   // Add second period
      }    
    }
    Cn = get_Cn(cf);
    p = Cn.first;
    q = Cn.second;

    std::cout << "(" << p << ")^2 - (" << N << ")(" << q << ")^2 = "
              << p*p << " - (" << N << ")(" << q*q << ") = "
              << p*p << " - " << N*q*q << " = " << p*p - N*q*q
              << "\n\nHence, x = " << p << ", y = " << q 
              << " is a particular solution of x^2 - " << N 
              << "*y^2 = 1\n\n";
    
   
}