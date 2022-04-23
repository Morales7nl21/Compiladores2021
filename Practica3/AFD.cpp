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
void AFD::setAlfabeto(vector<string> vA){
    for (auto  const  &sA : vA)
    {
        for(auto const & cA: sA){
            _alfabeto.push_back(cA);
        }
    }
    
}
void AFD::setEstadoInicial(string eI){
    Estado edI(eI);  
    _edoInicial = edI;  
}
void AFD::setEstadosFinales(vector<string> eF){
    vector<Estado> final;
    for (auto  const &sF : eF)
    {
        Estado edosF(sF); 
        _edoFinal.push_back(edosF);
    }    
}
void AFD::setEstados(vector<string> edos, vector<vector<string>> transicionPorEstado){
    for (auto const &e : edos)
    {
        Estado edos(e); 
        _estados.push_back(edos);        
    }
        
    string edoDeTransicion = "";
    string alfabetoLetraTransicion = "";
    string edoNuevoTransicion = "";
    
    for(auto  &es: _estados){
        vector<pair<Estado,char>> parestados; 
        
        for(auto const &t: transicionPorEstado){
            edoDeTransicion = t[0];
            alfabetoLetraTransicion = t[1];
            edoNuevoTransicion = t[2];
            //cout << "EdoT: " << edoDeTransicion << " alfbLetter: "<< alfabetoLetraTransicion << " newState: " << edoNuevoTransicion << endl;
            if(edoDeTransicion == es.getNombreEdo()){
                Estado n(edoNuevoTransicion);
                parestados.push_back(make_pair(n, alfabetoLetraTransicion[0]));
            }            
        }
        es.setSigEdos(parestados);
        parestados.clear();       
    }   
}
