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
    for (auto const &i : gramatica_sO)
    {
        stringstream ss_sO(i);
        istream_iterator<std::string> begin2(ss_sO);
        istream_iterator<std::string> end2;
        vector<std::string> vector_gramatica_sO(begin2, end2);
        v_sO_gramatica.push_back(vector_gramatica_sO);
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
    /*
    std::cout << "Primeros" << endl;
    for (auto const &cp : conjunto_primeros)
    {
        std::cout << cp.first << ": ";
        for (auto const &i : cp.second)
        {
            std::cout << i << " ";
        }
        std::cout << endl;
    }
    */
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
            // cout << "\nVF: " << snc.first << " FS:" << snc.second << endl;
            vector<string> r{};
            siguientes(nt, r);
            std::sort(r.begin(), r.end());
            auto last = std::unique(r.begin(), r.end());
            r.erase(last, r.end());
            conjunto_siguientes[nt] = r;
            // cout << "NT: " << nt << endl;
            /*
            for (auto const &itr : r)
            {
                cout << " itr:" << itr << " ";
            }
            */
        }
    }
    /*
    std::cout << "\n\nsiguientes: " << endl;
    for (auto const &vv : conjunto_siguientes)
    {
        std::cout << vv.first << ":";
        for (auto const &rtv : vv.second)
            std::cout << " " << rtv << " ";
        std::cout << endl;
    }
    std::cout << endl;
    */
}

void LL1::siguientes(const string &busqueda, vector<string> &vectorRet)
{

    if (cont_s == 0)
    {
        vectorRet.push_back("$");
        cont_s++;
    }
    // cout << "busqueda: " << busqueda << endl;
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
            // cout << "snc.second no vacio: se evaluara en segundo: " << snc.second << " el primero es: " << snc.first << endl;
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

    cabezera.push_back("M");
    for (auto const &t : terminales)
    {
        if (t != "ε")
            cabezera.push_back(t);
    }
    map<pair<string, string>, string> mp;

    cabezera.push_back("$");
    tabla.push_back(cabezera);
    map<pair<string, string>, string> conjuntosEnTabla;

    for (auto const &cp : conjunto_primeros)
    {

        if (verificaSiEsNoTerminal(cp.first))
        {

            if (cp.first == "E")
            {
                for (auto const &prodD : cp.second)
                {
                    conjuntosEnTabla[make_pair(cp.first, prodD)] = "E -> T E’";
                }
            }
            else if (cp.first == "E’")
            {
                for (auto const &prodD : cp.second)
                {
                    if (prodD == "ε")
                    {
                        conjuntosEnTabla[make_pair(cp.first, prodD)] = "E’ -> ε";
                        if (!conjunto_siguientes[cp.first].empty())
                        {
                            for (auto const &cs : conjunto_siguientes[cp.first])
                            {
                                conjuntosEnTabla[make_pair(cp.first, cs)] = "E’ -> ε";
                            }
                        }
                    }
                    else
                    {
                        conjuntosEnTabla[make_pair(cp.first, prodD)] = "E’ -> + T E’";
                    }
                }
            }
            else if (cp.first == "T")
            {
                for (auto const &prodD : cp.second)
                {
                    conjuntosEnTabla[make_pair(cp.first, prodD)] = "T -> F T’";
                }
            }
            else if (cp.first == "T’")
            {
                for (auto const &prodD : cp.second)
                {
                    if (prodD == "ε")
                    {
                        conjuntosEnTabla[make_pair(cp.first, prodD)] = "T’ -> ε";
                        if (!conjunto_siguientes[cp.first].empty())
                        {
                            for (auto const &cs : conjunto_siguientes[cp.first])
                            {
                                conjuntosEnTabla[make_pair(cp.first, cs)] = "E’ -> ε";
                            }
                        }
                    }
                    else
                    {
                        conjuntosEnTabla[make_pair(cp.first, prodD)] = "T’ -> * F T’";
                    }
                }
            }
            else if (cp.first == "F")
            {
                for (auto const &prodD : cp.second)
                {
                    if (prodD == "id")
                    {
                        conjuntosEnTabla[make_pair(cp.first, prodD)] = "F -> id";
                    }
                    else
                    {
                        conjuntosEnTabla[make_pair(cp.first, prodD)] = "F -> ( E )";
                    }
                }
            }
        }
    }
    primerColumna = {
        "M",
        "E",
        "E’",
        "T",
        "T’",
        "F"};
    for (int i = 0; i < 6; i++)
    {

        for (int j = 0; j < 7; j++)
        {
            if (j == 0)
            {
                if (i == 0)
                    tablaFinal[i][j] = primerColumna[i];
                if (i == 1)
                    tablaFinal[i][j] = primerColumna[i];
                if (i == 2)
                    tablaFinal[i][j] = primerColumna[i];
                if (i == 3)
                    tablaFinal[i][j] = primerColumna[i];
                if (i == 4)
                    tablaFinal[i][j] = primerColumna[i];
                if (i == 5)
                    tablaFinal[i][j] = primerColumna[i];
            }
            if (i == 0)
            {
                if (j > 0)
                    tablaFinal[i][j] = cabezera[j];
            }
            else if (i > 0 && j > 0)
            {
                string v1 = primerColumna[i];
                string v2 = cabezera[j];
                if (v2 == "$")
                {
                    v2 = "ε";
                }
                auto pairV1V2 = make_pair(v1, v2);
                if (!conjuntosEnTabla[pairV1V2].empty())
                {

                    tablaFinal[i][j] = conjuntosEnTabla[pairV1V2];
                }
                else
                {
                    tablaFinal[i][j] = "error";
                }
            }
        }
    }
    /*
    cout << endl;
    cout << "Tabla Final" << endl;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i == 0)
            {
                cout << "\t" << tablaFinal[i][j] << "\t";
            }
            else if (tablaFinal[i][j] == "error")
                cout << "\t" << tablaFinal[i][j] << "\t";
            else
            {
                cout << "\t" << tablaFinal[i][j] << " ";
            }
        }
        cout << endl;
    }
    */
}

