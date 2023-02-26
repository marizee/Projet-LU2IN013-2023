#include <stdio.h>
#include <stdlib.h>

#define P 7

long reste(long a) {
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

//a est inversible si il existe b€Z/pZ (inverse de a) tel que (a*b = 1[P]).
long inverse(long a) {
    long b = 0;
    while (produit(a, b) != 1) {
        b++;
    }
    return b;
}


int main() {
    for (long i=-20; i<20; i++) {
        printf("%ld = %ld mod %d\n", i, reste(i), P);
    }
    printf("-12*13 = %ld mod %d\n", produit(-12,13), P);
    printf("inverse de 3 = %ld\n", inverse(3));
    return 0;
}