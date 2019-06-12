#ifndef PERSISTENCIADAREDE_H
#define PERSISTENCIADAREDE_H

#include "RedeSocial.h"

class PersistenciaDaRede
{
    public:
        PersistenciaDaRede();
        virtual ~PersistenciaDaRede();

        void salvar(string arquivo, RedeSocial* r);
        RedeSocial* carregar(string arquivo);
    protected:

    private:
};

#endif // PERSISTENCIADAREDE_H
