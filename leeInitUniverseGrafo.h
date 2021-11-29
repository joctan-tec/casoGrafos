#ifndef _LEER_UNIVERSO_
#define _LEER_UNIVERSO_ 1

#include <iostream>

#include "json-develop/include/nlohmann/json.hpp"   // https://github.com/nlohmann/json/tree/develop/single_include/nlohmann/json.hpp
#include <fstream>                           
#include <string> 
#include <vector>
#include <stack>
#include <random>

#include "grafo.h"
#include "Galea.h"
#include "Inti.h"
#include "Katmeo.h"

#define N_ATOMOS 3
#define NUMERO_TOTAL 30
 
using json = nlohmann::json;
using namespace std;

class InitUniverseGraph{
    private:
        json archivoJson;
        string path;
    
    public:
        void setPath(string pPath){
            this->path = pPath;
        }

        Grafo leerArchivo(){
            // leer configuración desde el archivo
            ifstream lecturaArchivo (path);  // Nota aquí es una ruta relativa
            lecturaArchivo >> archivoJson;  
            lecturaArchivo.close();

            Grafo grafoInicial(true);   //se crea el Grafo a retornar
            for (int atomo = 0; atomo < N_ATOMOS; atomo++) {
                //se saca la cantidad del atomo a evaluarse 
                int cantidadxTipo = archivoJson["Atomos"][atomo]["cantidad"];
                //se saca el tipo del atomo
                string tipo = archivoJson["Atomos"][atomo]["tipo"]; 

                //se evalua cada cada uno y se crean las cantidades correspondientes
                if (tipo == "Galea"){
                    for (int cantidades = 0; cantidades < cantidadxTipo; cantidades++) {
                        grafoInicial.addNode(new Galea(cantidades)); 
                    }
                } else{
                }if (tipo == "Inti"){
                    for (int cantidades = 10; cantidades < cantidadxTipo*2; cantidades++) {
                        grafoInicial.addNode(new Inti(cantidades)); 
                    }
                }else{ 
                }if (tipo == "Katmeo"){
                    for (int cantidades = 20; cantidades < cantidadxTipo*3; cantidades++) {
                        grafoInicial.addNode(new Katmeo(cantidades));                         
                    }
                }
            }

            //CONECTA TODOS LOS ATOMOS ENTRE ELLOS SECUENCIALMENTE
            for (int i = 0; i < NUMERO_TOTAL; i++) {
                random_device rd;
                default_random_engine eng(rd());
                uniform_int_distribution<int> distr(1,21);  //los pesos entre 1 y 21
                if (i+1 == NUMERO_TOTAL){
                    break;
                }
                grafoInicial.addArc(i,i+1,distr(eng));          
            }
            
            //ACA SE ESTABLECEN LAS RELACIONES
            for (int relaciones = 0; relaciones < N_ATOMOS; relaciones++) {

                string tipoPrimero = archivoJson["Atomos"][relaciones]["tipo"];
                int rangoInicialPeso;
                int rangoFinalPeso;

                //ACA SE DAN LAS RELACIONES POR CADA ATOMO
                for (int relacionados = 0; relacionados < 2; relacionados++) {
                    int principioPrimero = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["idInicial"];
                    int maximoPrimero = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["idFinal"];

                    //CARACTERISTICAS DE LOS ATOMOS A RELACIONARSE CON EL PRINCIPAL
                    string tipoSegundo = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["tipo"];
                    int principioSegundo = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["destinoIdInicial"];
                    int maximoSegundo = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["destinoIdFinal"];
                    rangoInicialPeso = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["pesos"][0];
                    rangoFinalPeso = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["pesos"][1];

                    //Aca se crean los arcos segun cada atomo principal y con el que se va a relacionar
                    for (int xTipo = principioPrimero; xTipo <= maximoPrimero; xTipo++) {
                        random_device rd;
                        default_random_engine eng(rd());
                        uniform_int_distribution<int> distr(rangoInicialPeso, rangoFinalPeso);

                        grafoInicial.addArc(xTipo, principioSegundo, distr(eng));
                        principioSegundo++;
                    }
                }
            }

            return grafoInicial;
        }
};
#endif