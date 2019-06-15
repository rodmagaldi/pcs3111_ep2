#include "Pessoa.h"

Pessoa::Pessoa(int numeroUSP, string nome, string email): Perfil(nome), numeroUSP (numeroUSP), email (email) {
}

Pessoa::Pessoa(int id, int numeroUSP, string nome, string email): Perfil(nome), numeroUSP (numeroUSP), email (email) {
}

Pessoa::~Pessoa(){
}

string Pessoa::getEmail() {
    return this->email;
}

int Pessoa::getNumeroUSP() {
    return this->numeroUSP;
}
