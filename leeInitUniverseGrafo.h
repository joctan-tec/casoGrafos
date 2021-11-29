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

            Grafo grafoInicial(true);
            for (int atomo = 0; atomo < 3; atomo++) {

                int cantidadxTipo = archivoJson["Atomos"][atomo]["cantidad"];
                string tipo = archivoJson["Atomos"][atomo]["tipo"];
                if (tipo == "Galea"){
                    for (int cantidades = 0; cantidades < cantidadxTipo; cantidades++) {
                        grafoInicial.addNode(new Galea(cantidades,"Galea")); 
                    }
                } else{
                }if (tipo == "Inti"){
                    for (int cantidades = 10; cantidades < cantidadxTipo*2; cantidades++) {
                        grafoInicial.addNode(new Inti(cantidades,"Inti")); 
                    }
                }else{ 
                }if (tipo == "Katmeo"){
                    for (int cantidades = 20; cantidades < cantidadxTipo*3; cantidades++) {
                        grafoInicial.addNode(new Katmeo(cantidades,"Katmeo"));                         
                    }
                }
            }

            //CONECTA TODOS LOS ATOMOS ENTRE ELLOS SECUENCIALMENTE
            for (int i = 0; i < 30; i++) {
                random_device rd;
                default_random_engine eng(rd());
                uniform_int_distribution<int> distr(1,21);
                if (i+1 == 30){
                    break;
                }
                grafoInicial.addArc(i,i+1,distr(eng));          
            }
            

 
            for (int relaciones = 0; relaciones < 3; relaciones++) {
                //menor o igual
                string tipoPrimero = archivoJson["Atomos"][relaciones]["tipo"];
                int rangoInicialPeso;
                int rangoFinalPeso;

                
                for (int relacionados = 0; relacionados < 2; relacionados++) {
                    int principioPrimero = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["idInicial"];
                    int maximoPrimero = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["idFinal"];


                    string tipoSegundo = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["tipo"];
                    int principioSegundo = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["destinoIdInicial"];
                    int maximoSegundo = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["destinoIdFinal"];
                    rangoInicialPeso = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["pesos"][0];
                    rangoFinalPeso = archivoJson["Atomos"][relaciones]["relaciones"][relacionados]["pesos"][1];

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