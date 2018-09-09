#include <stdlib.h>
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

	//------------------------Lee un archivo para Productores---------------------------------------------
	ifstream lectura;
	lectura.open("arch0.txt", ios::in);
	char c = lectura.get();
	string content; //Lo que se guarda en la pila
	while (lectura.good()) {
		content += c;
		c = lectura.get();
	} 
	cout << content << endl;

	//------------------------Tokenizador para consumidor-----------------------------------------------------------------
	istringstream iss(content);
	string token;
	while (getline(iss, token, ' ')) {
		cout << token << endl;
	}

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






	cin >> n;
	return 0;
}



bool validaCntHilos(int ch) {
	return ch >= 1;
}