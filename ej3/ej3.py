import random

#TEST
a = range(-8, 9)
random.shuffle(a)
# a = [2, 3, 8, -7, -1, 1, -9, 6, 0, -2, 9, -3, -5, -6, 7, -10, 4, -4, 5, -8]
print a
##

sumaddeultimomax = 0
res = 0
 #solo p/ debug, no nos piden dar el rango
ultimomin = -1
ultimomax = -1

for i in range(len(a)):

#	ponele que tengo [a, b, [c, d, e], f..., [cde] es el max hasta ahora
#	y f es negativo porque si no lo habria agregado al max
#	y ponele que estoy leyendo g

# no puedo agregar g sin agregar f, salvo que tire todo lo anterior

	sumaddeultimomax += a[i]

	# me fijo si salgo ganando si agrego [fg]
	if (sumaddeultimomax > 0):
		ultimomax = i
		res += sumaddeultimomax
		sumaddeultimomax = 0

	#me fijo si me conviene tirar todo lo anterior
	elif (a[i] > res):
		ultimomin = i
		ultimomax = i
		res = a[i]
		sumaddeultimomax = 0

	#DEBUG: imprimo en cada paso la subseq que tenemos
	if ultimomin == -1 and ultimomax > -1: print '[',
	for j in range(len(a)):
		printear = ""
		if j == ultimomin: printear += '['
		printear += str(a[j])
		if j == ultimomax: printear += ']'
		if i == j: print printear + ' |',
		else: print printear + ",",
	print '\n',
	##

print "\n",a[max(0, ultimomin): ultimomax + 1], res
