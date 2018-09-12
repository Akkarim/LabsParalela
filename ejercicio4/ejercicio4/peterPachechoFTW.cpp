//#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <omp.h>
#include <math.h>
#include <random>
#include <algorithm>
#include <sstream>
#include"queue_lk.h"
//#include <yourself>
//#include <love>

using namespace std;

bool validaCntHilos(int ch);
bool find(vector<int> vector, int id);
queue_lk <string> cola;

int main(int argc, char* argv[]) {
	int n, hConsumidores; //Hilos productores, Hilos consumidores
	int hProductores = 0;
	string lineaArchivo, archivo;
	int indice; // Número de archivo
	string linea;

	while (!validaCntHilos(hProductores)) {
		cout << "Digite la cantidad de Hilos Productores ( >= 1 ): " << endl;
		cin >> hProductores;
		cout << "Digite la cantidad de Hilos Consumidores ( >= 1 ): " << endl; // Si lo prueba con 3 hilos funciona más o menos
		cin >> hConsumidores;
		cout << endl;
	}
	//---------------------------Asignar hilos--------------------------------------------------------------
	vector<int> productores;
	vector<int> consumidores;
	indice = hProductores + hConsumidores;
	productores.reserve(hProductores);
	consumidores.reserve(hConsumidores);

	for (int i = 0; i < indice; i++) {
		if (i < hProductores) {
			productores.push_back(i);
		}
		else if (i >= hProductores && i < indice) {
			consumidores.push_back(i);
		}
	}

	std::cout << "El Productores es: ";
	for (std::vector<int>::iterator it = productores.begin(); it != productores.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "El consumidores es: ";
	for (std::vector<int>::iterator it = consumidores.begin(); it != consumidores.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//indice = 0;
	//------------------------Lee un archivo para Productores en Paralelo---------------------------------------------

	string content; //Lo que se guarda en la pila
	int cont = 0;
	int cont2 = 0;
#	pragma omp parallel num_threads(hProductores+hConsumidores) private(content, linea) //Puse content como privada
	{
		indice = omp_get_thread_num();
		if (find(productores, indice)) {
			ifstream lectura;
			lectura.open("arch" + to_string(indice) + ".txt", ios::in);
			char c = lectura.get();
			while (lectura.good()) { // Funciona casi como good hay que ver cuál funciona mejor
				if (c == '.') { // Con \n no estaba funcando, se puede poner otra flag o mejorar
					cont++;
#	pragma omp critical
					{
						linea = content;
						cola.push(linea);
						content = "";
						linea.clear(); // Para separar las líneas
					}
					c = lectura.get();
				}
				else {
					cont2++;
					content += c;
					c = lectura.get();
				}
			}
			//---------------------------------------------Consumidores-----------------------------------------------------
			if (find(consumidores, indice)) {
				while (!cola.empty()) {
					if (cola.size() == 1) { //Si se pone <= cambia el comportamiento
						cola.set_lock();
						lineaArchivo = cola.front().msg;
						cola.pop();
						cola.unset_lock();
					}
					else {
						lineaArchivo = cola.front().msg;
						cola.pop();
					}
					istringstream iss(lineaArchivo);
					string token;
#	pragma omp critical
					{
						while (getline(iss, token, ' ')) {
							cout << token << endl;
						}
						cout << "Impreso por el hilo: " << indice << endl;
					}
				}
			}
			//---------------------------------------------Consumidores-----------------------------------------------------
		}

	}

	cout << "Contador de rayan " << cont << endl;
	cout << "Contador " << cont2 << endl;
	cout << "Tamaño de la cola " << cola.size() << endl;

	cin >> n;
	return 0;
}

bool validaCntHilos(int ch) {
	return ch >= 1;
}

bool find(vector<int> vector, int id) {
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] == id) {
			return true;
		}
	}
	return false;
}