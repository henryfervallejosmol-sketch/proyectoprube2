//cliente cpp
#include "clientes.h"
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

bool validarCliente(string cedulaBuscar) {
    ifstream archivo("clientes.csv");
    string linea;
    while (getline(archivo, linea)) {
        if (linea.find(cedulaBuscar + ",") == 0) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

void registrarCliente() {
    string cedula, nombre, linea, plan;
    int op;

    cout << "Cedula: ";
    cin >> cedula;

    if (validarCliente(cedula)) {
        cout << "Cliente ya existe.\n";
        return;
    }

    cout << "Nombre: ";
    cin >> nombre;
    cout << "Linea: ";
    cin >> linea;

    cout << "1. Basico ($10 - 200 min)\n";
    cout << "2. Plus   ($15 - 180 min)\n";
    cout << "Plan: ";
    cin >> op;

    if (op == 1) plan = "Basico";
    else if (op == 2) plan = "Plus";
    else {
        cout << "Plan invalido.\n";
        return;
    }

    ofstream archivo("clientes.csv", ios::app);
    archivo << cedula << "," << nombre << "," << linea << "," << plan << endl;
    archivo.close();

    cout << "Cliente registrado correctamente.\n";
}

void mostrarClientes() {
    ifstream archivo("clientes.csv");
    string linea;
    cout << "\n--- CLIENTES ---\n";
    while (getline(archivo, linea))
        cout << linea << endl;
    archivo.close();
}

void buscarCliente(string cedula) {
    ifstream archivo("clientes.csv");
    string linea;
    while (getline(archivo, linea)) {
        if (linea.find(cedula + ",") == 0) {
            cout << linea << endl;
            archivo.close();
            return;
        }
    }
    archivo.close();
    cout << "Cliente no encontrado.\n";
}

void actualizarCliente() {
    string cedula, nombre, nuevaLinea, nuevoPlan;
    int op;

    cout << "Cedula del cliente: ";
    cin >> cedula;

    if (!validarCliente(cedula)) {
        cout << "Cliente no existe.\n";
        return;
    }

    cout << "Nuevo nombre: ";
    cin >> nombre;
    cout << "Nueva linea: ";
    cin >> nuevaLinea;

    cout << "1. Basico\n2. Plus\nNuevo plan: ";
    cin >> op;

    if (op == 1) nuevoPlan = "Basico";
    else if (op == 2) nuevoPlan = "Plus";
    else {
        cout << "Plan invalido.\n";
        return;
    }

    ifstream archivo("clientes.csv");
    ofstream temp("temp.csv");
    string linea;

    while (getline(archivo, linea)) {
        if (linea.find(cedula + ",") == 0)
            temp << cedula << "," << nombre << "," << nuevaLinea << "," << nuevoPlan << endl;
        else
            temp << linea << endl;
    }

    archivo.close();
    temp.close();
    remove("clientes.csv");
    rename("temp.csv", "clientes.csv");

    cout << "Cliente actualizado correctamente.\n";
}

void eliminarCliente() {
    string cedula;
    cout << "Cedula a eliminar: ";
    cin >> cedula;

    ifstream archivo("clientes.csv");
    ofstream temp("temp.csv");
    string linea;
    bool eliminado = false;

    while (getline(archivo, linea)) {
        if (linea.find(cedula + ",") != 0)
            temp << linea << endl;
        else
            eliminado = true;
    }

    archivo.close();
    temp.close();
    remove("clientes.csv");
    rename("temp.csv", "clientes.csv");

    cout << (eliminado ? "Cliente eliminado.\n" : "Cliente no encontrado.\n");
}

