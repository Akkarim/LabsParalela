
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <omp.h>
#include <math.h>
#include <random>
#include <algorithm>
//#include <yourself>
//#include <love>
#include <time.h>


using namespace std;


bool validaCntHilos(int ch);

//vector<int>* mergesort(int* inicio, int* final, vector<int>* vector);


int main(int argc, char* argv[]) {
	vector<int> aleatorios; //Lista de números
	vector<int> resultado; //Resultados de Merge
	vector<vector<int>> vectores; // Vector de Vectores
	vector<int> myVector; // El que guardamos las copias de aleatorios 
	vector<int> merge1;
	vector<int> merge2;

	int tCount = 0;
	int	n, data_count, local_inicio, local_final, local_n, my_Rank;

	while (!validaCntHilos(tCount)) {
		cout << "Digite la cantidad de hilos ( >= 1 ): ";
		cin >> tCount;
		cout << "Cantidad de numeros: Ajua, aua aua" << endl;
		cin >> data_count;
		cout << endl;
	}

	int k = 0;
	aleatorios.reserve(data_count);
	vectores.reserve(data_count);
	local_n = data_count / tCount;

	for (int i = 0; i < data_count; i++) {
		k = rand() % 100 + 1;
		aleatorios.push_back(k);
	}

	myVector.reserve(local_n);

#pragma omp parallel num_threads(tCount) private(local_inicio,local_final,my_Rank, myVector)
	{
		myVector.clear();//JustInCase
		my_Rank = omp_get_thread_num();
		local_inicio = local_n * my_Rank;
		local_final = local_n + local_inicio;
		sort((aleatorios.begin() + local_inicio), (aleatorios.begin() + local_final));
		/*for (int i = local_inicio; i < local_final; i++) {
			myVector.push_back(aleatorios[i]); //Hay que cambiar esto para la versión paralela del merge
		}*/
#pragma omp critical
		vectores.push_back(myVector);
	}

	std::cout << "Lista contiene:";
	for (std::vector<int>::iterator it = aleatorios.begin(); it != aleatorios.end(); ++it)
		std::cout << ' ' << *it;
	cout << '\n';
	
	
	int i2, f2; //-------------------------------------Merge sin paralelizar------------------------------------------------
	int mitad = aleatorios.size()/ 2;
	resultado.resize(data_count);
	local_final = local_n;
	merge1.reserve(local_n);
	merge2.reserve(local_n);
	while(vectores.size()!=1){
		resultado.clear();
		resultado.resize(vectores[0].size()*2, 0);
		merge1 = vectores[0];
		merge2 = vectores[1];
		merge(merge1.begin(), merge1.end(), merge2.begin(), merge2.end(), resultado.begin());
		//aleatorios = resultado;
		vectores.push_back(resultado);
		vectores.erase(vectores.begin());
		vectores.erase(vectores.begin());
	}

	std::cout << "El resultado es: ";
	for (std::vector<int>::iterator it = resultado.begin(); it != resultado.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
	//---------------------------------------------------------------------------------------------------------------------

	cin >> n;
	return 0;
}

bool validaCntHilos(int ch) {
	return ch >= 1;
}