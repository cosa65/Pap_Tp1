#include <iostream>
#include <algorithm>
#include <vector>

void add_possible_subsets(int P, std::vector<int>& xs, int x) {
//todos los posibles resultados de agregar los elementos de xs a x
	int n = xs.size();

	if (x <= P) {
		xs.push_back(x);	
		int act;
		for (int i = 0; i < n; i++) {
			act = x + xs[i];
			if (act <= P) {
				xs.push_back(act);
			}
		}
	}
}

int binSearch(int P, int subX, std::vector<int>& subsY, int start, int pivot, int end) {
	if (pivot == start) {
		if (subX + subsY[start] <= P)
			return subX + subsY[start];
		else
			return 0;
	} 
	if (subX + subsY[pivot] > P)
		return binSearch(P, subX, subsY, start, (start + pivot)/2, pivot);
	else
		return binSearch(P, subX, subsY, pivot, (end + pivot)/2, end);

}

int combine(int P, std::vector<int>& subsX, std::vector<int>& subsY) {

	std::sort(subsY.begin(), subsY.end());
	int size_subs_x = subsX.size();
	int size_subs_y = subsY.size();
	int best = 0;

	for (int i = 0; i < size_subs_x && subsX[i] <= P; i++) {
		int cand = binSearch(P, subsX[i], subsY, 0, size_subs_y/2, size_subs_y);
		if (cand > best) cand = best;
	}
	return best;
}

std::vector<int> find_possibles(int P, std::vector<int> D, int start, int end) {

	std::vector<int> res;
	int n = D.size();
	for (int i = 0; i < n; i++) {
		add_possible_subsets(P, res, D[i]); //para cada elemento de X, agrego todo lo que puedo sumar
	}

	return res;
}

int main() {
	
	/*int P, N;
	std::cin >> P >> N;

	std::vector<int> D(N);
	
	for (int i = 0; i < N; i++) {
		std::cin >> D[i];
	}

	std::vector<int> X = find_possibles(P, D, 0, N/2);
	std::vector<int> Y = find_possibles(P, D, N/2, N);
	int res = combine(P, X, Y);

	std::cout << res << std::endl;*/

	int x = 10;
	int myints[] = {2,3,4,9};
  	std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
	int n = fifth.size();
	return binSearch(18, 10, fifth, 0, n/2, n);

}
