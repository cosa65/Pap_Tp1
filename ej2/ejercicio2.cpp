#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <algorithm> //max

using namespace std;


//int M [4][4] = {{0,-2,-1,-4},{-2,0,5,1},{-1,5,0,3},{-4,1,3,0}};
//int M [3][3] = {{0, -1, 1},{-1,0,-1},{1,-1,0}};
//int M[4][4] = {{0,2,-1,0},{2,0,0,-1},{-1,0,0,2},{0,-1,2,0}};
int M [4][4] = {{0,2,2,-1},{2,0,0,2},{2,0,0,2},{-1,2,2,0}};


///////////////////

int sumarpresentes(int presentes, int yo, int N)//sumo lo que cuesta agregar el nuevo elemento "yo" al conjunto "presentes"
{
	int res = 0;
	for(int j = 0; j < N; j++)
    {
            if(presentes & (1<<j)) 
            	res+= M[yo][j];
    }
    return res;
}


void init(vector<int> &resultados)
{
	resultados[0] = 0;
	resultados[1] = 0;
	for (int i = 2; i < resultados.size(); ++i)
	{
		resultados[i] = -100;
	}
	for (int i = 2; i < resultados.size(); i*=2)
	{
		resultados[i] = 0;
	}
}

void calcular(vector<int> &resultados, int N)
{
	for (int i = 0; i < resultados.size() ; ++i)//me guardo la suma de tener cada elemento en el conjunto complejidad O(2^n)*(n^2) <= O(3^n)
	{
		if(resultados[i] == -100)
		{
			for (int j = 0; j < N; ++j)
			{
				if(i & (1<<j)) //voy a sacar el bit menos significativo que es el que se agrego ahora
				{
					resultados[i] = resultados[(i)^(1<<j)] + sumarpresentes(i^(1<<j), j, N);
					break;
				}
			}

		}
	}

}

int mejor( vector<int> &resultados, int N, int mask)
{
	int res = 0;
	for (int i = 1; i < (1<<N); ++i)
	{	
		if ((mask & i)  == i) //tengo que ser una opcion para estar en la fiesta  //hmm complejidad O(4^n)???
		{ 
			res =  max(res,  resultados[i] + mejor(resultados, N, mask^i));
		}
		
	}
	return res;
}

////////////////////////////////
int main()
{

	int N = 4;

	vector<int> resultados(1<<N);

	init(resultados);
	calcular(resultados, N);

	int a = mejor(resultados, N, (1 << N)-1);
	
	cout << "RESULTADO FINAL " << a << endl;
	
	return 0;
}