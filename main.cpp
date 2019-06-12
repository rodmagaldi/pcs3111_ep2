#include "RedeSocial.h"
#include "Perfil.h"
#include "Publicacao.h"
#include "Professor.h"
#include "Disciplina.h"
#include "Evento.h"
#include "Aluno.h"
#include "PersistenciaDaRede.h"

#include <iostream>
#include <string>

#define MAXIMO_PUBLICACOES 20
#define MAXIMO_SEGUIDORES 2


using namespace std;

void visualizarPerfis(RedeSocial* redeSocial) {
    //Funcao que permite visualizar todos os perfis
    //da rede social com uma formatacao visualmente
    //agradavel, dentro dos limites de escopo do projeto

    for (int i = 0; i < redeSocial->getPerfis()->size(); i++) {
        cout << std::to_string(i+1) << ") " << redeSocial->getPerfis()->at(i)->getNome() << endl;
    }
}

void terminar(RedeSocial* redeSocial);
void cadastrarPerfil(RedeSocial* redeSocial);
void cadastrarDisciplina(RedeSocial* redeSocial);
void logar(RedeSocial* redeSocial);
void escolherAcao(RedeSocial* redeSocial, Perfil* perfil);
void verPublicacoesFeitas(RedeSocial* redeSocial, Perfil* perfil);
void verPublicacoesRecebidas(RedeSocial* redeSocial, Perfil* perfil);
void criarPublicacao(RedeSocial* redeSocial, Perfil* perfil);
void seguirPerfil(RedeSocial* redeSocial, Perfil* perfil);

void escolherOpcao(RedeSocial* redeSocial) {
    //Funcao que permite fazer a escolha de uma opcao
    //na inicializacao da rede social: cadastrar perfis,
    //fazer login ou terminar  o programa

    int input;
    cout << "Escolha uma opcao: " << endl;
    cout << endl;

    cout << "1) Cadastrar perfil" << endl;
    cout << "2) Cadastrar disciplina" << endl;
    cout << "3) Logar" << endl;
    cout << "0) Terminar" << endl;
    cout << endl;

    cin >> input;
    cout << endl;

    if (input == 1) {
        cout << "=== Cadastrar perfil ===" << endl;

        //chama a funcao para cadastrar um perfil
        cadastrarPerfil(redeSocial);

    } else if (input == 2) {
        cout << "=== Cadastrar disciplina ===" << endl;

        //chama a funcao para cadastrar uma disciplina
        cadastrarDisciplina(redeSocial);

    } else if (input == 3) {
        cout << "=== Logar ===" << endl;

        //chama a funcao para fazer login
        logar(redeSocial);

    } else if (input == 0) {
        cout << "=== Terminar ===" << endl;

        //chama a funcao para terminar
        terminar(redeSocial);

    } else {
        cout << "Escolha umas das alternativas: 1, 2, 3 ou 0." << endl;
        cout << endl;
        escolherOpcao(redeSocial);

    }
}

void cadastrarPerfil(RedeSocial* redeSocial) {
    //funcao que realiza o cadastro de novos perfis
    //na rede social


    int nusp;
    string nome;
    string email;
    string prof;
    string dept;

    cout << "Informe os dados do perfil: " << endl;
    cout << endl;

    cout << "Numero USP: ";
    cin >> nusp;
    cout << endl;

    cout << "Nome: ";
    cin.ignore(100, '\n');
    getline(cin, nome);
    cout << endl;

    cout << "E-mail: ";
    getline(cin, email);
    cout << endl;

    cout << "Professor (s/n): ";
    cin >> prof;
    cout << endl;

    if (prof == "n") {
        Aluno* perfilNovo = new Aluno(nusp, nome, email);
        redeSocial->adicionar(perfilNovo);
        escolherOpcao(redeSocial);
    }

    else if (prof == "s") {
        cout << "Departamento: ";
        cin >> dept;
        cout << endl;
        Professor* perfilNovo = new Professor(nusp, nome, email, dept);
        redeSocial->adicionar(perfilNovo);
        escolherOpcao(redeSocial);
    }

    else {
        cout << "Faça uma escolha valida para professor: 's' ou 'n'." << endl;
        cout << endl;
        cadastrarPerfil(redeSocial);
    }
}

