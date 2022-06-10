#include <iostream>
#include <bits/stdc++.h>
#include "proyecto.hpp"
#include "LL1.hpp"
using namespace std;
map<string, int> lexemaYToken{};
map<int, string> lexemaYTokenOrdenados{};
vector<string> palReservadas = {"repeat", "Init", "End", "Add",
                                "notTrue", "True", "False", "declare", "assign", "callfunctions",
                                "AsNumber", "AsFloat", "AsChar", "Array", "len", "AsString",
                                "()", "End", "showNumber", "showFloat", "showChar", "showString",
                                "value", "Zero", "void", "number", "char", "string", ">>"};
vector<string> tipoDeclaracion = {
    "AsNumber", "AsFloat", "AsChar", "Array", "AsString"};
vector<string> declaracionFuncion = {
    "showstring", "pow", "showint", "showchar"};

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

    int idToken = 0;
    int idx = 0;
    for (auto const &v : vectoresPorStringDeCadaOracion)
    {

        if (esPalReservada(v))
        {
            cout << "Palabra reservada  " << v << endl;
            lexemaYToken[v] = idToken;
            idx += v.size();
        }
        else
        {
            int idxPosicion = esPosibleNombre(v);
            if (regex_match(v, regexC))
            {
                // cout << "Numero posible " << v << endl;
                lexemaYToken[v] = idToken;
                idx += v.size();
            }
            else if (regex_match(v, regexD))
            {
                if (v == "+")
                {
                    // cout << "Simbolo suma " << v << endl;
                    lexemaYToken[v] = idToken;
                    idx += v.size();
                }

                else if (v == "-")
                {
                    // cout << "Simbolo resta " << v << endl;
                    lexemaYToken[v] = idToken;
                    idx += v.size();
                }

                else if (v == "*")
                {
                    // cout << "Simbolo multiplicacion " << v << endl;

                    lexemaYToken[v] = idToken;
                    idx += v.size();
                }

                else if (v == "/")
                {
                    // cout << "Simbolo divison " << v << endl;
                    lexemaYToken[v] = idToken;
                    idx += v.size();
                }

                else if (v == "(")
                {
                    // cout << "Simbolo parentesis abre" << v << endl;
                    lexemaYToken[v] = idToken;
                    idx += v.size();
                }
                else if (v == ")")
                {
                    // cout << "Simbolo parentesis cierra" << v << endl;
                    lexemaYToken[v] = idToken;
                    idx += v.size();
                }
                else if (v == "{")
                {
                    // cout << "Simbolo corchete abre" << v << endl;
                    lexemaYToken[v] = idToken;
                    idx += v.size();
                }
                else if (v == "}")
                {
                    // cout << "Simbolo corchete abre" << v << endl;
                    lexemaYToken[v] = idToken;
                    idx += v.size();
                }
                else if (v == ";")
                {
                    // cout << "Simbolo corchete abre" << v << endl;
                    lexemaYToken[v] = idToken;
                    idx += v.size();
                }
            }
            else if (idxPosicion == v.size())
            {
                // cout << "Variable " << v << endl;
                lexemaYToken[v] = idToken;
                idx += v.size();
            }
            else if (idxPosicion == v.size() + 1)
            { // Posible funcion
                // cout << "Funcion posible " << v << endl;
                lexemaYToken[v] = idToken;
                idx += v.size();
            }
            else
            {
                cout << "Palabra no posible en " << v << " indice: " << idxPosicion + idx + 1 << " indice no general: " << idxPosicion << endl;
                return false;
                idx += v.size();
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
        cout << "Id Lexema: " << d.first << " valor: " << d.second << endl;
    }

    AnalizadorSintactico *aSi;
    AnalizadorSemantico *aSe;
    idx = 0;
    bool inicio_programa = false;
    bool declaracion_variables = false;
    bool inicializacion_variablesLL1 = false;
    
    bool llamada_funciones = false;
    bool terminacion_programa = false;
    vector<int> vectorAAnalizarSintacticamente{};
    for (auto const &i : vectoresPorStringDeCadaOracion)
    {

        if (i == "{") // inicia programa;
        {
            inicio_programa = true;
        }
        else if (inicio_programa && lexemaYTokenOrdenados[idx] == "declare")
        {
            // Tenemos que dividr las cadenas hasta el ";"
            declaracion_variables = true;
        }
        // Falta contemplar la asignacion sin operadores
        else if (declaracion_variables && inicio_programa && lexemaYTokenOrdenados[idx] == "assign")
        {
            inicializacion_variablesLL1 = true;
        }

        else if (declaracion_variables && inicio_programa && inicializacion_variablesLL1 && lexemaYTokenOrdenados[idx] == "callfunctions")
        {
            llamada_funciones = true;
        }
        else if (declaracion_variables && inicio_programa && inicializacion_variablesLL1 && lexemaYTokenOrdenados[idx] == "}")
        {
            terminacion_programa = true;
        }

        if (declaracion_variables && !inicializacion_variablesLL1)
        {

            cout << "ID: " << lexemaYToken[i];
            cout << "  Valor declare: " << i << endl;
            if (i != "declare")
                vectorAAnalizarSintacticamente.push_back(lexemaYToken[i]);
            if (i == ";")
            {
                aSi = new AnalizadorSintactico(vectorAAnalizarSintacticamente);
                if (aSi->verificaDeclaracion() == 0)
                {
                    string declarion = "";
                    for (auto const &vAS : vectorAAnalizarSintacticamente)
                    {
                        declarion.push_back(vAS);
                    }
                    cout << "[sintactico] Se esperaban mas parametros para la declaracion de variables en: " << declarion << endl;
                    break;
                }
                vectorAAnalizarSintacticamente.clear();
            }
        }
        else if (inicializacion_variablesLL1 && !llamada_funciones)
        {

            cout << "Valor inicializacion: " << i << endl;
            if (i != "assign")
                vectorAAnalizarSintacticamente.push_back(lexemaYToken[i]);
            if (i == ";")
            {
                aSi = new AnalizadorSintactico(vectorAAnalizarSintacticamente);
                if (aSi->verificaInicializacionLL1() == 0)
                {
                    string inicializacion = "";
                    for (auto const &vAS : vectorAAnalizarSintacticamente)
                    {
                        inicializacion.push_back(vAS);
                    }
                    cout << "[sintactico] La inicializacion no es correcta: " << inicializacion << endl;
                    break;
                }
                vectorAAnalizarSintacticamente.clear();
            }
        }
        else if (llamada_funciones && !terminacion_programa)
        {

            cout << "Funciones: " << i << endl;
            if (i != "callfunctions")
                vectorAAnalizarSintacticamente.push_back(lexemaYToken[i]);
            if (i == ";")
            {
                aSi = new AnalizadorSintactico(vectorAAnalizarSintacticamente);
                /*
                if (aSi->verificafuncion())
                {
                }
                */
                vectorAAnalizarSintacticamente.clear();
            }
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
int AnalizadorSintactico::verificaDeclaracion()
{
    int cont = 0;
    for (auto const &id : idAAnalizar)
    {
        cont++;
    }
    return cont;
}
int AnalizadorSintactico::verificafuncion()
{
    string corte = ":";
    string func = lexemaYTokenOrdenados[idAAnalizar[0]];
    corteIzquierda(func, corte);
    corte = "(";
    corteDerecha(func, corte);
    for (auto const &f : declaracionFuncion)
    {
        if (func == f)
            return 1;
    }

    return 0;
}
int AnalizadorSintactico::verificaInicializacionLL1()
{ // Ocupamos LL1
    regex regexD("[-|+|*|/|(|)|;]+");
    regex regexC("[0-9]+");

    // cout << "Analizando fuincion" << endl;
    string idS = "";

    vector<string> cadAAnalizarLL1{};
    LL1 *l1 = new LL1();
    if (idAAnalizar.size() == 4 && lexemaYTokenOrdenados[idAAnalizar[1]] == "value")
    {
        cout << "4: " << endl
             << idAAnalizar[0] << " " << idAAnalizar[1] << " " << idAAnalizar[2] << endl;
    }
    else
    {
        if (lexemaYTokenOrdenados[idAAnalizar[1]] == "value")
        {
            idAAnalizar.erase(idAAnalizar.begin());
            idAAnalizar.erase(idAAnalizar.begin());
        }

        for (auto &id : idAAnalizar)
        {
            idS = lexemaYTokenOrdenados[id];

            if (!regex_match(idS, regexD))
            {
                // cout << "id Dif: " << idS << endl;
                idS = "id";
                cadAAnalizarLL1.push_back(idS);
            }
            else if (idS != ";")
            {
                if (idS == "-")
                    idS = "+";
                else if (idS == "/")
                    idS = "*";
                cadAAnalizarLL1.push_back(idS);
            }
            else
            {

                idS = "$";
                cadAAnalizarLL1.push_back(idS);
                for (auto const &cll1 : cadAAnalizarLL1)
                {
                    // cout << "Analizando:" << cll1 << endl;
                }

                if (!(l1->ingresaCadena(cadAAnalizarLL1)))
                {
                    cadAAnalizarLL1.clear();
                    return 0;
                } /* Meter el analizador semántico despues de que vimos que esta vien
                 else{

                 }
                 */
            }
        }
    }

    return 1;
}
int verificaInicializacion()
{
}