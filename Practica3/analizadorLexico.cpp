#include <iostream>
#include <bits/stdc++.h>
#include "analizadorLexico.hpp"
using namespace std;

string AnalizadorLexico::examinaArchivo()
{
    cout << "Abriendo archivo: " << nombreArchivo << endl;
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
    FuncionTransicion *ft =  creaAFNyAFD();
    map<string, string> simbolos {}; 
    
    //la vairable expAAFD sirve para ver si lo que se lleva leído es coherente a partir del AFN que se pasara a AFD y posterior se analizara dicha cadena
    string expAAFD=""; // Expresión resultante de simbolos que se generan a partir de determinar que tipo de conjunto es, se guarda como un string
    string aEvaluar = ""; // cadena leida a partir de cada espacio
    //Regex para ver si pertenece al tipo de dato visto en clase
    regex regexA("[A-Z]+");
    regex regexB("[a-z]+");
    regex regexC("[0-9]+");
    regex regexD("['/'|'*'|'+'|'-'|'('|')'|'<'|'>'|'>>'|'<<'|':'|';'|'.'|'{'|'}'|'->']+");
    regex regexF("(_)+");
   

    bool palR = false;
    int id =0;
    for (auto const &c : cad)
    {
        if (c == ' ' || c == ';' || c == ':' || c == '(' || c == ')' || c == '{' || c == '}' || c == '_') //Es necesario para casos como: "var a AsNumber value 10;" donde el ';' va pegado o los otros signos
        {
            if (c == ' '){
                    //cout << c << "->Its a E" << endl;
                    expAAFD.push_back('E');
                    string d = "";
                    d.push_back(c);
                    simbolos[d] = "Space";
            }
                
            if (aEvaluar.size() > 0)
            {                               
                    for (auto const &pr : palReservadas)
                    {
                        if (aEvaluar == pr)
                        {
                            //cout << aEvaluar << "->is a Pal Reservada" << endl;                            
                            simbolos[aEvaluar] = "Palabra reservado";
                            palR = true;
                            break;
                        }
                    }
                    if (regex_match(aEvaluar, regexA)){
                        //cout << aEvaluar << "->is a A" << endl;
                          expAAFD.push_back('A');
                          simbolos[aEvaluar] = "Variable mayusculas";
                    }
                    
                else if (regex_match(aEvaluar, regexB)){
                    //cout << aEvaluar << "->is a B" << endl;
                    expAAFD.push_back('B');
                    simbolos[aEvaluar] = "Variable minuscula";
                }
                else if (regex_match(aEvaluar, regexC)){
                    //cout << aEvaluar << "->is a C" << endl;
                    expAAFD.push_back('C');
                    simbolos[aEvaluar] = "Numero";
                }
                    
                else if (regex_match(aEvaluar, regexD)){
                    //cout << aEvaluar << "->is a D" << endl;
                    expAAFD.push_back('D');
                    simbolos[aEvaluar] = "Simbolo";
                }
                    
                else if (regex_match(aEvaluar, regexF)){
                    //cout << aEvaluar << "->is a F" << endl;
                    expAAFD.push_back('F');
                    simbolos[aEvaluar] = "Es guion bajo";
                }
                    
                else if (c == ';' || c == ':' || c == '(' || c == ')' || c == '{' || c == '}' || c == '_'){
                    //cout << c << "->is a D" << endl;  
                    string dv = "";  
                    dv.push_back(c);
                    expAAFD.push_back('D');
                    simbolos[dv] = "Simbolo";
                }
                    
                else if (!palR){
                    cout << aEvaluar << "->Its nothing :0" << endl;                    
                }            
                                                           
            }
            aEvaluar.clear();
        }
        else
            aEvaluar.push_back(c);
        
    }
    cout << "EXP: " << expAAFD << endl;
    for (auto const &i : simbolos)
    {
        cout << i.first << " - " << i.second << " id :  " <<id << endl;
        id++;
    }
    
    ft->hacerSigTransicion(expAAFD);
    
    return false;
}
FuncionTransicion*  AnalizadorLexico::creaAFNyAFD(){
     //Creo y abro archivo de txt para el afn del analizador léxico    
    archAFN->muestraArchivoLeido();  
    AFN* afn = new AFN(archAFN->getEstados(),archAFN->getEdoInicial(), archAFN->getEstadosFinales(),archAFN->getAlfabeto(),archAFN->getTransiciones());           
    //Se crea el afn con el metodo constructor a partir de los datos tomados del archivo AFN        
    afn->renombraEstados();    
    //afn->muestraTransiciones();
    //afn->muestraNuevosEstadosFinales();
    AFD *afd = new AFD();
            
    // Se toman los valores del AFN convertido a AFD para pasarlo al objeto AFD
    afd->setAlfabeto(afn->getAlfabeto());
    afd->setEstadoInicial(afn->getEdoInicial());
    vector<string> estadosFinales {"q2", "q3", "q4", "q5"};
    afd->setEstadosFinales(estadosFinales);
    //afn->muestraTransiciones();
    afd->setEstados(afn->getEstados(),afn->getTransiciones());
    Transicion* t = new Transicion(*afd);    
    t->llenaTransiciones();
    string sedoini = afd->getEdoInicial().getNombreEdo();
    FuncionTransicion *ft = new FuncionTransicion(*afd,sedoini,*t);    
    return ft;
}