#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "../include/statesReader.h"
#include "../include/estados.h"

LectorEstados::LectorEstados(std::string path){
    pathStates = path;
}

int LectorEstados::checkFileExistance(){
    std::ifstream f(pathStates.c_str());
    return f.good();
}

std::list<Estado> LectorEstados::getListado(){
    return listadoEstados;
}

std::list<std::string> LectorEstados::getAlfabeto(){
    return alfabeto;
}

std::string LectorEstados::getEstadoAceptacion(){
    return estadoAceptacion;
}

std::string LectorEstados::getEstadoInicial(){
    return estadoInicial;
}

std::string LectorEstados::getEstadoError(){
    return estadoError;
}

Estado* LectorEstados::analizeState(const std::string& line){
    Estado *tmp_estado;
    std::string originalState;
    std::string originalValue;
    std::string finalState;
    std::string finalValue;
    std::string direccion;
    std::string::iterator pos_string;

    originalState.clear();
    originalValue.clear();
    finalState.clear();
    finalValue.clear();
    direccion.clear();

    if(line.find("=") == std::string::npos)
        return nullptr;

    originalState = line.substr(0, line.find("="));
    finalState = line.substr((line.find("=")+1));
    pos_string = std::remove(originalState.begin(), originalState.end(), ' ');
    originalState.erase(pos_string, originalState.end());
    pos_string = std::remove(finalState.begin(), finalState.end(), ' ');
    finalState.erase(pos_string, finalState.end());

    if(originalState.find(",") == std::string::npos)
        return nullptr;
    if(finalState.find(",") == std::string::npos)
        return nullptr;

    originalValue = originalState.substr(originalState.find(",")+1);
    originalState = originalState.substr(0, originalState.find(","));
    finalValue = finalState.substr(finalState.find(",")+1);
    finalState = finalState.substr(0, finalState.find(","));

    if(finalValue.find(",") == std::string::npos)
        return nullptr;

    direccion = finalValue.substr(finalValue.find(",")+1);
    finalValue = finalValue.substr(0, finalValue.find(","));

    //Verificacion de valores que se asignaran al estado
    if(originalState.empty())
        return nullptr;
    if(originalValue.empty())
        return nullptr;
    if(finalState.empty())
        return nullptr;
    if(finalValue.empty())
        return nullptr;
    if(direccion.empty())
        return nullptr;

    //Definicion de estado temporal
    tmp_estado = new Estado(originalState);
    tmp_estado->setValorInicial(originalValue);
    tmp_estado->setEstadoFinal(finalState);
    tmp_estado->setValorFinal(finalValue);
    tmp_estado->setDireccionMov(direccion);

    return tmp_estado;
}

int LectorEstados::readStatesDefinition(){
    std::ifstream file;
    std::string line;
    Estado *tmp_estado;
    int foundDefinicion = 0;
    std::list<std::string>::const_iterator it;

    file.open(pathStates);

    while(std::getline(file, line)){
        if(!line.compare("definicion:")){
            foundDefinicion = 1;
            break;
        }
    }

    if(foundDefinicion == 0){
        std::cout << "Error con la definicion: " << line << std::endl;
        return -1;
    }

    while(getline(file, line)){
        if(line.find("//") != std::string::npos)
            continue;
        if(line.size() == 0)
            continue;
        tmp_estado = analizeState(line);

        if(tmp_estado == nullptr){
            std::cout << "Error en la definicion: " << line << std::endl;
            return -1;
        }

        for(it = estadosDef.begin(); it != estadosDef.end(); it++)
            if(!(*it).compare(tmp_estado->getEstadoInicial()))
                break;

        if(it == estadosDef.end()){
            std::cout << "El estado: " << tmp_estado->getEstadoInicial() << " no esta definido." << std::endl;
            return -1;
        }

        for(it = estadosDef.begin(); it != estadosDef.end(); it++)
            if(!(*it).compare(tmp_estado->getEstadoFinal()))
                break;

        if(it == estadosDef.end()){
            std::cout << "El estado: " << tmp_estado->getEstadoFinal() << " no esta definido." << std::endl;
            return -1;
        }

        listadoEstados.push_back(*tmp_estado);
    }

    file.close();
    return 0;
}

int LectorEstados::readAlfabeto(){
    return 0;
}

