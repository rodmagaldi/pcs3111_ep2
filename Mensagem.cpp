#include "Mensagem.h"
#include <stdexcept>

Mensagem::Mensagem(Perfil* autor, string texto): Publicacao(autor, texto) {
}

Mensagem::~Mensagem() {
}

void Mensagem::curtir(Perfil* quemCurtiu) {
    if (quemCurtiu != this->autor) {
        this->curtidas++;
    } else {
        throw new invalid_argument("Você não pode curtir sua própria mensagem.");
    }
}
