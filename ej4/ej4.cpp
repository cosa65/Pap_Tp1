#include "matriz.h"

int main() {
	int n, l, largo = 0;
	unsigned int minlargo;
	Matriz res;
	cin >> n >> l;
	cin >> res;
	vector<Matriz> matrices(n);
	for (int i = 0; i<n; i++) 
		cin >> matrices[i];

//Precalculo la pirámide de productos parciales, en el nivel 0 agrupo de a 1, en el 1 agrupo de a 2, en el i de a 2^i

	vector<vector<Matriz> > prodsParciales(n, vector<Matriz>(n));

	for (int i = 0; i < n; i++) // i = inicio
		prodsParciales[i][0] = matrices[i];

	for (int j = 1; largo < n; j++) {
		largo = 1 << j;
		for (int i = 0; i <= n - largo; i++) // i = inicio
			prodsParciales[i][j] = prodsParciales[i][j-1] * prodsParciales[i + (largo >> 1)][j-1];
	}

//Para cada lugar donde puedo iniciar, voy multiplicando los valores de la pirámide.

	for (int i = 0; i <= n - l; i++) { // i = inicio
		Matriz parcial = id();
		int pos = i;
		for (int j = 0; pos - i < l; j++) {
			if (l & (1 << j)) {
				parcial *= prodsParciales[pos][j];
				pos += (1 << j);
			}
		}
		if (parcial == res) {
			cout << "SI" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
}
