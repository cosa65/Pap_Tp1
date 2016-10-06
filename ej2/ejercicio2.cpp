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


void init(int *FelicidadFiesta, int N )
{
	FelicidadFiesta[0] = 0;
	FelicidadFiesta[1] = 0;
	for (int i = 2; i < (1<<N); ++i)
	{
		FelicidadFiesta[i] = -100;
	}
	for (int i = 2; i < (1<<N); i*=2)
	{
		FelicidadFiesta[i] = 0;
	}
}


void CalcularFelicidades(int *FelicidadFiesta, int N, int **M)
{
	for (int i = 3; i < (1<<N) ; ++i)//me guardo la suma de tener cada elemento en el conjunto complejidad O(2^n)*(n^2) <= O(3^n)
	{
		if(FelicidadFiesta[i] == -100)
		{
			for (int j = 0; j < N; ++j)
			{
				if(i & (1<<j)) //voy a sacar el bit menos significativo que es el que se agrego ahora
				{
					FelicidadFiesta[i] = FelicidadFiesta[(i)^(1<<j)] + sumarpresentes(i^(1<<j), j, N, M);
					break;
				}
			}

		}
	}

}

int MejorCombinacion(int *ResPrevios, int *FelicidadFiesta, int N, int mask)
{
	int res = 0;
	if (ResPrevios[mask] != -100)
		return ResPrevios[mask];

	for(int i=mask; i != 0; i = mask&(i-1)) //lo que baja a O(3^N), itero sobre el subconjunto que me permitiria (mask & i == i)
		res =  max(res,  FelicidadFiesta[i] + MejorCombinacion(ResPrevios, FelicidadFiesta, N, mask^i));
	
	ResPrevios[mask] = res;
	return res;
}

////////////////////////////////
int main()
{
	int N, elem;

    cin >> N;

    int **M = new int *[N];
	for(int i = 0; i < N; i++)  {M[i] = new int[N];}
		

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> elem;
			M[i][j] = elem;
		}
	}

 	int *FelicidadFiesta = new int [1<<N];
 	int *ResPrevios = new int [1<<N];

 	for (int i = 0; i < (1<<N); ++i)
 		ResPrevios[i] = -100;

	init(FelicidadFiesta, N);
	CalcularFelicidades(FelicidadFiesta, N, M);

	int a = MejorCombinacion(ResPrevios, FelicidadFiesta, N, (1 << N)-1);

	for(int i = 0; i < N; i++) {free (M[i]);} //LIBERO MEMORIA
	free (M);
	free (FelicidadFiesta);
	free (ResPrevios);

	
	cout << a << endl;
	
	return 0;
}