void cadastrarDisciplina(RedeSocial* redeSocial) {
    //funcao que realiza o cadastro de novas disciplinas
    //na rede social

    string nome;
    int nresponsavel;
    Professor* responsavel = NULL;
    int npreRequisito;
    Disciplina* preRequisito = NULL;

    cout << "Informe os dados da disciplina: " << endl;
    cout << endl;

    cout << "Nome: ";
    cin.ignore(100, '\n');
    getline(cin, nome);
    cout << endl;

    cout << "Responsavel: " << endl;
    visualizarPerfis(redeSocial);

    cout << "Digite o numero ou 0 para cancelar: ";
    cin >> nresponsavel;
    cout << endl;


    if (nresponsavel == 0) {
        //cancelamento da acao

        cout << "===== Criacao de disciplina cancelada! =====" << endl;
        cout << endl;
        escolherOpcao(redeSocial);
    } else if (nresponsavel > 0 && nresponsavel <= redeSocial->getPerfis()->size()) {
        //escolha de um responsavel
        nresponsavel--;

        if (dynamic_cast<Professor*>(redeSocial->getPerfis()->at(nresponsavel)) != NULL) {
            //caso seja professor

            responsavel = dynamic_cast<Professor*>(redeSocial->getPerfis()->at(nresponsavel));

            cout << "Pre-Requisito: " << endl;
            visualizarPerfis(redeSocial);

            cout << "Digite o numero ou 0 para nenhum: ";
            cin >> npreRequisito;
            cout << endl;

            if (npreRequisito == 0) {
                //caso nao haja pre-requisito

                Disciplina* perfilNovo = new Disciplina(nome, responsavel);
                redeSocial->adicionar(perfilNovo);
                escolherOpcao(redeSocial);
            } else if (npreRequisito > 0 && npreRequisito <= redeSocial->getPerfis()->size()) {
                //caso haja pre-requsito
                npreRequisito--;

                if (dynamic_cast<Disciplina*>(redeSocial->getPerfis()->at(npreRequisito))!= NULL) {
                    //caso seja valido

                    preRequisito = dynamic_cast<Disciplina*>(redeSocial->getPerfis()->at(npreRequisito));
                    Disciplina* perfilNovo = new Disciplina(nome, responsavel, preRequisito);
                    redeSocial->adicionar(perfilNovo);
                    escolherOpcao(redeSocial);

                } else {
                    //caso seja invalido

                    cout << "O Pre-Requisito deve ser uma disciplina!" << endl;
                    cout << endl;
                    cadastrarDisciplina(redeSocial);

                }
            } else {
                cout << "Escolha uma opcao valida." << endl;
                cout << endl;
                cadastrarDisciplina(redeSocial);
            }

        } else {
            //caso nao seja professor

            cout << "Somente professores podem ser responsaveis por disciplinas!" << endl;
            cout << endl;
            cadastrarDisciplina(redeSocial);
        }
    } else {
        cout << "Escolha um numero valido." << endl;
        cout << endl;
        cadastrarDisciplina(redeSocial);
    }
}

void logar(RedeSocial* redeSocial) {
    //funcao que permite escolher um perfil para fazer login
    //na rede social

    int nlogin;
    Perfil* usuarioLogado;

    cout << "Escolha um perfil:" << endl;
    visualizarPerfis(redeSocial);

    cout << "Digite o numero ou 0 para cancelar: ";
    cin >> nlogin;
    cout << endl;

    if (nlogin == 0) {
        cout << "===== Login cancelado =====" << endl;
        cout << endl;

        escolherOpcao(redeSocial);
    } else if (nlogin > 0 && nlogin <= redeSocial->getPerfis()->size()){
        nlogin--;
        usuarioLogado = redeSocial->getPerfis()->at(nlogin);
        escolherAcao(redeSocial, usuarioLogado);
    } else {
        cout << "Escolha uma opcao valida." << endl;
        cout << endl;
        logar(redeSocial);
    }
}

