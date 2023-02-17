#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynome.h"

int main() {
    Polynome* p1 = initialiser_polynome();
    Polynome* p2 = initialiser_polynome();
    affiche_polynome(p1);
    affiche_polynome(p2);
    affiche_polynome(addition(p1,p2));
    affiche_polynome(multiplication(p1,p2));
    return 0;
}