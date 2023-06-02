#include <NTL/ZZ.h>
#include <NTL/ZZ_pX.h>
#include <NTL/tools.h>
#include <iostream>
#include <NTL/lzz_pX.h>

using namespace NTL;
using namespace std;

//addition de deucx polynomes dans pZ
zz_pX addition(const zz_pX& f, const zz_pX& g) {
    long df = deg(f); // degré du polynôme f
    long dg = deg(g); // degré du polynôme g
    long dmin = std::min(df, dg);

    zz_pX res;
    SetCoeff(res, dmin, coeff(f, dmin) + coeff(g, dmin));

    // Vincent: pourquoi boucle "decroissante" de dmin-1 a 0, et pas de 0 a dmin-1?
    // Vincent: (ce n'est pas forcement la meme chose pour les performances, on peut en discuter si vous voulez)
    for (long i = dmin - 1; i >= 0; i--) {
        SetCoeff(res, i, coeff(f, i) + coeff(g, i));
    }

    // Ajout des derniers coefficients
    if (dmin == df) {
        for (long i = dmin + 1; i <= dg; i++) {
            SetCoeff(res, i, coeff(g, i));
        }
    } else {
        for (long i = dmin + 1; i <= df; i++) {
            SetCoeff(res, i, coeff(f, i));
        }
    }

    return res;
}

//soustraction de deux polynomes dans pZ
zz_pX soustraction(const zz_pX& f, const zz_pX& g) {
    long df = deg(f); // degré du polynôme f
    long dg = deg(g); // degré du polynôme g
    long dmin = std::min(df, dg);

    zz_pX res;
    SetCoeff(res, dmin, coeff(f, dmin) - coeff(g, dmin));

    // Vincent: pourquoi boucle "decroissante" de dmin-1 a 0, et pas de 0 a dmin-1?
    // Vincent: (ce n'est pas forcement la meme chose pour les performances, on peut en discuter si vous voulez)
    for (long i = dmin - 1; i >= 0; i--) {
        SetCoeff(res, i, coeff(f, i) - coeff(g, i));
    }

    // Ajout des derniers coefficients
    if (dmin == df) {
        for (long i = dmin; i <= dg; i++) {
            SetCoeff(res, i, -coeff(g, i));
        }
    } else {
        for (long i = dmin + 1; i <= df; i++) {
            SetCoeff(res, i, coeff(f, i));
        }
    }

    return res;
}

//division euclidienne de deux polynomes dans pZ
zz_pX division_euclidienne(const zz_pX& f, const zz_pX& g) {
    zz_pX quotient, reste;
    DivRem(quotient, reste, f, g);
    return quotient;
}

//fonction auxiliaire 
zz_pX init_poly_with_coeffs(const vec_zz_p& coeffs) {
    long n = coeffs.length();
    zz_pX poly;
    for (long i = 0; i < n; i++) {
        SetCoeff(poly, i, coeffs[i]);
    }
    return poly;
}


//multiplication de deux polynomes par l'algorithme de karatsuba
zz_pX karatsuba(const zz_pX& f, const zz_pX& g) {
    if (IsZero(f) || IsZero(g))
        return zz_pX(0);
    long df = deg(f);
    long dg = deg(g);
    if (df <= 10 && dg <= 10)
        return f * g;
    long k = max(df / 2, dg / 2);

    zz_pX f0, f1;
    random(f0, k);
    random(f1, df-k+1);
    for (long i = 0; i < k; i++)
        f0[i] = f[i];
    for (long i = k; i <= df; i++)
        f1[i - k] = f[i];

    zz_pX g0, g1;
    random(g0, k);
    random(g1, dg-k+1);
    for (long i = 0; i < k; i++)
        g0[i] = g[i];
    for (long i = k; i <= dg; i++)
        g1[i - k] = g[i];

    zz_pX h1 = karatsuba(f0, g0);
    zz_pX h2 = karatsuba(f1, g1);
    zz_pX h5 = karatsuba(f0 + f1, g0 + g1);
    zz_pX h7 = h5 - h1 - h2;

    zz_pX h;
    LeftShift(h7, h7, k);
    LeftShift(h2, h2, 2 * k);
    h = h1 + h7 + h2;

    f0.kill();
    f1.kill();
    g0.kill();
    g1.kill();
    h1.kill();
    h2.kill();
    h5.kill();
    h7.kill();

    return h;
}

