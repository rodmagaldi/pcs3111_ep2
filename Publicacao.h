#ifndef PUBLICACAO_H
#define PUBLICACAO_H

#include "Perfil.h"
#include "RedeSocial.h"
#include <string>
#include <iostream>

using namespace std;

class RedeSocial;
class Perfil;

class Publicacao {
private:
    string texto;
    Perfil* autor;

protected:
    int curtidas = 0;
public:
    //construtor e destrutor
    Publicacao(Perfil* autor, string texto);
    virtual ~Publicacao();

    Perfil* getAutor();
    string getTexto();

    virtual void curtir(Perfil* quemCurtiu) = 0;
    virtual int getCurtidas();

    virtual void imprimir();
};

#endif // PUBLICACAO_H
