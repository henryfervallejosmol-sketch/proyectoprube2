#include "facturas.h"
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

void generarFactura() {
    string cedula, mes;
    int minutos, plan;
    float total;
    const float EXTRA = 0.10;

    cout << "Cedula: ";
    cin >> cedula;
    cout << "Mes: ";
    cin >> mes;

    cout << "Plan (1 Basico / 2 Plus): ";
    cin >> plan;
    cout << "Minutos usados: ";
    cin >> minutos;

    if (plan == 1)
        total = (minutos <= 200) ? 10 : 10 + (minutos - 200) * EXTRA;
    else if (plan == 2)
        total = (minutos <= 180) ? 15 : 15 + (minutos - 180) * EXTRA;
    else {
        cout << "Plan invalido.\n";
        return;
    }

    ofstream archivo("facturas.csv", ios::app);
    archivo << cedula << "," << mes << "," << minutos << "," << total << ",PENDIENTE\n";
    archivo.close();

    cout << "Factura generada. Total: $" << total << endl;
}

void mostrarFacturas() {
    ifstream archivo("facturas.csv");
    string linea;
    cout << "\n--- FACTURAS ---\n";
    while (getline(archivo, linea))
        cout << linea << endl;
    archivo.close();
}

void mostrarFacturasCliente(string cedula) {
    ifstream archivo("facturas.csv");
    string linea;
    cout << "\n--- MIS FACTURAS ---\n";
    while (getline(archivo, linea)) {
        if (linea.find(cedula + ",") == 0)
            cout << linea << endl;
    }
    archivo.close();
}

void verFacturasPagadas() {
    ifstream archivo("facturas.csv");
    string linea;
    cout << "\n--- FACTURAS PAGADAS ---\n";
    while (getline(archivo, linea)) {
        if (linea.find("PAGADO") != string::npos)
            cout << linea << endl;
    }
    archivo.close();
}

void pagarFactura(string cedula) {
    ifstream archivo("facturas.csv");
    ofstream temp("temp.csv");
    string linea, mes;
    bool pagado = false;

    cout << "Mes a pagar: ";
    cin >> mes;

    string tarjeta;
    int cvv;
    cout << "Numero tarjeta: ";
    cin >> tarjeta;
    cout << "CVV: ";
    cin >> cvv;

    while (getline(archivo, linea)) {
        if (linea.find(cedula + "," + mes) == 0 && linea.find("PENDIENTE") != string::npos) {
            linea.replace(linea.find("PENDIENTE"), 9, "PAGADO");
            pagado = true;
        }
        temp << linea << endl;
    }

    archivo.close();
    temp.close();
    remove("facturas.csv");
    rename("temp.csv", "facturas.csv");

    cout << (pagado ? "Pago realizado correctamente.\n" : "Factura no encontrada.\n");
}

