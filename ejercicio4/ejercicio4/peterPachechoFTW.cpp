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
queue_lk <string> cola;

int main(int argc, char* argv[]) {
	int n, hConsumidores; //Hilos productores, Hilos consumidores
	int hProductores = 0;
	string lineaArchivo, archivo;
	int indice; // Número de archivo
	string linea;

	while (!validaCntHilos(hProductores)) {
		cout << "Digite la cantidad de Hilos Productores, los consumidores se asignarán según la nececidad ( >= 1 ): " << endl;
		cin >> hProductores; 
		cout << "Digite la cantidad de Hilos Consumidores ( >= 1 ): " << endl; // Si lo prueba con 3 hilos funciona más o menos
		cin >> hConsumidores;
		cout << endl;
	}

	//------------------------Lee un archivo para Productores en Paralelo---------------------------------------------

	string content; //Lo que se guarda en la pila
	int cont = 0;
	int cont2 = 0;
#	pragma omp parallel num_threads(hProductores) private(indice, content, linea) //Puse content como privada
	{
		indice = omp_get_thread_num();
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
		lectura.close();
	}

	cout << "Contador de rayan " << cont << endl;
	cout << "Contador " << cont2 << endl;
	cout << "Tamaño de la cola " << cola.size() << endl;

	/*cout << "Primero " << cola.front().msg << endl;
	cola.pop();
	cout << "Segundo " << cola.front().msg << endl;
	cola.pop();
	cout << "Tercero " << cola.front().msg << endl;
	cola.pop();
	cout << "Cuarto " << cola.front().msg << endl;
	cola.pop();
	cout << "Quinto " << cola.front().msg << endl;
	*/


#pragma omp parallel num_threads(hConsumidores)// private(lineaArchivo) 
	{

#	pragma omp critical
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
				
			while (getline(iss, token, ' ')) {
				cout << token << endl;
			}
		}
	}

	cin >> n;
	return 0;
}

bool validaCntHilos(int ch) {
	return ch >= 1;
}








//------------------------Tokenizador para consumidor-----------------------------------------------------------------
/*
	textoParcial = cola.front().msg;
	istringstream iss(textoParcial);
	string token;
	while (getline(iss, token, ' ')) {
		cout << token << endl;
	}
*/
//-----------------------------fin---------------------------------------------------


//------------------------Tokenizador para consumidor-----------------------------------------------------------------
/*
	textoParcial = cola.front().msg;
	istringstream iss(textoParcial);
	string token;
	while (getline(iss, token, ' ')) {
		cout << token << endl;
	}
*/
//-----------------------------fin---------------------------------------------------

//----------------------Guarda un archivo--------------------------------------------
/*
string numero = to_string(hProductores); // Convertir el número a String
string nombreArchivo = "arch" + numero + ".txt"; //Formar el nombre del archivo
ofstream nombre(nombreArchivo);
nombre << c << endl;
nombre.close();
*/
//----------------------------fin----------------------------------------------------

//----------------------Guarda un archivo--------------------------------------------
/*
string numero = to_string(hProductores); // Convertir el número a String
string nombreArchivo = "arch" + numero + ".txt"; //Formar el nombre del archivo
ofstream nombre(nombreArchivo);
nombre << c << endl;
nombre.close();
*/
//----------------------------fin----------------------------------------------------


