#include <iostream>
#include <bits/stdc++.h>
#include "analizadorLexico.hpp"
using namespace std;

string AnalizadorLexico::examinaArchivo()
{
    // cout << "Abriendo archivo: " << nombreArchivo << endl;
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

    regex regexA("[A-Z]+");
    regex regexB("[a-z]+");
    regex regexC("[0-9]+");
    regex regexD("[-|'+'|'*'|'/'|'='|'('|')'|'{'|'}'|';'|':'|',']");
    regex regexF("[_]+");

    vector<string> vectoresPorStringDeCadaOracion = split(cad, ' ');
    map<int, pair<string, string>> lexemaYToken{};
    int idToken = 0;
    for (auto const &v : vectoresPorStringDeCadaOracion)
    {
        if (esPalReservada(v))
        {
            cout << "Palabra reservada  " << v << endl;
            lexemaYToken[idToken] = (make_pair(v, "Palabra reservada"));
        }
        else
        {
            int idxPosicion = esPosibleNombre(v);
            if (regex_match(v, regexC))
            {
                cout << "Numero posible " << v << endl;
                lexemaYToken[idToken] = (make_pair(v, "Numero"));
            }else if(regex_match(v,regexD)){
                cout << "Simbolo Posible " << v << endl;
                lexemaYToken[idToken] = (make_pair(v, "Simbolo"));
            }
            else if (idxPosicion == v.size())
            {
                cout << "Palabra posible " << v << endl;
                lexemaYToken[idToken] = (make_pair(v, "Palabra reservada"));
            }
            else if (idxPosicion == v.size() + 1)
            { // Posible funcion
                cout << "Funcion posible " << v << endl;
                lexemaYToken[idToken] = (make_pair(v, "Funcion"));
            }
            else
            {
                cout << "Palabra no posible en " << v << " indice: " << idxPosicion << endl;
            }
        }
    }

    return true;
}
int AnalizadorLexico::esPosibleNombre(string nombre)
{
    regex regexA("[A-Z]+");
    regex regexB("[a-z]+");
    regex regexC("[0-9]+");
    regex regexD("['-'|'+'|'*'|'/'|'='|'('|')'|'{'|'}'|';'|':'|',']");
    regex regexF("[_]");
    regex regexP("[(|)]");

    bool primero = true;
    int cont = 0;
    int contF = 0;
    for (auto const &c : nombre)
    {
        string tmpC;
        tmpC.push_back(c);
        if (primero)
            primero = false;
        else
        {
            if (regex_match(tmpC, regexA))
                return cont;
            else if (regex_match(tmpC, regexF))
                return cont;
            else
            {
                if (c == ':')
                {
                    contF++;
                }
                if (contF == 1)
                {
                    if (regex_match(tmpC, regexP))
                    {

                        int id = esPosibleFuncion(nombre, cont);
                        if (id != nombre.size())
                        {
                            return id;
                        }
                        else
                        {
                            return nombre.size() + 1;
                        }
                    }
                }
            }
        }
        cont++;
        tmpC.clear();
    }
    if(regex_search(nombre,regexA) || regex_search(nombre,regexB) || regex_search(nombre,regexF) || regex_search(nombre,regexP) || regex_search(nombre,regexC) || regex_match(nombre,regexD)){
        return nombre.size();
    }
    return 0;
    
    
}
int AnalizadorLexico::esPosibleFuncion(string nombre, int id)
{
    bool parAbre = false;
    bool parCierra = false;
    int contParAbre = 0;
    int contParCierra = 0;

    if (nombre[id] == '(')
    {
        parAbre = true;
        contParAbre++;
    }
    else
        return id;

    if (id + 1 < nombre.size())
    {
        for (int i = id + 1; i < nombre.size(); i++)
        {
            if (nombre[i] == ')')
            {
                parCierra = true;
                contParCierra++;
            }
            else if (nombre[i] == '(')
            {
                return id;
            }
            if (contParCierra > 2)
            {
                return id;
            }
        }
    }
    else
    {
        return id;
    }
    return nombre.size();
}