int LectorEstados::readEstadoAceptacion(){
    std::fstream file;
    std::string linea;
    std::string estado;
    std::string estadoListado;
    std::string::iterator it;
    std::list<std::string>::const_iterator est;

    int foundInitialState = 0;

    file.open(pathStates);

    while(std::getline(file, linea)){
        if(!linea.compare("definicion:")){
            break;
        }
        if(linea.substr(0, linea.find(":")) == "ha"){
            foundInitialState = 1;
            break;
        }
    }

    if(foundInitialState == 0)
        return -1;

    estado = linea.substr(linea.find(":"));

    it = std::remove(estado.begin(), estado.end(), ' ');
    estado.erase(it, estado.end());
    estado.erase(estado.begin());

    foundInitialState = 0;
    for(est = estadosDef.begin(); est != estadosDef.end(); est++){
        if(!estado.compare(*est)){
            foundInitialState = 1;
            break;
        }
    }

    if(foundInitialState == 0){
        return -1;
    }

    this->estadoAceptacion = estado;
    return 0;
}

int LectorEstados::readEstadoError(){
    std::fstream file;
    std::string linea;
    std::string estadoListado;
    std::string estado;
    std::string::iterator it;
    std::list<std::string>::const_iterator est;

    int foundInitialState = 0;

    file.open(pathStates);

    while(std::getline(file, linea)){
        if(!linea.compare("definicion:")){
            break;
        }
        if(linea.substr(0, linea.find(":")) == "he"){
            foundInitialState = 1;
            break;
        }
    }

    if(foundInitialState == 0)
        return -1;

    estado = linea.substr(linea.find(":"));

    it = std::remove(estado.begin(), estado.end(), ' ');
    estado.erase(it, estado.end());
    estado.erase(estado.begin());
    foundInitialState = 0;
    for(est = estadosDef.begin(); est != estadosDef.end(); est++){
        if(!estado.compare(*est)){
            foundInitialState = 1;
            break;
        }
    }

    if(foundInitialState == 0){
        return -1;
    }

    this->estadoError = estado;
    return 0;
}

int LectorEstados::readEstadoInicial(){
    std::fstream file;
    std::string linea;
    std::string estadoListado;
    std::string estado;
    std::string::iterator it;
    std::list<std::string>::const_iterator est;

    int foundInitialState = 0;

    file.open(pathStates);

    while(std::getline(file, linea)){
        if(!linea.compare("definicion:")){
            break;
        }
        if(linea.substr(0, linea.find(":")) == "Inicial"){
            foundInitialState = 1;
            break;
        }
    }

    if(foundInitialState == 0)
        return -1;

    estado = linea.substr(linea.find(":"));

    it = std::remove(estado.begin(), estado.end(), ' ');
    estado.erase(it, estado.end());
    estado.erase(estado.begin());

    foundInitialState = 0;
    for(est = estadosDef.begin(); est != estadosDef.end(); est++){
        if(!estado.compare(*est)){
            foundInitialState = 1;
            break;
        }
    }

    if(foundInitialState == 0){
        return -1;
    }

    this->estadoInicial = estado;

    return 0;
}

int LectorEstados::readStates(){
    std::fstream file;
    std::string line;
    std::string listado;
    std::string::iterator it;
    std::string::iterator beginState;
    int foundStatesLine = 0;
    file.open(pathStates);

    while(std::getline(file, line)){
        if(line.substr(0, line.find(":")) == "Estados"){
            foundStatesLine = 1;
            break;
        }
        if(!line.compare("definicion:")){
            std::cout << "Se llego a la defincion\n";
            break;
        }
    }

    if(foundStatesLine == 0)
        return -1;

    listado = line.substr(line.find(":"));
    it = std::remove(listado.begin(), listado.end(), ' ');
    listado.erase(it, listado.end());
    listado.erase(listado.begin());

    beginState = listado.begin();

    if(beginState == listado.end()){
        return -1;
    }

    for(it = listado.begin(); it != listado.end(); it++){
        if((*it) == ','){
            estadosDef.push_back(std::string(beginState, it));
            beginState = it + 1;
        }
    }

    estadosDef.push_back(std::string(beginState, listado.end()));

    file.close();
    return 0;
}
