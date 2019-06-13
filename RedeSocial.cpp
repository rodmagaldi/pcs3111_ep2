#include "RedeSocial.h"
#include "Perfil.h"
#include "Disciplina.h"
#include "Professor.h"

#include "IdInvalido.h"
#include <stdexcept>

using namespace std;

RedeSocial::RedeSocial() {
    perfis = new vector<Perfil*>;
}

RedeSocial::~RedeSocial() {
  cout << "Destrutor de RedeSocial: " << this->perfis->size() << " perfis" << endl;

  for (int i = 0; i < this->perfis->size(); i++) {
        delete this->perfis->at(i);
    }

  cout << "RedeSocial deletada " << endl;
}

vector<Perfil*>* RedeSocial::getPerfis() {
    return this->perfis;
}

Perfil* RedeSocial::getPerfil(int id) {
    for (int i = 0; i<this->perfis->size(); i++) {
        if (this->perfis->at(i)->getId() == id) {
            return this->perfis->at(i);
        }
    }
    throw new IdInvalido();
}

void RedeSocial::adicionar(Perfil* p) {
    if (!checaPerfil(p)) {
        this->perfis->push_back(p);
    } else {
        cout << "Este perfil ja foi adicionado a esta Rede Social" << endl;
    }
}

void RedeSocial::imprimir () {
 cout << endl << "------------------------------ " << endl;
 cout << "RedeSocial: " << this->perfis->size() << " perfis" << endl;
 cout << "------------------------------ " << endl;
 if (this->perfis->size() == 0){
    cout << "Sem perfis" << endl;
    cout << "------------------------------ " << endl;
 } else {
    for (int i = 0; i < this->perfis->size(); i++){
        perfis->at(i)->imprimir();
        cout << "------------------------------ " << endl;
    }
 }
 cout << endl;
}


//protected
bool RedeSocial::checaPerfil(Perfil* perfil) {
    for (int i = 0; i < this->perfis->size(); i++){
        if (this->perfis->at(i)==perfil) {
            return true;
        }
    }
    return false;
}
