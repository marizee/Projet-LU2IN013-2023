#include <stdio.h>
#include <stdlib.h>
#include "congruence.h"
#define P 7

/*long reste(long a) {
    long q=0;
    while (abs(a-q*P) >= P) {
        if (a<0) { q--; }
        else { q++; }
    }
    return (a-q*P) < 0 ? (a-q*P)+P : a-q*P; //pour avoir un reste positif
}

//si (a = a'[P]) et (b = b'[P]), alors (a+b = a'+b'[P])
long somme(long a, long b) {
    return reste(reste(a) + reste(b)); 
}

//si (a = a'[P]) et (b = b'[P]), alors (a*b = a'*b'[P])
long produit(long a, long b) {
    return reste(reste(a)*reste(b));
}

//a est inversible si il existe b€Z/pZ (inverse de a) tel que (a*b = 1[P]).*/

long pgcd(long x,long y){
    long res = 0;
    if(y==0){
        res=x;
    }
    else{
        res=pgcd(y,x%y);
    }
    return res;
}

int est_inversible(long a){
    return (pgcd(a,P)==1);
 }


long inverse_euclide(long a) {
    int nO = a;
    int bO = P;
    int tO = 0;
    int t=1;
    int q = nO/bO;
    int r = nO - q*bO;
    int temp = 0;
    while(r>0){
        temp = tO -q*t;
        temp = (temp>=0) ? temp%P : P - ((-temp)%P);
        tO = t;
        t = temp;
        nO = bO;
        bO = r;
        q = nO/bO;
        r = nO - q*bO;
    }
    return t;
}