bool LL1::ingresaCadena(vector<string> cadena)
{
    /*
    cout << "Cadena:" << endl;
    for (auto const &c : cadena)
    {
        cout << c << " ";
    }
    cout << endl;
    */
    stack<string> pila{};
    pila.push("$");
    pila.push("E");

    int cont = 0;
    int prueba = 0;
    bool cadena_valida = false;

    while (cont < cadena.size())
    {

        string valor_tabla;
        int indice_cabe = 0;
        if (cadena_valida == true)
        {
            break;
        }
        for (const auto &c2 : cabezera)
        {
            if (c2 == cadena[cont])
                break;
            else
            {
                indice_cabe++;
            }
        }
        int indice_primerColumna = 0;
        for (const auto &c3 : primerColumna)
        {
            if (pila.top() == c3)
                break;
            indice_primerColumna++;
        }
        if (pila.empty())
        {
            cout << "NO VALIDA, pila vacia, cadena no aceptada" << endl;
            cadena_valida = true;
            break;
        }
        if (cadena[cont] == pila.top() && pila.top() == "$")
        {
            //cout << "ACEPTADA" << endl;
            return true;
            break;
        }
        else if (cadena[cont] == pila.top())
        {
            // cout << "Sacando ya que son iguales" << endl;
            cont++;
            if (pila.empty())
            {
                cadena_valida = true;
                break;
            }
            else
                pila.pop();
        }
        else
        {
            // IMP valor en pila
            string simbolo_mayor = ">";
            valor_tabla = tablaFinal[indice_primerColumna][indice_cabe]; // Obtenemos la produccion como string

            corte(valor_tabla, simbolo_mayor); // Cortamos lo que va despues del simbolo "->" ya que nos interesa el resultado de lo que
            // produce
            auto sentencias = split(valor_tabla, ' ');     // Dividimos el string en vector<string> con separador de ' '
            reverse(sentencias.begin(), sentencias.end()); // Volteamos el vector de string resultado para añadir a la pila
            pila.pop();
            for (const auto &vtr : sentencias)
            {
                // cout << "VTR: " << vtr << endl;
                if (vtr == "ε")
                {
                    continue;
                }
                else if (vtr == "rror" || vtr.size() < 1)
                {
                    //cout << "NO VALIDA" << endl;
                    cadena_valida = true;
                    break;
                }
                else if (vtr != " ")
                {
                    // cout << "metiendo en pila : " << vtr << endl;
                    pila.push(vtr);
                }
            }
        }
        prueba++;
    }
    return false;
}