#include <bits/stdc++.h>
using namespace std;
int cont = 0;
class AFD{
    private:         
        vector<string> _estados, _alfabeto;        
        string _edoInicial, _edoFinal, _edoActual;    
        
       
    public:        
        AFD(vector<string> &alfabeto, vector<string> &estados, string edoInicial, string edoFinal, string edoActual): 
        _alfabeto(alfabeto), _estados(estados), _edoInicial(edoInicial), _edoFinal(edoFinal), _edoActual(edoActual){};
        
        void hacerTransiciones(vector<string> &);        
        void imprimeTransiciones();
        bool verificaEstaEstado(string); //Son para cuando se pidan datos por ahora no estan implementadas
        bool verificaEstaAlfabeto(string); //Son para cuando se pidan datos por ahora no estan implementadas
        map<pair<string,char>,string> _transiciones;
        
        // Getters & Setters
        string getEstadoFinal();
        string getEstadoInicial();
        string getEstadoActual();
        vector<string> getAlfabeto();
        vector<string> getEstados();
        void setEstadoActual(string);
        map<pair<string,char>,string> getTransiciones();
};

class FuncionTransicion{
    private:
        AFD* _afd;                
        bool esPosible(string &pal);
    public:
        FuncionTransicion(AFD *afd):_afd(afd){};        
        void hacerSigTransicion(string &pal);        
};
void menu();

int main(){    
    
    menu();    
    return 0;
}


void ingresarAutomata(AFD *&);
void verificarPalabra(AFD *&);

void menu(){   
    AFD* afd;
    int k;
    do
    {      
        cout << endl;          
        cout << "1 -> Ingresar Automata" << endl;
        cout << "2 -> Imprimir tabla de transiciones del Automata" << endl;
        cout << "3 -> Verificar Palabra" << endl;
        cout << "4 -> Salir del programa" << endl;    
        cout << endl;
        cin>>k;
        switch (k)
        {
        case 1:
            ingresarAutomata(afd);
            break;
        case 2:
            afd->imprimeTransiciones();
            break;        
        case 3:
            verificarPalabra(afd);
            break;
        case 4:
            cout << "Saliendo" << endl;   
            break;     
        default: cout << "Opcion no valida" << endl;
            break;
        }
    } while (k!=4);    
}
void ingresarAutomata(AFD *&afd){
    vector<string> alfabeto, estados;
    string simbolos , edoInicial, edoFinal;   
    int tamAlfabeto, numEdos;
    char k;
    cout << "Ingrese cuantos simbolos conforman su alfabeto: ";
    cin >> tamAlfabeto;
    cout << "Ingrese los simbolos que conforman su alfabeto: ";
    for (int i = 0; i < tamAlfabeto; i++)
    {
        cin >> simbolos;
        alfabeto.push_back(simbolos);
    }
        
    cout << "Ingrese numero de estados: "; cin >> numEdos;
    cout << "Ingrese los estados: ";
    for (int i = 0; i < numEdos; i++)
    {
        cin >> simbolos;
        estados.push_back(simbolos);
    }
    cout << "Ingrese estado inicial: ";  cin >> edoInicial;
    cout << "Ingrese estado final: ";  cin >> edoFinal;
    afd = new AFD(alfabeto, estados, edoInicial, edoFinal, edoInicial); 
    cout << "Indique las transiciones de cada estado " << endl;

    for(int i = 0; i< estados.size(); i++)
    {
        for(int j=0 ; j< alfabeto.size(); j++)
        {
            cout << " Ingrese la transision  para el estado: " << estados[i] << "  con el simbolo:  " << alfabeto[j] <<"  ->  ";
            cin >> simbolos;
            k = alfabeto[j][0];            
            afd->_transiciones[make_pair(estados[i],k)] = simbolos;
        }
    }        
}

void verificarPalabra(AFD *&afd){
    string pal;
    FuncionTransicion *ft = new FuncionTransicion(afd);
    cout << "Ingrese la palabra a verificar en el automata: " << endl;
    cin >> pal;
    ft->hacerSigTransicion(pal);
}

void FuncionTransicion::hacerSigTransicion(string& pal){
    string auxE;
    if(cont == 0){
        auxE = _afd->getEstadoActual();
        cont++;
    }
    if(pal.length()==1){

        esPosible(pal) ? cout << "\nSi esta en el lenguaje" << endl : cout << "\nNo esta en el lenguaje" << endl;
        _afd->setEstadoActual(auxE);
    }
    else{            
        cout << "   ("<< _afd->getEstadoActual()<< "," << pal[0]<< ") |- ";               
        auto ret = _afd->getTransiciones().find(make_pair(_afd->getEstadoActual(),pal[0]));          
        cout << " " << ret->second;
        _afd->setEstadoActual(ret->second);    
        pal = pal.substr(1, pal.size());
        hacerSigTransicion(pal);              
    }
}
bool FuncionTransicion::esPosible(string& pal){  
    cout << "   ("<< _afd->getEstadoActual()<< "," << pal[0]<< ") |- ";          
    auto ret = _afd->getTransiciones().find(make_pair(_afd->getEstadoActual(),pal[0]));   
    cout << " " << ret->second;
    return (ret->second == _afd->getEstadoFinal());
}

void AFD::imprimeTransiciones(){    
    for(auto s: _transiciones){
        cout <<"( "<< s.first.first <<" , " <<s.first.second<< " )" << "= "<<  s.second << endl;        
    }
}
bool AFD::verificaEstaEstado(string edo){
    for(auto var : _estados){
        if(var==edo) return true;        
    }   
    return false;
}
bool AFD::verificaEstaAlfabeto(string edo){    
    for(auto var : _alfabeto){
        if(var==edo) return true;       
    }
    return false;
}
//Getters & setters
string AFD::getEstadoActual(){
    return _edoActual;
}
string AFD::getEstadoInicial(){
    return _edoInicial;
}
string AFD::getEstadoFinal(){
    return _edoFinal;
}
map<pair<string,char>,string> AFD::getTransiciones(){
    return _transiciones;
}
void AFD::setEstadoActual(string _edoActual){
    this->_edoActual = _edoActual;
}
vector<string> AFD:: getEstados(){
    return _estados;
}
vector<string> AFD::getAlfabeto(){
    return _alfabeto;
}