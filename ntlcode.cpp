#include <NTL/ZZ.h>
#include <NTL/mat_ZZ.h>
#include <NTL/vec_ZZ.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>
#include <NTL/tools.h>
#include <iostream>
#include <NTL/lzz_pX.h>

using namespace NTL;
using namespace std;

ZZ_pX karatsuba(const ZZ_pX& f, const ZZ_pX& g) {
    if (IsZero(f) || IsZero(g))
        return ZZ_pX(0);

    long df = deg(f);
    long dg = deg(g);
    if (df <= 10 && dg <= 10)
        return f * g;

    long k = max(df / 2, dg / 2);

    ZZ_pX f0, f1;
    SetLength(f0, k);
    SetLength(f1, df - k + 1);
    for (long i = 0; i < k; i++)
        f0[i] = f[i];
    for (long i = k; i <= df; i++)
        f1[i - k] = f[i];

    ZZ_pX g0, g1;
    SetLength(g0, k);
    SetLength(g1, dg - k + 1);
    for (long i = 0; i < k; i++)
        g0[i] = g[i];
    for (long i = k; i <= dg; i++)
        g1[i - k] = g[i];

    ZZ_pX h1 = karatsuba(f0, g0);
    ZZ_pX h2 = karatsuba(f1, g1);
    ZZ_pX h5 = karatsuba(f0 + f1, g0 + g1);
    ZZ_pX h7 = h5 - h1 - h2;

    ZZ_pX h;
    LeftShift(h7, h7, k);
    LeftShift(h2, h2, 2 * k);
    h = h1 + h7 + h2;

    return h;
}

ZZ_pX eval_naive_improved(const ZZ_pX& g, const ZZ_pX& a, const ZZ_pX& f) {
    ZZ_pX res = g[0];
    ZZ_pX ai = a % f;
    long n = g.degree();

    for (long i = 1; i <= n; i++) {
        res += g[i] * ai;
        ai = (a * ai) % f;
    }

    return res % f;
}

ZZ_pX brentkung(const ZZ_pX& g, const ZZ_pX& a, const ZZ_pX& f) {
    ZZ_pXContext context;
    context.save();
    context.restore();

    ZZ_pXModulus F;
    F.SetMod(f);

    long d = deg(g) + 1;
    long n = deg(f);
    if (deg(a) >= n) {
        throw std::invalid_argument("Erreur: a de degré trop élevé");
    }

    long r = long(ceil(sqrt(d)));
    long s = long(ceil(d / double(r)));

    vec_ZZ_pX ac;
    ac.SetLength(r + 1);
    ac[0] = 1;

    for (long i = 1; i <= r; i++) {
        ac[i] = (a * ac[i - 1]) % f;
    }

    mat_ZZ_p ma;
    ma.SetDims(r, n);
    for (long i = 0; i < r; i++) {
        for (long j = 0; j < n; j++) {
            ma[i][j] = rep(ac[i])[j];
        }
    }

    mat_ZZ_p mg;
    mg.SetDims(s, r);
    for (long i = 0; i < s; i++) {
        for (long j = 0; j < r; j++) {
            mg[i][j] = rep(g[i * r + j]);
        }
    }

    mat_ZZ_p mb;
    mb.SetDims(s, n);
    mb = mg * ma;

    vec_ZZ_p b;
    b.SetLength(s);
    for (long i = 0; i < s; i++) {
        b[i] = rep(mb[i]);
    }

    ZZ_pX res;
    res = b[0];
    ZZ_pX ar = ac[r];

    ZZ_pX tmp = ar;
    for (long i = 1; i < s; i++) {
        res += (b[i] * tmp) % f;
        tmp = ar * tmp;
    }

    return res;
}

int main () 
{
	  //zz_p::init(GenPrime_long(60));
		zz_p::init(97);

    // déclarer 2 polynômes dans Z/pZ
    zz_pX p1, p2;

    // initialiser les polynômes avec des coefficients
    SetCoeff(p1, 0, 1);
    SetCoeff(p1, 1, 2);
    SetCoeff(p1, 2, 3);
    SetCoeff(p2, 0, 4);
    SetCoeff(p2, 1, 5);
    SetCoeff(p2, 2, 6);

    // faire les opérations entre les deux polynômes
    zz_pX p3 = p1 + p2; 
    zz_pX p4 = p1 * p2; 
    zz_pX p5 = p1 / p2; 

    // afficher les valeurs obtenues
    std::cout << "p1 + p2 = " << p3 << std::endl;
    std::cout << "p1 * p2 = " << p4 << std::endl;
    std::cout << "p1 / p2 = " << p5 << std::endl;

		// mesurer le temps:
		long d = 100000;
		zz_pX m, n;
		random(m, d);
		random(n, d);
		double tstart, tend;
		tstart = GetWallTime();
		zz_pX c = m*n;
		tend = GetWallTime();
		std::cout << "m * n = " << c << std::endl;
		std::cout << "temps pour multiplication: " << tend - tstart << std::endl;
	
        	ZZ_pX g, a, f;
        	random(g, d);
		random(a, 1000);
        	random(f, 10000);
		
		double tstartk, tendk;
        	tstartk = GetWallTime();
		ZZ_pX result_karatsuba = karatsuba(g, f);
		tendk = GetWallTime();
		std::cout << "karatsuba(g, f) = " << result_karatsuba << std::endl;
		std::cout << "time karatsuba: " << tendk - tstartk << std::endl;

	
		double tstartn, tendn;
        	tstartn = GetWallTime();
		ZZ_pX result_naive = eval_naive_improved(g, a, f);
		tendn = GetWallTime();
		std::cout << "g(a) % f = " << result_naive << std::endl;
		std::cout << "time algo naive: " << tendn - tstartn << std::endl;

        	double tstartbk, tendbk;
        	tstartbk = GetWallTime();
		ZZ_pX result_brentkung = brentkung(g, a, f);
		tendbk = GetWallTime();
		std::cout << "g(a) % f = " << result_brentkung << std::endl;
		std::cout << "time brentkung: " << tendbk - tstartbk << std::endl;

    return 0;
}
