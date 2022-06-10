#include <iostream>
#include <bits/stdc++.h>

using namespace std;
extern vector<string> palReservadas;

class AnalizadorLexico
{
private:
    bool resultadoAnalisis;
    string nombreArchivo;

public:
    AnalizadorLexico(string nombreArchivo) : nombreArchivo(nombreArchivo){};

    string examinaArchivo();     // Parte que quita n espacios por 1 espacio
    bool analizaArchivo(string); // Parte que ya verifica

    int esPosibleNombre(string);
    int esPosibleFuncion(string, int);

    bool esPalReservada(string s)
    {
        bool esta = false;
        for (auto const &pr : palReservadas)
        {
            if (pr == s)
            {
                esta = true;
                break;
            }
        }
        if (esta)
            return true;
        return false;
    }
    vector<string> split(const string &s, char seperator)
    {
        vector<std::string> output;
        string::size_type prev_pos = 0, pos = 0;

        while ((pos = s.find(seperator, pos)) != string::npos)
        {
            string substring(s.substr(prev_pos, pos - prev_pos));
            output.push_back(substring);
            prev_pos = ++pos;
        }
        output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word
        return output;
    };
};
class AnalizadorSintactico
{
private:
    vector<int> idAAnalizar;

public:
    AnalizadorSintactico(vector<int> idAAnalizar) : idAAnalizar(idAAnalizar){};
    void setcadAnalizar(vector<int> idAAnalizar)
    {
        this->idAAnalizar = idAAnalizar;
    }
    int verificaDeclaracion();
   
    int verificaInicializacionLL1();
    int verificafuncion();
    string &corteIzquierda(string &str, string &c)
    {
        str.erase(0, str.find_first_of(c) + 1);
        return str;
    }
    string &corteDerecha(string &str, string &c)
    {
        str.erase(str.find_last_of(c) );
        return str;
    }
};
class AnalizadorSemantico
{
};