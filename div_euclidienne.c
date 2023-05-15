#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "div_euclidienne.h"

Polynome* division(Polynome* A,Polynome* B){
    if((A->n)<(B->n)){
        return A;
    }
    int k=A->n-B->n;
    Polynome* R = creer_polynome(A->n-1);
    Polynome* temp = creer_polynome(k);
    int i=A->n-1;
    int j=B->n-1;
    int b=1;
     R = coeff_to_polynome(A->coeff,(A->n)-1);
    while((i>=0)&&(j>=0)&&((R->n)>=(B->n))){
        temp->coeff[k]=A->coeff[i]*inverse_euclide(B->coeff[j]);
        R=soustraction(R, mult_naive(temp, B));
        temp->coeff[k]=0;
        k--;
        i--;
        j--;
    }
    detruire_polynome(temp);
    ajuste_degre(R);
    return R;
}
