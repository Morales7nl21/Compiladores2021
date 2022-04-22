#include <iostream>
#include <bits/stdc++.h>
#include "analizadorLexico.hpp"
using namespace std;

void AnalizadorLexico::examinaArchivo(){
    cout << "Abriendo archivo a examinar" << nombreArchivo << endl;
    ifstream archivo(nombreArchivo); // se lee el archivo
    string linea;
    if (archivo.is_open())
        cout << "Todo bien al abrir archivo" << endl;
   
   
    while(getline(archivo,linea)){
         
        string::iterator new_end = unique(linea.begin(), linea.end(), ambosEspacios);
        linea.erase(new_end, linea.end());   
        cout << linea << endl;
    }

    archivo.close();

}
bool ambosEspacios(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }