


#   ALGORITHME DE NÜSKEN ET ZIEGLER
#   - généralisation de l'algorithme de Brent et Kung
#   - #f(X) de degré n, a(X) de degré < n, g(x, y) de degré < d



def nusken(g, a, f) :
    ring = a.parent()
    d = RR(sqrt(g.degree()+1)).ceil()

    #réécriture
    ringY = g.parent().univariate_ring(y)
    lg = ringY(g)

    #calcul du produit matriciel
    mg = matrix(d, d, [lg[i+d*j](X) for j in range(d) for i in range(d) ])

    ac = [ring(0)]*d
    ac[0] = ring(1)
    for i in range(1, d) :
        ac[i] = (a*ac[i-1]) % f

    ma = vector(ac)
    mj = matrix(d, f.degree(), [(ac[i])[j] for i in range(d) for j in range(f.degree())])

    mr = mg*ma

    r = [ring(0)]*d
    for j in range(d) :
        r[j] = ring(mr[j].list()) %f
    
    #calcul des autres puissances de a
    aj = [ring(0)]*d
    for j in range(d) :
        aj[j] = a**(d*j) %f

    #calcul du resultat (utiliser Horner)
    res = ring(0)
    for j in range(d) :
        res += r[j]*aj[j] %f

    return res


#TESTS
R.<X> = PolynomialRing(FiniteField(97))
S.<x,y> = PolynomialRing(FiniteField(97))

f = R.random_element(20)
a = R.random_element(18)
g = S.random_element(4,terms=Infinity)

p = g(X, a)%f
q = nusken(g, a, f)
print(f"nusken et ziegler ok ? {p == q}")