//composition modulaire méthode naive
zz_pX eval_naive(const zz_pX& g, const zz_pX& a, const zz_pX& f) {
    zz_pX res;
    SetCoeff(res, 0, 0); // Initialisation de res à 0

    long dg = deg(g); // degré du polynôme g
    zz_pX ai;
    SetCoeff(ai, 0, 1); // ai = 1

    for (long i = 0; i <= dg; i++) {
        res += coeff(g, i) * ai; // res = res + cg[i] * ai
        ai = a * ai; // ai = a * ai
    }
    ai.kill();

    return res%f;
}

//composition modulaire horner
zz_pX horner(const zz_pX& g, const zz_pX& a, const zz_pX& f) {
    zz_pX res;
    SetCoeff(res, 0, coeff(g, deg(g)));
    
    for (long i = deg(g) - 1; i >= 0; i--) {
        res = (res*a)%f + coeff(g, i);
    }
    
    return res;
}


zz_pX brentkung(const zz_pX& g, const zz_pX& a, const zz_pX& f) {

    long d = deg(g) + 1;
    long n = deg(f);
    if (deg(a) >= n) {
        throw std::invalid_argument("Erreur: a de degré trop élevé");
    }

    long r = long(ceil(sqrt(d)));
    long s = long(ceil(d / double(r)));

    vec_zz_pX ac;
    ac.SetLength(r + 1);
    ac[0] = to_zz_pX(1);

    for (long i = 1; i <= r; i++) {
        ac[i] = (a * ac[i - 1]) % f;
    }
    //cout << "ac: " << ac << endl;

    mat_zz_p ma;
    ma.SetDims(r, n);
    int p = 1;
    int temp = 1;
    for (long i = 0; i < r; i++) {
        for (long j = 0; j < n; j++) {
            if(temp<p)
              ma[i][j] = rep((ac[i])[j]);
            else
              ma[i][j] = 0;
            temp++;
        }
        temp = 0;
        p = p+9;
    }
     ma[0][0] = 1;
    //cout << "matrice " << ma << endl;

    //j'ai procédé de cette maniere car implicitement quand il y'a des cases qui n'existent pas dans le polynome ça générait des nombres quelconques et donc la fonction ne marche pas

    mat_zz_p mg;
    mg.SetDims(s, r);
    for (long i = 0; i < s; i++) {
        for (long j = 0; j < r; j++) {
            mg[i][j] = rep(g[i * r + j]);
        }
    }

    mat_zz_p mb;
    mb = mg * ma;


    zz_pX res;
    res = init_poly_with_coeffs(mb[0]);
    zz_pX ar = ac[r];
    
    zz_pX tmp = ar;

    for (long i = 1; i < s; i++) {
        res += (init_poly_with_coeffs(mb[i]) * tmp) % f;
				//Vincent: attention ! ici meme probleme que dans l'evaluation naive:
				//Vincent: il n'y a pas "% f" donc le degré de "tmp" va devenir très
				//Vincent: gros au fur et à mesure des itérations de la boucle
        tmp = ar * tmp;
    }

    ar.kill();
    tmp.kill();
    mb.kill();
    mg.kill();
    ma.kill();

    return res;
}

zz_pX nusken(const zz_pX& g, const zz_pX& a, const zz_pX& f)
{
    long d = sqrt(g.rep.length() + 1);

    // Réécriture
    zz_pX ringY;
    ringY.SetMaxLength(g.rep.length());
    for (long i = 0; i <= g.rep.length(); i++) {
        ringY.rep[i] = g.rep[i];
    }
    // Calcul du produit matriciel
    mat_zz_p mg;
    mg.SetDims(d, d);
    for (long j = 0; j < d; j++) {
        for (long i = 0; i < d; i++) {
            mg[i][j] = ringY[i+d*j];
        }
    }

    vec_zz_pX ac;
    ac.SetLength(d);
    ac[0] = 1;
    for (long i = 1; i < d; i++) {
        ac[i] = (a * ac[i-1]) % f;
    }

    vec_zz_pX ma = ac;

    vec_zz_pX mr;
    mr.SetLength(d);
    for (long i = 0; i < d; i++) {
        mr[i] = 0;
        for (long j = 0; j < d; j++) {
            mr[i] += mg[i][j] * ma[j];
        }
    }

    vec_zz_pX r;
    r.SetLength(d);
    for (long i = 0; i < d; i++) {
        r[i] = mr[i] % f;
    }

    // Calcul des autres puissances de a
    vec_zz_pX aj;
    aj.SetLength(d);
    for (long j = 0; j < d; j++) {
        aj[j] = power(a, d*j) % f;
    }

    // Calcul du résultat
    zz_pX res = to_zz_pX(0);
    for (long j = 0; j < d; j++) {
        res += r[j] * aj[j] % f;
    }

    ringY.kill();

    return res;
}


