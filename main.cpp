#include <iostream>
#include <string>
#include <vector>

#include "include/statesReader.h"
#include "include/turingmachine.h"

std::string setPathFile();
std::string setCadenaEntrada();
void executeTuring(std::string pathFile, std::string cadenaEntrada);

int main(int argc, char ** argv){
    std::string pathFile = "";
    std::string cadenaEntrada = "";
    int op = 0;

    if(argc != 1){
        std::cout << "Error, el uso del programa debe ser: \n";
        std::cout << "./exec\n";
        std::cout << "No se aceptan argumentos.\n";
        return 1;
    }
    while(op != 4){
        std::cout << "****************** Menu *****************\n";
        std::cout << "1. Ingresar archivo de entrada.\n";
        std::cout << "2. Ingrear cadena de entrada en la cinta.\n";
        std::cout << "3. Analizar la cinta.\n";
        std::cout << "4. Salir.\n";
        std::cout << "Ingrese el numero de la accion que desea realizar: ";
        std::cin >> op;
        std::cin.ignore(32820, '\n');

        switch(op){
            case 1: pathFile = setPathFile(); break;
            case 2: cadenaEntrada = setCadenaEntrada(); break;
            case 3: executeTuring(pathFile, cadenaEntrada); break;
            case 4: break;
        }
    }

    return 0;
}

void executeTuring(std::string pathFile, std::string cadenaEntrada){
    LectorEstados *lector;
    TuringMachine *machine;

    lector = new LectorEstados(pathFile);

    if(!lector->checkFileExistance()){
        std::cout << "El archivo de entrada no existe.\n";
        std::cout << "Ingrese la direccion de un archivo valida.\n";
        return;
    }
    if(cadenaEntrada.empty()){
        std::cout << "No se ha ingresado una cadena de entrada para la cinta.\n";
        std::cout << "Ingrese una cadena de entrada valida.\n";
        return;
    }

    if(lector->readStates() != 0){
        std::cout << "Error, no se han definido correctamente los estados en el archivo de entrada\n";
        std::cout << "Verifique el archivo de entrada.\n";
        return;
    }

    if(lector->readAlfabeto() != 0){
        std::cout << "Error, no se ha definido el alfabeto en el archivo de entrada\n";
        std::cout << "Verifique el archivo de entrada.\n";
        return;
    }

    if(lector->readEstadoInicial() != 0){
        std::cout << "Error, no se ha definido el estado inicial en el archivo de entrada\n";
        std::cout << "Verifique el archivo de entrada.\n";
        return;
    }

    if(lector->readEstadoAceptacion() != 0){
        std::cout << "Error, no se ha definido el estado de aceptacion en el archivo de entrada\n";
        std::cout << "Verifique el archivo de entrada.\n";
        return;
    }

    if(lector->readEstadoError() != 0){
        std::cout << "Error, no se ha definido el estado de error en el archivo de entrada\n";
        std::cout << "Verifique el archivo de entrada.\n";
        return;
    }

    if(lector->readStatesDefinition() != 0){
        std::cout << "Error al leer la definicion de los estados en el archivo de entrada.\n";
        std::cout << "Verifique el archivo de entrada.\n";
        return;
    }


    machine = new TuringMachine(lector->getListado(), cadenaEntrada,
                                lector->getAlfabeto(), lector->getEstadoInicial(),
                                lector->getEstadoAceptacion(), lector->getEstadoError());

    if(machine->analizeInput() != 0){
        std::cout << "Error al ejecutar el contenido de la lista.\n";
        std::cout << "Verifique la entrada de la cinta y/o la definicion de los estados.\n";
        return;
    }

    std::cout << "Se ha finalizado la ejecucion.\n\n\n";
}

std::string setPathFile(){
    std::string pathFile;
    std::cout << "Ingrese la direccion del archivo: ";
    std::getline(std::cin, pathFile);
    return pathFile;
}

std::string setCadenaEntrada(){
    std::string cadenaEntrada;
    std::cout << "Ingrese la entrada de la cinta: ";
    std::getline(std::cin, cadenaEntrada);
    cadenaEntrada = "_" + cadenaEntrada + "_";
    return cadenaEntrada;
}