void escolherAcao(RedeSocial* redeSocial, Perfil* perfil) {
    //funcao que permite escolher a acao a ser tomada
    //quando o usuario esta logado

    int nopcao;

    if (dynamic_cast<Professor*>(perfil)!= NULL) {
        Professor* prof = dynamic_cast<Professor*>(perfil);
        cout << prof->getNumeroUSP() << " - " << prof->getNome() << endl;
        cout << "Departamento: " << prof->getDepartamento() << endl;
    }

    if (dynamic_cast<Disciplina*>(perfil)!= NULL) {
        Disciplina* disc = dynamic_cast<Disciplina*>(perfil);
        cout << disc->getNome() << endl;
        if (disc->getPreRequisito()!= NULL) {
            cout << "Pre-Requisito: " << disc->getPreRequisito()->getNome() << endl;
        } else {
            cout << "Pre-Requisito: -" << endl;
        }
    }

    cout << "Seguidores: " << perfil->getSeguidores()->size() << endl;
    cout << "---" << endl;
    cout << "Escolha uma opcao:" << endl;
    cout << "1) Ver publicacoes feitas" << endl;
    cout << "2) Ver publicacoes recebidas" << endl;
    cout << "3) Fazer publicacao" << endl;

    if (dynamic_cast<Disciplina*>(perfil) == NULL) {
        cout << "4) Seguir perfil" << endl;
    }

    cout << "0) Deslogar" << endl;
    cout << endl;

    cin >> nopcao;
    cout << endl;

    if (nopcao == 0) {
        cout << "===== Usuario " << perfil->getNome() << " deslogado! =====" << endl;
        cout << endl;
        logar(redeSocial);
    } else if (nopcao == 1) {
        verPublicacoesFeitas(redeSocial, perfil);
        escolherAcao(redeSocial, perfil);
    } else if (nopcao == 2) {
        verPublicacoesRecebidas(redeSocial, perfil);
    } else if (nopcao == 3) {
        criarPublicacao(redeSocial, perfil);
    } else if (nopcao == 4 && dynamic_cast<Disciplina*>(perfil) == NULL) {
        seguirPerfil(redeSocial, perfil);
    } else {
        cout << "Escolha uma opcao valida." << endl;
        cout << endl;
        escolherAcao(redeSocial, perfil);
    }

}

void verPublicacoesFeitas(RedeSocial* redeSocial, Perfil* perfil) {
    //funcao que permite ver todas as publicacoes feitas
    //pelo perfil que esta logado

    auto l_front = perfil->getPublicacoesFeitas()->begin();

    cout << "Publicacoes feitas: " << endl;
    for (int i = 0; i < perfil->getPublicacoesFeitas()->size(); i++) {

        Publicacao* pub = *l_front;

        if (dynamic_cast<Evento*>(pub)){
            Evento* ev = dynamic_cast<Evento*>(pub);
            cout << std::to_string(i+1) << ") " << ev->getData() << " - " << ev->getTexto() << " (" << perfil->getNome() << ") [" << ev->getCurtidas() << " curtidas]" << endl;
        } else {
            cout << std::to_string(i+1) << ") "<< pub->getTexto() << " (" << perfil->getNome() << ") [" << pub->getCurtidas() << " curtidas]" << endl;
        }

        std::advance(l_front, 1);
    }
    cout << endl;
}

