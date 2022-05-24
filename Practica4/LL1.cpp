#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "LL1.hpp"

vector<string> LL1::Primero(string simbolo){
    vector<string> conjuntoRetorno;
    //Condiciones dadas de la profesora.
    if(verificaSiEsTerminal(simbolo)){ //el simbolo es terminal
        conjuntoRetorno.push_back(simbolo);
    }else if(simbolo == "ε"){
        bool band_existeE = false;
        for (auto const &cR : conjuntoRetorno)
        {
            if(cR=="ε"){
                band_existeE = true;
            }
        }
        if(!band_existeE){
            conjuntoRetorno.push_back("ε");
        }
        
    }else if(!verificaSiEsTerminal(simbolo)){
        vector<string> conjuntoSimbolosPrimeros {};      
        conjuntoSimbolosPrimeros = verificaPrimero(simbolo);
        if(!conjuntoSimbolosPrimeros.empty()){
            for (auto const &cSP : conjuntoSimbolosPrimeros)
            {
                conjuntoRetorno.push_back(cSP);
            }            
        }else{
            //ESTA MAL
            primeros[simbolo] = {simbolo};
        }
    }
    return conjuntoRetorno;
}
bool LL1::verificaSiEsTerminal(string simbolo){
    bool esTerminal = false;
    for (auto const &t : terminales)
    {
        if(t==simbolo){
            esTerminal=true;
            break;
        }
    }
    return esTerminal;
}
vector<string> LL1::verificaPrimero(string simbolo){    
    for (auto  p : primeros)
    {        
        if(p.first == simbolo && !p.second.empty()){
            return p.second;                        
        }
    }    
}