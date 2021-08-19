#include <bits/stdc++.h>
using namespace std;

class AFD{
    private:         
        vector<string> _alfabeto, _estados;        
        string _edoInicial, _edoFinal, _edoActual;                
        map<pair<string,char>,string> _transiciones;
    public:        
        AFD(vector<string> &alfabeto, vector<string> &estados, string edoInicial, string edoFinal, string edoActual): 
        _alfabeto(alfabeto), _estados(estados), _edoInicial(edoInicial), _edoFinal(edoFinal), _edoActual(edoActual){
            hacerTransiciones(_estados);
        };
        void hacerTransiciones(vector<string> &);        
        void imprimeTransiciones();
        bool verificaEstaEstado(string); //Son para cuando se pidan datos por ahora no estan implementadas
        bool verificaEstaAlfabeto(string); //Son para cuando se pidan datos por ahora no estan implementadas
        // Getters & Setters
        string getEstadoFinal();
        string getEstadoInicial();
        string getEstadoActual();
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

int main(){    
    vector<string> alfabeto{"a", "b"},  estados{"q0", "q1", "q2"};    
    string edoInicial = "q0", edoFinal = "q0", cad_leer="baba";   
    AFD* afd = new AFD(alfabeto, estados, edoInicial, edoFinal, edoInicial);    
    FuncionTransicion *funct = new FuncionTransicion(afd);  

    afd->imprimeTransiciones();
    funct->hacerSigTransicion(cad_leer);
    return 0;
}

void FuncionTransicion::hacerSigTransicion(string& pal){
    if(pal.length()==1){
        esPosible(pal) ? cout << "Si esta en el lenguaje" << endl : cout << "No esta en el lenguaje" << endl;
    }
    else{                           
        auto ret = _afd->getTransiciones().find(make_pair(_afd->getEstadoActual(),pal[0]));          
        _afd->setEstadoActual(ret->second);    
        pal = pal.substr(1, pal.size());
        hacerSigTransicion(pal);              
    }
}
bool FuncionTransicion::esPosible(string& pal){            
    auto ret = _afd->getTransiciones().find(make_pair(_afd->getEstadoActual(),pal[0]));   
    return (ret->second == _afd->getEstadoFinal());
}
void AFD::hacerTransiciones(vector<string> &_estados){    
    //transiciones definidas por mí, se puede pedir datos o agilizar esto pero lo hice de la forma más rápida
    _transiciones[make_pair(_estados[0],'a')] = "q1";
    _transiciones[make_pair(_estados[0],'b')] = "q2";    
    _transiciones[make_pair(_estados[1],'a')] = "q2";
    _transiciones[make_pair(_estados[1],'b')] = "q0";
    _transiciones[make_pair(_estados[2],'a')] = "q2";
    _transiciones[make_pair(_estados[2],'b')] = "q2";
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