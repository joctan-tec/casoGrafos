#ifndef _GRAFO_MATRIZ_ATOMOS_
#define _GRAFO_MATRIZ_ATOMOS_ 1 

#include "Atomo.h"
#include <string>

using namespace std;

typedef int* pint;  // para el dimensionamiento de la matriz

class GrafoMatriz {
    public: 
        GrafoMatriz(int pMaxVertices){
            this->maxVerts = pMaxVertices;
            this->verts = new Atomo[pMaxVertices];          // vector de vértices
            this->matAd = new pint[pMaxVertices];           // vector de punteros
            this->numVerts = 0;
            //this->visitados[maxVerts];
            //this->distancias[maxVerts] = 0;
            for (int i = 0; i < pMaxVertices; i++) {
                this->matAd[i] = new int[pMaxVertices];     // matriz de adyacencia
            }     
        }
        GrafoMatriz(){
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

        void addVertice(Atomo* pAtomo){
            //bool esta = numVertice(pAtomo) >= 0;
            //if (!esta) {
                Atomo atomo = Atomo(pAtomo->getId(), pAtomo->getNombre());
                verts[numVerts++] = atomo;   // se asigna a la lista.
                // No se comprueba que sobrepase el máximo    
            //}
        }

        int numVertice(Atomo* pAtomo){
            int i;
            bool encontrado = false;
            for ( i = 0; (i < this->numVerts) && !encontrado;) {
                encontrado = this->verts[i].igual(pAtomo);
                if (!encontrado) {
                    i++;
                }
            }
            return (i < this->numVerts) ? i: -1;      
        }

        void nuevoArco(Atomo* pAtomoA, Atomo* pAtomoB, int valor) {
            int va, vb;
            va = numVertice(pAtomoA);
            vb = numVertice(pAtomoB);
            if (va < 0 || vb < 0) throw "Vértice no existe";
            matAd[va][vb] = valor;
        }

        void nuevoArco(int va, int vb) {
            if (va < 0 || vb < 0 || va > numVerts || vb > numVerts)
            throw "Vértice no existe";
            matAd[va][vb] = 1;
        }

        void nuevoArco(string pNombreA, string pNombreB, int va, int vb, int valor){
            int posicion1 = 0;
            int posicion2 = 0;
            for (int i = 0; i < this->maxVerts; i++) {
                if (this->verts[i].igualNombre(pNombreA) && this->verts[i].igualId(va)){
                    posicion1 = i;
                    break;
                }
            }

            for (int i = 0; i < this->maxVerts; i++) {
                if (this->verts[i].igualNombre(pNombreB) && this->verts[i].igualId(vb)){
                    posicion2 = i;
                    break;
                }
            }

            nuevoArco(posicion1, posicion2, valor);
            
        }


        void nuevoArco(int va, int vb, int valor) {
            if (va < 0 || vb < 0 || va > numVerts || vb > numVerts)
            throw "Vértice no existe";
            matAd[va][vb] = valor;
        }

        bool adyacente(Atomo* pAtomoA, Atomo* pAtomoB) {
            int va, vb;
            va = numVertice(pAtomoA);
            vb = numVertice(pAtomoB);
            if (va < 0 || vb < 0) throw "Vértice no existe";
            return matAd[va][vb] == 1;
        }

        bool adyacente(int va, int vb) {
            if (va < 0 || vb < 0 || va >= numVerts || vb >= numVerts)
            throw "Vértice no existe";
            return matAd[va][vb] == 1;
        }

        int Ovalor(Atomo* pAtomoA, Atomo* pAtomoB) {
            int va, vb;
            va = numVertice(pAtomoA);
            vb = numVertice(pAtomoB);
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

        Atomo* getVerts(){
            return this->verts;
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
        void dijkstra(Atomo* pAtomo) {
            int inicio = numVertice(pAtomo);
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
            
            cout << "Atomo   " << "  Distancia minima" << endl;
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

            for (int k = 0; k < n; k++) { // etapas de programación dinámica
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (caminos[i][k] * caminos[k][j]) {
                            //observe el índice k de la programación dinámica
                            caminos[i][j] = 1;
                        }
                    }
                }        
            }

            for (int recorrido = 0; recorrido < this.getNumVerts(); recorrido++) {
                for (int dentro = 0; dentro < this.getNumVerts(); dentro++) {
                    cout << caminos[recorrido][dentro] << endl;
                }
            }
        }


    protected:
        int maxVerts;       // máximo numero de vértices
        int numVerts;       // número de vértices actual
        Atomo* verts;       // array de vértices
        int ** matAd;       // matriz de adyacencia
};
#endif