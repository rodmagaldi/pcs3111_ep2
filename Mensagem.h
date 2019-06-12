#ifndef MENSAGEM_H
#define MENSAGEM_H

#include "Publicacao.h"


class Mensagem : public Publicacao
{
    public:
        Mensagem(Perfil* autor, string texto);
        virtual ~Mensagem();

        virtual void curtir(Perfil* quemCurtiu);

    protected:
        Perfil* autor;
        string texto;

    private:
};

#endif // MENSAGEM_H
