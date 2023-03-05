#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"


Polynome* creer_polynome(int degre){
    
    Polynome* p =(Polynome*)malloc(sizeof(Polynome));
    p->n = degre+1;
    
    //initialisation du tableau de coeff de taille degre+1
    if (p->n > 0) {
        p->coeff = (int*)malloc((degre+1)*sizeof(int));
        for (int i=0; i<degre+1; i++) {
            p->coeff[i] = 0;
        }
    } else p->coeff = NULL;
    
    return p;
}

void detruire_polynome(Polynome* p) {
    if (p->coeff != NULL) free(p->coeff);
    free(p);
}

Polynome* initialiser_polynome(){
    int a;   
    printf("Veuillez saisir \n- le degrÃ© de votre polynome:\t");
    scanf(" %d",&a);
    Polynome* p = creer_polynome(a);
    if (p->coeff != NULL) {
        printf("- ses coefficients:");
        for(int i=0; i<p->n; i++){
            printf("\t");
            scanf(" %d",&a);
            p->coeff[i] = a;
        }
    } 
    return p;
}

Polynome* coeff_to_polynome(int coeff[], int degre) {
    Polynome* new = creer_polynome(degre);
    if (new->coeff != NULL) {
        for (int i=0; i<degre+1; i++) {
            new->coeff[i] = coeff[i];
        }
    }
    return new;
}

void affiche_polynome(Polynome* p) {
    if (p->coeff == NULL) {printf("C'est le polynome nul\n");}
    else {
        for (int i=0; i<p->n; i++) {
            if (p->coeff[i] != 0) {
                if (i==0) {printf("%d", p->coeff[i]);}
                else if (i==1) {printf("%dX", p->coeff[i]);}
                else {printf("%dX^%d", p->coeff[i], i);}
                if (i != p->n-1) {
                    printf(" + ");}
            }        
        }
        printf("\n");    
    }
}

void affiche_coeff(Polynome* p) {
    if (p->coeff == NULL) {printf("[]\n");}
    else {
        printf("[%d", p->coeff[0]);
        for (int i=1; i<p->n; i++ ) {
            printf(",%d", p->coeff[i]);
        }
        printf("]\n");
    }
}

void ajuste_degre(Polynome* p) {
    if (p->coeff != NULL) {
        int i=p->n-1;
        while (p->coeff[i] == 0 && i>=0) {
            p->n--;
            i--;
        }
    }
}
