/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() {
  // Inicializa un proceso vacío
}

Proceso::Proceso(const int& idPro, const int& memo, const int& t) {
    idProceso = idPro;
    memoutilizada = memo;
    temps = t;
}

void Proceso::configurar_Proceso() {
    cin >> idProceso;
    cin >> memoutilizada;
    cin >> temps;
}

void Proceso::imprimir_proceso() {
    cout << idProceso << " " << memoutilizada << " " << temps << '\n';
}

int Proceso::consultar_idProceso() const{
    return idProceso;
}

int Proceso::consultar_memoutilizada() const{
    return memoutilizada;
}

int Proceso::consultar_temps() const{
    return temps;
}

void Proceso::modificar_tiempo(const int& t) {
    temps = temps - t;
}
