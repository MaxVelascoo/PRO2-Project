/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {
  // Inicializa un procesador vacío
}

Procesador::Procesador(const int& longm) {
    longmem = longm;
    mforats[longmem].insert(0);
    memolibre = longmem;
}

int Procesador::consultar_pos_mapa(const int& idPro) {
    map<int,int>::iterator it = mnoms.find(idPro);
    return it->second;
}


int Procesador::consultar_memolibre() const{
    return memolibre;
}

int Procesador::hueco_optimo(const int& memoutilizada) {
    map<int,set<int>>::iterator it = mforats.lower_bound(memoutilizada);
    return it->first;
}

bool Procesador::hueco(const int& memoutilizada) {
    map<int,set<int>>::iterator it = mforats.lower_bound(memoutilizada);
    if(it != mforats.end()) return true;
    else return false;
}

bool Procesador::buscar_proceso(const int& idPro) {
    map<int,int>::iterator it = mnoms.find(idPro);
    if(it != mnoms.end()) return true;
    else return false;
}

bool Procesador::tiene_procesos() const {
    if(not mnoms.empty()) return true;
    else return false;
}

void Procesador::modificar_pos(const int& idProceso, const int& pos) {
    mnoms.erase(idProceso);
    mnoms.insert(make_pair(idProceso,pos));
}

void Procesador::compactar_memoria() {
    if(not mp.empty()) { //Hay procesos
      mforats.clear(); //Borramos todos los huecos
      map<int,Proceso>::iterator it = mp.begin();
      map<int,Proceso>::iterator it2 = it;
      ++it2; //Apunta al supuesto siguiente proceso
      if(it2 == mp.end()) {//Solo hay un proceso
        int idProceso = it->second.consultar_idProceso();
        int posinicial = it->first;
        int memoutilizada = it->second.consultar_memoutilizada();
        if(posinicial != 0) {
          modificar_pos(idProceso, 0);
          mp.insert(make_pair(0,it->second));
          mp.erase(posinicial);
        }
        if(memoutilizada != longmem) {
          mforats[longmem-memoutilizada].insert(memoutilizada);
        }
      }else { //Hay mas de un proceso
          int pos = it->first;
          int proxpos;
          if(pos != 0) {
            modificar_pos(it->second.consultar_idProceso(), 0);
            mp.insert(make_pair(0,it->second));
            it = mp.erase(it);
            --it;
          }
        while(it2 != mp.end()) {
          pos = it->first;
          proxpos = it2->first;
          int memoutilizada = it->second.consultar_memoutilizada();
          if(pos + memoutilizada != proxpos) {
              proxpos = pos + memoutilizada;
              modificar_pos(it2->second.consultar_idProceso(),proxpos);
              mp.insert(make_pair(proxpos,it2->second));
              it2 = mp.erase(it2);
          }else ++it2;
          ++it;
        }
        --it2;
        if(memolibre != 0) { //insertamos hueco del tamaño de la memoria libre
          mforats[memolibre].insert(longmem-memolibre);
        }
      }
    }
}

void Procesador::insertar_proceso_mapa(const Proceso& pro, const int& idProceso, const int& memoutilizada) {
    map<int,set<int>>::iterator it = mforats.lower_bound(memoutilizada);
    set<int>::iterator it2 = it->second.lower_bound(0);
    int pos = *it2;
    int mida = it->first;

    it->second.erase(it->second.begin());
    if(it->second.empty()) mforats.erase(it);

    if(memoutilizada < mida) {
      int posicio = pos;
      mida -= memoutilizada;
      posicio += memoutilizada;
      mforats[mida].insert(posicio);
    }

    memolibre -= memoutilizada;
    mp.insert(make_pair(pos,pro));
    mnoms.insert(make_pair(idProceso,pos));
}

