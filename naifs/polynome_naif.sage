R.<t> = PolynomialRing(ZZ)

def produit(p1, p2) :
    return p1*p2

def somme(p1, p2) :
    return p1 + p2

#comment créer un polynome à partir d'une liste de coefficient (valeur de retour des algorithmes)

polynome1 = 1+2*t+3*t^2
polynome2 = 4+5*t+6*t^2

print(produit(polynome1, polynome2))
