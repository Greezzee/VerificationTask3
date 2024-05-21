#ifndef BOOKSHOP_H_
#define BOOKSHOP_H_

#include <map>
#include <ctime>
#include "book.hpp"
#include "cart.hpp"

namespace bookshop {

    using OrderID = size_t;

    enum class DeliveryMethod {
        SELF_DELIVERY,
        COURIER_DELIVERY
    };

    enum class PaymentMethod {
        NO_PAYMENT,
        UPON_CONTACT,
        UPON_RECEIVING,
    };

    enum class OrderStatus {
        NO_STATUS,
        ACCEPTED,
        AWAITING_PICKUP,
        IN_DELIVERY,
        FINISHED,
        PARTIALLY_REFUNDED,
        FULLY_REFUNDED,
    };

    struct Order {
        DeliveryMethod deliveryMethod;
        PaymentMethod paymentMethod;

        std::string deliveryAddress;
        time_t deliveryTime;

        OrderID id = 0;
        OrderStatus status;
        Cart initialCart; // what was initially ordered/refunded
        Cart actualCart; // what will be delivered/refunded
    };

    struct BooksPack {
        Book book;
        size_t count;
    };

    class Bookshop {
    public:
        Bookshop();

        void addBook(Book newBook, size_t count = 1);
        std::map<BookID, size_t> getCatalog();

        OrderID makeDeliveryOrder(Cart cart, DeliveryMethod dm, PaymentMethod pm, std::string delivery_addr, time_t delivery_time);
        OrderStatus getOrderStatus(OrderID id);
        Order getOrderInfo(OrderID id);

        void deliver(OrderID id);
        std::vector<BooksPack> transferToBuyer(OrderID id);

    private:
        std::map<Book, size_t> m_books; // contains all books existed in the shop (even if not it haven't it) and its amount
        std::map<BookID, Book> m_booksByID;

        std::map<OrderID, Order> m_orders;

        static OrderID s_nextFreeOrderID;
    };

} // namespace bookshop

#endif // BOOKSHOP_H_