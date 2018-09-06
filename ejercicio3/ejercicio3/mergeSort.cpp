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
vector<int> resultado(100, 0);

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
	aleatorios.reserve(data_count);
	local_n = data_count / tCount;
	int k = 0;

//#  pragma omp parallel for num_threads(tCount) private(k) //Lo Hace "bien" pero cada hilo genera el mismo número entonces :c
	for (int i = 0; i < data_count; i++) {
		k = rand() % 100 + 1;
//#	pragma omp critical
		cout << k << endl;
		aleatorios.push_back(k);
	}

#pragma omp parallel num_threads(tCount) private(local_inicio,local_final,my_Rank)
	{
		my_Rank = omp_get_thread_num();
		local_inicio = local_n * my_Rank;
		local_final = local_n + local_inicio;
		sort((aleatorios.begin() + local_inicio), (aleatorios.begin() + local_final));
	}

	std::cout << "Lista contiene:";
	for (std::vector<int>::iterator it = aleatorios.begin(); it != aleatorios.end(); ++it)
		std::cout << ' ' << *it;
	cout << '\n';

	int i2, f2;
	int mitad = aleatorios.size()/ 2;
	resultado.reserve(data_count);
	//cout << resultado.size << endl;
	local_final = local_n;

	/*
	std::vector<int>::iterator iti = aleatorios.begin();
	cout << "El inicio es " << *iti << endl;
	vector<int>::iterator itm = aleatorios.begin() + mitad + 1;
	cout << "La mitad es " << *itm << endl;
	*/

	//merge((aleatorios.begin()), (aleatorios.begin() + mitad), (aleatorios.begin() + mitad), (aleatorios.end()), resultado.begin());

	for (int i = 1; i < tCount-1; i++) {
		i2 = local_n * i;
		f2 = local_n + i2;
	//	merge((aleatorios.begin()),(aleatorios.begin()+mitad),(aleatorios.begin()+mitad),(aleatorios.end()),(aleatorios.begin()));
		merge((aleatorios.begin()), (aleatorios.begin() + local_final), (aleatorios.begin() + i2), (aleatorios.begin() + f2), resultado.begin());
		local_final = f2;
	}
	
	std::cout << "El resultado es: ";
	for (std::vector<int>::iterator it = resultado.begin(); it != resultado.end(); ++it)
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