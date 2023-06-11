


#	COMPOSITION MODULAIRE g(a) %f
#	- f(x) de degré n, a(x) de degré < n, g(y) de degré < d
#	- comprendre et implémenter les différents algorithmes de composition modulaire
#	- comparer les perfomances de ces derniers



from sage.matrix.constructor import matrix
import time

#calcul de g(a) puis réduction %f
def eval_naive(g, a, f) :
	ring = g.parent()
	cg = g.list()
	res = 0; ring(res)
	ai = 1

	for i in range(g.degree()+1) :
		res = res + cg[i]*ai
		ai = a*ai
	return res % f

#réduire %f au fur et à mesure les puissances de a
def eval_naive_improved(g, a, f) :
	ring = g.parent()

	res = ring(g[0])
	ai = a % f; n = g.degree()
	for i in range(1, n+1) :
		res = res + g[i]*ai
		ai = (a*ai) % f
	return res % f

#algorithme d'Horner
def horner(g, a, f) :
    res = g[g.degree()]
    for i in range(g.degree()-1, -1, -1) :
        res = (res*a)%f + g[i]
    return res%f

#algorithme d'Horner avec g liste de coefficients
def horner2(g, a, f) :
    res = g[len(g)-1]
    for i in range(len(g)-2, -1, -1) :
        res = (res*a)%f + g[i]
    return res%f


#algorithme de Brent et Kung
def brentkung(g, a, f) :

	ring = a.parent()
	d = g.degree()+1; n = f.degree()
	if a.degree() >= n:
		raise ValueError("Erreur: a de degré trop élevé")

	r = RR(d.sqrt()).ceil()
	s = RR(d/r).ceil()

	#calcul des puissances de a
	ac = [ring(0)]*(r+1)
	ac[0] = ring(1)

	for i in range(1, r+1) :
		ac[i] = (a*ac[i-1]) % f

	#calcul du produit matriciel
	ma = matrix(r, n, [(ac[i])[j] for i in range(r) for j in range(n)])
	mg = matrix(s, r, [g[i*r+j] for i in range(s) for j in range(r)])
	mb = mg*ma

	b = [ring(0)]*s
	for i in range(s) :
		b[i] = ring(mb[i].list())

	res = b[0]
	ar = ac[r]

	res = horner2(b, ar, f)
	return res


ring = PolynomialRing(FiniteField(97), 'x')

##TESTS
#f = ring.random_element(100)
#a = ring.random_element(99)
#g = ring.random_element(100)
#
##g(pring.quotient(f)(a)) ?
#p = g(a)%f; q = eval_naive(g, a, f); r = eval_naive_improved(g, a, f); s = horner(g, a, f); t = brentkung(g, a, f)
#print(f'naive ok ?\t {p==q}')
#print(f'naive_improved ok ?\t {p==r}')
#print(f'horner ok ?\t {p==s}')
#print(f'brent et kung ok ?\t {p==t}')



#COMPARAISONS TEMPS
print("d\tsage\tnaive\tnaiimp\thorner\tbrent&kung")
for e in range(1, 10) :
	d = 2**e
	f = ring.random_element(d)
	a = ring.random_element(d-1)
	g = ring.random_element(d)

	ts = time.time()
	sage = g(a) % f
	te = time.time()
	tsage = te - ts

	ts = time.time()
	naive = eval_naive(g, a, f)
	te = time.time()
	tnaive = te - ts

	ts = time.time()
	naive_improved = eval_naive_improved(g, a, f)
	te = time.time()
	tnaiveimp = te - ts

	ts = time.time()
	hor = horner(g, a, f)
	te = time.time()
	thorner = te - ts

	ts = time.time()
	bk = brentkung(g, a, f)
	te = time.time()
	tbk = te - ts

	print(f'{d}\t{tsage:.5f}\t{tnaive:.5f}\t{tnaiveimp:.5f}\t{thorner:.5f}\t{tbk:.5f}')
