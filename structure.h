#ifndef STRUCT_H
#define STRUCT_H

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

#endif
