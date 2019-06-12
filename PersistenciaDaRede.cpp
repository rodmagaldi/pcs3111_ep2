#include "PersistenciaDaRede.h"
#include "Aluno.h"

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
    arq.open("teste.txt");

    if(arq.fail()) {
        throw new logic_error("Erro ao salvar o arquivo.");

    } else {
        for (int i = 0; i<r->getPerfis()->size(); i++) {
            if (dynamic_cast<Aluno*>(r->getPerfis()->at(i))) {
                nAlunos++;
            }
        }

        arq << nAlunos << "\r\n";

        for (int i = 0; i<r->getPerfis()->size(); i++) {
            if (dynamic_cast<Aluno*>(r->getPerfis()->at(i))) {
                Aluno* aluno = dynamic_cast<Aluno*>(r->getPerfis()->at(i));
                arq << aluno->getNumeroUSP() << " " << aluno->getNome() << " " << aluno->getEmail() << " " << aluno->getId() << "\r\n";
            }
        }
    }

    arq.close();
}

RedeSocial* PersistenciaDaRede::carregar(string arquivo) {
    ifstream in;
    in.open(arquivo);

    if(in.fail()) {
        throw new logic_error("Falha no arquivo de entrada.");
        in.close();
    }

    RedeSocial* rede = new RedeSocial();

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

        Aluno* aluno = new Aluno(numeroUSP, nome, email);
        rede->adicionar(aluno);
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
