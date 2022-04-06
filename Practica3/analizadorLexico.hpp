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
    public:
        void examinaArchivo();
        void analizaArchivo();
};