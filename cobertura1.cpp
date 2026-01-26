#include "cobertura.h"
#include <iostream>
#include <fstream>

using namespace std;

void registrarCobertura() {
    string zona, distrito, circuito;
    cout << "Zona: ";
    cin >> zona;
    cout << "Distrito: ";
    cin >> distrito;
    cout << "Circuito: ";
    cin >> circuito;

    ofstream archivo("cobertura.csv", ios::app);
    archivo << zona << "," << distrito << "," << circuito << endl;
    archivo.close();

    cout << "Cobertura registrada.\n";
}

void mostrarCobertura() {
    ifstream archivo("cobertura.csv");
    string linea;
    cout << "\n--- COBERTURA ---\n";
    while (getline(archivo, linea))
        cout << linea << endl;
    archivo.close();
}

