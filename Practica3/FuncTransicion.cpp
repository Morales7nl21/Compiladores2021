#include <bits/stdc++.h>
#include <iostream>
#include "clases.hpp"
using namespace std;

int cont = 0;

FuncionTransicion::FuncionTransicion(){};
FuncionTransicion::FuncionTransicion(AFD &_afd, string &_edoActual, Transicion &_transiciones){
    this->_edoActual = _edoActual;
    this->_afd = _afd;
    this->_transiciones = _transiciones;
}              
bool FuncionTransicion::esPosible(string &pal){
    bool encontroalgunEdoFinal = false;
    cout << "   ("<< _edoActual<< "," << pal[0]<< ") |- ";          
    auto ret = _transiciones.getTransiciones().find(make_pair(_edoActual,pal[0]));   
    string edoF = ret->second;
    cout << " " << ret->second;
    for(auto &var : _afd.getEdosFinales())
    {
        if(edoF == var.getNombreEdo()){
            encontroalgunEdoFinal = true;
        }
    }
    return encontroalgunEdoFinal;
}     
void FuncionTransicion::hacerSigTransicion(string &pal){
    string auxE;
    if(cont == 0){
        auxE = _edoActual;
        cont++;
    }
    if(pal.length()==1){
        esPosible(pal) ? cout << "\nSi" << endl : cout << "\nNo" << endl;
        _edoActual = auxE;        
    }
    else{            
        cout << "   ("<< _edoActual << "," << pal[0]<< ") |- ";               
        auto ret = _transiciones.getTransiciones().find(make_pair(_edoActual,pal[0]));          
        cout << " " << ret->second;
        _edoActual = ret->second;
        pal = pal.substr(1, pal.size());
        hacerSigTransicion(pal);              
    }
}       
void FuncionTransicion:: setEstadoActual(string &_edoActual){
    this->_edoActual = _edoActual;
}
string FuncionTransicion::getEstadoActual(){
    return _edoActual;
}