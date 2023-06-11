#include <stdio.h>
#include <flint/flint.h>
#include <flint/fmpz.h>
#include <flint/fmpz_poly.h>

int main()
{
    // Initialisation des polynômes
    fmpz_poly_t g, f;
    fmpz_poly_init(g);
    fmpz_poly_init(f);

    // Initialisation des entiers
    fmpz_t a, res;
    fmpz_init(a);
    fmpz_init(res);

    // Affectation des coefficients des polynômes g et f
    fmpz_poly_set_coeff_si(g, 0, 1);
    fmpz_poly_set_coeff_si(g, 1, 2);
    fmpz_poly_set_coeff_si(g, 2, 3);
    fmpz_poly_set_coeff_si(g, 3, 4);

    fmpz_poly_set_coeff_si(f, 0, 5);
    fmpz_poly_set_coeff_si(f, 1, 6);
    fmpz_poly_set_coeff_si(f, 2, 7);

    // Affectation de la valeur a
    fmpz_set_si(a, 2);

    // Calcul de la longueur des polynômes g et f
    slong deg_g = fmpz_poly_length(g);
    slong deg_f = fmpz_poly_length(f);

    // Évaluation du polynôme g en a modulo f
    fmpz_t term, tmp;
    fmpz_init(term);
    fmpz_init(tmp);

    fmpz_zero(res);  // Initialisation du résultat à zéro

    // Évaluation du polynôme g en a modulo f
    for (slong i = 0; i <= deg_g; i++)
    {
        fmpz_poly_get_coeff_fmpz(term, g, i);
        fmpz_pow_ui(tmp, a, i);
        fmpz_mul(tmp, tmp, term);
        fmpz_add(res, res, tmp);
    }

    // Réduction modulo f
    fmpz_poly_get_coeff_fmpz(term, f, 0); // Coefficient constant de f
    fmpz_mod(res, res, term);

    // Affichage du résultat
    printf("Result: ");
    fmpz_print(res);
    printf("\n");

    // Libération de la mémoire
    fmpz_clear(a);
    fmpz_clear(res);
    fmpz_clear(term);
    fmpz_clear(tmp);
    fmpz_poly_clear(g);
    fmpz_poly_clear(f);

    return 0;
}

// j'ai compilé avec : gcc -Wall -o code_flint code_flint.c -lflint -lgmp
