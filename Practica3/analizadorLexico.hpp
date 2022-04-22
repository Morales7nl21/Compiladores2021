#include <iostream>
#include <bits/stdc++.h>
#include "../Practica2/clasesAFN.hpp"
#include "../Practica1/clases.hpp"
using namespace std;

class AnalizadorLexico{
    private:
        AFD* afd;
        AFN* afn; 
        bool resultadoAnalisis;
        string nombreArchivo;
    public:
        friend bool ambosEspacios(char, char);   
        AnalizadorLexico(string nombreArchivo):nombreArchivo(nombreArchivo){};
        void examinaArchivo();
        void analizaArchivo();
};