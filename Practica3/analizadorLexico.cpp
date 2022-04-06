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
         linea.erase(remove(linea.begin(), linea.end(), ' '), linea.end());
        linea.erase(remove(linea.begin(), linea.end(), '\t'), linea.end());
    }

    archivo.close();

}