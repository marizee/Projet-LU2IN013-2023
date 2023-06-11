field = FiniteField(97)
ring.<x> = PolynomialRing(field)

def somme(p1, p2) :
    df = f.degree() ; cf = f.list()
    dg = g.degree() ; cg = g.list()
    dmin = min(df, dg)
    res = [0]*(dmin+1)
    
    for i in range(0, dmin+1) :
        res[i] = cf[i] + cg[i]
    if i == df :
        res.extend(cg[i+1:])        #ajoute en fin de liste tous les éléments à partir du (i+1ème)
    else :
        res.extend(cf[i+1:])

    return ring(res)

def mult_naive(p1, p2) :
    df = f.degree() ; cf = f.list()
    dg = g.degree() ; cg = g.list()
    res = [0]*(df+dg+1)             #créé liste de 0
    
    for i in range(0, df+1) :
        for j in range(0, dg+1) :
            res[i+j] += cf[i]*cg[j]
            
    return ring(res)



polynome1 = 1+2*t+3*t^2
polynome2 = 4+5*t+6*t^2

print(produit(polynome1, polynome2))
