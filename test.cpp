#include <NTL/ZZ.h>
#include <NTL/tools.h>
#include <iostream>
#include <NTL/lzz_pX.h>

using namespace NTL;
using namespace std;

int main () 
{
	  //zz_p::init(GenPrime_long(60));
		zz_p::init(97);

    // déclarer 2 polynômes dans Z/pZ
    zz_pX p1, p2;

    // initialiser les polynômes avec des coefficients
    SetCoeff(p1, 0, 1);
    SetCoeff(p1, 1, 2);
    SetCoeff(p1, 2, 3);
    SetCoeff(p2, 0, 4);
    SetCoeff(p2, 1, 5);
    SetCoeff(p2, 2, 6);

    // faire les opérations entre les deux polynômes
    zz_pX p3 = p1 + p2; 
    zz_pX p4 = p1 * p2; 
    zz_pX p5 = p1 / p2; 

    // afficher les valeurs obtenues
    std::cout << "p1 + p2 = " << p3 << std::endl;
    std::cout << "p1 * p2 = " << p4 << std::endl;
    std::cout << "p1 / p2 = " << p5 << std::endl;

		// mesurer le temps:
		long d = 1000000;
		zz_pX a, b;
		random(a, d);
		random(b, d);
		double tstart, tend;
		tstart = GetWallTime();
		zz_pX c = a*b;
		tend = GetWallTime();
		std::cout << "time: " << tend - tstart << std::endl;

    return 0;
}

// composition modulaire rapide:
// void CompMod(zz_pX& x, const zz_pX& g, const zz_pX& h, const zz_pXModulus& F);
