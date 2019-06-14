#include "Perfil.h"
#include "Evento.h"
#include "Mensagem.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include <stdexcept>

#define MAXIMO_SEGUIDORES 2

using namespace std;

class Publicacao;

int Perfil::id = 1;
int Perfil::ultimoId = 0;

Perfil::Perfil(string nome): nome (nome) {
    this->id_perfil = Perfil::id;
    Perfil::id++;
}

Perfil::Perfil(int id, string nome) {
    this->id_perfil = Perfil::id;
    Perfil::id++;
}

Perfil::~Perfil(){
    cout << "Destrutor de perfil: " << this->nome << " - Quantidade de publicacoes feitas: " << this->publicacoesFeitas->size() << endl;

    list<Publicacao*>::iterator i = publicacoesFeitas->begin();
    while (i!=publicacoesFeitas->end()) {
        delete (*i);
        i++;
    }

    cout << "Perfil deletado" << endl;
};

void Perfil::setUltimoId(int ultimoId) {
    Perfil::ultimoId = ultimoId;
}

int Perfil::getUltimoId() {
    return Perfil::ultimoId;
}

int Perfil::getId() {
    return this->id_perfil;
}

string Perfil::getNome() {
    return this->nome;
}

void Perfil::adicionarSeguidor(Perfil* seguidor) {
//    caso seja possivel adicionar seguidores
    if (!conferirSeguidor(seguidor) && seguidor!=this) {
        this->seguidores->push_back(seguidor);

        //adiciona publicacao a lista de recebidas
        Mensagem* p = new Mensagem(this, "Novo seguidor: " + seguidor->nome);
        this->receber(p);
    }
    else if(seguidor==this || conferirSeguidor(seguidor)) throw new logic_error("Nao faz sentido adicionar este seguidor.");
}

void Perfil::publicar(string texto) {

    //adiciona o texto a lista de publicacoes feitas
    this->publicacoesFeitas->push_back(new Mensagem(this, texto));
    //adiciona o texto aos seguidores
    if (this->seguidores->size() > 0) {

        auto i = seguidores->begin();
        while (i!=seguidores->end()) {
            (*i)->receber(publicacoesFeitas->back());
            i++;
        }
    }
}

void Perfil::publicar(string texto, string data) {
    //adiciona o texto a lista de publicacoes feitas
    this->publicacoesFeitas->push_back(new Evento(this, data, texto));
    //adiciona o texto aos seguidores
    if (this->seguidores->size() > 0) {
        auto i = seguidores->begin();
        while (i!=seguidores->end()) {
            (*i)->receber(publicacoesFeitas->back());
            i++;
        }
    }
}

void Perfil::receber(Publicacao* p) {
    this->publicacoesRecebidas->push_back(p);
}

list<Publicacao*>* Perfil::getPublicacoesFeitas() {
    return this->publicacoesFeitas;
}

list<Publicacao*>* Perfil::getPublicacoesRecebidas() {
    return this->publicacoesRecebidas;
}

vector<Perfil*>* Perfil::getSeguidores() {
    return this->seguidores;
}

void Perfil::imprimir() {
    cout << "Nome: " << nome << " - ID: " << id_perfil << endl;
    if (this->seguidores->size() == 0)
        cout << "Sem seguidor " << endl;
    else {

        auto i = seguidores->begin();
        while (i!=seguidores->end()) {
            cout << "Seguidor "<< (*i)->getNome() << endl;
            i++;
        }

    }
    cout << "Numero de publicacoes feitas: " << this->publicacoesFeitas->size() << endl;
    list<Publicacao*>::iterator i = publicacoesFeitas->begin();
    while (i!=publicacoesFeitas->end()) {
        (*i)->imprimir();
        i++;
    }

    cout << "Numero de publicacoes recebidas: " << this->publicacoesRecebidas->size() << endl;
    list<Publicacao*>::iterator j = publicacoesRecebidas->begin();
    while (j!=publicacoesRecebidas->end()) {
        (*j)->imprimir();
        j++;
    }
    cout << endl;
}

//metodos privados ou protegidos

bool Perfil::conferirSeguidor(Perfil* seguidorTeorico) {

    auto i = find(seguidores->begin(), seguidores->end(), seguidorTeorico);

    if (i!=seguidores->end())
        return true;
    else return false;
}
