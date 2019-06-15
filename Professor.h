#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Pessoa.h"

#include <iostream>
#include <string>

using namespace std;

class Professor: public Pessoa {
    public:
        Professor(int numeroUSP, string nome, string email, string departamento);
        Professor(int id, int numeroUSP, string nome, string email, string departamento);
        virtual ~Professor();
        string getDepartamento();

        void imprimir();
    protected:
        int numeroUSP;
        string nome;
        string email;
        string departamento;
    private:
};

#endif // PROFESSOR_H
