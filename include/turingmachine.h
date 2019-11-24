#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <string>
#include <vector>

#include "estados.h"

class TuringMachine{
public:
    TuringMachine(std::list<Estado> states, std::string entrada,
                  std::list<std::string> alfabeto, std::string estadoInicial,
                  std::string estadoAceptacion, std::string estadoError);
    int analizeInput();
private:
    std::string cinta;
    std::list<Estado> estados;
    std::list<std::string> alfabeto;
    std::string estadoInicial;
    std::string estadoAceptacion;
    std::string estadoError;
};

#endif
