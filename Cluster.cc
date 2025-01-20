/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

Cluster::Cluster() {
  // Inicializa un procesador vacío
}

void Cluster::configurar_cluster() {
    mc.clear();
    leercluster(c);
}

void Cluster::leercluster(BinTree<string>& c) {
    pair<string,int> p;
    cin >> p.first;
    if(p.first != "*") {
        string idProcesador = p.first;
        cin >> p.second;
        mc.insert(make_pair(p.first,Procesador(p.second)));
        BinTree<string> left;
        leercluster(left);
        BinTree<string> right;
        leercluster(right);
        c = BinTree<string> (idProcesador,left,right);
    }
}

void Cluster::avanzar_tiempo() {
    int t;
    cin >> t;
    cout << " " << t << '\n'; // ECO
    map<string,Procesador>::iterator it = mc.begin();
    while(it != mc.end()) {
        it->second.avanzar_tiempo_procesos(t); //Modificamos los tiempos en el mapa de procesos
        ++it;
    }
}

void Cluster::modificar_cluster() {
    string p;
    cin >> p;
    cout << " " << p << '\n'; //ECO
    map<string,Procesador>::iterator it = mc.find(p);
    if(it == mc.end()) cout << "error: no existe procesador" << '\n';
    else if(it->second.tiene_procesos()) cout << "error: procesador con procesos" << '\n';
    else {
        anadir_cluster(c,p);
    }
}

void Cluster::anadir_cluster(BinTree<string>& c, const string& p) {
    if(not c.empty()){
       if(c.value() == p) {
            if(c.left().empty() and c.right().empty()) {
                mc.erase(p);
                BinTree<string> nouarbre;
                leercluster(nouarbre);
                c = nouarbre;
            }else cout << "error: procesador con auxiliares" << '\n';
        }else {
            BinTree<string> left = c.left();
            anadir_cluster(left,p);
            BinTree<string> right = c.right();
            anadir_cluster(right,p);
            c = BinTree<string>(c.value(),left,right);
        }
    }
}

void Cluster::alta_proceso_procesador() {
    string idProcesador;
    int idProceso, memoutilizada, temps;
    cin >> idProcesador >> idProceso >> memoutilizada >> temps;
    cout << " " << idProcesador << " " << idProceso << '\n'; //ECO
    map<string,Procesador>::iterator it = mc.find(idProcesador);
    if(it == mc.end()) cout << "error: no existe procesador" << '\n';
    else {
        if(it->second.buscar_proceso(idProceso)) cout << "error: ya existe proceso" << '\n';
        else if(not it->second.hueco(memoutilizada) or memoutilizada == 0) cout << "error: no cabe proceso" << '\n';
        else {
            Proceso pro(idProceso,memoutilizada,temps);
            it->second.insertar_proceso_mapa(pro,idProceso,memoutilizada);
        }
    }
}


void Cluster::baja_proceso_procesador() {
    string idProcesador;
    int idProceso;
    cin >> idProcesador >> idProceso;
    cout << " " << idProcesador << " " << idProceso << '\n'; //ECO
    map<string,Procesador>::iterator it = mc.find(idProcesador);
    if(it == mc.end()) cout << "error: no existe procesador" << '\n';
    else {
        if(not it->second.buscar_proceso(idProceso)) cout << "error: no existe proceso" << '\n';
        else {
            int pos = it->second.consultar_pos_mapa(idProceso);
            it->second.borrar_proceso_mapa(pos,idProceso);
            it->second.borrar_mp(pos);
        }
    }
}

void Cluster::compactar_memoria_procesador() {
    string idProcesador;
    cin >> idProcesador;
    cout << " " << idProcesador << '\n'; //ECO
    map<string,Procesador>::iterator it = mc.find(idProcesador);
    if(it == mc.end()) cout << "error: no existe procesador" << '\n';
    else {
        it->second.compactar_memoria();
    }
}

void Cluster::compactar_memoria_cluster() {
    map<string,Procesador>::iterator it = mc.begin();
    while(it != mc.end()) {
        it->second.compactar_memoria();
        ++it;
    }
}

void Cluster::enviar_proceso(const Proceso& proceso, bool& found) {
    int profundidad = 0;
    int memoutilizada = proceso.consultar_memoutilizada();
    int idProceso = proceso.consultar_idProceso();
    Candidato r = encontrar_procesador(c,memoutilizada,profundidad,idProceso);
    map<string,Procesador>::iterator it = mc.find(r.idPro);
    if(r.posible) it->second.insertar_proceso_mapa(proceso,idProceso,memoutilizada);
    found = r.posible;
}

Candidato Cluster::encontrar_procesador(const BinTree<string>& c, int memoutilizada, int profundidad, int idProceso) {
    if(c.empty()) {
        Candidato cd;
        cd.posible = false;
        return cd;
    }else {
        Candidato cd;
        map<string,Procesador>::iterator it = mc.find(c.value());

        cd.posible = (it->second.hueco(memoutilizada) and (not it->second.buscar_proceso(idProceso)));
        if(cd.posible) {
            cd.idPro = it->first;
            cd.hueco = it->second.hueco_optimo(memoutilizada);
            cd.memolibre = it->second.consultar_memolibre();
            cd.prof = profundidad;
        }
        Candidato cdizq = encontrar_procesador(c.left(),memoutilizada,profundidad +1,idProceso);
        Candidato cddcha = encontrar_procesador(c.right(),memoutilizada,profundidad +1,idProceso);

        if(cdizq.posible and (not cd.posible or hijo_mejor_raiz(cdizq,cd))) {
            cd = cdizq;
        }
        if(cddcha.posible and (not cd.posible or hijo_mejor_raiz(cddcha,cd))) {
            cd = cddcha;
        }
        return cd;
    }
}

bool Cluster::hijo_mejor_raiz(const Candidato& rhijo, const Candidato& r) const{
    if(rhijo.hueco < r.hueco) {
        return true;
    }else if(rhijo.hueco == r.hueco) {

        if(rhijo.memolibre > r.memolibre) {
            return true;
        }else if(rhijo.memolibre == r.memolibre) {

            if(rhijo.prof < r.prof) {
                return true;
            }else return false;

        }else return false;

    }else return false;
}

void Cluster::imprimir_procesador() {
    string idProcesador;
    cin >> idProcesador;
    cout << " " << idProcesador << '\n'; //ECO
    map<string,Procesador>::iterator it = mc.find(idProcesador);
    if(it == mc.end()) cout << "error: no existe procesador" << '\n';
    else {
        it->second.imprimir_procesos_mapa();
    }
}

void Cluster::imprimir_procesadores_cluster() {
    map<string,Procesador>::iterator it = mc.begin();
    while(it != mc.end()) {
        cout << it->first << '\n'; //ECO
        it->second.imprimir_procesos_mapa();
        ++it;
    }
}

void Cluster::imprimir_estructura_cluster() const{
    imprimir_cluster(c);
}

void Cluster:: imprimir_cluster(const BinTree<string>& c) const{
    if(not c.empty()) {
        cout << "(" << c.value();
        imprimir_cluster(c.left());
        imprimir_cluster(c.right());
        cout << ")";
    }else cout << " ";
}
