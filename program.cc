/**
 * @mainpage Simulación del rendimiento de procesadores interconectados

En esta Practica se construira un programa modular que simulara el funcionamiento de una arquitectura multiprocesador, donde cada procesador trabaja exclusivamente con su propia memoria y puede ejecutar más de un proceso simultaneamiente

*/

/** @file program.cc
    @brief Programa principal de Simulación del rendimiento de procesadores interconectados
*/

#include "Cluster.hh"
#include "Area_de_espera.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;

int main() {
    Cluster c;
    c.configurar_cluster();
    Area_de_espera ma;
    ma.configurar_area();
    string comando;
    cin >> comando;
    while(comando != "fin") {
        if(comando == "bpp" or comando == "baja_proceso_procesador") {
            cout << '#' << comando;
            c.baja_proceso_procesador();
        }else if(comando == "app" or comando == "alta_proceso_procesador") {
            cout << '#' << comando;
            c.alta_proceso_procesador();
        }else if(comando == "at" or comando == "avanzar_tiempo") {
            cout << '#' << comando;
            c.avanzar_tiempo();
        }else if(comando == "cc" or comando == "configurar_cluster") {
            cout << '#' << comando << '\n';
            c.configurar_cluster();
        }else if(comando == "mc" or comando == "modificar_cluster") {
            cout << '#' << comando;
            c.modificar_cluster();
        }else if(comando == "ap" or comando == "alta_prioridad") {
            cout << '#' << comando;
            ma.alta_prioridad();
        }else if(comando == "bp" or comando == "baja_prioridad") {
            cout << '#' << comando;
            ma.baja_prioridad();
        }else if(comando == "ape" or comando == "alta_proceso_espera") {
            cout << '#' << comando;
            ma.alta_proceso_espera();
        }else if(comando == "epc" or comando == "enviar_procesos_cluster") {
            cout << '#' << comando;
            ma.enviar_procesos_cluster(c);
        }else if(comando == "ipri" or comando == "imprimir_prioridad") {
            cout << '#' << comando;
            ma.imprimir_prioridad();
        }else if(comando == "iae" or comando == "imprimir_area_espera") {
            cout << '#' << comando << '\n';
            ma.imprimir_area_espera();
        }else if(comando == "ipro" or comando == "imprimir_procesador") {
            cout << '#' << comando;
            c.imprimir_procesador();
        }else if(comando == "ipc" or comando == "imprimir_procesadores_cluster") {
            cout << '#' << comando << '\n';
            c.imprimir_procesadores_cluster();
        }else if(comando == "iec" or comando == "imprimir_estructura_cluster") {
            cout << '#' << comando << '\n';
            c.imprimir_estructura_cluster();
            cout << '\n';
        }else if(comando == "cmp" or comando == "compactar_memoria_procesador") {
            cout << '#' << comando;
            c.compactar_memoria_procesador();
        }else if(comando == "cmc" or comando == "compactar_memoria_cluster") {
            cout << '#' << comando << '\n';
            c.compactar_memoria_cluster();
        }
        cin >> comando;
    }
}
