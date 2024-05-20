#ifndef BOOKSHOP_H_
#define BOOKSHOP_H_

#include "book.hpp"

namespace bookshop {

    class Bookshop {
    public:
        Bookshop();
        void addBook();
        void refund();
        void deliver();

    private:
    };

} // namespace bookshop

#endif // BOOKSHOP_H_