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
    map<pair<string, string>, int> lexemaYToken{};
    map<int, pair<string, string>> lexemaYTokenOrdenados{};

    int idToken = 0;
    int idx = 0;
    for (auto const &v : vectoresPorStringDeCadaOracion)
    {

        if (esPalReservada(v))
        {
            cout << "Palabra reservada  " << v << endl;
            lexemaYToken[make_pair("Palabra reservada", v)] = idToken;
            idx += v.size();
        }
        else
        {
            int idxPosicion = esPosibleNombre(v);
            if (regex_match(v, regexC))
            {
                // cout << "Numero posible " << v << endl;
                lexemaYToken[make_pair("Numero", v)] = idToken;
                idx += v.size();
            }
            else if (regex_match(v, regexD))
            {
                if (v == "+")
                {
                    // cout << "Simbolo suma " << v << endl;
                    lexemaYToken[make_pair("Suma", v)] = idToken;
                    idx += v.size();
                }

                else if (v == "-")
                {
                    // cout << "Simbolo resta " << v << endl;
                    lexemaYToken[make_pair("Resta", v)] = idToken;
                    idx += v.size();
                }

                else if (v == "*")
                {
                    // cout << "Simbolo multiplicacion " << v << endl;

                    lexemaYToken[make_pair("Multiplicacion", v)] = idToken;
                    idx += v.size();
                }

                else if (v == "/")
                {
                    // cout << "Simbolo divison " << v << endl;
                    lexemaYToken[make_pair("Division", v)] = idToken;
                    idx += v.size();
                }

                else if (v == "(")
                {
                    // cout << "Simbolo parentesis abre" << v << endl;
                    lexemaYToken[make_pair("Parentesis abre", v)] = idToken;
                    idx += v.size() ;
                }
                else if (v == ")")
                {
                    // cout << "Simbolo parentesis cierra" << v << endl;
                    lexemaYToken[make_pair("Parentesis cierra", v)] = idToken;
                    idx += v.size() ;
                }
                else if (v == "{")
                {
                    // cout << "Simbolo corchete abre" << v << endl;
                    lexemaYToken[make_pair("Corchete abre", v)] = idToken;
                    idx += v.size() ;
                }
                else if (v == "}")
                {
                    // cout << "Simbolo corchete abre" << v << endl;
                    lexemaYToken[make_pair("Corchete cierra", v)] = idToken;
                    idx += v.size() ;
                }
            }
            else if (idxPosicion == v.size())
            {
                // cout << "Variable " << v << endl;
                lexemaYToken[make_pair("Variable", v)] = idToken;
                idx += v.size() ;
            }
            else if (idxPosicion == v.size() + 1)
            { // Posible funcion
                // cout << "Funcion posible " << v << endl;
                lexemaYToken[make_pair("Funcion posible", v)] = idToken;
                idx += v.size() ;
            }
            else
            {
                cout << "Palabra no posible en " << v << " indice: " << idxPosicion + idx +1<< " indice no general: " << idxPosicion << endl;
                return false;
                idx += v.size() ;
            }
        }
        idx += 1;
        idToken++;
    }
    for (const auto &lYT : lexemaYToken)
    {
        lexemaYTokenOrdenados.emplace(lYT.second, lYT.first);
    };
    for (auto const &d : lexemaYTokenOrdenados)
    {
        cout << "Id Lexema: " << d.first << " valor: " << d.second.second << "  significado: " << d.second.first << endl;
    }
    idx = 0;
    bool inicio_programa = false;
    bool declaracion_variables = false;
    bool inicializacion_variables = false;
    bool llamada_funciones = false;
    bool terminacion_programa = false;
    for (auto const &i : vectoresPorStringDeCadaOracion)
    {
        if (i == "{") // inicia programa;
        {
            inicio_programa = true;
        }
        else if (inicio_programa && lexemaYTokenOrdenados[idx].second == "declare")
        {
            // Tenemos que dividr las cadenas hasta el ";"
            declaracion_variables = true;
        }
        
        else if(declaracion_variables && inicio_programa && lexemaYTokenOrdenados[idx].second=="assign"){
            inicializacion_variables = true;
        }
        
        else if(declaracion_variables && inicio_programa && inicializacion_variables &&lexemaYTokenOrdenados[idx].second=="callfunctions"){
            llamada_funciones = true;
        }else if(declaracion_variables && inicio_programa && inicializacion_variables &&lexemaYTokenOrdenados[idx].second=="}"){
            terminacion_programa = true;
        }

        if (declaracion_variables && !inicializacion_variables)
        {
            cout << "Valor declare: " << i << endl;
        }
        else if (inicializacion_variables && !llamada_funciones)
        {
            cout << "Valor inicializacion: " << i << endl;
        }else if(llamada_funciones && !terminacion_programa){
            cout << "Funciones: " << i << endl;
        }
        idx++;
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
    if (regex_search(nombre, regexA) || regex_search(nombre, regexB) || regex_search(nombre, regexF) || regex_search(nombre, regexP) || regex_search(nombre, regexC) || regex_match(nombre, regexD))
    {
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
