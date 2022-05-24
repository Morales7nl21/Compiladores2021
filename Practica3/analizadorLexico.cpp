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
    FuncionTransicion *ft = creaAFNyAFD();
    map<string, string> simbolos{};
    map<pair<string,int>, string> simbolos2{};
    simbolos2[make_pair("Q0",1)] = 3;
    vector<string> expresionesAlmacenadas {};
    // la vairable expAAFD sirve para ver si lo que se lleva leído es coherente a partir del AFN que se pasara a AFD y posterior se analizara dicha cadena
    string expAAFD = "";  // Expresión resultante de simbolos que se generan a partir de determinar que tipo de conjunto es, se guarda como un string
    string aEvaluar = ""; // cadena leida a partir de cada espacio
    // Regex para ver si pertenece al tipo de dato visto en clase
    regex regexA("[A-Z]+");
    regex regexB("[a-z]+");
    regex regexC("[0-9]+");
    regex regexD("['/'|'*'|'+'|'-'|'('|')'|'<'|'>'|'>>'|'<<'|':'|';'|'.'|'{'|'}'|'->']+");
    regex regexF("[_]+");
    bool bandera_soloespacio = false;
    bool palR = false;
    int id = 0;
    for (auto const &c : cad)
    {
        if (c == '_')
        {
            if (aEvaluar.size() == 0)
            {
                expAAFD.push_back('F');
            }
            else
            {
                bool bandera_num = false;
                for (auto const &c : expAAFD)
                {
                    if (c != ' ' || !regex_match(aEvaluar, regexA) || !regex_match(aEvaluar, regexB))
                    {
                        bandera_num = true;
                        break;
                    }
                    else
                    {
                        bandera_num = false;
                    }
                }
                if (bandera_num)
                    expAAFD.push_back('F');
                expAAFD = "F";
            }

            simbolos["_"] = "Simbolo de guien bajo";
        }
        if (c == ' ' || c == ';' || c == ':' || c == '(' || c == ')' || c == '{' || c == '}' || c == '_') // Es necesario para casos como: "var a AsNumber value 10;" donde el ';' va pegado o los otros signos
        {

            if (aEvaluar.size() > 0)
            {

                for (auto const &pr : palReservadas)
                {
                    if (aEvaluar == pr)
                    {
                        // cout << aEvaluar << "->is a Pal Reservada" << endl;
                        simbolos[aEvaluar] = "Palabra reservada";
                        palR = true;
                        break;
                    }
                }
                if (regex_match(aEvaluar, regexF) || c == '_')
                {
                    cout << aEvaluar << "->is a F" << endl;
                    expAAFD = "F";
                    // expAAFD.push_back('F');
                    simbolos[aEvaluar] = "Simbolo de guion bajo";
                }
                else if (regex_match(aEvaluar, regexA))
                {
                    // cout << aEvaluar << "->is a A" << endl;
                    bool band_signo_otro = true;
                    if (expAAFD.size() > 0)
                    {
                        if (expAAFD[expAAFD.size() - 1] == 'D')
                        {
                            band_signo_otro = false;
                        }
                    }
                    if (band_signo_otro)
                        expAAFD.push_back('A');
                    else
                    {
                        expAAFD = "A";
                    }
                    simbolos[aEvaluar] = "Variable mayusculas";
                }

                else if (regex_match(aEvaluar, regexB))
                {
                    // cout << aEvaluar << "->is a B" << endl;
                    bool band_signo_otro = true;
                    if (expAAFD.size() > 0)
                    {
                        if (expAAFD[expAAFD.size() - 1] == 'D')
                        {
                            band_signo_otro = false;
                        }
                    }
                    if (band_signo_otro)
                        expAAFD.push_back('B');
                    else
                    {
                        expAAFD = "B";
                    }

                    simbolos[aEvaluar] = "Variable minuscula";
                }
                else if (regex_match(aEvaluar, regexC))
                {
                    // cout << aEvaluar << "->is a C" << endl;
                    // expAAFD = "C";
                    bool band_signo_otro = true;
                    if (expAAFD.size() > 0)
                    {
                        if (expAAFD[expAAFD.size() - 1] == 'D')
                        {
                            band_signo_otro = false;
                        }
                    }
                    if (band_signo_otro)
                        expAAFD.push_back('C');
                    else
                    {
                        expAAFD = "C";
                    }

                    simbolos[aEvaluar] = "Numero entero constante";
                }

                else if (regex_match(aEvaluar, regexD))
                {
                    // cout << aEvaluar << "->is a D" << endl;
                    bool band_espacio_signo = true;
                    if (expAAFD.size() > 0)
                    {
                        for (auto const &c : expAAFD)
                        {
                            if (c != 'E')
                            {
                                //if (!(expAAFD[expAAFD.size() - 1] == 'C' ))
                                if(!(expAAFD[expAAFD.size() - 1] == 'C' ))
                                {                                    
                                    expAAFD = "D";
                                    band_espacio_signo = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (band_espacio_signo)
                    {

                        expAAFD.push_back('D');
                    }

                    if (aEvaluar == "*")
                        simbolos[aEvaluar] = "Simbolo multiplicacion";
                    else if (aEvaluar == "-")
                        simbolos[aEvaluar] = "Simbolo de resta";
                    else if (aEvaluar == "+")
                        simbolos[aEvaluar] = "Simbolo de suma";
                    else if (aEvaluar == ">>")
                        simbolos[aEvaluar] = "Simbolo de funcion";
                    else
                        simbolos[aEvaluar] = "Simbolo no operacion";
                }

                else if (c == ';' || c == ':' || c == '(' || c == ')' || c == '{' || c == '}')
                {
                    // cout << c << "->is a D" << endl;
                    string dv = "";
                    dv.push_back(c);

                    // expAAFD.push_back('D');
                    if (c == ';')
                        simbolos[dv] = "Simbolo de terminacion";
                    else if (c == ':')
                        simbolos[dv] = "Simbolo de metodo";
                    else if (c == '_')
                        simbolos[dv] = "Simbolo guion bajo";
                    else if (c == '(')
                        simbolos[dv] = "Simbolo abrir parentesis";
                    else if (c == ')')
                        simbolos[dv] = "Simbolo cerrar parentesis";
                    else if (c == '{')
                        simbolos[dv] = "Simbolo abrir llave";
                    else if (c == '}')
                        simbolos[dv] = "Simbolo cerrar llave";

                    bool band_espacio_signo = true;
                    if (expAAFD.size() > 0)
                    {
                        for (auto const &c : expAAFD)
                        {
                            if (c != 'E')
                            {
                                if (!(expAAFD[expAAFD.size() - 1] == 'C' )){
                                    expAAFD = "D";
                                    band_espacio_signo = false;
                                    break;
                                }
                                
                            }
                        }
                    }
                    if (band_espacio_signo)
                    {
                        expAAFD.push_back('D');
                    }
                }
                if (c == ' ')
                {
                    // cout << c << "->Its a E" << endl;
                    if (expAAFD.size() > 0)
                    {
                        if (expAAFD[expAAFD.size() - 1] != 'E')
                        {
                            expAAFD = "E";
                        }
                        else
                        {
                            expAAFD.push_back('E');
                        }
                    }
                    string d = "";
                    d.push_back(c);
                    simbolos[d] = "Simbolo de espacio";
                }
                else if (!palR)
                {

                    cout << "ERROR -> Simbolo no encontrado " << endl;
                    return false;
                    break;
                }
            }
            aEvaluar.clear();
        }
        else
            aEvaluar.push_back(c);
        for (auto const &c : expAAFD)
        {
            if (c != 'E')
            {
                bandera_soloespacio = false;
                break;
            }
            else
            {
                bandera_soloespacio = true;
            }
        }
        if (expAAFD.size() > 0 && bandera_soloespacio == false)
        {
            expAAFD = regex_replace(expAAFD, regex("[' ']"), "");
            expresionesAlmacenadas.push_back(expAAFD);            
        }
        
    }
    for (auto &&expToCheck : expresionesAlmacenadas)
    {
        
            cout << "EXP: [" << expToCheck <<"]" <<endl;
            ft->hacerSigTransicion(expToCheck);
            string estadoIni = "q0";
            ft->setEstadoActual(estadoIni);
    }
    
    cout << "ID\t|COMPONENTE LEXICO\t| LEXEMA  " << endl;
    for (auto const &i : simbolos)
    {
        cout << "id :" << id << "\t|" << i.second << " \t| " << i.first << endl;
        id++;
    }
    return true;
}
FuncionTransicion *AnalizadorLexico::creaAFNyAFD()
{
    // Creo y abro archivo de txt para el afn del analizador léxico
    // archAFN->muestraArchivoLeido();
    AFN *afn = new AFN(archAFN->getEstados(), archAFN->getEdoInicial(), archAFN->getEstadosFinales(), archAFN->getAlfabeto(), archAFN->getTransiciones());
    // Se crea el afn con el metodo constructor a partir de los datos tomados del archivo AFN
    afn->renombraEstados();
    // afn->muestraTransiciones();
    // afn->muestraNuevosEstadosFinales();
    AFD *afd = new AFD();

    // Se toman los valores del AFN convertido a AFD para pasarlo al objeto AFD
    afd->setAlfabeto(afn->getAlfabeto());
    afd->setEstadoInicial(afn->getEdoInicial());
    vector<string> estadosFinales{"q1","q2", "q3", "q4"};
    afd->setEstadosFinales(estadosFinales);
    // afn->muestraTransiciones();
    afd->setEstados(afn->getEstados(), afn->getTransiciones());
    Transicion *t = new Transicion(*afd);
    t->llenaTransiciones();
    string sedoini = afd->getEdoInicial().getNombreEdo();
    FuncionTransicion *ft = new FuncionTransicion(*afd, sedoini, *t);
    return ft;
}