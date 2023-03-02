#ifndef OPNAIVES_H
#define OPNAIVES_H

#include "structure.h"
#include <math.h>

Polynome* addition(Polynome* p1, Polynome* p2);
Polynome* soustraction(Polynome* p1, Polynome* p2);
Polynome* mult_naive(Polynome* p1, Polynome* p2);
Polynome* karatsuba(Polynome* f, Polynome* g);

#endif
