#include <iostream>
#include <bits/stdc++.h>
#include "clases.hpp"
using namespace std;



AFD::AFD(){};
AFD::AFD(vector<char> _alfabeto, vector<Estado> &_estados, Estado &_edoInicial, vector<Estado> &_edoFinal){
    this->_alfabeto = _alfabeto;
    this->_estados = _estados;
    this->_edoInicial = _edoInicial;
    this->_edoFinal =_edoFinal;
};
vector<char> AFD::getAlfabeto(){
    return this->_alfabeto;
}
vector<Estado> AFD::getEstados(){
    return this->_estados;
}
Estado AFD::getEdoInicial(){
    return this->_edoInicial;
}
vector<Estado> AFD::getEdosFinales(){
    return this->_edoFinal;
}
