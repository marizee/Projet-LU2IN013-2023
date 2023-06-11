#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynome.h"
#define P 7

//___________________________creation de polynome____________________________//
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

// allocation version 2
void allocatePolynomial(Polynome* poly, int degree) {
    poly->n = degree;
    poly->coeff = (int*)malloc((degree + 1) * sizeof(int));
}

// Fonction pour libérer la mémoire d'un polynôme version 2
void freePolynomial(Polynome* poly) {
    free(poly->coeff);
}

// Fonction pour initialiser un polynôme avec des coefficients donnés version 2
void initializePolynomial(Polynome* poly, int degree, int p, int* coefficients) {
    allocatePolynomial(poly, degree);
    for (int i = 0; i <= degree; i++) {
        poly->coeff[i] = coefficients[i] % p;
    }
}

// Fonction pour afficher un polynôme version 2
void printPolynomial(const Polynome* poly) {
    for (int i = poly->n; i >= 0; i--) {
        int coefficient = poly->coeff[i];
        if (coefficient != 0) {
            printf("%d", coefficient);
            if (i > 0) {
                printf("x^%d + ", i);
            }
        }
    }
    printf("\n");
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
            p->coeff[i] = a%P;
        }
    } 
    return p;
}

Polynome* coeff_to_polynome(int coeff[], int degre) {
    Polynome* new = creer_polynome(degre);
    if(new->coeff != NULL){
        for (int i=0; i<degre+1; i++){
            new->coeff[i] = coeff[i]%P;
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
        while (((p->coeff[i] == P)||(p->coeff[i] == 0)) && i>=0) {
            p->n--;
            i--;
        }
    }
}

//_____________________addition soustraction et multiplication_________________________//
//ARITHMETIQUE
Polynome* addition(Polynome* p1, Polynome* p2) {
    int n_sup = (p1->n > p2->n) ? p1->n : p2->n;
    int n_inf = (p1->n > p2->n) ? p2->n : p1->n;
    Polynome* new = creer_polynome(n_sup-1);

    for (int i=0; i<n_sup; i++) {

        //on applique l'addition tant que les 2 opÃ©randes existent
        if (i < n_inf) new->coeff[i] = (p1->coeff[i] + p2->coeff[i])%P;
        else {
            //on ajoute les coefficients restants
            if (n_inf == p1->n) new->coeff[i] = (p2->coeff[i])%P;
            else new->coeff[i] = (p1->coeff[i])%P;
        }
    }
    ajuste_degre(new);
    return new;
}

Polynome* soustraction(Polynome* p1, Polynome* p2) {
    int n_sup = (p1->n > p2->n) ? p1->n : p2->n;
    int n_inf = (p1->n > p2->n) ? p2->n : p1->n;
    Polynome* new = creer_polynome(n_sup-1);

    for (int i=0; i<n_sup; i++) {
        //on applique la soustraction tant que les 2 opÃ©randes existent
        if (i < n_inf) new->coeff[i] = (p1->coeff[i] - p2->coeff[i])%P;
        else {
            //on ajoute les coefficients restants
            if (n_inf == p1->n) new->coeff[i] = (-p2->coeff[i])%P;
            else new->coeff[i] = (p1->coeff[i])%P;
        }
    }
    ajuste_degre(new);
    return new;
}


//MULTIPLICATION
Polynome* mult_naive(Polynome* p1, Polynome* p2) {

    //si un des deux polynomes est nul, alors new est nul et on le retourne directement
    int test = (p1->n <= 0 || p2->n <= 0) ? -1 : (p1->n+p2->n)-2;
    Polynome* new = creer_polynome(test);
    if (test == -1) return new;

    for (int i=0; i<p1->n; i++) {
        for (int j=0; j<p2->n; j++) {
            new->coeff[i+j] += (p1->coeff[i]*p2->coeff[j])%P;
        }
    }
    ajuste_degre(new);
    return new;
}

Polynome* karatsuba(Polynome* f, Polynome* g) {

    //si un des deux polynomes est nul, alors la multiplication est nulle
    if (f->n <= 0 || g->n <= 0) return creer_polynome(-1);
    
    //si un des deux polynomes est de degrÃ© 0, on utilise la multiplication naÃ¯ve
    if (f->n == 1 || g->n == 1) return mult_naive(f, g);
    
    int k = (f->n >= g->n) ? f->n/2.0 : g->n/2.0;

    //allocation mÃ©moire des "sous-polynomes"
    Polynome* f0 = creer_polynome(k-1);
    Polynome* f1 = creer_polynome((f->n)-k-1);

    Polynome* g0 = creer_polynome(k-1);
    Polynome* g1 = creer_polynome((g->n)-k-1);

    //affectation des coeff aux sous-polynomes correspondants
    int i,j;  
    if (f->coeff != NULL) {
        if (f0->coeff != NULL) for (i=0; i < k; i++) f0->coeff[i] = (f->coeff[i])%P;
        if (f1->coeff != NULL) for (i=k, j=0; i < f->n; i++, j++) f1->coeff[j] = (f->coeff[i])%P; 
    }
    int l,m;
    if (g->coeff != NULL) {
        if (g0->coeff != NULL) for (l=0; l < k; l++) g0->coeff[l] = (g->coeff[l])%P;
        if (g1->coeff != NULL) for (l=k, m=0; l < g->n; l++, m++) g1->coeff[m] = (g->coeff[l])%P;
    }
    
    //Ã©tapes de l'algorithmes
    Polynome* h1 = karatsuba(f0, g0);
    Polynome* h2 = karatsuba(f1, g1);   

    Polynome* h3 = addition(f0, f1);
    Polynome* h4 = addition(g0, g1);

    Polynome* h5 = karatsuba(h3, h4);

    Polynome* h6 = soustraction(h5, h1);
    Polynome* h7 = soustraction(h6, h2);

    //polynomes pour faire l'Ã©quivalent de la fonction shift en python
    Polynome* un = creer_polynome(k);
    un->coeff[k] = 1;
    Polynome* deux = creer_polynome(2*k);
    deux->coeff[2*k] = 1;

    Polynome* h8 = mult_naive(h7,un);
    Polynome* h9 = addition(h1, h8);
    Polynome* h10 = mult_naive(h2, deux);
    
    Polynome* h = addition(h9, h10);
    
    //libération de la mémoire
    detruire_polynome(f0);detruire_polynome(f1);detruire_polynome(g0);detruire_polynome(g1);
    detruire_polynome(h1);detruire_polynome(h2); detruire_polynome(h3);detruire_polynome(h4);
    detruire_polynome(h5);detruire_polynome(h6);detruire_polynome(un);detruire_polynome(deux);
    detruire_polynome(h7);detruire_polynome(h8);detruire_polynome(h9);detruire_polynome(h10);
    
    return h;
}


//__________________________CALCUL D'INVERSE___________________//

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


int inverseMod(int a, int p) {
    int m0 = p;
    int y = 0, x = 1;

    if (p == 1)
        return 0;

    while (a > 1) {
        int q = a / p;
        int t = p;

        p = a % p;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

//________________________division euclidienne________________________//
void polynomialDivision(const Polynome* dividend, const Polynome* divisor, Polynome* quotient, Polynome* remainder) {
    int maxDegree = dividend->n - divisor->n;

    // Allocation du quotient et du reste
    allocatePolynomial(quotient, maxDegree);
    allocatePolynomial(remainder, divisor->n);

    // Copie du dividende dans le reste
    for (int i = 0; i <= dividend->n; i++) {
        remainder->coeff[i] = dividend->coeff[i];
    }

    // Boucle de division
    for (int i = maxDegree; i >= 0; i--) {
        int q = (remainder->coeff[divisor->n + i] * inverseMod(divisor->coeff[divisor->n], P)) % P;

        quotient->coeff[i] = q;

        for (int j = divisor->n; j >= 0; j--) {
            int term = (q * divisor->coeff[j]) % P;
            remainder->coeff[i + j] = (remainder->coeff[i + j] - term + P) % P;
        }
    }
}

//___________________________HORNER____________________________//

/*Polynome* Horner(Polynome* g, Polynome* a, Polynome* f){
        Polynome* res = g->coeff[g->n];
        Polynome* quotient;
        Polynome* remainder;

        for(int i = g->n; i>=0; i--){
            res = mult_naive(res,a);
            polynomialDivision(res,f,quotient,remainder);
            res = addition(remainder,g->coeff[i]);
        }
        polynomialDivision(res,f,quotient,remainder);
       return remainder;

}*/



//__________________________LES TESTS__________________________//

int main(){
    Polynome* p1 = initialiser_polynome();
    Polynome* p2 = initialiser_polynome();
    //Polynome* p0 = initialiser_polynome();
    Polynome* p3 = karatsuba(p1,p2);
    Polynome* p4 = mult_naive(p1,p2);
    Polynome* p6 = mult_naive(p4,p1);
    //Polynome* p5 = Horner(p1,p2,p0);
    
    printf("mult par karatsuba : "); affiche_polynome(p3);
    printf("mult naïve : "); affiche_polynome(p4);
    printf("mult naive : "); affiche_polynome(p6);
    //printf("horner : "); affiche_polynome(p5);

    detruire_polynome(p1);
    detruire_polynome(p2);
    detruire_polynome(p3);
    detruire_polynome(p4);
    detruire_polynome(p6);

    // Définition des polynômes et du modulo p
    int dividendCoefficients[] = {7, 8, -6, 5, 5, 4};  // Polynôme 7x^5 + 8x^4 + 6x^3 + 5x^2 + 5x + 4
    int divisorCoefficients[] = {-4, 2, 7};     // Polynôme 4x^2 + 2x + 7

    Polynome dividend, divisor, quotient, remainder;

    // Initialisation des polynômes
    initializePolynomial(&dividend, 5, P, dividendCoefficients);
    initializePolynomial(&divisor, 2, P, divisorCoefficients);

    // Division euclidienne
    polynomialDivision(&dividend, &divisor, &quotient, &remainder);

    // Affichage du quotient et du reste

    printf("Dividende : ");
    printPolynomial(&dividend);

    printf("Diviseur : ");
    printPolynomial(&divisor);

    printf("Quotient: ");
    printPolynomial(&quotient);

    printf("Reste: ");
    printPolynomial(&remainder);
    

    // Libération de la mémoire
    freePolynomial(&dividend);
    freePolynomial(&divisor);
    freePolynomial(&quotient);
    freePolynomial(&remainder);

    return 0;
}
