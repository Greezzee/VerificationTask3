#include "bookshop/shop.hpp"

bookshop::Bookshop::Bookshop() {}

void bookshop::Bookshop::addBook(Book newBook, size_t count = 1) {
    if (!Book::isBookExists(newBook.getId()))
        return;
    
    if (count == 0)
        return;
    
    m_books[newBook] += count;
}

std::map<bookshop::BookID, size_t> bookshop::Bookshop::getCatalog() {
    std::map<bookshop::BookID, size_t> out;

    for (auto pair : m_books) {
        out[pair.first.getId()] = pair.second;
    }

    return out;
}

bookshop::OrderID bookshop::Bookshop::makeDeliveryOrder(Cart cart, DeliveryMethod dm, PaymentMethod pm, std::string delivery_addr, time_t delivery_time) {
    return {};
}

bookshop::OrderStatus bookshop::Bookshop::getOrderStatus(OrderID id) {
    return {};
}

bookshop::Order bookshop::Bookshop::getOrderInfo(OrderID id) {
    return {};
}

void bookshop::Bookshop::deliver(OrderID id) {

}

std::vector<bookshop::BooksPack> bookshop::Bookshop::transferToBuyer(OrderID id) {
    return {};
}