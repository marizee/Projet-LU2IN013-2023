#include <NTL/ZZ.h>
#include <iostream>

using namespace std;
using namespace NTL;

int main()
{
    ZZ p;
    cout << "Entrez un entier  ";
    cin >> p;

    // Créez deux polynômes
    ZZX a, b;
    cout << "Entrez le premier polynôme: ";
    cin >> a;
    cout << "Entrez le second polynôme: ";
    cin >> b;

    // Effectuez les opérations sur les polynômes et stockez le résultat
    ZZX resultAdd, resultMul, resultDiv;
    resultAdd = a + b; 
    resultMul = a * b;
    resultDiv = a / b; 

    // Calculer le reste modulo p
    ZZX rest;
    rest = resultAdd % p;

    // Afficher le résultat avec des jeux de tests
    cout << "Test addition: " << endl;
    cout << "  polynomial1 + polynomial2 = " << resultAdd << endl;
    cout << "  (polynomial1 + polynomial2) % " << p << " = " << rest << endl;
    cout << endl;
    cout << "Test multiplication: " << endl;
    cout << "  polynomial1 * polynomial2 = " << resultMul << endl;
    cout << "  (polynomial1 * polynomial2) % " << p << " = " << rest << endl;
    cout << endl;
    cout << "Test division euclidienne: " << endl;
    cout << "  polynomial1 / polynomial2 = " << resultDiv << endl;
    cout << "  (polynomial1 / polynomial2) % " << p << " = " << rest << endl;
    return 0;
}
