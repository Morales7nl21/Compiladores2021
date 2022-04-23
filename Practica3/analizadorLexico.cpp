#include <iostream>
#include <bits/stdc++.h>
#include "analizadorLexico.hpp"
using namespace std;

string AnalizadorLexico::examinaArchivo()
{
    cout << "Abriendo archivo: " << nombreArchivo << endl;
    ifstream archivo(nombreArchivo); // se lee el archivo
    string linea;
    string archivoSinEspacios1Linea;
    if (archivo.is_open())
        cout << "Todo bien al abrir archivo" << endl;
    while (getline(archivo, linea))
    {
        linea = regex_replace(linea, regex("[' ']{2,}"), " "); // se remplazan mas de 2 spacios por uno con regex
        archivoSinEspacios1Linea.append(linea);
    }
    return archivoSinEspacios1Linea;
    archivo.close();
}
bool AnalizadorLexico::analizaArchivo(string cad)
{

    string aEvaluar = "";
    regex regexA("[A-Z]+");
    regex regexB("[a-z]+");
    regex regexC("[0-9]+");
    regex regexD("['/'|'*'|'+'|'-'|'('|')'|]+");
    regex regexE("\\s+");
    regex regexF("(_)+");
    bool palR = false;
    for (auto const &c : cad)
    {
        if (c == ' ' || c==';' || c==':')
        {
            if(aEvaluar.size()>0){

                 if(regex_match(aEvaluar,regexA))
                     cout << aEvaluar<< "->" << "is a A" << endl;
                 else if(regex_match(aEvaluar,regexB))
                     cout << aEvaluar<< "->" << "is a B" << endl;
                 else if(regex_match(aEvaluar,regexC))
                     cout << aEvaluar<< "->" << "is a C" << endl;
                 else if(regex_match(aEvaluar,regexD))
                     cout << aEvaluar<< "->" << "is a D" << endl;
                 else if(regex_match(aEvaluar,regexE))
                     cout << aEvaluar<< "->" << "is a E" << endl;
                 else if(regex_match(aEvaluar,regexF))
                     cout << aEvaluar<< "->" << "is a F" << endl;    
                
                else   {
                    for (auto const & pr : palReservadas)
                    {
                        if(aEvaluar == pr){
                            cout << aEvaluar<< "->" << "is a Pal Reservada" << endl;    
                            palR = true;
                            break;
                        } 
                    }                    
                    if(!palR)
                        cout << aEvaluar <<"-> Its nothing :0" << endl;
                } 

            }
            aEvaluar.clear();            
        }
        else
            aEvaluar.push_back(c);
    }    
       
    return false;
}