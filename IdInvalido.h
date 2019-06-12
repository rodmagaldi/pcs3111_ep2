#ifndef IDINVALIDO_H
#define IDINVALIDO_H

#include <stdexcept>
using namespace std;

class IdInvalido: public logic_error {
    public:
        IdInvalido();
        virtual ~IdInvalido();

    protected:

    private:
};

#endif // IDINVALIDO_H
