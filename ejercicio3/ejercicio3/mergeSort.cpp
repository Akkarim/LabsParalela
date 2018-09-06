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

/*Datos Globales*/

bool validaCntHilos(int ch);

//vector<int>* mergesort(int* inicio, int* final, vector<int>* vector);

vector<int> aleatorios;
vector<int> resultado;
vector<vector<int>> vectores;
vector<int> myVector;
vector<int> merge1;
vector<int> merge2;
int main(int argc, char* argv[]) {
	int tCount = 0;
	int	n,data_count,local_inicio,local_final,local_n,my_Rank;

	while (!validaCntHilos(tCount)) { /*Que mordido rata*/
		cout << "Digite la cantidad de hilos ( >= 1 ): ";
		cin >> tCount;
		cout << "Cantidad de numeros: Ajua, aua aua" << endl;
		cin >> data_count;
		cout << endl;
	}

	int k = 0;
	aleatorios.reserve(data_count);
	local_n = data_count / tCount;
	for (int i = 0; i < data_count; i++) {
		k = rand() % 100 + 1;
		aleatorios.push_back(k);
	}

	myVector.reserve(local_n);

#pragma omp parallel num_threads(tCount) private(local_inicio,local_final,my_Rank)
	{
		myVector.clear();//JustInCase
		my_Rank = omp_get_thread_num();
		local_inicio = local_n * my_Rank;
		local_final = local_n + local_inicio;
		sort((aleatorios.begin() + local_inicio), (aleatorios.begin() + local_final));
		for(int i = local_inicio; i < local_final; i++) {
			myVector.push_back(aleatorios[i]);
		}
#pragma omp critical
		vectores.push_back(myVector);
	}

	/*
	std::cout << "Lista contiene:";
	for (std::vector<int>::iterator it = aleatorios.begin(); it != aleatorios.end(); ++it)
		std::cout << ' ' << *it;
	cout << '\n';


	/*int i2, f2;
	int mitad = aleatorios.size()/ 2;
	resultado.resize(data_count);
	//cout << resultado.size << endl;
	local_final = local_n;
	merge1.reserve(local_n);
	merge2.reserve(local_n);
	while(vectores.size()!=1){
		resultado.clear();
		resultado.resize(vectores[0].size()*2, 100);
		merge1 = vectores[0];
		merge2 = vectores[1];	
		vectores.erase(vectores.begin());
		vectores.erase(vectores.begin());
		merge(merge1.begin(), merge1.end(), merge2.begin(), merge2.end(), resultado.begin());	
		aleatorios = resultado;
		vectores.push_back(aleatorios);
	}*/

	while (vectores.size() != 1) {
		cout << "Hello world" << endl;
		tCount = tCount / 2;
#pragma omp parallel num_threads(tCount) private(my_Rank, resultado)
		{
			resultado.clear();
			resultado.resize(vectores[0].size() * 2, 0);
			my_Rank = omp_get_thread_num()*2;
			//merge1 = vectores[0];
			//merge2 = vectores[1];
			//vectores.erase(vectores.begin());
			merge(vectores[my_Rank].begin(), vectores[my_Rank].end(), vectores[my_Rank + 1].begin(), vectores[my_Rank + 1].end(), resultado.begin());
#pragma omp critical
			vectores.push_back(resultado);
		}
#pragma omp barrier
		for (int j = 0; j < tCount*2; j++) {
			vectores.erase(vectores.begin());
		}
	}
	
	std::cout << "El resultado es: ";
	for (std::vector<int>::iterator it = vectores[0].begin(); it != vectores[0].end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';


	/*
	steady_clock::time_point t2 = steady_clock::now();
	std::cout << "Lista contiene:";
	for (std::vector<int>::iterator it = lista.begin(); it != lista.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << "Duracion " << time_span.count() << " segundos.";
	std::cout << std::endl;
	*/

	cin >> n;
	return 0;
}

bool validaCntHilos(int ch) {
	return ch >= 1;
}