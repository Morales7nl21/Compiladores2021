#include <bits/stdc++.h>
#include <iostream>
#include "clases.hpp"
using namespace std;

Transicion::Transicion(){};

Transicion::Transicion(AFD &_afd){

    this->_afd = _afd;
    llenaTransiciones();
};

void Transicion::llenaTransiciones(){
    
    for(auto edo: _afd.getEstados()){         
        auto k = edo.getSigEdos();
        for(auto edoedo : k)
        {            
           _transiciones[make_pair(edo.getNombreEdo(),edoedo.second)]= edoedo.first.getNombreEdo();                     
        }         
    }
   
}
void Transicion::setTransiciones(map<pair<string,char>,string> &_transiciones){
    this->_transiciones = _transiciones;
}
map<pair<string,char>,string> Transicion::getTransiciones(){
    return _transiciones;
}