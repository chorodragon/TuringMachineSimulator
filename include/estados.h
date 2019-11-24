#ifndef ESTADOS_H
#define ESTADOS_H

#include <string>

class Estado{
public:
    //Setters
    Estado(std::string estado);
    void setEstadoFinal(std::string estado);
    void setValorFinal(std::string valor);
    void setValorInicial(std::string valor);
    void setDireccionMov(std::string direccion);
    //Getters
    std::string getEstadoInicial();
    std::string getValorInicial();
    std::string getEstadoFinal();
    std::string getValorFinal();
    std::string getDireccionMov();
private:
    std::string estadoInicial;
    std::string valorInicial;
    std::string estadoFinal;
    std::string valorFinal;
    std::string direccionMov;
};


#endif // ESTADOS_H
