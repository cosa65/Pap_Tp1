#include <iostream>
#include <vector>
#include <string>
#include <algorithm> //max
#include <fstream>


using namespace std;

///////////////////

int sumarpresentes(int presentes, int yo, int N, int **M)//sumo lo que cuesta agregar el nuevo elemento "yo" al conjunto "presentes"
{
	int res = 0;
	for(int j = 0; j < N; j++)
    {
            if(presentes & (1<<j)) 
            	res+= M[yo][j];
    }
    return res;
}


void init(int *resultados, int N )
{
	resultados[0] = 0;
	resultados[1] = 0;
	for (int i = 2; i < (1<<N); ++i)
	{
		resultados[i] = -100;
	}
	for (int i = 2; i < (1<<N); i*=2)
	{
		resultados[i] = 0;
	}
}


void calcular(int *resultados, int N, int **M)
{
	for (int i = 0; i < (1<<N) ; ++i)//me guardo la suma de tener cada elemento en el conjunto complejidad O(2^n)*(n^2) <= O(3^n)
	{
		if(resultados[i] == -100)
		{
			for (int j = 0; j < N; ++j)
			{
				if(i & (1<<j)) //voy a sacar el bit menos significativo que es el que se agrego ahora
				{
					resultados[i] = resultados[(i)^(1<<j)] + sumarpresentes(i^(1<<j), j, N, M);
					break;
				}
			}

		}
	}

}

int mejor( int *resultados, int N, int mask)
{
	int res = 0;
//	for (int i = 1; i < (1<<N); ++i)
	for(int i=mask; i != 0; i = mask&(i-1)) //lo que supuestamente baja a O(3^N)
	{	
		if ((mask & i)  == i) //tengo que ser una opcion para estar en la fiesta  //hmm complejidad O(4^n)???
		{ 
			res =  max(res,  resultados[i] + mejor(resultados, N, mask^i));
		}
		
	}
	return res;
}

////////////////////////////////
int main(int argc, char *argv[])//SOLO PASAR COMO ENTRADA EL NOMBRE DEL ARCHIVO EN EL FORMATO PEDIDO POR EL TP
{
	int N, elem;

	if(argc != 2){
		cout << "falta la entrada" << endl;
		return 0; 
	}
		
	ifstream archivo (argv[1]);

    archivo >> N;

    int **M = new int *[N];
	for(int i = 0; i < N; i++)  {M[i] = new int[N];}
		

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			archivo >> elem;
			M[i][j] = elem;
		}
	}

	archivo.close();

 	int *resultados = new int [1<<N];

	init(resultados, N);
	calcular(resultados, N, M);

	int a = mejor(resultados, N, (1 << N)-1);

	for(int i = 0; i < N; i++) {free (M[i]);} //LIBERO MEMORIA
	free (M);
	free (resultados);
	
	cout << "RESULTADO FINAL " << a << endl;
	
	return 0;
}