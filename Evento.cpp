#include "Evento.h"

Evento::Evento(Perfil* autor, string data, string texto): Publicacao (autor, texto), data (data) {
}

Evento::~Evento() {
}

string Evento::getData() {
    return this->data;
}

void Evento::curtir(Perfil* quemCurtiu) {
    this->curtidas++;
}
