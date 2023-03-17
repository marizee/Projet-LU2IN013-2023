#include <string.h>
#include <math.h>
#include "div_euclidienne.h"

Polynome* division(Polynome* A,Polynome* B){
    Polynome* R = creer_polynome(B->n-1);
    Polynome* Q = creer_polynome(A->n);
    Polynome* temp = creer_polynome(A->n-B->n);
    int i=A->n;
    int j=B->n;
    while((R->n<B->n)&&(i>=0)&&((A->n-B->n)>=0)&&(j>=0)){
        temp->coeff[A->n-B->n]=A->coeff[i]*inverse(B->coeff[j]);
        Q->coeff[A->n-B->n]=A->coeff[i]*inverse(B->coeff[j]);
        A=soustraction(A, mult_naive(temp, B));
        R=A;
        temp->coeff[A->n-B->n]=0;
    }
    detruire_polynome(Q);
    detruire_polynome(temp);
    return R;
}
