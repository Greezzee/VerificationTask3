#ifndef CART_H_
#define CART_H_

#include <vector>
#include "book.hpp"

namespace bookshop {

    struct BookOrder
    {
        BookID id;
        size_t count;
    };

    class Cart {
    public:
        Cart();

        void addBook(BookID book_id, size_t count = 0);

        std::vector<BookOrder> getAllOrderedBooks();

    };

} // namespace bookshop

#endif

