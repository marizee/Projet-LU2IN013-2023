#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "polynome.h"

#define P 7


//ARITHMETIQUE
Polynome* addition(Polynome* p1, Polynome* p2) {
    int n_sup = (p1->n > p2->n) ? p1->n : p2->n;
    int n_inf = (p1->n > p2->n) ? p2->n : p1->n;
    Polynome* new = creer_polynome(n_sup-1);

    for (int i=0; i<n_sup; i++) {

        //on applique l'addition tant que les 2 opÃ©randes existent
        if (i < n_inf) new->coeff[i] = (p1->coeff[i] + p2->coeff[i])%P;
        else {
            //on ajoute les coefficients restants
            if (n_inf == p1->n) new->coeff[i] = (p2->coeff[i])%P;
            else new->coeff[i] = (p1->coeff[i])%P;
        }
    }
    ajuste_degre(new);
    return new;
}

Polynome* soustraction(Polynome* p1, Polynome* p2) {
    int n_sup = (p1->n > p2->n) ? p1->n : p2->n;
    int n_inf = (p1->n > p2->n) ? p2->n : p1->n;
    Polynome* new = creer_polynome(n_sup-1);

    for (int i=0; i<n_sup; i++) {
        //on applique la soustraction tant que les 2 opÃ©randes existent
        if (i < n_inf) new->coeff[i] = (p1->coeff[i] - p2->coeff[i])%P;
        else {
            //on ajoute les coefficients restants
            if (n_inf == p1->n) new->coeff[i] = (-p2->coeff[i])%P;
            else new->coeff[i] = (p1->coeff[i])%P;
        }
    }
    ajuste_degre(new);
    return new;
}


//MULTIPLICATION
Polynome* mult_naive(Polynome* p1, Polynome* p2) {

    //si un des deux polynomes est nul, alors new est nul et on le retourne directement
    int test = (p1->n <= 0 || p2->n <= 0) ? -1 : (p1->n+p2->n)-2;
    Polynome* new = creer_polynome(test);
    if (test == -1) return new;

    for (int i=0; i<p1->n; i++) {
        for (int j=0; j<p2->n; j++) {
            new->coeff[i+j] += (p1->coeff[i]*p2->coeff[j])%P;
        }
    }
    ajuste_degre(new);
    return new;
}

Polynome* karatsuba(Polynome* f, Polynome* g) {

    //si un des deux polynomes est nul, alors la multiplication est nulle
    if (f->n <= 0 || g->n <= 0) return creer_polynome(-1);
    
    //si un des deux polynomes est de degrÃ© 0, on utilise la multiplication naÃ¯ve
    if (f->n == 1 || g->n == 1) return mult_naive(f, g);
    
    int k = (f->n >= g->n) ? f->n/2.0 : g->n/2.0;

    //allocation mÃ©moire des "sous-polynomes"
    Polynome* f0 = creer_polynome(k-1);
    Polynome* f1 = creer_polynome((f->n)-k-1);

    Polynome* g0 = creer_polynome(k-1);
    Polynome* g1 = creer_polynome((g->n)-k-1);

    //affectation des coeff aux sous-polynomes correspondants
    int i,j;  
    if (f->coeff != NULL) {
        if (f0->coeff != NULL) for (i=0; i < k; i++) f0->coeff[i] = (f->coeff[i])%P;
        if (f1->coeff != NULL) for (i=k, j=0; i < f->n; i++, j++) f1->coeff[j] = (f->coeff[i])%P; 
    }
    int l,m;
    if (g->coeff != NULL) {
        if (g0->coeff != NULL) for (l=0; l < k; l++) g0->coeff[l] = (g->coeff[l])%P;
        if (g1->coeff != NULL) for (l=k, m=0; l < g->n; l++, m++) g1->coeff[m] = (g->coeff[l])%P;
    }
    
    //Ã©tapes de l'algorithmes
    Polynome* h1 = karatsuba(f0, g0);
    Polynome* h2 = karatsuba(f1, g1);   

    Polynome* h3 = addition(f0, f1);
    Polynome* h4 = addition(g0, g1);

    Polynome* h5 = karatsuba(h3, h4);

    Polynome* h6 = soustraction(h5, h1);
    Polynome* h7 = soustraction(h6, h2);

    //polynomes pour faire l'Ã©quivalent de la fonction shift en python
    Polynome* un = creer_polynome(k);
    un->coeff[k] = 1;
    Polynome* deux = creer_polynome(2*k);
    deux->coeff[2*k] = 1;

    Polynome* h8 = mult_naive(h7,un);
    Polynome* h9 = addition(h1, h8);
    Polynome* h10 = mult_naive(h2, deux);
    
    Polynome* h = addition(h9, h10);
    
    //libération de la mémoire
    detruire_polynome(f0);detruire_polynome(f1);detruire_polynome(g0);detruire_polynome(g1);
    detruire_polynome(h1);detruire_polynome(h2); detruire_polynome(h3);detruire_polynome(h4);
    detruire_polynome(h5);detruire_polynome(h6);detruire_polynome(un);detruire_polynome(deux);
    detruire_polynome(h7);detruire_polynome(h8);detruire_polynome(h9);detruire_polynome(h10);
    
    return h;
}
