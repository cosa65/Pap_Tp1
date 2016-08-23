#include <iostream>
#include <vector>

void add_possible_subsets(int P, std::vector<int>& xs, int x) {

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

std::vector<int> combine(int P, std::vector<int> X, std::vector<int> Y) {

	vector<int> subsX, subsY;
	int n = X.size();
	int m = Y.size();
	for (int i = 0; i < n; i++) {
		add_possible_subsets(P, subsX, X[i]);
	}

	for (int i = 0; i < m; i++) {
		add_possible_subsets(P, subsY, Y[i]);
	}

	int size_subs_x = subsX.size();

	for (int i = 0; i < size_subs_x; i++) {
		add_possible_subsets(P, subsY, subsX[i]);
	}
}

std::vector<int> find_possibles(int P, std::vector<int> D, int start, int end) {

	std::vector<int> X = find_possibles(P, D, start, end/2);
	std::vector<int> Y = find_possibles(P, D, end/2, end);
	std::vector<int> res = combine(P, X, Y);
	return res;
}

int main() {
	
	int P, N;
	std::cin >> P >> N;

	std::vector<int> D(N);
	
	for (int i = 0; i < N; i++) {
		std::cin >> D[i];
	}

	int res = best_option(P, D, 0, N);

}