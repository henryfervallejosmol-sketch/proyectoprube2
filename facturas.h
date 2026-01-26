#ifndef FACTURAS_H
#define FACTURAS_H

#include <string>
using namespace std;

void generarFactura();
void mostrarFacturas();
void mostrarFacturasCliente(string cedula);
void pagarFactura(string cedula);
void verFacturasPagadas();

#endif

