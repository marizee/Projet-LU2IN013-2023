from sage.matrix.constructor import matrix
import time

def eval_naive(g, a, f) :
	ring = g.parent()
	cg = g.list()
	res = 0; ring(res)
	ai = 1

	for i in range(g.degree()+1) :
		res = res + cg[i]*ai
		ai = a*ai
	return res % f;

def eval_naive_improved(g, a, f) :
	ring = g.parent()

	res = ring(g[0])
	ai = a % f; n = g.degree()
	for i in range(1, n+1) :
		res = res + g[i]*ai
		ai = (a*ai) % f
	return res % f

# TODO Horner
def horner(g, a, f) :
    res = g[g.degree()]
    for i in range(g.degree()-1, -1, -1) :
        res = (res*a)%f + g[i]
    return res%f
def horner2(g, a, f) :
    res = g[len(g)-1]
    for i in range(len(g)-2, -1, -1) :
        res = (res*a)%f + g[i]
    return res%f

def brentkung(g, a, f) :

	ring = a.parent()
	d = g.degree()+1; n = f.degree()
	if a.degree() >= n:
		raise ValueError("Erreur: a de degré trop élevé")

	r = RR(d.sqrt()).ceil()
	s = RR(d/r).ceil()

	ac = [ring(0)]*(r+1)
	ac[0] = ring(1)

	for i in range(1, r+1) :
		ac[i] = (a*ac[i-1]) % f

	ma = matrix(r, n, [(ac[i])[j] for i in range(r) for j in range(n)])
	mg = matrix(s, r, [g[i*r+j] for i in range(s) for j in range(r)])
	mb = mg*ma

	b = [ring(0)]*s
	for i in range(s) :
		b[i] = ring(mb[i].list())

	res = b[0];
	ar = ac[r]

	res = horner2(b, ar, f)
	return res

def brentkung2(g, a, f) :

	ring = a.parent()
	d = g.degree()+1; n = f.degree()
	if a.degree() >= n:
		raise ValueError("Erreur: a de degrÃ© trop Ã©levÃ©")

	r = RR(d.sqrt()).ceil()
	s = RR(d/r).ceil()

	ac = [ring(0)]*(r+1)
	ac[0] = ring(1)

	ts = time.time()
	for i in range(1, r+1) :
		ac[i] = (a*ac[i-1]) % f
	te = time.time()
	puissa = te - ts

	ts = time.time()
	ma = matrix(r, n, [(ac[i])[j] for i in range(r) for j in range(n)])
	mg = matrix(s, r, [g[i*r+j] for i in range(s) for j in range(r)])
	mb = mg*ma
	te = time.time()
	pmat = te - ts

	b = [ring(0)]*s
	for i in range(s) :
		b[i] = ring(mb[i].list())

	res = b[0];
	ar = ac[r]

	ts = time.time()
	tmp = ar
	for i in range(1, s) :
		res += (b[i]*tmp) % f
		tmp = ar*tmp
	te = time.time()
	tres = te - ts

	print(f'\t{r}\t{s}\t{puissa:.5f}\t{pmat:.5f}\t{tres:.5f}')
	return res

#####EXAMPLES#####
field = FiniteField(97)
ring.<x> = PolynomialRing(field)

print("Comparaisons temps")
print("df\tda\tdg\tsage\tnaive\thorner\tbrent&kung")
for e in range(1, 10) :
	df = 2**e; da = ceil(df/2.); dg = ceil(df/1.5)
	f = ring.random_element(df)
	a = ring.random_element(da)
	g = ring.random_element(dg)

	ts = time.time()
	sage = g(a) % f
	te = time.time()
	tsage = te - ts

	ts = time.time()
	naive = eval_naive(g, a, f)
	te = time.time()
	tnaive = te - ts

	ts = time.time()
	horner = eval_naive_improved(g, a, f)
	te = time.time()
	thorner = te - ts

	ts = time.time()
	bk = brentkung(g, a, f)
	te = time.time()
	tbk = te - ts

	print(f'{df}\t{da}\t{dg}\t{tsage:.5f}\t{tnaive:.5f}\t{thorner:.5f}\t{tbk:.5f}')

print("df\tda\tdg\thorner\tbrent&kung")
for e in range(10, 15) :
	df = 2**e; da = df-1; dg = df-1
	f = ring.random_element(df)
	a = ring.random_element(da)
	g = ring.random_element(dg)

	ts = time.time()
	horner = eval_naive_improved(g, a, f)
	te = time.time()
	thorner = te - ts

	ts = time.time()
	bk = brentkung(g, a, f)
	te = time.time()
	tbk = te - ts

	print(f'{df}\t{da}\t{dg}\t{thorner:.5f}\t{tbk:.5f}')

print("Close-up sur Brent & Kung")
print("df\tda\tdg\tr\ts\ta^i\tGA\thorner")
for e in range(1, 15) :
	df = 2**e; da = ceil(df/2.); dg = ceil(df/1.5)
	f = ring.random_element(df)
	a = ring.random_element(da)
	g = ring.random_element(dg)

	print(f'{df}\t{da}\t{dg}', end="")
	p = brentkung2(g, a, f)
