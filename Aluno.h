#ifndef ALUNO_H
#define ALUNO_H

#include "Pessoa.h"
#include <string>

using namespace std;

class Pessoa;

class Aluno : public Pessoa {
    public:
        Aluno(int numeroUSP, string nome, string email);
        Aluno(int id, int numeroUSP, string nome, string email);
        virtual ~Aluno();
    protected:
        int numeroUSP;
        string nome;
        string email;

    private:
};

#endif // ALUNO_H
