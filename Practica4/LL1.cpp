#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "LL1.hpp"

vector<string> LL1::primeros(string simbolo){
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
            conjunto_primeros[simbolo] = {simbolo};
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
    for (auto  p : conjunto_primeros)
    {        
        if(p.first == simbolo && !p.second.empty()){
            return p.second;                        
        }
    }  
    vector<string> r{};
    return r;  

}/*
vector<string> gramatica = {
        "E ⟶ TE’",
        "E’ ⟶ + TE’ | ε",
        "T ⟶ FT’",
        "T’ ⟶ * FT’ | ε",
        "F ⟶ id | ( E )"};
*/
void LL1::asignaTermNoTermYProduc(){
    
    vector<vector<string>> v_gramatica{};
    for (auto const &simbolo : gramatica)
    {
        stringstream ss(simbolo);
        istream_iterator<std::string> begin(ss);
        istream_iterator<std::string> end;
        vector<std::string> vector_gramatica(begin, end);    
        terminales.push_back(vector_gramatica[0]);                  
        v_gramatica.push_back(vector_gramatica);       
    }
    //Despues de que sabemos cuales son los no temrinales recorremos cada vector de la gramatica para sacar lso terminales
    bool banderaTerminalEncontrado = false;
    for (auto const &vector : v_gramatica)
    {
        for (auto const &string_simbolo : vector)
        {            
            if(!verificaSiEsTerminal(string_simbolo)){
                
                if(string_simbolo!="⟶" && string_simbolo != "|"){
                    
                    for (auto const &nt : noTerminales)
                    {
                        if(string_simbolo == nt){
                            banderaTerminalEncontrado = true;
                            break;
                        }        
                    }
                    if(!banderaTerminalEncontrado){
                        noTerminales.push_back(string_simbolo);
                    }
                    banderaTerminalEncontrado = false;
                }

                    
            }                        
        }                
    }
    cout << "NO TERMINALEs " << endl;
    for (auto const &nt : noTerminales)
    {
        cout << nt << endl;
    }
    cout << "TERMINALEs " << endl;
    for (auto const &t : terminales)
    {
        cout << t << endl;
    }
    cout << endl;
    
    

}