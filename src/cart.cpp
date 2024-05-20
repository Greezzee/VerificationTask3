#include "bookshop/cart.hpp"

bookshop::Cart::Cart() {}

void bookshop::Cart::addBook(BookID book_id, size_t count) {
    if (count == 0)
        return;
    if (!Book::isBookExists(book_id))
        return;
    
    // there are we init with 0 AND adding count
    m_content[book_id] += count;
}

std::vector<bookshop::BookOrder> bookshop::Cart::getAllOrderedBooks() {
    std::vector<BookOrder> out;
    for (auto& order : m_content)
        out.push_back({order.first, order.second});
    return out;
}