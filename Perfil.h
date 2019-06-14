#ifndef PERFIL_H
#define PERFIL_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Publicacao.h"
#include "RedeSocial.h"

#define MAXIMO_SEGUIDORES 2

using namespace std;

class Publicacao;

class Perfil {
protected:

  static int id; //ESCOPO DE CLASSE
  static int ultimoId;

  string nome;
  int id_perfil;

  vector<Perfil*>* seguidores = new vector<Perfil*>;

  list<Publicacao*>* publicacoesFeitas = new list<Publicacao*>;

  list<Publicacao*>* publicacoesRecebidas = new list<Publicacao*>;

  //Confere se o seguidor ja foi adicionado a lista de seguidores. Se sim, ele nao eh adicionado novamente
  bool conferirSeguidor(Perfil* seguidorTeorico);

public:

  Perfil(string nome);
  Perfil(int id, string nome); //persistencia
  virtual ~Perfil() = 0;

  static void setUltimoId(int ultimoId); //persistencia, ESCOPO DE CLASSE
  static int getUltimoId(); //persistencia, ESCOPO DE CLASSE

  virtual int getId();
  string getNome();

  virtual void adicionarSeguidor(Perfil* seguidor);

  virtual void publicar(string texto); //mensagem
  virtual void publicar(string texto, string data); //evento

  virtual void receber(Publicacao* p);
  virtual list<Publicacao*>* getPublicacoesFeitas();
  virtual list<Publicacao*>* getPublicacoesRecebidas();

  virtual vector<Perfil*>* getSeguidores();

  virtual void imprimir(); //fazer como eu quiser
};

#endif // PERFIL_H
