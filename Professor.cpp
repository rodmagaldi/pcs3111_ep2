#include "Professor.h"

using namespace std;

class Perfil;

Professor::Professor(int numeroUSP, string nome, string email, string departamento): Pessoa (numeroUSP, nome, email), departamento (departamento) {
}

Professor::Professor(int id, int numeroUSP, string nome, string email, string departamento): Pessoa (numeroUSP, nome, email), departamento (departamento) {
    this->id_perfil = id;
}

Professor::~Professor() {
}

string Professor::getDepartamento(){
    return this->departamento;
}

void Professor::imprimir() {
    cout << "Departamento: " << this->getDepartamento() << endl;
    Perfil::imprimir();
}

