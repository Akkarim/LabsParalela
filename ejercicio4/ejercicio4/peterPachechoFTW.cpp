#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <omp.h>
#include <math.h>
#include <random>
#include <algorithm>
//#include"queue_lk.h"
//#include <yourself>
//#include <love>

using namespace std;

bool validaCntHilos(int ch);

int main(int argc, char* argv[]) {
	int n, hConsidores; //Hilos productores, Hilos consumidores
	int hProductores = 0;

	while (!validaCntHilos(hProductores)) {
		cout << "Digite la cantidad de Hilos Productores ( >= 1 ): " << endl;
		cin >> hProductores;
		cout << "Digite la cantidad de Hilos Consumidores ( >= 1 ): " << endl;
		cin >> hConsidores;
		cout << endl;
	}







	cin >> n;
	return 0;
}



bool validaCntHilos(int ch) {
	return ch >= 1;
}