#ifndef REDESOCIAL_H
#define REDESOCIAL_H
#include "Perfil.h"
#include <vector>

using namespace std;

class Perfil;

class RedeSocial {
public:
  RedeSocial();
  virtual ~RedeSocial();
  vector<Perfil*>* getPerfis();
  Perfil* getPerfil(int id);
  void adicionar(Perfil* perfil);
  void imprimir();

protected:
  vector<Perfil*>* perfis;

  bool checaPerfil(Perfil* perfil);
};

#endif // REDESOCIAL_H
