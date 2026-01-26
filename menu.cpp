#include "menus.h"
#include "clientes.h"
#include "facturas.h"
#include "cobertura.h"
#include <iostream>

using namespace std;

void menuAdministrador() {
    int op;
    do {
        cout << "\n--- MENU ADMIN ---\n";
        cout << "1. Registrar cliente\n";
        cout << "2. Mostrar clientes\n";
        cout << "3. Actualizar cliente\n";
        cout << "4. Eliminar cliente\n";
        cout << "5. Generar factura\n";
        cout << "6. Ver facturas\n";
        cout << "7. Ver facturas pagadas\n";
        cout << "8. Registrar cobertura\n";
        cout << "9. Mostrar cobertura\n";
        cout << "0. Volver\n";
        cin >> op;

        switch (op) {
            case 1: registrarCliente(); break;
            case 2: mostrarClientes(); break;
            case 3: actualizarCliente(); break;
            case 4: eliminarCliente(); break;
            case 5: generarFactura(); break;
            case 6: mostrarFacturas(); break;
            case 7: verFacturasPagadas(); break;
            case 8: registrarCobertura(); break;
            case 9: mostrarCobertura(); break;
        }
    } while (op != 0);
}

void menuUsuario(string cedula) {
    int op;
    do {
        cout << "\n--- MENU USUARIO ---\n";
        cout << "1. Ver mis datos\n";
        cout << "2. Ver mis facturas\n";
        cout << "3. Pagar factura\n";
        cout << "0. Volver\n";
        cin >> op;

        switch (op) {
            case 1: buscarCliente(cedula); break;
            case 2: mostrarFacturasCliente(cedula); break;
            case 3: pagarFactura(cedula); break;
        }
    } while (op != 0);
}

