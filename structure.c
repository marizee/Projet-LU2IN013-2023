#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"


Polynome* creer_polynome(int degre){
    Polynome* p =(Polynome*)malloc(sizeof(Polynome));
    p->n = degre+1;
    p->coeff = (int*)malloc((degre+1)*sizeof(int));
    for (int i=0; i<degre+1; i++) {
        p->coeff[i] = 0;
    }
    return p;
}
void detruire_polynome(Polynome* p) {
    free(p->coeff);
    free(p);
}

Polynome* initialiser_polynome(){
    //Polynome* p =(Polynome*)malloc(sizeof(Polynome));
    int a;   
    printf("Veuillez saisir \n- le degré de votre polynome:\t");
    scanf(" %d",&a);
    Polynome* p = creer_polynome(a);
    printf("- ses coefficients:");
    for(int i=0; i<p->n; i++){
        printf("\t");
        scanf(" %d",&a);
        p->coeff[i] = a;
    }
    return p;
}

Polynome* coeff_polynome(int coeff[], int taille) {
    Polynome* new = creer_polynome(taille-1);
    for (int i=0; i<taille; i++) {
        new->coeff[i] = coeff[i];
    }
    return new;
}

void affiche_polynome(Polynome* p) {
    for (int i=0; i<p->n; i++) {
        if (p->coeff[i] != 0) {
            if (i==0) {printf("%d", p->coeff[i]);}
            else if (i==1) {printf("%dX", p->coeff[i]);}
            else {printf("%dX^%d", p->coeff[i], i);}
        }
        if (i != p->n-1) {printf(" + ");}
    }
    printf("\n");
    
}

void affiche_coeff(Polynome* p) {
    printf("[%d", p->coeff[0]);
    for (int i=1; i<p->n; i++ ) {
        printf(",%d", p->coeff[i]);
    }
    printf("]\n");
}
