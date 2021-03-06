#include <iostream>
#include <bits/stdc++.h>
#include "proyecto.hpp"
#include "LL1.hpp"
using namespace std;
map<string, int> lexemaYToken{};
map<string, string> tiposDatoYVariable;
map<string, string> datoAsignadoValorDeclarado;
map<int, string> lexemaYTokenOrdenados{};
vector<string> palReservadas = {"repeat", "Init", "End", "Add",
                                "notTrue", "True", "False", "declare", "assign", "callfunctions", "endfunctions",
                                "AsNumber", "AsFloat", "AsChar", "Array", "len", "AsString",
                                "()", "End", "showNumber", "showFloat", "showChar", "showString",
                                "value", "Zero", "void", "number", "char", "string", ">>", "AsFunc"};
vector<string> tipoDeclaracion = {
    "AsNumber", "AsFloat", "AsChar", "Array", "AsString", "AsFunc"};
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
        cout << linea << endl;
        linea = regex_replace(linea, regex("[' ']{2,}"), " "); // se remplazan mas de 2 spacios por uno con regex
        archivoSinEspacios1Linea.append(linea);
    }
    return archivoSinEspacios1Linea;
    archivo.close();
}
bool AnalizadorLexico::analizaArchivo(string cad)
{
    AnalizadorSemantico *asem;
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
            // cout << "Palabra reservada  " << v << endl;
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

                lexemaYToken[v] = idToken;
                idx += v.size();
            }
            else if (idxPosicion == v.size())
            {
                lexemaYToken[v] = idToken;
                idx += v.size();
            }
            else if (idxPosicion == v.size() + 1)
            { // Posible funcion
                lexemaYToken[v] = idToken;
                idx += v.size();
            }
            else
            {
                cout << "[lexico] Palabra no posible en " << v << " indice: " << idxPosicion + idx + 1 << " indice no general: " << idxPosicion << endl;
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
    /*
    for (auto const &d : lexemaYTokenOrdenados)
    {
        cout << "Id Lexema: " << d.first << " valor: " << d.second << endl;
    }
    */
    AnalizadorSintactico *aSi;
    AnalizadorSemantico *aSe;
    idx = 0;
    bool inicio_programa = false;
    bool declaracion_variables = false;
    bool inicializacion_variablesLL1 = false;
    bool verificaTerminacion = false;
    bool verificoFunciones = false;
    bool llamada_funciones = false;
    bool terminacion_programa = false;
    vector<int> auxvectorAAnalizarSintacticamente{};

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

            if (vectorAAnalizarSintacticamente.size() > 1)
            {
                cout << "[sintactico] falto cerrar con ';' en la declaracion" << endl;
                break;
            }
            vectorAAnalizarSintacticamente.clear();
            inicializacion_variablesLL1 = true;
        }

        else if (declaracion_variables && inicio_programa && inicializacion_variablesLL1 && lexemaYTokenOrdenados[idx] == "callfunctions")
        {
            llamada_funciones = true;
        }
        if (declaracion_variables && inicio_programa && inicializacion_variablesLL1 && lexemaYTokenOrdenados[idx] == "endfunctions")
        {
            verificoFunciones = true;
        }
        else if (declaracion_variables && inicio_programa && inicializacion_variablesLL1 && lexemaYTokenOrdenados[idx] == "}")
        {
            terminacion_programa = true;
        }

        if (declaracion_variables && !inicializacion_variablesLL1)
        {

            // cout << "ID: " << lexemaYToken[i];
            // cout << "  Valor declare: " << i << endl;
            if (i != "declare" && i != "assign")
                vectorAAnalizarSintacticamente.push_back(lexemaYToken[i]);
            if (i == ";")
            {
                aSi = new AnalizadorSintactico(vectorAAnalizarSintacticamente);
                int nparams = aSi->verificaDeclaracion();
                // cout << "NPARAMS:" << nparams << endl;
                if (nparams < 3 || nparams > 3)
                {

                    if (nparams < 3)
                    {
                        cout << "[sintactico] Se esperaban mas parametros para la declaracion de variables en: " << endl;
                        for (auto const &vAS : vectorAAnalizarSintacticamente)
                        {
                            cout << lexemaYTokenOrdenados[vAS] << " ";
                        }
                    }
                    else if (nparams > 3)
                    {
                        cout << "[sintactico] Se esperaban ';', demaciados parametros al declarar: " << endl;
                        for (auto const &vAS : vectorAAnalizarSintacticamente)
                        {
                            cout << lexemaYTokenOrdenados[vAS] << " ";
                        }
                    }
                    vectorAAnalizarSintacticamente.clear();
                    break;
                }
                else
                {
                    asem = new AnalizadorSemantico(vectorAAnalizarSintacticamente);
                    if (!(asem->analizaSemanticamenteDeclaracion()))
                    {
                        break;
                    }
                }
                vectorAAnalizarSintacticamente.clear();
            }
        }
        else if (inicializacion_variablesLL1 && !llamada_funciones)
        {

            if (i != "assign")
                vectorAAnalizarSintacticamente.push_back(lexemaYToken[i]);
            if (i == ";")
            {
                aSi = new AnalizadorSintactico(vectorAAnalizarSintacticamente);
                if (aSi->verificaInicializacionLL1() == 0)
                {
                    string inicializacion = "";
                    cout << "[sintactico] La inicializacion no es correcta: " << inicializacion << endl;
                    for (auto const &vAS : vectorAAnalizarSintacticamente)
                    {
                        cout << lexemaYTokenOrdenados[vAS] << " ";
                    }

                    break;
                }
                else
                {
                    aSe = new AnalizadorSemantico(vectorAAnalizarSintacticamente);
                    aSe->analizaSemanticamenteAsignacion();
                    vectorAAnalizarSintacticamente.clear();
                }
            }
        }
        else if (llamada_funciones && !terminacion_programa)
        {

            if (i == "endfunctions")
            {
                llamada_funciones = false;
                verificaTerminacion = true;
            }

            else
            {
                if (!verificaTerminacion)
                {
                    cout << "Funciones: " << i << endl;
                    if (i != "callfunctions" && i != ";")
                        vectorAAnalizarSintacticamente.push_back(lexemaYToken[i]);
                    if (i == ";")
                    {

                        vectorAAnalizarSintacticamente.push_back(lexemaYToken[i]);
                        aSi = new AnalizadorSintactico(vectorAAnalizarSintacticamente);
                        if (aSi->verificafuncion() == 0)
                        {

                            cout << "[sintactico] La declaracion de la funcion no es correcta en: " << endl;
                            for (auto const &vAS : vectorAAnalizarSintacticamente)
                            {
                                cout << lexemaYTokenOrdenados[vAS] << " ";
                            }
                        }
                        vectorAAnalizarSintacticamente.clear();
                    }
                }
            }
        }
        if (verificoFunciones && verificaTerminacion)
        {

            if (vectorAAnalizarSintacticamente.size() > 2)
            {
                cout << "[sintactico] La declaracion de la funcion no es correcta falto un ';' en: " << endl;
                for (auto const &vAS : vectorAAnalizarSintacticamente)
                {
                    cout << lexemaYTokenOrdenados[vAS] << " ";
                }

                break;
            }
        }
        idx++;
    }

    bool assignboolsemantico = false;
    bool funcbool = false;
    vectorAAnalizarSintacticamente.clear();

    // Volviendo a reccorer para analizar semanticamente

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
    // cout << "CONT FUNC: " << cont << endl;
    if (cont >= 3)
        return cont;
    else
        return 0;
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
    bool palReservada = false;
    if (idAAnalizar.size() == 4 && lexemaYTokenOrdenados[idAAnalizar[1]] == "value")
    {

        for (auto const &pR : palReservadas)
        {
            if (lexemaYTokenOrdenados[idAAnalizar[0]] == pR)
            {
                cout << "[sintactico] Se esperaba un identificador que no es palabra reservada en: " << pR << endl;
                return 0;
            }
            else if (lexemaYTokenOrdenados[idAAnalizar[1]] == pR)
            {
                palReservada = true;
            }
            if (lexemaYTokenOrdenados[idAAnalizar[2]] == pR)
            {
                cout << "[sintactico] Se esperaba un identificador que no es palabra reservada en: " << pR << endl;
                return 0;
            }
        }
        if (!palReservada)
            cout << "[sintactico] Se esperaba una palabra reservada  en: " << lexemaYTokenOrdenados[idAAnalizar[1]] << endl;
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
                } /* Meter el analizador sem??ntico despues de que vimos que esta vien
                 else{

                 }
                 */
            }
        }
    }

    return 1;
}
bool AnalizadorSemantico::analizaSemanticamenteDeclaracion()
{
    regex regexA("[A-Z]+");
    regex regexB("[a-z]+");
    regex regexC("[0-9]+");
    regex regexD("[-|+|*|/|(|)|;]");
    regex regexF("[_]");
    regex regexP("[(|)|{|}]");
    regex regexEspacio("[ ]+");
    bool boolID1palReservada = false;
    bool boolID2palReservada = false;
    string palReservadaID1 = "";

    // cout << "ANALIZADOR SEMANTICO PARA: " << endl;
    /*
    for(auto const &id:idAAnalizar){
        cout << lexemaYTokenOrdenados[id] << " ";
    }
    */
    for (auto const &pR : palReservadas)
    {
        if (lexemaYTokenOrdenados[idAAnalizar[0]] == pR)
        {
            palReservadaID1 = pR;
            boolID1palReservada = true;
        }
        if (lexemaYTokenOrdenados[idAAnalizar[1]] == pR)
        {
            boolID2palReservada = true;
        }
    }
    if (boolID1palReservada)
    {
        cout << "[Semantico] Se esperaba una definicion de variable no una palabra reservada en: " << palReservadaID1;
    }
    if (regex_match(lexemaYTokenOrdenados[idAAnalizar[0]], regexC))
    {
        cout << "[Semantico] Se esperaba una definicion de variable no un numero: " << lexemaYTokenOrdenados[idAAnalizar[0]];
    }
    else if (regex_match(lexemaYTokenOrdenados[idAAnalizar[0]], regexD))
    {
        cout << "[Semantico] Se esperaba una definicion de variable no un signo: " << lexemaYTokenOrdenados[idAAnalizar[0]];
    }
    else if (regex_match(lexemaYTokenOrdenados[idAAnalizar[0]], regexF))
    {
        cout << "[Semantico] Se esperaba una definicion de variable no un guion bajo: " << lexemaYTokenOrdenados[idAAnalizar[0]];
    }
    else if (regex_match(lexemaYTokenOrdenados[idAAnalizar[0]], regexP))
    {
        cout << "[Semantico] Se esperaba una definicion de variable no un corchete o parentesis: " << lexemaYTokenOrdenados[idAAnalizar[0]];
    }
    else if (regex_match(lexemaYTokenOrdenados[idAAnalizar[0]], regexEspacio))
    {
        cout << "[Semantico] Se esperaba una definicion de variable no espacio: " << lexemaYTokenOrdenados[idAAnalizar[0]];
    }
    else
    {
        if (!boolID2palReservada)
        {
            cout << "[Semantico] Se esperaba una variable reservada no un: " << lexemaYTokenOrdenados[idAAnalizar[1]];
        }
        else
        {
            // cout << "Guardando key en tipodato: " << lexemaYTokenOrdenados[idAAnalizar[0]] << " valor: " << lexemaYTokenOrdenados[idAAnalizar[1]] << endl;
            tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[0]]] = lexemaYTokenOrdenados[idAAnalizar[1]];
            return true;
        }
    }
    return false;
}
bool AnalizadorSemantico::analizaSemanticamenteAsignacion()
{
    regex regexString("[A-Z | a-z]+"); //
    regex regexChar("[A-Z | a-z]");
    regex regexNumber("[0-9]+");
    regex regexBrackets("[(|)|{|}]");

    regex regexOperations("[+|*|/|-]");

    bool esAsignacion = false;
    /*
    for (auto const &id : idAAnalizar)
    {
        cout << lexemaYTokenOrdenados[id] << " ";
    }
    cout << endl;
    */
    if ("value" == lexemaYTokenOrdenados[idAAnalizar[1]])
        esAsignacion = true;

    if (esAsignacion && idAAnalizar.size() == 4)
    {

        if (tiposDatoYVariable.count(lexemaYTokenOrdenados[idAAnalizar[0]]))
        { // Si esta declarado
            if (tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[0]]] == "AsNumber")
            {
                if (regex_match(lexemaYTokenOrdenados[idAAnalizar[2]], regexNumber))
                {
                    //cout << " Declaracion correcta: " << lexemaYTokenOrdenados[idAAnalizar[0]] << "->" << tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[0]]] << "->" << lexemaYTokenOrdenados[idAAnalizar[2]] << endl;
                    return true;
                }
            }
            else if (tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[0]]] == "AsChar")
            {
                if (regex_match(lexemaYTokenOrdenados[idAAnalizar[2]], regexChar))
                {
                    //cout << " Declaracion correcta: " << lexemaYTokenOrdenados[idAAnalizar[0]] << "->" << tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[0]]] << "->" << lexemaYTokenOrdenados[idAAnalizar[2]] << endl;
                    return true;
                }
            }
            else if (tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[0]]] == "AsString")
            {
                if (regex_match(lexemaYTokenOrdenados[idAAnalizar[2]], regexString))
                {
                    //cout << " Declaracion correcta: " << lexemaYTokenOrdenados[idAAnalizar[0]] << "->" << tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[0]]] << "->" << lexemaYTokenOrdenados[idAAnalizar[2]] << endl;
                    return true;
                }
            }
            cout << "[Semantico] Valor incompatible: " << lexemaYTokenOrdenados[idAAnalizar[2]] << " se esperaba: " << tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[0]]] << endl;
            return false;
        }
        else
        {
            cout << "[Semantico] Variable no declarada: " << lexemaYTokenOrdenados[idAAnalizar[0]] << endl;
        }
    }
    else
    {

        // Checamos de nuevo si existe una asignacion
        if ("value" == lexemaYTokenOrdenados[idAAnalizar[1]])
        {

            if (tiposDatoYVariable.count(lexemaYTokenOrdenados[idAAnalizar[0]]))
            { // existe si est?? declarada
                if (tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[0]]] == "AsNumber")
                { // checamos que todos sean numeros
                    int cont_omision = 0;
                    for (auto const &i : idAAnalizar)
                    {
                        if (cont_omision >= 2)
                        {
                            if (!regex_match(lexemaYTokenOrdenados[i], regexBrackets) && !regex_match(lexemaYTokenOrdenados[i], regexNumber) && !regex_match(lexemaYTokenOrdenados[i], regexOperations) && lexemaYTokenOrdenados[i] != ";")
                            {

                                if (tiposDatoYVariable.count(lexemaYTokenOrdenados[i]))
                                {
                                    if (tiposDatoYVariable[lexemaYTokenOrdenados[i]] != "AsNumber")
                                        cout << "[Semantico] Se esperaba una variable de tipo 'AsNumber', pero se encontro: " << lexemaYTokenOrdenados[i] << " de tipo: " << tiposDatoYVariable[lexemaYTokenOrdenados[i]] << endl;
                                }
                                else
                                {
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsNumber', pero no se encontro el tipo de dato de la variable: " << lexemaYTokenOrdenados[i] << endl;
                                }
                            }
                        }
                        cont_omision++;
                    }
                }
            }
        }
        else
        { // Checamos icompatibilidad de datos con base al primer dato
            string tipoAUsar = "";
            int final_operacion = 0;
            while (tipoAUsar == "")
            {
                if (final_operacion < idAAnalizar.size() - 1)
                {
                    if (regex_match(lexemaYTokenOrdenados[idAAnalizar[final_operacion]], regexNumber))
                        tipoAUsar = "AsNumber";
                    else if (tiposDatoYVariable.count(lexemaYTokenOrdenados[idAAnalizar[final_operacion]]))
                        tipoAUsar = tiposDatoYVariable[lexemaYTokenOrdenados[idAAnalizar[final_operacion]]];
                    else if (regex_match(lexemaYTokenOrdenados[idAAnalizar[final_operacion]], regexChar))
                        tipoAUsar = "AsChar";
                    else if (regex_match(lexemaYTokenOrdenados[idAAnalizar[final_operacion]], regexString))
                        tipoAUsar = "AsString";
                    final_operacion++;
                }
                else
                    break;
            }

            cout << "tipoAusar " << tipoAUsar << endl;
            int cont_omision = 0;

            for (auto const &i : idAAnalizar)
            {
                if (cont_omision > 0)
                {
                    if (tipoAUsar == "AsNumber")
                    {
                        if (!regex_match(lexemaYTokenOrdenados[i], regexBrackets) && !regex_match(lexemaYTokenOrdenados[i], regexNumber) && !regex_match(lexemaYTokenOrdenados[i], regexOperations) && lexemaYTokenOrdenados[i] != ";")
                        {
                            if (tiposDatoYVariable.count(lexemaYTokenOrdenados[i]))
                            {
                                if (tiposDatoYVariable[lexemaYTokenOrdenados[i]] != "AsNumber")
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsNumber', pero se encontro: " << lexemaYTokenOrdenados[i] << " de tipo: " << tiposDatoYVariable[lexemaYTokenOrdenados[i]] << endl;
                            }
                            else
                            {
                                cout << "[Semantico] Se esperaba una variable de tipo 'AsNumber', pero no se encontro el tipo de dato de la variable: " << lexemaYTokenOrdenados[i] << endl;
                            }
                        }
                    }
                    else if (tipoAUsar == "AsChar")
                    {
                        if (!regex_match(lexemaYTokenOrdenados[i], regexBrackets) && (lexemaYTokenOrdenados[i] != "+") && lexemaYTokenOrdenados[i] != ";")
                        {
                            if (lexemaYTokenOrdenados[i] == "*" || lexemaYTokenOrdenados[i] == "/" || lexemaYTokenOrdenados[i] == "-")
                            {
                                cout << "[Semantico] Solo se puede concatenar con simbolo '+', se encontro " << lexemaYTokenOrdenados[i] << endl;
                            }
                            else if (regex_match(lexemaYTokenOrdenados[i], regexNumber))
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsString', pero se encontro 'AsNumber' en: " << lexemaYTokenOrdenados[i] << endl;                                
                            else if (tiposDatoYVariable.count(lexemaYTokenOrdenados[i]))
                            {
                                if (tiposDatoYVariable[lexemaYTokenOrdenados[i]] != "AsChar")
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsChar', pero se encontro: " << lexemaYTokenOrdenados[i] << " de tipo: " << tiposDatoYVariable[lexemaYTokenOrdenados[i]] << endl;
                            }
                            else
                            {                                
                                if (regex_match(tiposDatoYVariable[lexemaYTokenOrdenados[i]], regexString))
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsChar', pero no se encontro el tipo 'AsString' en: " << lexemaYTokenOrdenados[i] << endl;
                                if (!regex_match(tiposDatoYVariable[lexemaYTokenOrdenados[i]], regexChar))
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsChar', pero no se encontro el tipo de dato de la variable: " << lexemaYTokenOrdenados[i] << endl;
                            }
                        }
                    }
                    else if (tipoAUsar == "AsString")
                    {
                        if (!regex_match(lexemaYTokenOrdenados[i], regexBrackets) && (lexemaYTokenOrdenados[i] != "+") && lexemaYTokenOrdenados[i] != ";")
                        {
                            if (lexemaYTokenOrdenados[i] == "*" || lexemaYTokenOrdenados[i] == "/" || lexemaYTokenOrdenados[i] == "-")
                            {
                                cout << "[Semantico] Solo se puede concatenar con simbolo '+', se encontro " << lexemaYTokenOrdenados[i] << endl;
                            }
                            else if (regex_match(lexemaYTokenOrdenados[i], regexNumber))
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsString', pero se encontro 'AsNumber' en: " << lexemaYTokenOrdenados[i] << endl;                                
                                
                            else if (tiposDatoYVariable.count(lexemaYTokenOrdenados[i]))
                            {
                                if (tiposDatoYVariable[lexemaYTokenOrdenados[i]] != "AsString")
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsString', pero se encontro: " << lexemaYTokenOrdenados[i] << " de tipo: " << tiposDatoYVariable[lexemaYTokenOrdenados[i]] << endl;
                            }
                            else
                            {
                                if (regex_match(tiposDatoYVariable[lexemaYTokenOrdenados[i]], regexChar))
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsString', pero se encontro 'AsChar' en: " << lexemaYTokenOrdenados[i] << endl; 
                                if (!regex_match(tiposDatoYVariable[lexemaYTokenOrdenados[i]], regexString))
                                    cout << "[Semantico] Se esperaba una variable de tipo 'AsString', pero no se encontro el tipo de dato de la variable: " << lexemaYTokenOrdenados[i] << endl;                                
                            }
                        }
                    }
                }

                cont_omision++;
            }
        }
    }
}