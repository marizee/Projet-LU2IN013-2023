#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynome.h"

Polynome* addition(Polynome* p1, Polynome* p2) {
    int degre_inf;
    Polynome* new_poly;
    if((p1->n)<=(p2->n)){
        new_poly = creer_polynome(p2->n-1);
        degre_inf = p1->n;
    }else{
        new_poly = creer_polynome(p1->n-1);
        degre_inf = p2->n;
    }
    for (int i=0; i<(new_poly->n); i++) {
        if(i<=degre_inf){
            new_poly->coeff[i] = p1->coeff[i] + p2->coeff[i];
        }else{
            if(new_poly->n == p1->n){
                new_poly->coeff[i] = p1->coeff[i];
            }else{
                new_poly->coeff[i] = p2->coeff[i];
            }
        }
    }
    return new_poly;
}
Polynome* soustraction(Polynome* p1, Polynome* p2) {
    int degre_inf;
    Polynome* new_poly;
    if((p1->n)<=(p2->n)){
        new_poly = creer_polynome(p2->n-1);
        degre_inf = p1->n;
    }else{
        new_poly = creer_polynome(p1->n-1);
        degre_inf = p2->n;
    }
    for (int i=0; i<(new_poly->n); i++) {
        if(i<=degre_inf){
            new_poly->coeff[i] = p1->coeff[i] - p2->coeff[i];
        }else{
            if(new_poly->n == p1->n){
                new_poly->coeff[i] = p1->coeff[i];
            }else{
                new_poly->coeff[i] = p2->coeff[i];
            }
        }
    }
    return new_poly;
}

Polynome* mult_naive(Polynome* p1, Polynome* p2) {
    Polynome* new_poly = creer_polynome((p1->n+p2->n)-2);
    for (int i=0; i<p1->n; i++) {
        for (int j=0; j<p2->n; j++) {
            new_poly->coeff[i+j] += p1->coeff[i]*p2->coeff[j];
        }
    } 
    return new_poly;
}

Polynome* karatsuba(Polynome* f, Polynome* g) {
    
    //cas d'arrêt
    if (f->n == 0) return f;
    if (g->n == 0) return g;
    if (f->n == 1 || g->n == 1) return mult_naive(f, g);
    
    int k = ceil(fmax(f->n, g->n)/2.);

    //initialisation des 2 composantes de f et g
    Polynome* f0 = creer_polynome(k-1);
    Polynome* f1 = creer_polynome((f->n)-k-1);

    Polynome* g0 = creer_polynome(k-1);
    Polynome* g1 = creer_polynome((g->n)-k-1);

    //affectation des coefficients
    int i,j;
    for (i=0; i < k; i++) f0->coeff[i] = f->coeff[i];
    for (i=k, j=0; i < f->n; i++, j++) f1->coeff[j] = f->coeff[i]; 
    int l,m;
    for (l=0; l < k; l++) g0->coeff[l] = g->coeff[l];
    for (l=k, m=0; l < g->n; l++, m++) g1->coeff[m] = g->coeff[l];
    
    //étapes de l'algorithme
    Polynome* h1 = katsubara(f0, g0);
    Polynome* h2 = katsubara(f1, g1);   
    Polynome* h5 = katsubara(addition(f0, f1), addition(g0, g1));
    Polynome* h7 = soustraction(soustraction(h5, h1), h2);
    
    //polynome X^k
    Polynome* un = creer_polynome(k);
    un->coeff[k] = 1;
    //polynome X^{2k}
    Polynome* deux = creer_polynome(2*k);
    deux->coeff[2*k] = 1;

    //reconstitution de h = fg
    Polynome* h = addition(addition(h1, mult_naive(h7,un)), mult_naive(h2, deux));
    
    return h;
}


// TODO fonction pour "detruire" un polynome (clear, kill, ...) ok
// TODO Z/pZ plutot que les entiers:
//  --> arithmetique (+ , - , * , inversion) dans Z/pZ, dans un fichier separe ok
//  --> dans ce fichier ici, realiser les operations sur les coefficients dans Z/pZ

