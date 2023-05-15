#include <NTL/ZZ.h>
#include <NTL/mat_ZZ.h>
#include <NTL/vec_ZZ.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>

using namespace NTL;

ZZ_p brentkung(const ZZ_pX& g, const ZZ_pX& a, const ZZ_pX& f) {
    ZZ_pContext context;
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

    ZZ_p res;
    res = b[0];
    ZZ_p ar = ac[r];

    ZZ_p tmp = ar;
    for (long i = 1; i < s; i++) {
        res += (b[i] * tmp) % f;
        tmp = ar * tmp;
    }

    return res;
}
