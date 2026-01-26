#include <iostream>
#include "clientes.h"
#include "menus.h"

using namespace std;

int main() {
    int rol;
    string cedula;

    do {
        cout << "\n=== TELEFONIA FIJA ===\n";
        cout << "1. Administrador\n";
        cout << "2. Usuario\n";
        cout << "0. Salir\n";
        cin >> rol;

        if (rol == 1)
            menuAdministrador();
        else if (rol == 2) {
            cout << "Cedula: ";
            cin >> cedula;
            if (validarCliente(cedula))
                menuUsuario(cedula);
            else
                cout << "Cliente no existe.\n";
        }
    } while (rol != 0);

    return 0;
}

