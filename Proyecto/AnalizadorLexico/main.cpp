#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#include "analizadorLexico.hpp"



int main(int argc, char const *argv[])
{
    AnalizadorLexico *al = new AnalizadorLexico("archivoAnalizar.txt");
    //AnalizadorLexico *al = new AnalizadorLexico("archivoAnalizarErroresLexicos.txt");
    
    string alEA = al->examinaArchivo();    
    cout << alEA << endl;
    al->analizaArchivo(alEA);
    return 0;
}
