#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <math.h>
#include <iostream>
#include <omp.h>


using namespace std;
#pragma warning(disable : 4996)

bool validaCntHilos(int ch);

int main(int argc, char* argv[]) {
	//default_random_engine generator;
	//uniform_real_distribution<double> distribution(-1, 1);

	double aciertosGlobales = 0.0; //Aciertos globales

	double x = 0.0;
	double y = 0.0;
	double resultado = 0.0;

	int tCount = 0; //Thread Count
	int intentos = 0; //Intentos

	while (!validaCntHilos(tCount)) {
		cout << "Digite la cantidad de hilos ( >= 1 ): ";
		cin >> tCount;
		cout << endl;
		cout << "Digite la cantidad de Intentos: ";
		cin >> intentos;
		cout << endl;
	}

	//# pragma omp parallel private(x, y)
	 //{
#  pragma omp parallel for num_threads(tCount) 
	for (int i = 0; i <= intentos - 1; i++) {
		//x = distribution(generator);
		x = ((double)rand() / (RAND_MAX + 1) + (rand() % 2) - 1.0);

		y = ((double)rand() / (RAND_MAX + 1) + (rand() % 2) - 1.0);
		//y = distribution(generator); 


# pragma omp critical
		{
			if (((x*x) + (y*y)) <= 1) {
				aciertosGlobales++;
			}
		}
		//cout << "X es " << x << endl;
		//cout << "y es " << y << endl;
	}
	//cout << aciertosGlobales << endl;
	//}


	resultado = 4 * (aciertosGlobales) / ((double)intentos);

	cout << "La aproximacion es:  " << resultado << " con " << aciertosGlobales << " aciertos." << endl;

	int final = 0;
	cin >> final;
	return 0;
}

bool validaCntHilos(int ch) {
	return ch >= 1;
}