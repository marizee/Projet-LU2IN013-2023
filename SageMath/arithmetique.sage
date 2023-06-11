


#	OPERATIONS ARITHMETIQUES SUR LES ENTIERS ET POLYNOMES A COEFFICIENTS DANS Z/pZ
#   - comprendre ce qui se cache dans l'opération %
#   - comprendre comment fonctionne le corps Z/pZ



#calcul de l'inverse d'un entier dans Z/pZ
def inverse(a, p=7) :
    b = 0
    while (a*b != 1) :     
        b=b+1
    return b

#avec l'algorithme d'euclide ====> NE FONCTIONNE PAS
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

#addition de deux polynomes f+g
def addition(f, g) :
    ring = f.parent()
    dmin = min(f.degree(), g.degree())

    res = [0]*(dmin+1)
    for i in range(0, dmin+1):
        res[i] = f[i]+g[i]
    
    #ajout des derniers coefficients
    if dmin==f.degree() :
        res.extend(g.list()[dmin+1:])
    else :
        res.extend(f.list()[dmin+1:])
    return ring(res)

#soustraction de deux polynomes f-g
def soustraction(f, g) :
    ring = f.parent()
    dmin = min(f.degree(), g.degree())

    res = [0]*(dmin+1)
    for i in range(0, dmin+1):
        res[i] = f[i]-g[i]
    
    #ajout des derniers coefficients. 
    if dmin==f.degree() :
        for e in g[dmin:] :
            res.append(-e)
    else :
        res.extend(f.list()[dmin+1:])
    return ring(res)

#division euclidienne polynomes : f%g
def division(f, g) :
    ring = f.parent()
    r = f
    invg = inverse(g.leading_coefficient())

    while (r.degree() >= g.degree()) :
        q = r.leading_coefficient()*invg
        q = ring(q).shift(r.degree()-g.degree())
        r = r - q*g

    return r




#TESTS
#ring = PolynomialRing(GF(97), 'x')
#
#f = ring.random_element(1000)
#g = ring.random_element(900)
#
#p = f+g; q = addition(f, g)
#print(f'addition ok ?\t {p==q}')
#
#p = f-g; q = soustraction(f, g)
#print(f'soustraction ok ?\t {p==q}')
#
#p = f%g; q = division(f, g)
#print(f'division ok ?\t {p==q}')