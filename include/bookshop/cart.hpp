#ifndef CART_H_
#define CART_H_

#include <vector>
#include <map>
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

        void addBook(BookID book_id, size_t count = 1);

        std::vector<BookOrder> getAllOrderedBooks();
    private:
        std::map<BookID, size_t> m_content;
    };

} // namespace bookshop

#endif

