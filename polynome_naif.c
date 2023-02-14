#include <stdio.h>
#include <stdlib.h>

int* addition(int* polynome1, int* polynome2, int n) {
    int* res = (int *)malloc(n*sizeof(int));
    for (int i=0; i<n; i++) {
        res[i] = polynome1[i]+polynome2[i];
    }
    return res;
}
int* multiplication(int* polynome1, int* polynome2, int n) {
    int* res = (int *)malloc((2*n-2)*sizeof(int));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            res[i+j] += polynome1[i]*polynome2[j];
        }
        
    }
    return res;
}

void affiche_polynome(int* p, int t) {
    printf("%d + ", p[0]);
    for (int i=1; i<t-1; i++) {
        printf("%dX^%d + ", p[i], i);
    }
    printf("%dX^%d\n", p[t-1], t-1);
}

int main() {
    int p1[3] = {1,2,3};
    int p2[3] = {4,5,6};
    affiche_polynome(multiplication(p1, p2, 3), 5);
    affiche_polynome(addition(p1, p2, 3), 3);

    return 0;
}