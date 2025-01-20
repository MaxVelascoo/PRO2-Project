/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef _PROCESO_HH_
#define _PROCESO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;

/** @class Proceso
    @brief Representa un Proceso.

    Representa un Proceso el cual contiene un identificador, la cantidad de memoria estimada que va a necesitar para ejecutarse y el tiempo estimado de ejecucion.
*/
class Proceso {

private:
    /** @brief Identificador del proceso */
    int idProceso;
    /** @brief Memoria utilizada por el proceso */
    int memoutilizada;
    /** @brief Tiempo usado para ejecutar el proceso */
    int temps;
public:
    //Constructoras

/**
        @brief Creadora por defecto
        \pre <em>cierto</em>
        \post Crea un proceso vacío
    */
    Proceso();

/**
        @brief Creadora por defecto
        \pre <em>cierto</em>
        \post Crea un Proceso no vacío
    */
    Proceso(const int& idPro, const int& memo, const int& t);


/**
        @brief Lee los datos del proceso
        Añade al Proceso su identificador, su tiempo de ejecucion y su memoria que utilizará
        \pre <em>cierto</em>
        \post El resultado es un Proceso no vacío
    */
    void configurar_Proceso();

    //Consultoras

/**
        @brief Consulta el identificador del parametro implícito
        \pre <em>cierto</em>
        \post El resultado es el identificador del Proceso
    */
    int consultar_idProceso() const;

/**
        @brief Consulta la memoria utilizada por el parametro implícito
        \pre <em>cierto</em>
        \post El resultado es la memoria utilizada por el parametro implícito
    */
    int consultar_memoutilizada() const;

/**
        @brief Consulta el tiempo que dura el parametro implícito
        \pre <em>cierto</em>
        \post El resultado es el tiempo que dura el parametro implícito
    */
    int consultar_temps() const;

    //Modificadoras

/**
        @brief Modifica el tiempo del parametro implícito
        \pre <em>cierto</em>
        \post El tiempo del parametro implícito ha sido modificado
    */
    void modificar_tiempo(const int& t);

    //Escritura del Proceso

/**
        @brief Imprime los datos de un Proceso
        \pre <em>cierto</em>
        \post Se han impreso los datos de dicho Proceso
    */
    void imprimir_proceso();
};
#endif
