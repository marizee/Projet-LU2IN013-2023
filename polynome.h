#ifndef POLYNOMES_H
#define POLYNOMES_H
#include <math.h>

typedef struct _poly{
    int n; //nombre de variables (soit degre+1)
    int* coeff;
} Polynome;

Polynome* creer_polynome(int degre);
void detruire_polynome(Polynome* p);
Polynome* initialiser_polynome();
Polynome* coeff_to_polynome(int coeff[], int degre);
void affiche_polynome(Polynome* p);
void affiche_coeff(Polynome* p);
void ajuste_degre(Polynome* p);
void allocatePolynomial(Polynome* poly, int degree);
void freePolynomial(Polynome* poly);
void initializePolynomial(Polynome* poly, int degree, int p, int* coefficients);
void printPolynomial(const Polynome* poly);

Polynome* addition(Polynome* p1, Polynome* p2);
Polynome* soustraction(Polynome* p1, Polynome* p2);
Polynome* mult_naive(Polynome* p1, Polynome* p2);
Polynome* karatsuba(Polynome* f, Polynome* g);

long pgcd(long x,long y);
int est_inversible(long a);
int inverseMod(int a, int p);

void polynomialDivision(const Polynome* dividend, const Polynome* divisor, Polynome* quotient, Polynome* remainder);

#endif
