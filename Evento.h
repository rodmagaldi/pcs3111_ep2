#ifndef EVENTO_H
#define EVENTO_H

#include "Publicacao.h"


class Evento : public Publicacao
{
    public:
        Evento(Perfil* autor, string data, string texto);
        virtual ~Evento();

        string getData();
        virtual void curtir(Perfil* quemCurtiu);
    protected:
        string data;

    private:
};

#endif // EVENTO_H
