/** @file Area_de_espera.cc
    @brief Código de la clase Area_de_espera
*/

#include "Area_de_espera.hh"

Area_de_espera::Area_de_espera() {
// Inicializa un Area_de_espera vacío
}

void Area_de_espera::configurar_area() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        string id;
        cin >> id;
        ma[id];
    }
}

void Area_de_espera::alta_prioridad(){
    string id;
    cin >> id;
    cout << " " << id << '\n'; //ECO
    map<string,prioridad>::const_iterator it = ma.find(id);
    if(it != ma.end()) cout << "error: ya existe prioridad" << '\n';
    else {
        ma[id];
    }
}

void Area_de_espera::baja_prioridad() {
    string id;
    cin >> id;
    cout << " " << id << '\n'; //ECO
    map<string,prioridad>::const_iterator it = ma.find(id);
    if(it == ma.end()) cout << "error: no existe prioridad" << '\n';
    else if(not it->second.lp.empty()) cout << "error: prioridad con procesos" << '\n';
    else {
        ma.erase(it);
    }
}

void Area_de_espera::alta_proceso_espera() {
    string id;
    int idPro;
    int memoutilizada, temps;
    cin >> id >> idPro >> memoutilizada >> temps;
    cout << " " << id << " " << idPro << '\n'; //ECO
    map<string,prioridad>::iterator it = ma.find(id);
    if(it == ma.end()) cout << "error: no existe prioridad" << '\n';
    else {
        set<int>::iterator it2 = it->second.sp.find(idPro);
        if(it2 != it->second.sp.end()) cout << "error: ya existe proceso" << '\n';
        else {
            Proceso pro(idPro,memoutilizada,temps);
            it->second.lp.insert(it->second.lp.end(), pro);
            it->second.sp.insert(idPro);
        }
    }
}

void Area_de_espera::enviar_procesos_cluster(Cluster& c) {
    int n;
    cin >> n;
    cout << " " << n << '\n'; //ECO
    map<string,prioridad>::iterator it = ma.begin();
    while(n > 0 and it != ma.end()) {
        list<Proceso>::iterator it2 = it->second.lp.begin();
        int lsize = it->second.lp.size();
        int i = 0;
        while(n > 0 and i < lsize) {
            bool found = false;
            Proceso pro = *it2;
            c.enviar_proceso(pro,found);
            it->second.sp.erase(pro.consultar_idProceso());
            it2 = it->second.lp.erase(it2);
            if(found) {
                --n;
                it->second.acept += 1;
            }else {
                it->second.rechaz += 1;
                it->second.lp.insert(it->second.lp.end(),pro);
                it->second.sp.insert(pro.consultar_idProceso());
            }
            ++i;
        }
        ++it;
    }
}

void Area_de_espera::imprimir_prioridad() {
    string id;
    cin >> id;
    cout << " " << id << '\n'; //ECO
    map<string,prioridad>::iterator it = ma.find(id);
    if(it == ma.end()) cout << "error: no existe prioridad" << '\n';
    else {
        list<Proceso>::iterator it2 = it->second.lp.begin();
        while(it2 != it->second.lp.end()) { //imprimimos los procesos de dicha prioridad
            it2->imprimir_proceso();
            ++it2;
        }
        cout << it->second.acept << " " << it->second.rechaz << '\n'; //imprimimos los procesos aceptados y rechazados de dicha prioriudad
    }
}

void Area_de_espera::imprimir_area_espera() {
    map<string,prioridad>::iterator it = ma.begin();
    while(it != ma.end()) {
        cout << it->first << '\n'; //ECO
        list<Proceso>::iterator it2 = it->second.lp.begin();
        while(it2 != it->second.lp.end()) { //imprimimos los procesos de dicha prioridad
            it2->imprimir_proceso();
            ++it2;
        }
        cout << it->second.acept << " " << it->second.rechaz << '\n'; //imprimimos los procesos aceptados y rechazados de dicha prioriudad
        ++it;
    }
}

