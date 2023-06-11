


#	MULTIPLICATION DE DEUX POLYNOMES f*g
#	- f, g de degré au plus n
#	- comprendre et implémenter les différents algorithmes de multiplication
#	- comparer les perfomances de ces derniers


import time

def mult_naive(f, g) :
    ring = f.parent()
  
    res = [0]*(f.degree()+g.degree()+1) 
    
    for i in range(0, f.degree()+1):
        for j in range(0, g.degree()+1):
            res[i+j] += f[i]*g[j]

    return ring(res) 
    
def karatsuba(f, g, seuil=5) :
    ring = f.parent()

    if f.is_zero() : return f
    if g.is_zero() : return g
    
    if (f.degree() <= seuil and g.degree() <= seuil) :  
        return mult_naive(f, g)

    k = max(f.degree()/2, g.degree()/2).ceil()

    #décomposition
    f0 = ring(f.list()[:k]); f1 = ring(f.list()[k:])
    g0 = ring(g.list()[:k]); g1 = ring(g.list()[k:])

    #calcul des éléments de la formule
    h1 = karatsuba(f0, g0)
    h2 = karatsuba(f1, g1)
    h5 = karatsuba(f0+f1, g0+g1)
    
    h7 = h5 - h1 - h2
    h = h1 + h7.shift(k) + h2.shift(2*k)

    return h


ring = PolynomialRing(FiniteField(97), 'x')

##TESTS
#f = ring.random_element(1000)
#g = ring.random_element(1000)
#
#p = f*g; q = mult_naive(f, g); r = karatsuba(f, g)
#print(f'naive ok ?\t {p==q}')
#print(f'karatsuba ok ?\t {p==r}')



#COMPARAISONS TEMPS
print("n\tnaive\tKaratsuba")
for e in range(1, 10) :
    n = 2**e; 
    f = ring.random_element(n)
    g = ring.random_element(n)

    ts = time.time()
    naive = mult_naive(f, g)
    te = time.time()
    tnaive = te - ts

    ts = time.time()
    kara = karatsuba(f, g)
    te = time.time()
    tkara = te - ts

    print(f'{n}\t{tnaive:.5f}\t{tkara:.5f}')