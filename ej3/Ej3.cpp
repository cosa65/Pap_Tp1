#include<iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	int a;
	long long suma = 0;
	long long max = 0;
	for(int i=0; i<n; i++){
		cin >> a;
		suma += a;
		if(suma > max) max = suma;
		else if (suma < 0) suma = 0;
	}
	cout << max << endl;
	return 0;
}
