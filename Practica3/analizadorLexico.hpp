#include <iostream>
#include <bits/stdc++.h>
#include "../Practica2/clasesAFN.hpp"
#include "../Practica1/clases.hpp"
using namespace std;

class AnalizadorLexico
{
private:
    AFD *afd;
    AFN *afn;
    bool resultadoAnalisis;
    string nombreArchivo;
    vector<string> palReservadas = {"repeat", "Init", "End", "Add",
                                    "notTrue", "True", "False", "declare",
                                    "AsNumber", "AsFloat", "AsChar", "Array", "len", "AsString",
                                    "()", "End", "showNumber", "showFloat", "showChar", "showString", 
                                    "value", "Zero", "void", "number", "char", "string"};

    vector<string> D = {"/", "*", "+", "-", "{", "}", "(", ")", "<", ">", ".", ":", ">>", "<-", "->"};
    vector<char> E = {' '};
    char F = '_';

public:
    AnalizadorLexico(string nombreArchivo) : nombreArchivo(nombreArchivo){};
    string examinaArchivo();
    bool analizaArchivo(string);
};