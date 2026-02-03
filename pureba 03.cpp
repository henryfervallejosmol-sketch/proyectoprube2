#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

/* ================= CLIENTES ================= */
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
    string cedula, nuevaLinea, nuevoPlan, nombre;
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

/* ================= FACTURAS ================= */
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
            int pos = linea.find("PENDIENTE");
            linea.replace(pos, 9, "PAGADO");
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

/* ================= COBERTURA ================= */
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

/* ================= MENUS ================= */
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

/* ================= MAIN ================= */
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



