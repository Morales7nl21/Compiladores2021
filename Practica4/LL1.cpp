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
            if (conjunto_primeros.find(eAP) != conjunto_primeros.end())
            {

                for (auto const &cpf : conjunto_primeros[eAP])
                {
                    bool band_existeE = false;
                    for (auto const &cR : conjuntoRetorno)
                    {
                        if (cR == cpf)
                        {
                            band_existeE = true;
                        }
                    }
                    if (!band_existeE)
                    {
                        conjuntoRetorno.push_back(cpf);
                    }
                }
            }
            else
            {
                for (auto const &pNC : primerosNoConjunto)
                {
                    if (eAP == pNC.first)
                    {
                        primeros(pNC.second, conjuntoRetorno);
                    }
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

void LL1::obtienePrimeros() // Aqui ademas se tiene el conjunto de terminales y no terminales
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

    for (auto const &pnc : primerosNoConjunto) // Se inicia la busqueda de primeros
    {
        vector<string> cr{};
        primeros(pnc.second, cr);
        conjunto_primeros[pnc.first] = cr;
    }

    cout << "Primeros" << endl;
    for (auto const &cp : conjunto_primeros)
    {
        cout << cp.first << ": ";
        for (auto const &i : cp.second)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    cout << endl
         << endl;
}
void LL1::obtieneSiguientes()
{
    vector<vector<string>> cv_gramatica = v_gramatica;
    vector<pair<string, vector<vector<string>>>> conjuntoParBusqueda{};
    vector<pair<string, pair<vector<string>,vector<string>>>> paresPorSimbolo{}; // Ocupara los pares de simbolo y string donde se encuentra de todas las cadenas
    // Limpiar data y asignacion de vector de vectores de string pa cada terminal
    int cont = 0;
    for (auto const &nt : noTerminales)
    {
        vector<vector<string>> conjuntoBusqueda{};

        for (auto &vg : cv_gramatica)
        {
            cont = 0;
            for (auto const &vgc : vg)
            {
                if (cont > 1 && vgc == nt)
                {
                    conjuntoBusqueda.push_back(vg);
                    break;
                }
                cont++;
            }
        }
        conjuntoParBusqueda.push_back(make_pair(nt, conjuntoBusqueda));
    }
    for (auto const &conjuntoParesBS : conjuntoParBusqueda)
    {
        vector<string> sentencias_validas{}; // Contendrá solo las producciones que tienen al sig del elemento a buscar
        vector<string> valorOrigen{};
        for (auto const &i : conjuntoParesBS.second)
        {

            ostringstream vts;
            copy(i.begin(), i.end() - 1, ostream_iterator<string>(vts, " "));
            vts << i.back();          // se agrega ultimo elemento sin identificador ','
            string vts_s = vts.str(); // contiene el elemento que va despues del simbolo de produce "->"

            vector<string> delimitadores{"->", " "};
            vector<string> sentencias{}; // contiene todas las producciones despues de or '|'

            leftTrim(vts_s, delimitadores[0]); // Cortamos la cadena hasta -> por izquierda

            sentencias = split(vts_s, '|');

            for (auto &&s : sentencias)
            {

                if (s[0] == ' ')
                    s = s.substr(1, s.size());
                if (s[s.size() - 1] == ' ')
                    s = s.substr(0, s.size() - 1);
               
                vector<string> busquedaDondeNoEsta = split(s, ' '); // Volvemos a dividir los grupos ya limpios de spaces en un vector de string para ver si esta ahí el elemento
                if (any_of(busquedaDondeNoEsta.begin(), busquedaDondeNoEsta.end(), [&](const string &elem)
                           { return elem == conjuntoParesBS.first; }))
                { // se checa si esta en todos los grupos encontrados
                    sentencias_validas.push_back(s);
                    
                    valorOrigen.push_back(i[0]);
                    cout<<"METIENDO AL PAIR: " << s << "="<< i[0] << endl;
                }
            }
        }
        paresPorSimbolo.push_back(make_pair(conjuntoParesBS.first,make_pair(valorOrigen,sentencias_validas) ));
    }

    for (auto &&pps : paresPorSimbolo)
    {
        cout << pps.first << " se ha encontrado en: " << endl;
        vector<string> vectoresSiguiente{};
        vector<pair<string,string>> vectorSiguienteClean{};
        int contParOrigen  = 0;  
        for (auto &&ppsv : pps.second.second)
        {                        
            vector<string> vectoresPorStringDondeSeEncontro = split(ppsv, ' ');
            auto ret = std::find_if(vectoresPorStringDondeSeEncontro.begin(), vectoresPorStringDondeSeEncontro.end(),
                                    [&](string s)
                                    { return s == pps.first; });

            int contVectoresBuenos = 0;
              
            for (auto const &vsS : vectoresPorStringDondeSeEncontro)
            {

                if (contVectoresBuenos > ret - vectoresPorStringDondeSeEncontro.begin() && ret != vectoresPorStringDondeSeEncontro.end())
                {
                    vectoresSiguiente.push_back(vsS);
                    vectorSiguienteClean.push_back(make_pair(pps.second.first[contParOrigen],vsS));                    
                }else if(ret+1 == vectoresPorStringDondeSeEncontro.end()){
                    string nada= "";
                    vectorSiguienteClean.push_back(make_pair(pps.second.first[contParOrigen],nada)); 
                }
                
                
                contVectoresBuenos++;               
                
            } 
            contParOrigen++;            
        }
       
                
        std::sort(vectorSiguienteClean.begin(), vectorSiguienteClean.end());
        auto last = std::unique(vectorSiguienteClean.begin(), vectorSiguienteClean.end());
        vectorSiguienteClean.erase(last, vectorSiguienteClean.end());

        
        for (auto const &vSB : vectorSiguienteClean)
        {            
            cout << vSB.second<< "padre:"<<vSB.first << endl;
        }
        

        cout << endl;
    }
}