//________________________________LES TESTS_______________________________//
int main () 
{
    zz_p::init(97);

    // Déclarer 2 polynômes dans Z/pZ
    zz_pX p1, p2;

    // Initialiser les polynômes avec des coefficients
    SetCoeff(p1, 0, 1);
    SetCoeff(p1, 1, 2);
    SetCoeff(p1, 2, 3);
    SetCoeff(p2, 0, 4);
    SetCoeff(p2, 1, 5);
    SetCoeff(p2, 2, 6);

    // Faire les opérations entre les deux polynômes
    zz_pX p3 = p1 + p2; 
    zz_pX p4 = p1 * p2; 
    zz_pX p5 = p1 / p2; 

    // Afficher les valeurs obtenues
    //cout << "p1 + p2 = " << p3 << endl;
    //cout << "p1 * p2 = " << p4 << endl;
    //cout << "p1 / p2 = " << p5 << endl;

    // Mesurer le temps :
    long d = 300;
    long e = 10;
    zz_pX g, f, a;
    random(g, d);
    random(f, d);
    //random(a, e);
		//Vincent: en general, pour le cas Brent-Kung, on prend deg(a) < d-1
    random(a, d-1);

    double tstart, tend;
    tstart = GetTime();
    zz_pX mult = g * f;
    tend = GetTime();
    if (d < 150)
        cout << "m * n = " << mult << endl;
    cout << "Temps pour multiplication : " << tend - tstart << endl;
    
    double tstartk, tendk;
    tstartk = GetTime();
    zz_pX result_karatsuba = karatsuba(g, f);
    tendk = GetTime();
    if (d < 150)
        cout << "karatsuba(g, f) = " << result_karatsuba << endl;
    cout << "Temps pour karatsuba : " << tendk - tstartk << endl;

    double tstartn, tendn;
    tstartn = GetTime();
    zz_pX result_naive = eval_naive(g, a, f);
    tendn = GetTime();
    if (d < 150)
        std::cout << "g(a) mod f = " << result_naive << std::endl;
    std::cout << "time algo naive: " << tendn - tstartn << std::endl;

    double tstarth, tendh;
    tstarth = GetTime();
    zz_pX result_horner = horner(g, a, f);
    tendh = GetTime();
    if (d < 150)
        std::cout << "g(a) mod f = " << result_horner << std::endl;
    std::cout << "time horner: " << tendh - tstarth << std::endl;


    double tstartbk, tendbk;
    zz_pX x;
    tstartbk = GetTime();
    zz_pX result_brentkung = brentkung(g, a, f);
    tendbk = GetTime();
    if (d < 150)
        std::cout << "g(a) mod f = " << result_brentkung << std::endl;
    std::cout << "time brentkung: " << tendbk - tstartbk << std::endl;


    double tstartbk2, tendbk2;
    tstartbk2 = GetTime();
    zz_pX result;
    CompMod(result, g, a, f);
    tendbk2 = GetTime();
    if (d < 150)
        std::cout << "g(a) mod f = " << result << std::endl;
    std::cout << "time brentkung2: " << tendbk2 - tstartbk2 << std::endl;

    // Appel de la fonction nusken
    double tstartnk, tendnk;
    tstartnk = GetTime();
    zz_pX nuskenziegler = nusken(g, a, f);
    tendnk = GetTime();

    // Affichage du résultat
    if (d < 150)
        cout << "nusken: " << nuskenziegler << endl;
    cout << "Temps pour nusken : " << tendnk - tstartnk << endl;

    p1.kill();
    p2.kill();
    p3.kill();
    p4.kill();
    p5.kill();
    f.kill();
    g.kill();
    a.kill();
    mult.kill();
    result_karatsuba.kill();
    result_brentkung.kill();
    result_horner.kill();

    return 0;
}
