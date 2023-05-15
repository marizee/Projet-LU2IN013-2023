import time
#congruence sur les entiers
def inverse(a, p=7) :
    b = 0
    while (a*b != 1) :     
        b=b+1   
    return b

#inverse avec euclide 
def inverse_euclide(a, p=7) :
    nO = a
    bO = p
    tO = 0
    t = 1
    q = nO//bO
    r = nO - q*bO
    temp = 0
    while (r > 0) :
        temp = tO - q*t
        if temp >= 0 :
            temp = temp % p
        else :
            temp = p - ((-temp) % p)
        tO = t
        t = temp
        nO = bO
        bO = r
        q = nO//bO
        r = nO - q*bO
    return t

#calcul pgcd pour verifier si un nombre est inversible dans Z/pZ
def pgcd(x, y) :
    res = 0
    if y==0 :
        res = x
    else :
        res = pgcd(y, x%y)
    return res

def est_inversible(x, p=7) :
    if pgcd(x, p) == 1 :
        return True
    return False

#addition et multiplication sur polynomes
def addition(f, g) :
    ring = f.parent()
    df = f.degree() ; cf = f.list()
    dg = g.degree() ; cg = g.list()
    dmin = min(df, dg)

    res = [0]*(dmin+1)
    for i in range(0, dmin+1):
        res[i] = cf[i]+cg[i]
    
    #ajout des derniers coefficients
    if dmin==df :
        res.extend(cg[dmin+1:])
    else :
        res.extend(cf[dmin+1:])
    return ring(res)

def soustraction(f, g) :
    ring = f.parent()
    df = f.degree() ; cf = f.list()
    dg = g.degree() ; cg = g.list()
    dmin = min(df, dg)

    res = [0]*(dmin+1)
    for i in range(0, dmin+1):
        res[i] = cf[i]-cg[i]
    
    #ajout des derniers coefficients
    if dmin==df :
        for e in cg[dmin:] :
            res.append(-e)
    else :
        res.extend(cf[dmin+1:])
    return ring(res)


def mult_naive(f, g) :
    ring = f.parent()
    df = f.degree() ; cf = f.list()
    dg = g.degree() ; cg = g.list()
    
    res = [0]*(df+dg+1) 
    
    for i in range(0, df+1):
        for j in range(0, dg+1):
            res[i+j] += cf[i]*cg[j]

    return ring(res) 
    
def karatsuba(f, g) :
    ring = f.parent()
    t = ring.gen()
    if f.is_zero() : return f
    if g.is_zero() : return g
    
    df = f.degree(); dg = g.degree()
    if (df <= 10 and dg <= 10) : #on considère que le thresold est 0 (à modifier ?) 
        return mult_naive(f, g)

    cf = f.list(); cg = g.list()
    k = max(df/2, dg/2).ceil()

    f0 = ring(cf[:k]); f1 = ring(cf[k:])
    g0 = ring(cg[:k]); g1 = ring(cg[k:])

    h1 = karatsuba(f0, g0)
    h2 = karatsuba(f1, g1)
    h5 = karatsuba(f0+f1, g0+g1)
    h7 = h5 - h1 - h2

    #h = h1 + h7.shift(k) + h2.shift(2*k) 
    #to shift a function = "déplacer le graphe de la fonction"
    #h7.shift(k) va remplacer l'indet par t^k donc élever le degré de k ?

    h = h1 + h7.shift(k) + h2.shift(2*k)

    return h

#division euclidienne polynomes
def division(f, g) :
    t = f.parent().gen()    

    r = f
    cr = f.list(); cg = g.list()
    if f.is_zero() : return f

    while (r.degree() >= g.degree()) :
        q = cr[-1]*inverse_euclide(cg[g.degree()])*t**(r.degree()-g.degree()) #cr[-1] n'est pas bon, l'algorithme ne fonctionne pas si à la fin de la boucle r a un coeff dominant nul
        r = r - q*g
        cr = r.list()
    return r

#division euclidienne polynomes
def division2(f, g) :
    ring = f.parent()
    r = f
    invg = inverse_euclide(g.leading_coefficient())

    while (r.degree() >= g.degree()) :
        q = r.leading_coefficient()*invg
        q = ring(q).shift(r.degree()-g.degree())
        r = r - q*g

    return r


#algorithmes du calcul de g(a) mod f
def eval_naive(g, a, f) :
    ring = g.parent()
    cg = g.list()
    res = 0; ring(res)
    ai = 1
    
    for i in range(g.degree()+1) :
        res = res + cg[i]*ai
        ai = a*ai
    return division(res, f)
    
def eval_horner(g, a, f) :
    ring = g.parent()
    cg = g.list()
    res = cg[0]; 
    ring(res)
    ai = a; 
    for i in range(1,g.degree()+1) :
        res = res + cg[i]*(division(ai, f))
        ai = a*ai
    return res


from sage.matrix.constructor import matrix
def brentkung(f, a, g) :
    #f de degré n, a de degré < n, g de degré < d
    ring = a.parent()

    d = g.degree()+1; n = f.degree()
    r = RR(d.sqrt()).ceil()
    s = RR(d/r).ceil()
    print("- d:", d, "n:", n, "; r:",r, "; s:", s)
    print()

    ac = [ring(0)]*r
    ac[0] = ring(1)

    for i in range(1, r) : 
        ac[i] = (a*ac[i-1])%f
        print("- a**",i, " = ", ac[i])
    print()

    ma = matrix(r, n, [(ac[i])[j] for i in range(r) for j in range(n)])
    mg = matrix(s, r, [g.list()[i*r+j] for i in range(s) for j in range(r)])
    mb = mg*ma
    print("- matrix a = ", ma)
    print("- matrix g = ", mg)
    print("- matrix b = ", mb)
    print()

    b = [ring(0)]*s
    for i in range(s) :
        b[i] = ring(mb[i].list())
        print("- b[", i, "] = ", b[i])
    print()

    res = b[0]; 
    ar = ac[r-1]
    print("- ar:", ar)
    for i in range(1, s) :
        res += b[i]*ar
        ar = ar*ar
        print("- res au tour de boucle ", i, " = ", res)
    print()

    return  res%f

# TODO
# -> version comme naive2
# -> reduire modulo f au fur et a mesure (dans naive 2)
# -> faire version Horner

######################################################
#  quand a est dans le corps (et donc pas de mod f)  #
######################################################


#algorithmes du calcul de g(a) pour a dans le corps
def eval_naive2(g, a) :
    res = 0
    ai = 1
    for i in range(g.degree()+1) :
        res += g[i]*ai
        ai = a * ai
    return res

#methode de Horner
def eval_naive_horner(g,a):
    n = g.degree()
    res = g.leading_coefficient()
    for i in range(1,n+1) :
        res = g[n-i] + res*a
    return res


