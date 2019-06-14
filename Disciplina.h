#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "Perfil.h"
#include "Professor.h"

class Perfil;

class Disciplina : public Perfil
{
    public:
        Disciplina(string nome, Professor* responsavel);
        Disciplina(string nome, Professor* responsavel, Disciplina* preRequisito);
        Disciplina(int id, string nome, Professor* responsavel, Disciplina* preRequisito);
        virtual ~Disciplina();

        virtual Disciplina* getPreRequisito();
        virtual Professor* getResponsavel();

    protected:
        Professor* responsavel;
        Disciplina* preRequisito = NULL;

        void imprimir();
        void receber(Publicacao* p);
        void adicionarSeguidor(Perfil* seguidor);

    private:
};

#endif // DISCIPLINA_H
