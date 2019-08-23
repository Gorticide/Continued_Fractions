#include <iostream>
#include <cmath>     // floor
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>

static bool contains(
                long p,
                long q,
                std::map<std::pair<long, long>, int> pq_dict)
{

    std::pair<long, long> a = std::make_pair(p, q);
    if( pq_dict.find(a) == pq_dict.end())  {
        return false;
    }
    else return true;

}
std::string cf_periodic(
                                  long P,  // Rational Numerator
                                  long Q,  // Rational Denominator
                                  long D)  // Irrational Numerator
                                  {

    std::map<std::pair<long, long>, int> pq;

    long R = floor((P + sqrt(D))/Q);
    std::vector<long> f;
    f.push_back(R);
    double sd = sqrt(D);

    if ((D - P*P)%Q != 0)  {
        D *= Q*Q;
        sd *= Q;
        P *= abs(Q);
        Q *= abs(Q);
    }

    long a = R;  // P = 0, Q = 1;

    while( !contains(P, Q, pq) ) {

        pq[std::make_pair(P,Q)] = f.size() - 1;
        P = a*Q - P;
        Q = (D - P*P)/Q;
        a = floor((P + sqrt(D))/Q);
        if (!contains(P, Q, pq))  f.push_back(a);
        }

     int j = pq[std::make_pair(P, Q)];
     std::string cf = "";
     std::ostringstream convert;

     cf += "[";
     for (int i = 0; i < j; ++i)
        {
        convert << f[i];
        cf += convert.str() + ", ";
        convert.str("");
        convert.clear();
        }
     cf += "[";
     for(int i = j; i < f.size(); i++) {
           convert << f[i];
           if (i == f.size() - 1)  cf += convert.str() + ']';
           else cf += convert.str() + ", ";
           convert.str("");
           convert.clear();
      }
     cf += "]";

     return cf;
}


int main(int argc, char *argv[])  {

  std::string S = "";

  if (argc!= 4)  {
	std::cout << "[USE] : " << argv[0] << " <P> <Q> <D> where (P + sqrt(D)) / Q";
    std::cout << "\nYou cannot have " << argc - 1 << " parameters.\n\n";
	  return -1;
  }
   long p = atoi(argv[1]);   // Rational Numerator
   long q = atoi(argv[2]);   // Rational Denominator
   long d = atoi(argv[3]);   // Irrational Numerator

   if (q == 0) {
       std::cout << "\nThe denominator is zero.\n\n";
       return -1;
   }
   if (d < 0)  {
       std::cout << "\nDelta is supposed to be a non-negative integer, got " << d
                 << "\n\nIf you are trying to input " << "\n\n  " << p
                 << " - sqrt(" << -d << ")\n --------------\n\t" << q
                 << "\n\n input as: cf_periodic " << -p << ' '
                 << -q << ' ' << -d << "\n\n";
      return -1;
   }
   if ( (floor(sqrt(d)) * floor(sqrt(d)) == d)  || (d == 0) ) {
        // Oops, a square
        std::cout << "\nThird argument D is a perfect square and required to be nonsquare";
        std::cout << "\nUse program cf_rat " << p + sqrt(d) << ' ' << q << "\n\n";
        return -1;
    }

   S += cf_periodic(p, q, d);
   std::cout << "\n  " << p << " + sqrt(" << d << ")\n --------------- = "
             << S << "\n\t" << q << "\n\n";
}
