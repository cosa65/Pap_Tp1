#include "matriz.h"

Matriz productoria(vector<Matriz>& matrices, int inicio, int largo) {
// Se puede optimizar, si uso los niveles de abajo de la pirámide sale en log^2 esta parte
	Matriz res = id();
	for (int i=inicio; i<inicio + largo; i++) {
		res *= matrices[i];
	}
	return res;
}

unsigned int getlogmaxlargo(int i) {

/* Acá lo que me fijo es cual es el nivel más alto al que se podría a llegar empezando por i, sin importar hasta donde quiero sumar
Por ej, i si i = 4, va a dar 2, porque voy a tener [4], [4 5] y [4 5 6 7] pero no [4 5 6 7 8 9 10 11 12]
Es la cantidad de ceros al final, si es cero le hardcodeamos algo
No está bueno que sea log, pero creo que no hay un bit twiddling que fncione
Lo más fácil es precalcularlo */
	if (i==0) return -1; //Infinito: el límite me lo va a dar la otra fn
	unsigned int res;
	for (res = 0; !(i & 1); i >>= 1) 
		res++;
	return res;
}

unsigned int logbottom(int i) {
/* Si voy a sumar del 3 al 7 por ejemplo, y estoy buscando empezar por el 4, no quiero llegar a
[4 5 6 7], solo voy a usar el [4 5]
O sea, redondeo a la anterior potencia de 2 */
	if (!i) return 0;
	unsigned int res = -1;	
	for (;i > 0; i>>=1)
		res++;
	return res;
}

int main() {
	int n, l, largo = 0;
	unsigned int maxlargo;
	Matriz res;
	cin >> n >> l;
	cin >> res;
	vector<Matriz> matrices(n);
	for (int i = 0; i<n; i++) 
		cin >> matrices[i];

//Precalculo la pirámide de productos parciales, en el nivel 0 agrupo de a 1, en el 1 agrupo de a 2, en el i de a 2^i

	vector<vector<Matriz> > prodsParciales(n, vector<Matriz>(n));
	for (int j = 0; largo <  n; j++) {
		largo = 1 << j;
		for (int i = 0; i < n; i += largo) { // i = inicio
			prodsParciales[i][j] = productoria(matrices, i, largo);
//			cout << prodsParciales[i][j] << endl;
		}
	}

//para cada lugar donde puedo iniciar, voy multiplicando los valores de la pirámide más altos que pueda.
//Supongo que es log, si no bueno, cosas que pasan

	for (int i = 0; i <= n - l; i++) { // i = inicio
		Matriz parcial = id();
		for (int j = i; j < i + l; j += 1 << maxlargo) {
			maxlargo = min(getlogmaxlargo(j), logbottom(i+l-j));
			parcial *= prodsParciales[j][maxlargo];
//			cout << prodsParciales[j][maxlargo];
		}
//		cout << i << endl << parcial << endl;
		if (parcial == res) {
			cout << "SI" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
}
