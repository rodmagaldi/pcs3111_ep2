#ifndef PESSOA_H
#define PESSOA_H

#include "Perfil.h"
#include <string>

using namespace std;

class Pessoa : public Perfil {
    public:
        Pessoa(int numeroUSP, string nome, string email);
        Pessoa(int id, int numeroUSP, string nome, string email);
        virtual ~Pessoa() = 0;

        virtual int getNumeroUSP();
        virtual string getEmail();

    protected:
        int numeroUSP;
        string nome;
        string email;

    private:
};

#endif // PESSOA_H
