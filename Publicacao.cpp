#include "Publicacao.h"

#include <iostream>
#include <string>

using namespace std;

Publicacao::Publicacao(Perfil* autor, string texto) {
    this->autor = autor;
    this->texto = texto;
}

Publicacao::~Publicacao(){
    cout << "Destrutor de publicacao: " << this->texto << endl;
}

Perfil* Publicacao::getAutor() {
    return this->autor;
}

string Publicacao::getTexto() {
    return this->texto;
}

void Publicacao::curtir(Perfil* quemCurtiu) {
    if (quemCurtiu != this->autor) {
        this->curtidas++;
    }
}

int Publicacao::getCurtidas() {
    return this->curtidas;
}

void Publicacao::imprimir() {
    cout << "Texto: " << this->getTexto() << " - Autor: " << this->autor->getNome() << endl;
}
