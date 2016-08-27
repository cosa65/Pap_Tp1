#include <iostream>
#include <vector>
#include <algorithm>

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

	int first = 0;
	int last = Y.size() - 1;
	int mid = last/2;
	int res = 0;
	int act;

	while(last - first > 1) {
		mid = (first + last) / 2;
		act = xi + Y[mid];
		
		if (P > act) {
			if (P < Y[mid+1] + xi) return act;
			first = mid;
		} else if (P < act) {
			last = mid;
		} else if (P == act) {
			return P;
		}
	}

	return 0;
}

int best_fit(std::vector<int>& X, std::vector<int>& Y, int P) {

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

	return best_fit(X, Y, P);
}

std::vector<int> poss_subsets(int P, std::vector<int>& D, int start, int end) {

	std::vector<int> res;
	for (int i = start; i < end; i++) {
		add_possible_subsets(P, res, D[i]);
	}

	return res;
}

int get_best(int P, std::vector<int>& D) {

	int end = D.size();
	std::vector<int> X = poss_subsets(P, D, 0, D.size()/2);
	std::vector<int> Y = poss_subsets(P, D, end/2, end);
	return combine(P, X, Y);
}

int main() {
	
	int P, N;
	std::cin >> P >> N;
	std::vector<int> D(N);
	for (int i = 0; i < N; i++) {
		std::cin >> D[i];
	}

	int res = get_best(P, D);
	std::cout << res << std::endl;
}