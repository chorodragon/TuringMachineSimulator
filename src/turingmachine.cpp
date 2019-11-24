#include <string>
#include <iostream>
#include <list>

#include "../include/turingmachine.h"
#include "../include/estados.h"

TuringMachine::TuringMachine(std::list<Estado> states, std::string entrada,
                             std::list<std::string> alfabeto, std::string estadoInicial,
                             std::string estadoAceptacion, std::string estadoError){
    this->cinta = entrada;
    this->estados = states;
    this->alfabeto = alfabeto;
    this->estadoInicial = estadoInicial;
    this->estadoAceptacion = estadoAceptacion;
    this->estadoError = estadoError;
}

int TuringMachine::analizeInput(){
    int pasos = 0;
    std::vector<char> cintaEntrada(cinta.c_str(), cinta.c_str() + cinta.length() + 1);
    std::string::iterator position;
    std::vector<char>::iterator pos;
    std::list<Estado>::iterator state;
    std::vector<char>::iterator i;
    std::string estadoActual;
    std::string finalValueChar;
    int found;
    int positionChar = 0;

    position = cinta.begin();
    pos = cintaEntrada.begin() + 1;
    estadoActual = estadoInicial;

    while(true){
        found = 0;
        std::cout << "Pasos: " << ++pasos << std::endl;
        std::cout << "Estado: " << estadoActual << std::endl;
        std::cout << "Posicion de lectura en la cinta: " << positionChar << std::endl;
        std::cout << "Cinta de entrada: ";
        for(i = cintaEntrada.begin(); i != cintaEntrada.end(); i++)
            std::cout << *i;
        std::cout << "\n";
        std::string  sym(1, (*pos));
        std::string character = sym.c_str();
        for(state = estados.begin(); state != estados.end(); state++){
            if(!state->getEstadoInicial().compare(estadoActual) && !state->getValorInicial().compare(character)){
                found = 1;
                break;
            }
        }
        if(found == 0){
            std::cout << "Error, cinta de entrada rechazada" << std::endl;;
            break;
        }
        estadoActual = state->getEstadoFinal();
        finalValueChar = state->getValorFinal();
        *pos = finalValueChar[0];

        if(!estadoActual.compare(estadoAceptacion)){
            std::cout << "Aceptado" << std::endl;
            break;
        }

        if(!estadoActual.compare(estadoError)){
            std::cout << "Error, cinta de entrada rechazada" << std::endl;
            break;
        }

        std::cin.get();
        if(!state->getDireccionMov().compare("d")){
            pos++;
            if(pos == cintaEntrada.end()){
                cintaEntrada.push_back('_');
                pos = cintaEntrada.end() - 1;
            }
            positionChar++;
        }
        else if(!state->getDireccionMov().compare("i")){
            if(pos == cintaEntrada.begin()){
                cintaEntrada.insert(cintaEntrada.begin(), '_');
                positionChar = 0;
                pos = cintaEntrada.begin();
            }
            else{
                pos--;
                positionChar--;
            }
        }
        else if(!state->getDireccionMov().compare("n")){
            ;
        }
    }
    return 0;
}
