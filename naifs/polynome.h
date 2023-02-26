#ifndef POLYNOME_H
#define POLYNOME_H
typedef struct _poly{
    int n;
    char indet; 
    int* coeff;
} Polynome;

Polynome* creer_polynome(int degre, char indet);

void detruire_polynome(Polynome* p);

Polynome* initialiser_polynome();

Polynome* addition(Polynome* p1, Polynome* p2);

Polynome* mult_naive(Polynome* p1, Polynome* p2);

void affiche_polynome(Polynome* p);

/*a completer au fur et a mesure qu'on avance*/

#endif
