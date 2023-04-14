#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "polynome.h"
#include "div_euclidienne.h"
#include "congruence.h"
#define P 7

int main(){
    Polynome* p1 = initialiser_polynome();
    Polynome* p2 = initialiser_polynome();
    Polynome* p3 = karatsuba(p1,p2);
    Polynome* p4 = mult_naive(p1,p2);
    Polynome* p5 = division(p1,p2);
    Polynome* p6 = mult_naive(p4,p1);
    
    printf("mult par karatsuba : "); affiche_polynome(p3);
    printf("mult naïve : "); affiche_polynome(p4);
    printf("division : "); affiche_polynome(p5);
    printf("mult naive : "); affiche_polynome(p6);

    detruire_polynome(p1);
    detruire_polynome(p2);
    detruire_polynome(p3);
    detruire_polynome(p4);
    //detruire_polynome(p5);
    detruire_polynome(p6);
    return 0;
}
