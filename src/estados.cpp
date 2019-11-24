#include <string>

#include "../include/estados.h"

Estado::Estado(std::string estado){
    estadoInicial = estado;
}

void Estado::setValorInicial(std::string valor){
    valorInicial = valor;
}

void Estado::setEstadoFinal(std::string estado){
    estadoFinal = estado;
}

void Estado::setValorFinal(std::string valor){
    valorFinal = valor;
}

void Estado::setDireccionMov(std::string direccion){
    direccionMov = direccion;
}

std::string Estado::getDireccionMov(){
    return direccionMov;
}

std::string Estado::getValorFinal(){
    return valorFinal;
}

std::string Estado::getValorInicial(){
    return valorInicial;
}

std::string Estado::getEstadoFinal(){
    return estadoFinal;
}

std::string Estado::getEstadoInicial(){
    return estadoInicial;
}
