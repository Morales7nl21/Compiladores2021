#include <bits/stdc++.h>
#include <iostream>

#include "proyecto.hpp"
#include "LL1.hpp"

using namespace std;
int main(int argc, char const *argv[])
{
    //AnalizadorLexico *al = new AnalizadorLexico("archivoAnalizar.txt"); //Comenzamos a analizar lexicamente    
    //AnalizadorLexico *al = new AnalizadorLexico("archivoAnalizarErroresLexicos.txt");
    //AnalizadorLexico *al = new AnalizadorLexico("archivoAnalizarErroresSintacticos.txt");
    AnalizadorLexico *al = new AnalizadorLexico("archivoAnalizarErroresSemanticos.txt"); //Comenzamos a analizar lexicamente
    string alEA = al->examinaArchivo();    
    cout << alEA << endl;
    al->analizaArchivo(alEA);
    return 0;
}
