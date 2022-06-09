#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class AnalizadorLexico
{
private:
    bool resultadoAnalisis;
    string nombreArchivo;
    vector<string> palReservadas = {"repeat", "Init", "End", "Add",
                                    "notTrue", "True", "False", "declare",
                                    "AsNumber", "AsFloat", "AsChar", "Array", "len", "AsString",
                                    "()", "End", "showNumber", "showFloat", "showChar", "showString",
                                    "value", "Zero", "void", "number", "char", "string", ">>"};

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
    }
};