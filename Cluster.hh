/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#include "Procesador.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include "BinTree.hh"
#include <list>
#include <map>
#endif
using namespace std;

/** @class Cluster
    @brief Representa un cluster.
    Representa un Cluster que contiene un numero variable de Procesadores, distribuidos en forma de arbol binario, con identificadores.
*/

/** @brief Es el Procesador candidato donde colocaremos el Proceso */
struct Candidato {
    /** @brief identificador del Procesador*/
    string idPro;
    /** @brief Tamaño del hueco mas ajustado*/
    int hueco = 0;
    /** @brief Cantidad de memoria libre*/
    int memolibre = 0;
    /** @brief Profundidad que tiene en el arbol*/
    int prof = 0;
    /** @brief Proporciona si es posible candidato o no*/
    bool posible;
};

class Cluster {
private:
    /** @brief Mapa de Procesadores */
    map <string,Procesador> mc;
    /** @brief Arbol Cluster del identificador del Procesador */
    BinTree <string> c;

public:
  //Constructoras

/**
        @brief Creadora por defecto
        \pre <em>cierto</em>
        \post Crea un cluster vacío
    */
    Cluster();

/**
        @brief Lee los datos del Cluster
        Añade al cluster los identificadores de los Procesadores en forma de arbol binario y en el mapa de procesadores
        \pre <em>cierto</em>
        \post El resultado es un Cluster con uno o mas Procesadores
    */
    void configurar_cluster();

  //Modificadoras

/**
        @brief Modifica el Cluster a partir de p
        \pre <em>cierto</em>
        \post El resultado es que el Cluster ha sido modificado, ya que donde estaba el Procesador p ahora esta el nuevo arbol proporcionado
    */
    void modificar_cluster();


/**
        @brief El tiempo se avanza
        \pre t > 0
        \post El resultado es que el tiempo ha sido avanzado, y han sido eliminados los Procesos que ya hayan acabado en ese periódo de tiempo
    */
    void avanzar_tiempo();

/**
        @brief Compacta la memoria del Procesador
        \pre <em>cierto</em>
        \post El resultado es que la memoria ha sido compactada, todos los procesos han sido movidos a la izquierda, sin solaparse, sin dejar huecos y respetando el orden inicial
    */
    void compactar_memoria_procesador();

/**
        @brief Compacta la memoria de todos los Procesadores
        \pre <em>cierto</em>
        \post El resultado es que todas las memorias han sido compactadas, todos los procesos han sido movidos a la izquierda, sin solaparse, sin dejar huecos y respetando el orden inicial
    */
    void compactar_memoria_cluster();

/**
        @brief Añade un Proceso al Procesador
        \pre <em>cierto</em>
        \post Si cumple los requisitos, ha sido añadido dicho Proceso al Procesador
    */
    void alta_proceso_procesador();

/**
        @brief Elimina un Proceso del Procesador
        \pre <em>cierto</em>
        \post Si cumple los requisitos, ha sido eliminado dicho Proceso del Procesador
    */
    void baja_proceso_procesador();

/**
        @brief Envia un Proceso al Procesador candidato
        \pre <em>cierto</em>
        \post Si cumple los requisitos, el Proceso ha sido añadido al Procesador con las mejores condiciones
    */
    void enviar_proceso(const Proceso& proceso, bool& found);

  // Consultoras

/**
        @brief Compara un Procesador con su Procesador auxiliar
        \pre <em>cierto</em>
        \post El resultado es true si el Procesador auxiliar es mejor que su Procesador antecesor, false en caso contrario
    */
    bool hijo_mejor_raiz(const Candidato& rizq, const Candidato& r) const;

  // Escritura del Cluster

/**
        @brief Imprime los Procesos de un Procesador
        \pre <em>cierto</em>
        \post Imprime todos los Procesos de dicho procesador por orden creciente de primera posición de memoria
    */
    void imprimir_procesador();

/**
        @brief Imprime todos los Procesadores y sus Procesos
        \pre <em>cierto</em>
        \post Imprime todos los Procesadores del cluster por orden creciente de identificador, y todos sus procesos.
    */
    void imprimir_procesadores_cluster();

/**
        @brief Imprime la estructura del arbol Cluster
        \pre <em>cierto</em>
        \post El resultado es que se han impreso los identificadores de los procesadores que estan en el arbol del cluster en preorden
    */
    void imprimir_estructura_cluster() const;

private:
/**
        @brief Imprime la estructura del arbol Cluster
        \pre Arbol no vacío
        \post El resultado es que se ha impreso el arbol cluster en preorden
    */
    void imprimir_cluster(const BinTree<string>& c) const;

/**
        @brief Lee el arbol cluster y el mapa de Procesadores
        \pre Arbol no vacío
        \post El resultado es un Cluster con uno o mas Procesadores
    */
    void leercluster(BinTree<string>& c);

/**
        @brief Modifica el Cluster
        \pre Arbol no vacío
        \post El resultado es que ha sido modificado el arbol cluster a partir del Procesador con identificador p
    */
    void anadir_cluster(BinTree<string>& c, const string& p);

/**
        @brief Encuentra el mejor Procesador
        \pre Arbol no vacío
        \post El resultado es el Procesador con las mejores condiciones de todo el Cluster
    */
    Candidato encontrar_procesador(const BinTree<string>& c, int memoutilizada, int profundidad, int idProceso);

};
#endif
