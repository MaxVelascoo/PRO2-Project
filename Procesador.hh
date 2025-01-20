/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/

#ifndef _PROCESADOR_HH_
#define _PROCESADOR_HH_

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <set>
#include <map>
#endif
using namespace std;

/** @class Procesador
    @brief Representa un Procesador.

    Representa un Procesador el cual contiene una memoria en la que guardara y ejecutará los procesos
*/
class Procesador
{
private:
    /** @brief  Identificador del Procesador*/
    string idProcesador;
    /** @brief  El primer int es la longitud del hueco, el segundo int son todas las posiciones con esa longitud de hueco*/
    map<int,set<int>> mforats;
    /** @brief  */
    //map<int,int> mnom;
    map<int,int> mnoms; //El primer int es el idProceso y el segundo es la posicion
    /** @brief */
    map<int,Proceso> mp;
    /** @brief Longitud de la lista de memoria */
    int longmem;
    /** @brief Cantidad de memoria libre */
    int memolibre;

public:
    //Constructoras
/**
        @brief Creadora por defecto
        \pre <em>cierto</em>
        \post Crea un procesador
    */
    Procesador();

/**
        @brief Creadora por defecto
        \pre <em>cierto</em>
        \post Crea un procesador no vacío
    */
    Procesador(const int& longmem);

    //Consultoras

/**
        @brief Consulta si hay hueco libre en la memoria
        \pre memoutilizada diferente de 0
        \post True si hay un hueco libre donde quepa el proceso, false en caso contrario
    */
    bool hueco(const int& memoutilizada);

/**
        @brief Consulta si existe ese proceso
        \pre idPro no vacío
        \post True si existe un Proceso con dicho identificador, false en case contrario
    */
    bool buscar_proceso(const int& idPro);

/**
        @brief Consulta si el Procesador tiene algun proceso pendiente
        \pre <em>cierto</em>
        \post True si hay algun Proceso pendiente, false en caso contrario
    */
    bool tiene_procesos() const;

/**
        @brief Consulta la posicion en la memoria de un Proceso
        \pre idPro no vacío
        \post True si el Proceso existe, false en case contrario.
    */
    int consultar_pos_mapa(const int& idPro);

/**
        @brief Consulta el hueco mas reducido donde quepa el Proceso
        \pre memoutilizada no vacía
        \post El resultado es la medida del hueco mas ajustado
    */
    int hueco_optimo(const int& memoutilizada);

/**
        @brief Consulta la cantidad de memoria libre que queda en Procesador
        \pre <em>cierto</em>
        \post El resultado es la cantidad de memoria libre que queda
    */
    int consultar_memolibre() const;

    //Modificadoras
/**
        @brief Inserta un nuevo proceso en el Procesador
        \pre Proceso no vacío
        \post El resultado es que ha sido agregado un nuevo Proceso al Procesador
    */
    void insertar_proceso_mapa(const Proceso& pro, const int& idProceso, const int& memoutilizada);


/**
        @brief Compacta la memoria de un Procesador
        \pre <em>cierto</em>
        \post El resultado es que la memoria de dicho Procesador ha sido compactada
    */
    void compactar_memoria();

/**
        @brief Borra un Proceso del mapa
        \pre Pos y idProceso no vacío
        \post El resultado es que ha sido borrado un Proceso del mapa
    */
    void borrar_proceso_mapa(const int& pos, const int& idProceso);

/**
        @brief Modifica la posicion de un Proceso
        \pre idProceso y pos no vacíos
        \post El resultado es que la posicion ha sido modificada
    */
    void modificar_pos(const int& idProceso, const int& pos);

/**
        @brief Borra un proceso del mapa de Procesos
        \pre Pos no vacío
        \post El resultado es que ha sido borrado un proceso del mapa de Procesos
    */
    void borrar_mp(const int& pos);

/**
        @brief Avanza el tiempo de los Procesos de dicho Procesador
        \pre t diferente de 0
        \post El tiempo ha sido adelantado
    */
    void avanzar_tiempo_procesos(const int& t);

    //Escritura

/**
        @brief Imprime todos los Procesos de un Procesador
        \pre <em>cierto</em>
        \post El resultado es que los Procesos han sido impresos
    */
    void imprimir_procesos_mapa() ;

private:
};
#endif
