#include "matriz.h"

Matriz productoria(vector<Matriz> matrices, int inicio, int largo) {
	Matriz res = id();
	for (int i=inicio; i<largo; i++) {
		res *= matrices[i];
	}
	return res;
}

int getmaxlargo(int i) {
			// Es la cantidad de ceros al final, si es cero le hardcodeamos algo
			// No está bueno que sea log, pero creo que no hay un bit twiddling que fncione
			// Lo más fácil es precalcularlo
	int res;
	for (res = 0; !(i & 1); i >>= 1) 
		res++;
	return res;
}

int main() {
	int n, l, maxlargo;
	Matriz res;
	cin >> n >> l;
	cin >> res;
	vector<Matriz> matrices(n);
	for (int i = 0; i<n; i++) {
		cin >> matrices[i];
	}

	vector<vector<Matriz> > prodsParciales(n, vector<Matriz>(n));
	for (int j = 0; j < n; j <<= 1) {	 // j = largo
		for (int i = 0; i<n-l; i += j) { // i = inicio
			prodsParciales[i][j] = productoria(matrices, i, j);
		}
	}

	for (int i = 0; i < n - l; i++) { // i = inicio
		Matriz parcial = id();
		for (int j = i; j < i + l; j += maxlargo) {
			maxlargo = getmaxlargo(i);
			parcial *= prodsParciales[i][j];
		}
		if (parcial == res) {
			cout << "SI" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;

