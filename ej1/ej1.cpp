#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> heapsort(std::vector<int>& vec) {

	int n = vec.size();
	std::vector<int> res(n);

	std::make_heap(vec.begin(), vec.end());
	for (int i = n; i != 0; i--) {
		res[i-1] = vec.front();
		std::pop_heap(vec.begin(), vec.end());
		vec.pop_back();
	}
	return res;
}

int binary_search(std::vector<int>& Y, int xi, int P) {
	if (Y.size() == 0) return 0;

	int best_pos = upper_bound(Y.begin(), Y.end(), P - xi) - 1 - Y.begin();
		//Upper bound me devuelve en log(n) un iterador al primer elemento de y que es mayor a P - xi
		//El anterior es el último que me sirve; si no existe, no hay ninguno que me sirva.
	if (best_pos == -1) return 0;

	return xi + Y[best_pos];
}

int search_best(std::vector<int>& X, std::vector<int>& Y, int P) {

	X.push_back(0);				//Caso borde, en el que X no tenga elementos. 
								//El caso en que Y no tenga elementos esta cubierto por el binary search.
	int n = X.size();			
	int greater = 0;
	int act;


	for (int i = 0; i < n; i++) {
		act = binary_search(Y, X[i], P);
		if (act > greater) greater = act;
	}
	return greater;
}

int combine(int P, std::vector<int>& X, std::vector<int>& Y) {

	int n = X.size();
	int m = Y.size();

	Y = heapsort(Y);

	return search_best(X, Y, P);
} 

void add_possible_subsets(int P, std::vector<int>& xs, int x) {

	int n = xs.size();

	if (x <= P) {	
		int act;
		for (int i = 0; i < n; i++) {
			act = x + xs[i];
			if (act <= P) {
				xs.push_back(act);
			}
		}
	}
}

std::vector<int> get_subsets(int P, std::vector<int>& D, int start, int end) {

	std::vector<int> res;
	res.push_back(0);
	for (int i = start; i < end; i++) {
		add_possible_subsets(P, res, D[i]);
	}

	return res;
}

int meet_in_the_middle(int P, std::vector<int>& D) {	//Algoritmo principal, separa las operaciones internas en obtener los subsets de los dos subarrays
														//Luego combine ordena y hace la busqueda binaria
	int end = D.size();
	std::vector<int> X = get_subsets(P, D, 0, D.size()/2);
	std::vector<int> Y = get_subsets(P, D, end/2, end);

	return combine(P, X, Y);
}

int main() {
	
	int P, N;
	std::cin >> P >> N;
	std::vector<int> D(N);
	for (int i = 0; i < N; i++) {
		std::cin >> D[i];
	}

	int res = meet_in_the_middle(P, D);
	std::cout << res << std::endl;
}
