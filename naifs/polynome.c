#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynome.h"

/*version naif*/

Polynome* creer_polynome(int degre, char *indet){
    Polynome* p =(Polynome*)malloc(sizeof(Polynome));
    p->n = degre+1;
    p->coeff = (int*)malloc((degre+1)*sizeof(int));
    p->indet = strdup(indet);
    return p;
}

Polynome* initialiser_polynome(){
    int a; 
    char var2[1];  
    printf("Veuillez saisir \n- le degré de votre polynome:\t");
    scanf(" %d",&a);
    printf("- son indeterminée:\t");
    scanf(" %c",var2);
    Polynome* p = creer_polynome(a, var2);
    printf("- ses coefficients:");
    for(int i=0; i<p->n; i++){
        printf("\t");
        scanf(" %d",&a);
        p->coeff[i] = a;
    }
    return p;
}

Polynome* addition(Polynome* p1, Polynome* p2) {
    int degre_inf;
    Polynome* new_poly;
    if((p1->n)<=(p2->n)){
        new_poly = creer_polynome(p2->n-1,"X");
        degre_inf = p1->n;
    }else{
        new_poly = creer_polynome(p1->n-1,"X");
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

Polynome* multiplication(Polynome* p1, Polynome* p2) {
    int degre_prod = p1->n+ p2->n;
    Polynome* new_poly = creer_polynome(degre_prod-2,"X");
    for (int i=0; i<p1->n; i++) {
        for (int j=0; j<p2->n; j++) {
            new_poly->coeff[i+j] += p1->coeff[i]*p2->coeff[j];
        }
    } 
    return new_poly;
}

void affiche_polynome(Polynome* p) {
    for (int i=0; i<p->n; i++) {
        if (p->coeff[i] != 0) {
            if (i==0) {printf("%d", p->coeff[i]);}
            else if (i==1) {printf("%d%s", p->coeff[i], p->indet);}
            else {printf("%d%s^%d", p->coeff[i], p->indet, i);}
        }
        if (i != p->n-1) {printf(" + ");}
    }
    printf("\n");
    
}

/*il y a d'autre fonctions a implementer biensur*/

// TODO fonction pour "detruire" un polynome (clear, kill, ...)
// TODO Z/pZ plutot que les entiers:
//  --> arithmetique (+ , - , * , inversion) dans Z/pZ, dans un fichier separe
//  --> dans ce fichier ici, realiser les operations sur les coefficients dans Z/pZ

