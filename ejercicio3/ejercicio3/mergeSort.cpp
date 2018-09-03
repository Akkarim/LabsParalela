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

#  pragma omp parallel for num_threads(tCount) 
	for (int i = 0; i < data_count; i++) {
		aleatorios.push_back(rand() % 100);
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
	std::cout << '\n';

	int i2, f2;
	int mitad = data_count / 2;

	vector<int> resultado;
	resultado.reserve(data_count);
	local_final = local_n;
	for (int i = 0; i < tCount-1; i++) {
		i2 = local_n * i;
		f2 = local_n + i2;
		merge((aleatorios.begin()),(aleatorios.begin()+mitad),(aleatorios.begin()+mitad),(aleatorios.end()),(aleatorios.begin()));
	//	merge((aleatorios.begin()), (aleatorios.begin() + local_final), (aleatorios.begin() + i2), (aleatorios.begin() + f2), aleatorios.begin());
		local_final = f2;
	}
//#endif
	


	std::cout << "Lista contiene:";
	for (std::vector<int>::iterator it = aleatorios.begin(); it != aleatorios.end(); ++it)
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


	cout << aleatorios[2];

	cin >> n;
	return 0;
}

bool validaCntHilos(int ch) {
	return ch >= 1;
}
/*
void AlgoritmosIndexada::mergeSort(lista& l, int inicio, int final) {
	if (inicio < final) {
		int cantElem = 0;
		int min = inicio;
		int max = final;
		while (min <= max) {
			cantElem++;
			min++;
		}
		cantElem = cantElem / 2;
		int mitad = (inicio - 1) + cantElem;
		mergeSort(l, inicio, mitad);
		mergeSort(l, mitad + 1, final);

		merge(l, inicio, mitad, final);
	}
}

void AlgoritmosIndexada::merge(lista& l, int inicio, int medio, int final) {
	lista l2;
	l2.iniciar();
	int insertar = 1;
	for (int i = inicio; i <= final; i++) {
		l2.insertar(l.recuperar(i), insertar);
		insertar++;
	}

	int i = 1;
	int j = (medio%l2.numElem()) + 1;
	int mitad = medio % l2.numElem();
	int max = l2.numElem();
	int k = inicio;

	while (i <= mitad && j <= max) {
		if (l2.recuperar(i) <= l2.recuperar(j)) {
			l.modificarElem(l2.recuperar(i), k);
			i++;
		}
		else {
			l.modificarElem(l2.recuperar(j), k);
			j++;
		}
		k++;
	}
	while (i <= mitad) {
		l.modificarElem(l2.recuperar(i), k);
		i++;
		k++;
	}
	while (j <= max) {
		l.modificarElem(l2.recuperar(j), k);
		j++;
		k++;
	}
}
*/