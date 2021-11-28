#ifndef _GRAFOMATRIZ_
#define _GRAFOMATRIZ_ 1 

#include "INodo.h"
#include "Ciudad.h"
#include <string>

using namespace std;

typedef int* pint;  // para el dimensionamiento de la matriz

class GrafoMatriz {
    public: 
        GrafoMatriz(int pMaxVertices){
            this->maxVerts = pMaxVertices;
            this->verts = new Ciudad[pMaxVertices];          // vector de vértices
            this->matAd = new pint[pMaxVertices];           // vector de punteros
            this->numVerts = 0;
            for (int i = 0; i < pMaxVertices; i++) {
                this->matAd[i] = new int[pMaxVertices];     // matriz de adyacencia
            }     
        }
        GrafoMatriz(){
            this->maxVerts = 1;
            GrafoMatriz(maxVerts);
        }

        int getNumVerts() {
	        return this->numVerts;
        }

        int** getMatriz(){
            return this->matAd;
        }

        void setNumVerts(int pNumVerts) {
	        this->numVerts = pNumVerts;
        }

        void addVertice(Ciudad pCity){
            bool esta = numVertice(pCity) >= 0;
            if (!esta) {
                Ciudad city = Ciudad(pCity.getNombre(),numVerts,pCity.getIdentificador());
                verts[numVerts++] = city;   // se asigna a la lista.
                // No se comprueba que sobrepase el máximo    
            }
        }

        int numVertice(Ciudad pCity){
            int i;
            bool encontrado = false;
            for ( i = 0; (i < this->numVerts) && !encontrado;) {
                encontrado = this->verts[i].igual(pCity);
                if (!encontrado) {
                    i++;
                }
            }
            return (i < this->numVerts) ? i: -1;      
        }

        void nuevoArco(Ciudad pCityA, Ciudad pCityB, int valor) {
            int va, vb;
            va = numVertice(pCityA);
            vb = numVertice(pCityB);
            if (va < 0 || vb < 0) throw "Vértice no existe";
            matAd[va][vb] = valor;
        }

        void nuevoArco(int va, int vb) {
            if (va < 0 || vb < 0 || va > numVerts || vb > numVerts)
            throw "Vértice no existe";
            matAd[va][vb] = 1;
        }

        void nuevoArco(int va, int vb, int valor) {
            if (va < 0 || vb < 0 || va > numVerts || vb > numVerts)
            throw "Vértice no existe";
            matAd[va][vb] = valor;
        }

        bool adyacente(Ciudad pCityA, Ciudad pCityB) {
            int va, vb;
            va = numVertice(pCityA);
            vb = numVertice(pCityB);
            if (va < 0 || vb < 0) throw "Vértice no existe";
            return matAd[va][vb] > 1;
        }

        bool adyacente(int va, int vb) {
            if (va < 0 || vb < 0 || va >= numVerts || vb >= numVerts)
            throw "Vértice no existe";
            return matAd[va][vb] > 1;
        }

        int Ovalor(Ciudad pCityA, Ciudad pCityB) {
            int va, vb;
            va = numVertice(pCityA);
            vb = numVertice(pCityB);
            if (va < 0 || vb < 0) throw "Vértice no existe";
            return matAd[va][vb];
        }

        int Ovalor(int va, int vb) {
            if (va < 0 || vb < 0 || va >= numVerts || vb >= numVerts)
            throw "Vértice no existe";
            return matAd[va][vb];
        }

        void imprimirMatriz(){ 
            for (int i = 0; i < this->maxVerts; i++) {
                for (int j = 0; j < this->maxVerts; j++) {
                    cout << matAd[i][j] << "  ";
                }
                cout << endl;
            }    
        }

        int findMinVertice(int* pDistancia, bool* pVisitados){
            int minVertex = -1;
            for (int i = 0; i < this->maxVerts; i++) {
                if (!pVisitados[i] && (minVertex == -1 || pDistancia[i] < pDistancia[minVertex])) {
                    minVertex = i;
                }    
            }
            return minVertex;           
        }

        #define CONSTANTE_X 66666
        void dijkstra(Ciudad pCity) {
            int inicio = numVertice(pCity);
            int* distancia = new int[this->maxVerts];
            bool* visitados = new bool[this->maxVerts];

            for (int i = 0; i < this->maxVerts; i++) {
                distancia[i] = CONSTANTE_X;
                visitados[i] = false;
            }

            distancia[inicio] = 0;

            for (int  i = 0; i < this->maxVerts; i++) {
                int minVertex = findMinVertice(distancia,visitados);
                visitados[minVertex] = true;
                for (int j = 0; j < this->maxVerts; j++) {
                    if (this->matAd[minVertex][j] != 0 && !visitados[j]){
                        int dist = distancia[minVertex] + this->matAd[minVertex][j];
                        if (dist < distancia[j]) {
                            distancia[j] = dist;
                        }
                    }
                }      
            }
            
            cout << "Ciudad   " << "  Distancia minima" << endl;
            for (int i = 0; i < this->maxVerts; i++) {
                cout << this->verts[i].getNombre() << "\t\t" << distancia[i] << endl;
            } 
            
            delete [] visitados;
            delete [] distancia;            
        }

        void warshall(){
            int ** caminos = new pint[this->getNumVerts()];
            for (int i = 0; i < this->getNumVerts(); i++) {
                caminos[i]= new int[this->getNumVerts()]; 
            }
            for (int i = 0; i < this->getNumVerts(); i++) {
                for (int j = 0; j < this->getNumVerts(); j++) {
                    caminos[i][j] = this->adyacente(i,j) ? 1 : 0;
                }  
            }

            for (int k = 0; k < this->getNumVerts(); k++) { // etapas de programación dinámica
                for (int i = 0; i < this->getNumVerts(); i++) {
                    for (int j = 0; j < this->getNumVerts(); j++) {
                        caminos[i][j]= caminos[i][j] || caminos[i][k] && caminos[k][j];
                    }
                }        
            }

            for (int recorrido = 0; recorrido < this->getNumVerts(); recorrido++) {
                for (int dentro = 0; dentro < this->getNumVerts(); dentro++) {
                    cout << caminos[recorrido][dentro] << "  ";
                }
                cout << endl;
            }
        }
 
    protected:
        int maxVerts;       // máximo numero de vértices
        int numVerts;       // número de vértices actual
        Ciudad* verts;       // array de vértices
        int ** matAd;       // matriz de adyacencia
};
#endif