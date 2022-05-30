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
    for (auto const &ctp : terminales)
    {
        vector<string> cr{};
        cr.push_back(ctp);
        conjunto_primeros[ctp] = cr;
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

}
void LL1::obtieneSiguientes()
{
    vector<vector<string>> cv_gramatica = v_gramatica;
    vector<pair<string, vector<vector<string>>>> conjuntoParBusqueda{};
    vector<pair<string, pair<vector<string>, vector<string>>>> paresPorSimbolo{}; // Ocupara los pares de simbolo y string donde se encuentra de todas las cadenas
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
                    // cout << "METIENDO AL PAIR: " << s << "=" << i[0] << endl;
                }
            }
        }
        paresPorSimbolo.push_back(make_pair(conjuntoParesBS.first, make_pair(valorOrigen, sentencias_validas)));
    }

    for (auto &&pps : paresPorSimbolo)
    {
        // cout << pps.first << " se ha encontrado en: " << endl;
        vector<string> vectoresSiguiente{};
        vector<pair<string, string>> vectorSiguienteClean{};
        int contParOrigen = 0;
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
                    vectorSiguienteClean.push_back(make_pair(pps.second.first[contParOrigen], vsS));
                }
                else if (ret + 1 == vectoresPorStringDondeSeEncontro.end())
                {
                    string nada = "";
                    vectorSiguienteClean.push_back(make_pair(pps.second.first[contParOrigen], nada));
                }

                contVectoresBuenos++;
            }
            contParOrigen++;
        }

        std::sort(vectorSiguienteClean.begin(), vectorSiguienteClean.end());
        auto last = std::unique(vectorSiguienteClean.begin(), vectorSiguienteClean.end());
        vectorSiguienteClean.erase(last, vectorSiguienteClean.end());

        sigNoConjunto[pps.first] = vectorSiguienteClean;
    }

    for (auto const &nt : noTerminales)
    {
        // cout << "NT: " << nt << endl;
        for (auto const &doomie : sigNoConjunto[nt])
        {
            //cout << "\nVF: " << snc.first << " FS:" << snc.second << endl;
            vector<string> r{};
            siguientes(nt, r);
            std::sort(r.begin(), r.end());
            auto last = std::unique(r.begin(), r.end());
            r.erase(last, r.end());
            conjunto_siguientes[nt] = r;
            //cout << "NT: " << nt << endl;
            /*
            for (auto const &itr : r)
            {
                cout << " itr:" << itr << " ";
            }
            */
        }
    }
    cout << "\n\nsiguientes: " << endl;
    for (auto const &vv : conjunto_siguientes)
    {
        cout << vv.first << ":";
        for (auto const &rtv : vv.second)
            cout << " " << rtv << " ";
        cout << endl;
    }
    cout << endl;
}

void LL1::siguientes(const string &busqueda, vector<string> &vectorRet)
{

    if (cont_s == 0)
    {
        vectorRet.push_back("$");
        cont_s++;
    }
    //cout << "busqueda: " << busqueda << endl;
    for (auto const &snc : sigNoConjunto[busqueda])
    {
        bool band_sigE = false;
        if (!conjunto_siguientes[busqueda].empty())
        {
            for (auto const &i : conjunto_siguientes[busqueda])
            {
                vectorRet.push_back(i);
            }
        }
        else if (!snc.second.empty())
        {
            //cout << "snc.second no vacio: se evaluara en segundo: " << snc.second << " el primero es: " << snc.first << endl;
            for (auto const &cp : conjunto_primeros[snc.second])
            {
                if (cp != "ε")
                {
                    vectorRet.push_back(cp);
                }
                else
                {
                    band_sigE = true;
                }
               // cout << endl;
            }
        }
        else if (snc.second.empty())
        {
            if (busqueda != snc.first)
            {
               // cout << "Solo se mandara sig: " << snc.first << endl;
                siguientes(snc.first, vectorRet);
            }
        }
        if (band_sigE)
        {
            siguientes(snc.first, vectorRet);
        }
        band_sigE = false;
    }
}
void LL1::generacionTabla()
{
    vector<string> cabezera{};
    for (auto const &t : terminales)
    {
        cabezera.push_back(t);
    }
    map<pair<string, string>, string> mp;

    cabezera.push_back("$");
    tabla.push_back(cabezera);
    map<pair<string, string>, string> conjuntosEnTabla;
    int cont_t = 0;
    for (auto const &cp : conjunto_primeros)
    {

        if (verificaSiEsNoTerminal(cp.first))
        {
            bool nohayE = false;
            ostringstream vts;
            copy(cp.second.begin(), cp.second.end() - 1, ostream_iterator<string>(vts, " "));
            vts << cp.second.back(); // se agrega ultimo elemento sin identificador ','
            string vts_s = vts.str();
           
            for (auto const &cps : cp.second)
            {
                if (cps == "ε")
                {
                    nohayE = true;
                }
            }
            if (!nohayE)
            {

                ostringstream vts2;
                copy(v_gramatica[cont_t].begin(), v_gramatica[cont_t].end() - 1, ostream_iterator<string>(vts2, " "));                
                vts2 << v_gramatica[cont_t].back(); // se agrega ultimo elemento sin identificador ','
                string vts_s2 = vts2.str();
                conjuntosEnTabla[make_pair(cp.first, vts_s)] = vts_s2;              
            }
            else
            {
                vector<string> toS{};
                for(auto const & cs: conjunto_siguientes[cp.first]){
                    toS.push_back(cs);
                }
                ostringstream vts2;
                copy(toS.begin(), toS.end() - 1, ostream_iterator<string>(vts2, " "));
                vts2 <<toS.back(); // se agrega ultimo elemento sin identificador ','
                string vts_s2 = vts2.str();
                conjuntosEnTabla[make_pair(cp.first, vts_s2)] = "ε";               
            }
            nohayE = false;
            cont_t++;
        }
        
    }
    for (auto const &i : conjuntosEnTabla)
    {
        cout << "Tabla: " << i.first.first << " : " << i.first.second << " = " << i.second << endl;
    }
}
