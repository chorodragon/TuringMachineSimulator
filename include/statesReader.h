#ifndef STATESREADER_H
#define STATESREADER_H
#include <list>
#include <string>

#include "estados.h"

class LectorEstados{
public:
    LectorEstados(std::string path);
    int readStatesDefinition();
    int readStates();
    int readAlfabeto();
    int readEstadoInicial();
    int readEstadoAceptacion();
    int readEstadoError();
    int checkFileExistance();
    std::list<Estado> getListado();
    std::list<std::string> getAlfabeto();
    std::string getEstadoInicial();
    std::string getEstadoAceptacion();
    std::string getEstadoError();
    Estado* analizeState(const std::string& linea);
private:
    std::list<Estado> listadoEstados;
    std::list<std::string> estadosDef;
    std::list<std::string> alfabeto;
    std::string pathStates;
    std::string estadoInicial;
    std::string estadoAceptacion;
    std::string estadoError;
};

#endif
