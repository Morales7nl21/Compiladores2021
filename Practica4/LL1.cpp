#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <sstream>
#include "LL1.hpp"

void LL1::primeros(const vector<string> &elementoAbuscarPrimero, vector<string> &conjuntoRetorno)
{

    for (auto const &eAP : elementoAbuscarPrimero)
    {
        if (!verificaSiEsNoTerminal(eAP))
        { // el simbolo es terminal
            bool band_existeE = false;
            for (auto const &cR : conjuntoRetorno)
            {
                if (cR == eAP)
                {
                    band_existeE = true;
                }
            }
            if (!band_existeE)
            {
                conjuntoRetorno.push_back(eAP);
            }
        }
        else if (eAP == "ε")
        {
            bool band_existeE = false;
            for (auto const &cR : conjuntoRetorno)
            {
                if (cR == "ε")
                {
                    band_existeE = true;
                }
            }
            if (!band_existeE)
            {
                conjuntoRetorno.push_back("ε");
            }
        }
        else if (verificaSiEsNoTerminal(eAP))
        {
            for (auto const &pNC : primerosNoConjunto)
            {                
                if(eAP == pNC.first ){
                    primeros(pNC.second, conjuntoRetorno);
                }
            }            
        }
        
    }
}
bool LL1::verificaSiEsNoTerminal(string simbolo)
{
    bool esTerminal = false;
    for (auto const &t : noTerminales)
    {
        if (t == simbolo)
        {
            esTerminal = true;
            break;
        }
    }
    return esTerminal;
}
vector<string> LL1::verificaPrimero(string simbolo)
{
    for (auto p : conjunto_primeros)
    {
        if (p.first == simbolo && !p.second.empty())
        {
            return p.second;
        }
    }
    vector<string> r{};
    return r;

} /*
 vector<string> gramatica = {
         "E ⟶ T E’",
         "E’ ⟶ + T E’ | ε",
         "T ⟶ FT’",
         "T’ ⟶ * FT’ | ε",
         "F ⟶ id | ( E )"};
 */
void LL1::asignaTermNoTermYProduc()
{

    for (auto const &simbolo : gramatica)
    {
        stringstream ss(simbolo);
        istream_iterator<std::string> begin(ss);
        istream_iterator<std::string> end;
        vector<std::string> vector_gramatica(begin, end);
        noTerminales.push_back(vector_gramatica[0]);
        v_gramatica.push_back(vector_gramatica);
    }
    // Despues de que sabemos cuales son los no temrinales recorremos cada vector de la gramatica para sacar lso terminales
    bool banderaTerminalEncontrado = false;
    for (auto const &vector : v_gramatica)
    {
        for (auto const &string_simbolo : vector)
        {
            if (!verificaSiEsNoTerminal(string_simbolo))
            {

                if (string_simbolo != "->" && string_simbolo != "|")
                {

                    for (auto const &nt : noTerminales)
                    {
                        if (string_simbolo == nt)
                        {
                            banderaTerminalEncontrado = true;
                            break;
                        }
                    }
                    if (!banderaTerminalEncontrado)
                    {
                        terminales.push_back(string_simbolo);
                    }
                    banderaTerminalEncontrado = false;
                }
            }
        }
    }
}

void LL1::obtienePrimeros()
{
    int cont = 0;
    vector<string> r{};
    
    for (auto const &t : noTerminales)
    {

        ostringstream vts;
        copy(v_gramatica[cont].begin(), v_gramatica[cont].end() - 1, ostream_iterator<string>(vts, " "));
        vts << v_gramatica[cont].back(); // se agrega ultimo elemento sin identificador ','
        string vts_s = vts.str();        // contiene el elemento que va despues del simbolo de produce "->"
        // rightTrim(vts_s);
        vector<string> delimitadores{"->", " "};
        vector<string> sentencias{}; // contiene todas las producciones despues de or '|'

        leftTrim(vts_s, delimitadores[0]); // Cortamos la cadena hasta -> por izquierda
        sentencias = split(vts_s, '|');

        // rightTrim(vts_s, delimitadores[1]); //
        for (auto &&i : sentencias)
        {
            // LIMPIAMOS DATA pa dejar solo los primeros de los conjuntos
            if (i[0] == ' ')
                i = i.substr(1, i.size());
            if (i.size() > 2)
                rightTrim(i, delimitadores[1]); // cortamos la cadena despues del priemr space para obtener solo el primer elemnto
            i.erase(remove(i.begin(), i.end(), ' '), i.end());
            // cout << "S " << i  << " z: "<< i.length()<< endl;
        }

        primerosNoConjunto.push_back(make_pair(t, sentencias)); // Se añade al grupo de pares de primeros
        cont++;
    }

    cout << "NO Terminales" << endl;
    for (auto const &t : noTerminales)
    {
        cout << t << endl;
    }
    cout << "Terminales" << endl;
    for (auto const &t : terminales)
    {
        cout << t << endl;
    }
    cout << "Pares primero" << endl;

    for (auto const &pnc : primerosNoConjunto)
    {
        cout << pnc.first << ": ";
        for (auto const &conjP : pnc.second)
        {
            cout << conjP << ",";
        }
        cout << endl;
    }
    
    
    for (auto const &pnc : primerosNoConjunto)
    {
        vector<string> cr{};
        cout << "ENCONTRANDO PRIMEROS" << endl;
        
        cout << pnc.first << ": ";
        primeros(pnc.second, cr);
        
        for (auto const &i : cr)
        {
             cout << i << endl;
        }
        
    }
    
    cout << endl
         << endl;


}