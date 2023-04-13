#include <iostream>
#include <NTL/ZZ_p.h>

using namespace NTL;
using namespace std;

int main () 
{
    // déclarer 2 polynômes dans Z/pZ
    ZZ_pX p1, p2;

    // initialiser les polynômes avec des coefficients
    p1 = 1 + 2*X + 3*X^2;
    p2 = 4 + 5*X + 6*X^2;

    // faire les opérations entre les deux polynômes
    ZZ_pX p3 = p1 + p2; 
    ZZ_pX p4 = p1 * p2; 
    ZZ_pX p5 = p1 / p2; 

    // afficher les valeurs obtenues
    :cout << "p1 + p2 = " << p3 << std::endl;
    std::cout << "p1 * p2 = " << p4 << std::endl;
    std::cout << "p1 / p2 = " << p5 << std::endl;

    return 0;
}
