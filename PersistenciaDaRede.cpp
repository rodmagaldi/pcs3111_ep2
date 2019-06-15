#include "PersistenciaDaRede.h"
#include "Aluno.h"
#include "Disciplina.h"
#include "Professor.h"
#include <stdexcept>

#include <fstream>
#include <sstream>

PersistenciaDaRede::PersistenciaDaRede() {
    //ctor
}

PersistenciaDaRede::~PersistenciaDaRede() {
    //dtor
}

void PersistenciaDaRede::salvar(string arquivo, RedeSocial* r) {
    ofstream arq;
    int nAlunos = 0;
    int nProfs = 0;
    int nDisc = 0;
    arq.open(arquivo);

    //erro
    if(arq.fail()) {
        throw new logic_error("Erro ao salvar o arquivo.");

    //sucesso
    } else {

        //conta a quantidade de cada tipo de perfil
        for (int i = 0; i<r->getPerfis()->size(); i++) {
            if (dynamic_cast<Aluno*>(r->getPerfis()->at(i))) {
                nAlunos++;
            }
            if (dynamic_cast<Professor*>(r->getPerfis()->at(i))) {
                nProfs++;
            }
            if (dynamic_cast<Disciplina*>(r->getPerfis()->at(i))) {
                nDisc++;
            }
        }

        //registra o numero total de perfis
        arq << r->getPerfis()->size() << "\r\n";

        //registra o numero total de alunos
        arq << nAlunos << "\r\n";

        //registra cada aluno
        for (int i = 0; i<r->getPerfis()->size(); i++) {
            if (dynamic_cast<Aluno*>(r->getPerfis()->at(i))) {
                Aluno* aluno = dynamic_cast<Aluno*>(r->getPerfis()->at(i));
                arq << aluno->getNumeroUSP() << " " << aluno->getNome() << " " << aluno->getEmail() << " " << aluno->getId() << "\r\n";
            }
        }

        //numero total de professores
        arq << nProfs << "\r\n";

        //cada professor
        for (int i = 0; i<r->getPerfis()->size(); i++) {
            if (dynamic_cast<Professor*>(r->getPerfis()->at(i))) {
                Professor* prof = dynamic_cast<Professor*>(r->getPerfis()->at(i));
                arq << prof->getNumeroUSP() << " " << prof->getNome() << " " << prof->getEmail() << " " << prof->getDepartamento() << " " << prof->getId() << "\r\n";
            }
        }

        //numero total de disciplinas
        arq << nDisc << "\r\n";

        //cada disciplina
        for (int i = 1; i<=r->getPerfis()->size(); i++) {
            if (dynamic_cast<Disciplina*>(r->getPerfil(i))) {
                Disciplina* disc = dynamic_cast<Disciplina*>(r->getPerfil(i));
                if (!disc->getPreRequisito()) {
                    arq << disc->getNome() << " " << disc->getResponsavel()->getId() << " " << -1 << " " << disc->getId() << "\r\n";
                } else {
                    arq << disc->getNome() << " " << disc->getResponsavel()->getId() << " " << disc->getPreRequisito()->getId() << " " << disc->getId() << "\r\n";
                }
            }
        }

        //registra seguidores
        for (int i=1; i<=r->getPerfis()->size(); i++) {
            for (int j=0; j<r->getPerfil(i)->getSeguidores()->size(); j++) {
                arq << i << " " << r->getPerfil(i)->getSeguidores()->at(j)->getId() << "\r\n";
            }
        }
    }

    arq.close();
}

RedeSocial* PersistenciaDaRede::carregar(string arquivo) {

    //conta o numero total de linhas do arquivo.
    //esse numero sera usado no final deste metodo,
    //para registrar as relacoes de seguidores
    ifstream contaLinhas;
    contaLinhas.open(arquivo);
    int nLinhas = 0;
    string linhas;
    while (getline(contaLinhas, linhas))
        nLinhas++;
    contaLinhas.close();

    //abre novamente o arquivo
    ifstream in;
    in.open(arquivo);

    //se arquivo nao existe
    if(!in.is_open()) {
        RedeSocial* rede = new RedeSocial();
        in.close();
        return rede;
    }

    //se ha erro no arquivo
    if(in.fail()) {
        throw new logic_error("Falha no arquivo de entrada.");
        in.close();
    }

    RedeSocial* rede = new RedeSocial();

    int nUsuarios;
    in >> nUsuarios;

    int nAlunos;
    in >> nAlunos;

    //cadastra alunos
    for (int i=0; i<nAlunos; i++) {
        int numeroUSP;
        string nome;
        string email;
        int id;

        in >> numeroUSP;
        in >> nome;
        in >> email;
        in >> id;

        Aluno* aluno = new Aluno(id, numeroUSP, nome, email);
        rede->adicionar(aluno);
    }

    int nProfessores;
    in >> nProfessores;

    //cadastra professores
    for (int i=0; i<nProfessores; i++) {
        int numeroUSP;
        string nome;
        string email;
        string departamento;
        int id;

        in >> numeroUSP;
        in >> nome;
        in >> email;
        in >> departamento;
        in >> id;

        Professor* prof = new Professor(id, numeroUSP, nome, email, departamento);
        rede->adicionar(prof);
    }

    int nDisc;
    in >> nDisc;

    //cadastra disciplinas
    for (int i=0; i<nDisc; i++) {
        string nome;
        int idResp;
        int idPreReq;
        int id;

        Perfil* resp;
        Professor* profResp;
        Perfil* preReq;
        Disciplina* DiscPreReq;

        in >> nome;
        in >> idResp;
        in >> idPreReq;
        in >> id;

        for (int j=0; j<rede->getPerfis()->size(); j++) {
            if (rede->getPerfis()->at(j)->getId() == idResp) {
                profResp = dynamic_cast<Professor*>(rede->getPerfis()->at(j));
            }
        }

        for (int j=0; j<rede->getPerfis()->size(); j++) {
            if (rede->getPerfis()->at(j)->getId() == idPreReq) {
                DiscPreReq = dynamic_cast<Disciplina*>(rede->getPerfis()->at(j));
            } else if (idPreReq == -1) {
                DiscPreReq = NULL;
            }
        }

        Disciplina* disc = new Disciplina(id, nome, profResp, DiscPreReq);
        rede->adicionar(disc);
    }

    //cria relacoes entre seguidores
    while (nLinhas > 4+nUsuarios) {
        int idSeguido;
        int idSeguidor;

        in >> idSeguido;
        in >> idSeguidor;

        for (int i=1; i<=rede->getPerfis()->size(); i++) {
            for (int j=1; j<=rede->getPerfis()->size(); j++) {
                if (i == idSeguido && j == idSeguidor) {
                    rede->getPerfil(i)->adicionarSeguidor(rede->getPerfil(j));
                }
            }
        }

        nLinhas--;
    }

    in.close();
    return rede;

}
