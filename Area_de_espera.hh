/** @file Area_de_espera.hh
    @brief Especificación de la clase Area_de_espera
*/

#ifndef _AREA_DE_ESPERA_HH_
#define _AREA_DE_ESPERA_HH_

#include "Proceso.hh"
#include "Cluster.hh"


#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#include <map>
#endif
using namespace std;

/** @class Area_de_espera
    @brief Representa un Area_de_espera.
    Representa un Area de espera que contiene los procesos pendientes.
*/

/** @brief Es la prioridad que gestiona los Procesos del Area de espera */
struct prioridad {
    /** @brief Numero de Procesos aceptados por el Cluster*/
    int acept = 0;
    /** @brief Numero de Procesos rechazados por el Cluster*/
    int rechaz = 0;
    /** @brief Lista de Procesos*/
    list<Proceso> lp;
    /** @brief Set con los identificadores de los Procesos*/
    set<int> sp;
};

class Area_de_espera {
private:

    /** @brief Mapa de Prioridades */
    map<string,prioridad> ma;

public:

    //Constructoras
/**
        @brief Creadora por defecto
        \pre <em>cierto</em>
        \post Crea un Area de espera sin prioridades
    */
    Area_de_espera();

/**
        @brief Lee los datos del Area de espera
        Añade las prioridades que se indiquen al area de espera
        \pre <em>cierto</em>
        \post El resultado es un Area de espera con una o mas prioridades
    */
    void configurar_area();

    //Modificadoras

/**
        @brief Añade una prioridad al Area de espera
        \pre <em>cierto</em>
        \post Si cumple los requisitos, el resultado es que se ha añadido una nueva prioridad al Area de espera
    */
    void alta_prioridad();

/**
        @brief Elimina una prioridad del Area de espera
        \pre <em>cierto</em>
        \post Si cumple los requisitos, el resultado es que se ha eliminado dicha prioridad del area de espera
    */
    void baja_prioridad();

/**
        @brief Añade un Proceso al Area de espera
        \pre <em>cierto</em>
        \post Si cumple los requisitos, el resultado es que se ha añadido un proceso al area de espra con dicha prioridad
    */
    void alta_proceso_espera();

/**
        @brief Envia n Procesos al cluster
        \pre n > 0
        \post El resultado es que se han intentado enviar n Procesos al cluster por orden de prioridad, y por orden de antiguedad
    */
    void enviar_procesos_cluster(Cluster& c);

    //Escritura del Area_de_espera
/**
        @brief Imprime los Procesos pendientes de dicha prioridad
        \pre <em>cierto</em>
        \post El resultado es que se han impreso los procesos pendientes de dicha prioridad, numero de rechazos y aceptados y procesos de dicha Prioridad
    */
    void imprimir_prioridad() ;

/**
        @brief Imprime todos los Procesos pendientes del Area de espera
        \pre <em>cierto</em>
        \post El resultado es que se han iumpreso todos los Procesos pendientes del area de espera por orden creciente de prioridad.
    */
    void imprimir_area_espera() ;

private:

};
#endif