void verPublicacoesRecebidas(RedeSocial* redeSocial, Perfil* perfil) {
    //funcao que permite ver todas as publicacoes recebidas pelo
    //perfil que esta logado, alem de permitir a curtida das publicacoes

    int npub;
    auto l_front = perfil->getPublicacoesRecebidas()->begin();

    cout << "Publicacoes recebidas: " << endl;
    for (int i = 0; i < perfil->getPublicacoesRecebidas()->size(); i++) {

        Publicacao* pub = *l_front;

        if (dynamic_cast<Evento*>(pub)) {
            Evento* ev = dynamic_cast<Evento*>(pub);
            cout << std::to_string(i+1) << ") " << ev->getData() << " - " << ev->getTexto() << " (" << ev->getAutor()->getNome() << ") [" << ev->getCurtidas() << " curtidas]" << endl;
        } else {
            cout << std::to_string(i+1) << ") " << pub->getTexto() << " (" << pub->getAutor()->getNome() << ") [" << pub->getCurtidas() << " curtidas]" << endl;
        }
        std::advance(l_front, 1);
    }

    cout << endl;
    cout << "Digite o numero da mensagem para curtir ou 0 para voltar: ";
    cin >> npub;
    cout << endl;

    if (npub == 0) {
        escolherAcao(redeSocial, perfil);
    } else if(npub > 0 && npub <= perfil->getPublicacoesRecebidas()->size()) {
        npub--;

        auto j_front = perfil->getPublicacoesRecebidas()->begin();
        std::advance(j_front, npub);
        Publicacao* pub = *j_front;
        pub->curtir(perfil);
        verPublicacoesRecebidas(redeSocial, perfil);
    } else {
        cout << "Escolha uma opcao valida." << endl;
        cout << endl;
        verPublicacoesRecebidas(redeSocial, perfil);
    }
}

void criarPublicacao(RedeSocial* redeSocial, Perfil* perfil) {
    //funcao usada para a criacao de uma publicacao
    //a partir do perfil logado


    string evento;
    string dataEvento;
    string msg;

    cout << "===== Criador de publicacao =====" << endl;
    cout << endl;
    cout << "Evento (s/n): ";
    cin >> evento;
    cout << endl;
    cin.ignore(1000, '\n');

    if (evento == "s") {
        cout << "Data: ";
        getline(cin, dataEvento);
        cout << endl;
        cout << "Texto: ";
        getline(cin, msg);
        cout << endl;

        perfil->publicar(msg, dataEvento);
        escolherAcao(redeSocial, perfil);

    } else if (evento == "n") {
        cout << "Texto: ";
        getline(cin, msg);
        cout << endl;

        perfil->publicar(msg);
        escolherAcao(redeSocial, perfil);

    } else {
        cout << "Escolha uma opcao valida: 's' ou 'n'." << endl;
        cout << endl;
        criarPublicacao(redeSocial, perfil);
    }
}

void seguirPerfil(RedeSocial* redeSocial, Perfil* perfil) {
    //funcao chamada sob a opcao `seguir perfil` do usuario logado.
    //permite seguir algum outro perfil que nao o seu proprio


    int nperfil;

    cout << "Perfil:" << endl;
    visualizarPerfis(redeSocial);
    cout << endl;
    cout << "Digite o numero ou 0 para cancelar: ";
    cin >> nperfil;
    cout << endl;

    if (nperfil == 0) {
        cout << "===== Acao de seguir cancelada =====" << endl;
        cout << endl;
        escolherAcao(redeSocial, perfil);

    } else if (nperfil > 0 && nperfil <= redeSocial->getPerfis()->size()){
        nperfil--;
        redeSocial->getPerfis()->at(nperfil)->adicionarSeguidor(perfil);

        if (redeSocial->getPerfis()->at(nperfil) == perfil) {
            cout << "Voce nao pode seguir a si mesmo!" << endl;
            cout << endl;
        }

        escolherAcao(redeSocial, perfil);
    } else {
        cout << "Escolha uma opcao valida." << endl;
        cout  << endl;
        seguirPerfil(redeSocial, perfil);
    }
}

void terminar(RedeSocial* redeSocial) {
    //funcao que termina todo o processo. Pode ser chamada
    //apenas quando nao ha usuarios logados

    delete redeSocial;
}

int main() {

    cout << "Bem vindo ao inicializador de Rede Social." << endl << endl;
    cout << "===== Rede Social iniciada =====" << endl;
    cout << endl;

    RedeSocial* redeSocial = new RedeSocial();

    escolherOpcao(redeSocial);

  return 0;
}
