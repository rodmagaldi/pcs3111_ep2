#include "PersistenciaDaRede.h"
#include "Aluno.h"
#include "Disciplina.h"
#include "Professor.h"

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

    if(arq.fail()) {
        throw new logic_error("Erro ao salvar o arquivo.");

    } else {
        for (int i = 0; i<r->getPerfis()->size(); i++) {
            if (dynamic_cast<Aluno*>(r->getPerfis()->at(i))) {
                cout << "aluno" << endl;
                nAlunos++;
            }
            if (dynamic_cast<Professor*>(r->getPerfis()->at(i))) {
                cout << "prof" << endl;
                nProfs++;
            }
            if (dynamic_cast<Disciplina*>(r->getPerfis()->at(i))) {
                cout << "disc" << endl;
                nDisc++;
            }
        }

        arq << r->getPerfis()->size() << "\r\n";
        cout << "nPerfis" << endl;

        arq << nAlunos << "\r\n";
        cout << "nAlunos" << endl;

        for (int i = 0; i<r->getPerfis()->size(); i++) {
            if (dynamic_cast<Aluno*>(r->getPerfis()->at(i))) {
                Aluno* aluno = dynamic_cast<Aluno*>(r->getPerfis()->at(i));
                arq << aluno->getNumeroUSP() << " " << aluno->getNome() << " " << aluno->getEmail() << " " << aluno->getId() << "\r\n";
            }
        }

        arq << nProfs << "\r\n";
        cout << "nProfs" << endl;

        for (int i = 0; i<r->getPerfis()->size(); i++) {
            if (dynamic_cast<Professor*>(r->getPerfis()->at(i))) {
                Professor* prof = dynamic_cast<Professor*>(r->getPerfis()->at(i));
                arq << prof->getNumeroUSP() << " " << prof->getNome() << " " << prof->getEmail() << " " << prof->getDepartamento() << " " << prof->getId() << "\r\n";
            }
        }

        arq << nDisc << "\r\n";
        cout << "nDisc" << endl;

        for (int i = 0; i<r->getPerfis()->size(); i++) {
            if (dynamic_cast<Disciplina*>(r->getPerfis()->at(i))) {
                Disciplina* disc = dynamic_cast<Disciplina*>(r->getPerfis()->at(i));
                if (!disc->getPreRequisito()) {
                    arq << disc->getNome() << " " << disc->getResponsavel()->getId() << " " << -1 << " " << disc->getId() << "\r\n";
                } else {
                    arq << disc->getNome() << " " << disc->getResponsavel()->getId() << " " << disc->getPreRequisito()->getId() << " " << disc->getId() << "\r\n";
                }
            }
        }
    }

    arq.close();
}

RedeSocial* PersistenciaDaRede::carregar(string arquivo) {
    ifstream in;
    in.open(arquivo);

    if(!in.is_open()) {
        RedeSocial* rede = new RedeSocial();
        in.close();

        cout << "Arquivo nao encontrado!" << endl << "Inicializando rede vazia..." << endl;

        return rede;
    }

    if(in.fail()) {
        throw new logic_error("Falha no arquivo de entrada.");
        in.close();
    }

    RedeSocial* rede = new RedeSocial();

    int nUsuarios;
    in >> nUsuarios;

    int nAlunos;
    in >> nAlunos;

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

    in.close();
    return rede;

//    double temp;
//
//    for (int i = 0; i < nAlunos; i++) {
//        getline(file, linha);
//        stringstream in(linha);
//
//
//        for (int j = 0; j < quant; j++) {
//            in >> temp;
//            matrizArquivo->matriz[i][j] = (double)temp / 255;
//        }
//    }
}
