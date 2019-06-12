#include "IdInvalido.h"

#include <string>
#include <stdexcept>

using namespace std;

IdInvalido::IdInvalido(): logic_error("Id invalido.") {
};


IdInvalido::~IdInvalido() {
    //dtor
}
