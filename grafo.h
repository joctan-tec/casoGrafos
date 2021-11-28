#ifndef _GRAFO_
#define _GRAFO_ 1
#include <vector>
#include "NodoGrafo.h"
#include "INodo.h"
#include <map>
#include <queue>
#include <stack>
#include "Arco.h"

#define MAX 1000
#define Node pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas

//La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
//por ello es necesario realizar nuestro comparador para que sea un min-Heap
struct cmp {
    bool operator() ( const Node &a , const Node &b ) {
        return a.second > b.second;
    }
};

using namespace std;

class Grafo { 
    private:
        vector<NodoGrafo*> listaNodos;
        bool esDirigido = true;
        int totalArcos = 0;
        std::map<int,NodoGrafo*> hashNodos;
        int distancia[ MAX ];      //distancia[ u ] distancia de vértice inicial a vértice con ID = u
        bool visitado[ MAX ];      //para vértices visitados
        int previo[ MAX ];         //para la impresion de caminos
        priority_queue< Node , vector<Node> , cmp > colaCaminosCortos; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope



        void resetNodes() {
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                actual->setProcesado(false);
                actual->setVisitado(false);
            }
        }

        NodoGrafo* findNotVisited() {
            NodoGrafo* result = nullptr;
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                if (!actual->getVisitado()) {
                    result = actual;
                    break;
                }
            }
            return result;
        }

        int findNotVisitedDijkstra(){
            int result = 0;
            for (int i = 0; i < this->getSize(); i++) {
                if (visitado[i] == false){
                    result = i;
                    break;
                }
            }
            return result;       
        }

        void init(){
            for (int i = 0; i < this->getSize(); i++)  {
                distancia[i] = INF;
                visitado[i] = false;
                previo[i] = -1;
            }
        }

        void searchMinPath( int pActual, int pAdyacente, int pPeso){
            if (distancia[pActual] + pPeso < distancia[pAdyacente] ) {
                distancia[pAdyacente] = distancia[pActual] + pPeso;
                previo[pAdyacente] = pActual;
                colaCaminosCortos.push( Node(pAdyacente, distancia[pAdyacente] ) );
            }
        }


    public:
        Grafo(bool pDirigido) {
            this->esDirigido =  pDirigido;
        }

        vector<NodoGrafo*> getListaNodos() {
	        return this->listaNodos;
        }

        int getAmountArcs(){
            return totalArcos;
        }

        int getSize() {
            return this->listaNodos.size();
        }

        void addNode(INodo* pNodo) {
            NodoGrafo* nuevoNodo = new NodoGrafo(pNodo);
            this->listaNodos.push_back(nuevoNodo);
            hashNodos.insert(pair<int,NodoGrafo*>(pNodo->getId(),nuevoNodo));
        }

        void addArc(NodoGrafo* pOrigen, NodoGrafo* pDestino) {
            this->addArc(pOrigen, pDestino, 0);
        }

        void addArc(NodoGrafo* pOrigen, NodoGrafo* pDestino, int pPeso) {
            Arco* newArc = new Arco(pOrigen, pDestino, pPeso);

            pOrigen->addArc(newArc);
            if (!this->esDirigido) {
                Arco* reverseArc =  new Arco(pDestino, pOrigen , pPeso);
                pDestino->addArc(reverseArc);
            }
            totalArcos++;

        }

        void addArc(INodo* pOrigen, INodo* pDestino) {
            this->addArc(pOrigen->getId(), pDestino->getId(), 0);
        }

        void addArc(INodo* pOrigen, INodo* pDestino, int pPeso) {
            this->addArc(pOrigen->getId(), pDestino->getId(), pPeso);
        }

        void addArc(int pOrigen, int pDestino) {
            this->addArc(pOrigen, pDestino, 0);
        }

        void addArc(int pOrigen, int pDestino, int pPeso) {
            this->addArc(this->getNodo(pOrigen), this->getNodo(pDestino), pPeso);
        }

        NodoGrafo* getNodo(int pId) { 
            return hashNodos.at(pId);
        }

        vector<INodo*> path(int pOrigen, int pDestino){
            return this->path((INodo*)this->getNodo(pOrigen), (INodo*)this->getNodo(pDestino));
        }

        vector<INodo*> path(INodo* pOrigen, INodo* pDestino){  
            // debe retornar un camino, el primero que encuentre estre el nodo oriegn y destino.
            // en caso de que no haya camino, result se retorna vacío.
            vector<INodo*> result;
            stack<NodoGrafo*> nodosProcesados;

            resetNodes();

            NodoGrafo* puntoPartida = this->getNodo(pOrigen->getId());
            NodoGrafo* puntoDestino = this->getNodo(pDestino->getId());

            if (puntoPartida->getInfo() == puntoDestino->getInfo()) {
                result.push_back(puntoPartida->getInfo());
                return result;
            }


            nodosProcesados.push(puntoPartida);
            puntoPartida->setProcesado(true);

            while (!nodosProcesados.empty()) {
                NodoGrafo* actual = nodosProcesados.top();
                nodosProcesados.pop();

                actual->setVisitado(true);
                result.push_back(actual->getInfo());

                vector<Arco*> *adyacentes = actual->getArcs();
                for (int indiceArcos = 0; indiceArcos < adyacentes->size(); indiceArcos++) {
                    
                    Arco* arco = adyacentes->at(indiceArcos);
                    NodoGrafo* adyacente;

                    if (arco != nullptr) {
                        adyacente = (NodoGrafo*)arco->getDestino();
                        if (!adyacente->getProcesado()) {
                            nodosProcesados.push(adyacente);
                            adyacente->setProcesado(true);
                            if (adyacente->getInfo() == puntoDestino->getInfo()){
                                result.push_back(adyacente->getInfo());
                                return result;
                            }
                        }
                    } 
                }
            }
            return result;
        }

        vector<INodo*> deepPath(int pOrigen){ 
            INodo* nodo = this->getNodo(pOrigen)->getInfo();
            return this->deepPath(nodo);
        }

        vector<INodo*> deepPath(INodo* pOrigen) {  //recorrido en profundidad
            vector<INodo*> result;
            stack<NodoGrafo*> nodosProcesados;
            int visitados = 0;

            resetNodes();

            NodoGrafo* puntoPartida = this->getNodo(pOrigen->getId());
            nodosProcesados.push(puntoPartida);
            puntoPartida->setProcesado(true);

            do {
                while (!nodosProcesados.empty()) {
                    NodoGrafo* actual = nodosProcesados.top();
                    nodosProcesados.pop();

                    actual->setVisitado(true);
                    result.push_back(actual->getInfo());
                    visitados++;

                    vector<Arco*> *adyacentes = actual->getArcs();
                    for (int indiceArcos = 0; indiceArcos < adyacentes->size(); indiceArcos++) {

                        Arco* arco = adyacentes->at(indiceArcos);
                        NodoGrafo* adyacente;

                        if (arco != nullptr) {
                            adyacente = (NodoGrafo*)arco->getDestino();
                            if (!adyacente->getProcesado()) {
                                nodosProcesados.push(adyacente);
                                adyacente->setProcesado(true);
                            }
                        }
                    }
                }
                if (visitados<this->getSize()) {
                    puntoPartida = this->findNotVisited();
                    nodosProcesados.push(puntoPartida);
                    puntoPartida->setProcesado(true);
                }

            } while (visitados<this->getSize());

            return result;
        } 

        vector<INodo*> broadPath(int pOrigen){
            INodo* nodo = this->getNodo(pOrigen)->getInfo();
            return this->broadPath(nodo);
        }

        vector<INodo*> broadPath(INodo* pOrigen) {
            vector<INodo*> result;
            queue<NodoGrafo*> nodosProcesados;
            int visitados = 0;
            
            resetNodes();

            NodoGrafo* puntoPartida = this->getNodo(pOrigen->getId());
            nodosProcesados.push(puntoPartida);
            puntoPartida->setProcesado(true);
            
            do {
                while (!nodosProcesados.empty()) {
                    NodoGrafo* actual = nodosProcesados.front();
                    nodosProcesados.pop();

                    actual->setVisitado(true);
                    visitados++;
                    result.push_back(actual->getInfo());

                    vector<Arco*> *adyacentes = actual->getArcs();

                    for (int indiceArcos=0; indiceArcos<adyacentes->size(); ++indiceArcos) {
                        Arco* arco = adyacentes->at(indiceArcos);
                        NodoGrafo* adyacente = (NodoGrafo*)arco->getDestino();
                        if (!adyacente->getProcesado()) {
                            nodosProcesados.push(adyacente);
                            adyacente->setProcesado(true);
                        }
                    }
                }

                if (visitados<this->getSize()) {
                    puntoPartida = this->findNotVisited();
                    nodosProcesados.push(puntoPartida);
                    puntoPartida->setProcesado(true);
                }
            } while (visitados<this->getSize()); 

            return result;
        }


        vector<int> dijkstraNodoANodo(INodo* pOrigen, INodo* pDestino){
            init();
            vector<int> result;
            int visitados = 0;
            colaCaminosCortos.push( Node(pOrigen->getId(),0) );
            distancia[pOrigen->getId()] = 0;
            int actual , adyacente , peso;
            do {
                while (!colaCaminosCortos.empty()){
                    actual = colaCaminosCortos.top().first;
                    colaCaminosCortos.pop();
                    if (visitado[ actual ]) continue; 
                    visitado [actual] = true;
                    visitados++;

                    NodoGrafo* nodoActual = getNodo(actual);
                    vector<Arco*>* adyacentes =  nodoActual->getArcs();
                    
                    for (int i = 0; i < adyacentes->size(); i++) {
                        Arco* arco = adyacentes->at(i);
                        NodoGrafo* ady = (NodoGrafo*)arco->getDestino();
                        adyacente = ady->getInfo()->getId();
                        peso = arco->getPeso();
                        if (!visitado[adyacente]){
                            searchMinPath(actual, adyacente, peso);
                            NodoGrafo* puntoDestino = this->getNodo(pDestino->getId());
                            if (ady->getInfo() == puntoDestino->getInfo()){
                                for (int j = 0; j < this->getSize(); j++) {
                                    if (j == pDestino->getId())
                                        result.push_back(distancia[j]);
                                }
                                return result;
                            }
                        }
                    }   
                }
                if (visitados<this->getSize()) {
                    actual = this->findNotVisitedDijkstra();
                    colaCaminosCortos.push( Node(actual,0) );
                }
            } while (visitados<this->getSize());

            for (int j = 0; j < this->getSize(); j++) {
                result.push_back(distancia[j]);
            }
            return result;
        }

        vector<int> dijkstraNodoANodo(int pOrigen, int pDestino){
            INodo* nodoPartida = this->getNodo(pOrigen)->getInfo();
            INodo* nodoDestino = this->getNodo(pDestino)->getInfo();
            return this->dijkstraNodoANodo(nodoPartida, nodoDestino);
        }

        vector<int> algoritmoDijkstra(INodo* pNodo){
            init();
            vector<int> result;
            int visitados = 0;
            colaCaminosCortos.push( Node(pNodo->getId(),0) );
            distancia[pNodo->getId()] = 0;
            int actual , adyacente , peso;
            do {
                while (!colaCaminosCortos.empty()) {
                    actual = colaCaminosCortos.top().first;
                    colaCaminosCortos.pop();
                    if (visitado[ actual ]) continue; 
                    visitado [actual] = true;
                    visitados++;

                    NodoGrafo* nodoActual = getNodo(actual);
                    vector<Arco*>* adyacentes =  nodoActual->getArcs();
                    
                    for (int i = 0; i < adyacentes->size(); i++) {
                        Arco* arco = adyacentes->at(i);
                        NodoGrafo* ady = (NodoGrafo*)arco->getDestino();
                        adyacente = ady->getInfo()->getId();
                        peso = arco->getPeso();
                        if (!visitado[adyacente]){
                            searchMinPath(actual, adyacente, peso);
                        }
                    }   
                }
                if (visitados<this->getSize()) {
                    actual = this->findNotVisitedDijkstra();
                    colaCaminosCortos.push( Node(actual,0) );
                }
            } while (visitados<this->getSize());

            for (int j = 0; j < this->getSize(); j++) {
                result.push_back(distancia[j]);
            }
            return result;
        }


        vector<int> algoritmoDijkstra(int pOrigen){
            INodo* nodo = this->getNodo(pOrigen)->getInfo();
            return this->algoritmoDijkstra(nodo);
        }


        void reproduccionAtomos(INodo* pNodo){
            vector<INodo*> recorrido = this->deepPath(pNodo);
            vector<int> distanciasXNodo;
            int comparador = 0;
            for (int i = 0; i < recorrido.size(); i++) {
                INodo* nodo = recorrido.at(i);
                distanciasXNodo = this->algoritmoDijkstra(nodo);
                for (int j = 0; j < distanciasXNodo.size(); j++) {
                    int distanciaActual = distanciasXNodo.at(j);
                    if (distanciaActual > comparador) {
                        //ACA DEBO DE OBTENER EL NOMBRE DEL ATOMO QUE SE ESTA ANALIZANDO Y COMPARAR SI ES 
                        //DIFERENTE AL PRINCIPAL Y GUARDAR LA DISTANCIA (INT) 
                        //Y LUEGO DEBO DE SACAR LO MISMO, PERO LA MENOR DISTANCIA CON EL
                        //ATOMO DE IGUAL NOMBRE
                        if (this->getListaNodos().at(j)->getInfo())
                    }
                }
            }
            
        }


        void printCounters() {
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                cout << actual->getInfo()->getId() << " tiene " << actual->getArcs()->size() << endl;
            }
        }
};

#endif