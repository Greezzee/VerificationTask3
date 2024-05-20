#ifndef CART_H_
#define CART_H_

#include <vector>
#include "book.hpp"

namespace bookshop {

    class Cart {
    public:
        Cart();

        void addBook(BookID book_id);

        std::vector<BookID> getAllOrderedBooks();
    };

} // namespace bookshop

#endif

