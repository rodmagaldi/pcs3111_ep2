#include "Aluno.h"
#include <string>

Aluno::Aluno(int numeroUSP, string nome, string email): Pessoa(numeroUSP, nome, email) {
}

Aluno::Aluno(int id, int numeroUSP, string nome, string email): Pessoa(numeroUSP, nome, email) {
    this->id_perfil = id;
}

Aluno::~Aluno(){
}
