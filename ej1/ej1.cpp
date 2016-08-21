#include <iostream>
#include <vector>

bool get_best_bag(std::vector<int> D, int N, int P, int& res) {

	bool changed_res = false;

	for (int i = 0; i < N; i++) {
		if (D[i] >= res and D[i] <= P) {
			res = D[i];
			changed_res = true;
		}
	}

	return res;
}

void get_min(std::vector<int>& D, int& min1, int& min2, int N) {

	min1 = 0;
	min2 = 1;

	if (D[0] > D[1]) std::swap(min1, min2);
	
	for (int i = 2; i < N; i++) {
		if (D[i] < D[min1]) {
			min2 = min1;
			min1 = i;
		}
	}
}

void add_and_merge(std::vector<int>& D, int min1, int min2, int& N) {	
 
	if (min1 != N-1) {		//Si min1 no es el ultimo elemento puedo mover al ultimo a ese lugar.
		D[min2] += D[min1];	//Sumo a los dos menores
		D[min1] = D[N-1];	//Achico en 1 el vector (muevo al ultimo elemento al lugar sobrante de uno de los 2 menores que mergie)
	} else {
		D[min1] += D[min2];	//Sumo a los dos menores
		D[min2] = D[N-1];	//Achico en 1 el vector (muevo al ultimo elemento al lugar sobrante de uno de los 2 menores que mergie)
	}

	N--;
}

int best_option(int P, int N, std::vector<int>& D) {

	int min1, min2;
	int res = 0;
	bool can_spend_more;

	while (can_spend_more) {
		can_spend_more = get_best_bag(D, N, P, res);
		if (N < 2) {
			return res;
		}
		get_min(D, min1, min2, N);
		if (P < D[min1]) {
			return res;
		}
		add_and_merge(D, min1, min2, N);
	}

	return res;

}

int main() {
	
	int P, N;
	std::cin >> P >> N;

	std::vector<int> D(N);
	
	for (int i = 0; i < N; i++) {
		std::cin >> D[i];
	}

	int res = best_option(P, N, D);

}