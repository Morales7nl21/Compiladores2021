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
    int cont = 0;
    for(auto const &t: transicionPorEstado){
        if(cont != 0){
            cout << t[1] << endl;
        }else if(cont == 3){
            
            cont =0;
        }
        cont++;
    }
}
