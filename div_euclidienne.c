#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "div_euclidienne.h"

//pas encore fini car elle renvoie une resultat fausse de calcul
/*Polynome* division(Polynome* A,Polynome* B){
    if((A->n)<(B->n)){
        return A;
    }
    int k=A->n-B->n;
    Polynome* R = creer_polynome(A->n-1);
    Polynome* temp = creer_polynome(k);
    int i=A->n-1;
    int j=B->n-1;
    int b=1;
    while((i>=0)&&(j>=0)){
        detruire_polynome(R);
        temp->coeff[k]=A->coeff[i]*inverse_euclide(B->coeff[j]);
        int z = A->n-B->n;
        A=soustraction(A, mult_naive(temp, B));
        R = coeff_to_polynome(A->coeff,(A->n)-1);
        k=A->n-B->n;
        temp->coeff[z]=0;
        i--;
        j--;
        
    }
    detruire_polynome(temp);
    return R;
}*/
