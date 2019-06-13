#include "Disciplina.h"
#include <string>

using namespace std;

class Perfil;
class Professor;

Disciplina::Disciplina(string nome, Professor* responsavel, Disciplina* preRequisito): Perfil (nome), responsavel (responsavel), preRequisito (preRequisito) {
    this->adicionarSeguidor(responsavel);
}

Disciplina::Disciplina(string nome, Professor* responsavel): Perfil (nome), responsavel (responsavel) {
    this->adicionarSeguidor(responsavel);
}

Disciplina::Disciplina(int id, string nome, Professor* responsavel, Disciplina* preRequisito): Perfil (nome), responsavel (responsavel), preRequisito (preRequisito) {
    this->id_perfil = id;
    this->adicionarSeguidor(responsavel);
}

Disciplina::~Disciplina() {
}

Disciplina* Disciplina::getPreRequisito() {
    return this->preRequisito;
}

Professor* Disciplina::getResponsavel() {
    return this->responsavel;
}

void Disciplina::imprimir() {
    cout << endl;
    cout << "Nome: " << nome << " - ID: " << id_perfil << " - Responsavel: " << responsavel->getNome() << endl;
}

void Disciplina::adicionarSeguidor(Perfil* seguidor) {
    //caso seja possivel adicionar seguidores
    if (seguidor!=this && !conferirSeguidor(seguidor)) {
        seguidores->push_back(seguidor);
    }
    else if(seguidor==this || conferirSeguidor(seguidor)) throw new logic_error("Nao faz sentido adicionar este seguidor.");
}

void Disciplina::receber(Publicacao* p) {
}