void Procesador::borrar_proceso_mapa(const int& pos, const int& idProceso){
    map<int,Proceso>::iterator it2 = mp.find(pos);
    int memoutilizada = it2->second.consultar_memoutilizada();
    if(memolibre == 0) { //Cas 1: mforats vacío
      mforats[memoutilizada].insert(pos);
    }else { //mforats no vacío
      if(pos == 0) { //El proceso esta a la izquierda de todo
        ++it2; //Este iterador apunta al siguiente proceso del que que queremos eliminar
        if(it2 == mp.end()) { //No hay ningun proceso a su derecha (como mforats no es vacío, hay un hueco entre el proceso y el final de la memoria)
          int hueco = longmem - memoutilizada;
          int poshueco = memoutilizada;
          map<int,set<int>>::iterator it = mforats.find(hueco);
          it->second.erase(it->second.find(poshueco));
          if(it->second.empty()) mforats.erase(it);
          hueco += memoutilizada;
          mforats[hueco].insert(0);
        }else { //Hay como minimo un proceso a su derecha
          if(memoutilizada == it2->first) { //El proceso esta justo al lado
            mforats[memoutilizada].insert(0);
          }else { //Hay un hueco entremedio de los dos procesos
            int hueco = it2->first - memoutilizada;
            map<int,set<int>>::iterator it = mforats.find(hueco);
            it->second.erase(it->second.find(memoutilizada));
            if(it->second.empty()) mforats.erase(it);
            hueco += memoutilizada;
            mforats[hueco].insert(0);
          }
        }
      }else { //El proceso no esta a la izquierda de todo
        if(it2 == mp.begin()) { //Hay un hueco entre el principio de la memoria y nuestro proceso
          map<int,Proceso>::iterator it3 = mp.find(pos);
          ++it3; //it3 apunta al proceso siguiente de nuestro proceso
          if(it3 == mp.end()) {//Nuestro proceso es el de mas a la derecha
            if(pos + memoutilizada == longmem) { //El proceso esta a la derecha del todo
              int hueco = pos;
              map<int,set<int>>::iterator it = mforats.find(hueco);
              it->second.erase(it->second.find(0));
              if(it->second.empty()) mforats.erase(it);
              hueco += memoutilizada;
              mforats[hueco].insert(0);
            }else { //Hay un hueco entre nuestro proceso y el final de la memoria
              int poshuecod = pos + memoutilizada;
              int huecoi = pos; //Hueco izquierdo
              int huecod = longmem - poshuecod; //Hueco derecho
              map<int,set<int>>::iterator it = mforats.find(huecoi);
              it->second.erase(it->second.find(0));
              if(it->second.empty()) mforats.erase(it);
              it = mforats.find(huecod);
              it->second.erase(it->second.find(poshuecod));
              if(it->second.empty()) mforats.erase(it);
              int hueco = huecoi + huecod + memoutilizada;
              mforats[hueco].insert(0);
            }
          }else { //Hay mas procesos a la derecha
            if(pos + memoutilizada == it3->first) { //El proceso siguiente esta justo despues de nuestro proceso (No espacio)
              map<int,set<int>>::iterator it = mforats.find(pos);
              it->second.erase(it->second.find(0));
              if(it->second.empty()) mforats.erase(it);
              mforats[pos + memoutilizada].insert(0);
            }else {  //Hay un hueco entre nuestro proceso y el siguiente proceso
              int poshuecod = pos + memoutilizada;
              int huecoi = pos;
              int huecod = it3->first - poshuecod;
              map<int,set<int>>::iterator it = mforats.find(huecoi);
              it->second.erase(it->second.find(0));
              if(it->second.empty()) mforats.erase(it);
              it = mforats.find(huecod);
              it->second.erase(it->second.find(poshuecod));
              if(it->second.empty()) mforats.erase(it);
              int hueco = huecoi + huecod + memoutilizada;
              mforats[hueco].insert(0);
            }
          }
        }else { //Hay un proceso a la izquierda de nuestro proceso
          --it2;
          if(it2->first + it2->second.consultar_memoutilizada() == pos) { //El proceso de antes esta justo detras (no espacio en medio)
            ++it2;
            ++it2; //apunta al siguiente
            if(it2 == mp.end()) { //Nuestro proceso es el de mas a la derecha
              if(pos + memoutilizada == longmem) { //El proceso esta a la derecha del todo
                mforats[memoutilizada].insert(pos);
              }else { //Hay un hueco entre nuestro proceso y el final de la memoria
                int poshueco = pos + memoutilizada;
                int hueco = longmem - poshueco;
                map<int,set<int>>::iterator it = mforats.find(hueco);
                it->second.erase(it->second.find(poshueco));
                if(it->second.empty()) mforats.erase(it);
                hueco += memoutilizada;
                mforats[hueco].insert(pos);
              }
            }else { //Hay mas procesos a la derecha
              if(pos + memoutilizada == it2->first) { //El proceso siguiente esta justo despues de nuestro proceso (No espacio)
                mforats[memoutilizada].insert(pos);
              }else { //Hay un hueco entre nuestro proceso y el siguiente proceso
                int poshueco = pos + memoutilizada;
                int hueco = it2->first - poshueco;
                map<int,set<int>>::iterator it = mforats.find(hueco);
                it->second.erase(it->second.find(poshueco));
                if(it->second.empty()) mforats.erase(it);
                hueco += memoutilizada;
                mforats[hueco].insert(pos);
              }
            }
          }else { //Hay un espacio en medio entre el proceso a eliminar y el anterior
            map<int,Proceso>::iterator it3 = mp.find(pos);
            ++it3; //it3 apunta al proceso siguiente de nuestro proceso
            if(it3 == mp.end()) {//Nuestro proceso es el de mas a la derecha
              if(pos + memoutilizada == longmem) { //El proceso esta a la derecha del todo
                int poshueco = it2->first + it2->second.consultar_memoutilizada();
                int hueco = pos - (poshueco);
                map<int,set<int>>::iterator it = mforats.find(hueco);
                it->second.erase(it->second.find(poshueco));
                if(it->second.empty()) mforats.erase(it);
                hueco += memoutilizada;
                mforats[hueco].insert(poshueco);
              }else { //Hay un hueco entre nuestro proceso y el final de la memoria
                int poshuecoi = it2->first + it2->second.consultar_memoutilizada();
                int poshuecod = pos + memoutilizada;
                int huecoi = pos - poshuecoi; //Hueco izquierdo
                int huecod = longmem - poshuecod; //Hueco derecho
                map<int,set<int>>::iterator it = mforats.find(huecoi);
                it->second.erase(it->second.find(poshuecoi));
                if(it->second.empty()) mforats.erase(it);
                it = mforats.find(huecod);
                it->second.erase(it->second.find(poshuecod));
                if(it->second.empty()) mforats.erase(it);
                int hueco = huecoi + huecod + memoutilizada;
                mforats[hueco].insert(poshuecoi);
              }
            }else { //Hay mas procesos a la derecha
              if(pos + memoutilizada == it3->first) { //El proceso siguiente esta justo despues de nuestro proceso (No espacio)
                int poshueco = it2->first + it2->second.consultar_memoutilizada();
                int hueco = pos - poshueco;
                map<int,set<int>>::iterator it = mforats.find(hueco);
                it->second.erase(it->second.find(poshueco));
                if(it->second.empty()) mforats.erase(it);
                hueco += memoutilizada;
                mforats[hueco].insert(poshueco);
              }else { //Hay un hueco entre nuestro proceso y el siguiente proceso
                int poshuecoi = it2->first + it2->second.consultar_memoutilizada();
                int huecoi = pos - poshuecoi;
                int poshuecod = pos + memoutilizada;
                int huecod = it3->first - poshuecod;
                map<int,set<int>>::iterator it = mforats.find(huecoi);
                it->second.erase(it->second.find(poshuecoi));
                if(it->second.empty()) mforats.erase(it);
                it = mforats.find(huecod);
                it->second.erase(it->second.find(poshuecod));
                if(it->second.empty()) mforats.erase(it);
                int hueco = huecoi + huecod + memoutilizada;
                mforats[hueco].insert(poshuecoi);
              }
            }
          }
        }
      }
    }
    mnoms.erase(idProceso);
    memolibre += memoutilizada;
}

void Procesador::borrar_mp(const int& pos) {
  mp.erase(pos);
}

void Procesador::imprimir_procesos_mapa() {
    map<int,Proceso>::iterator it = mp.begin();
    while(it != mp.end()) {
      cout << it->first << " ";
      it->second.imprimir_proceso();
      ++it;
    }
}

void Procesador::avanzar_tiempo_procesos(const int& t) {
    map<int,Proceso>::iterator it = mp.begin();
    while(it != mp.end()) {
      if(it->second.consultar_temps() <= t) {
        borrar_proceso_mapa(it->first,it->second.consultar_idProceso());
        it = mp.erase(it);
      } else {
        it->second.modificar_tiempo(t);
        ++it;
      }
    }
}
