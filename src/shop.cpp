#include "bookshop/shop.hpp"

bookshop::Bookshop::Bookshop() {}

bookshop::OrderID bookshop::Bookshop::s_nextFreeOrderID = 1;

void bookshop::Bookshop::addBook(Book newBook, size_t count) {
    if (!Book::isBookExists(newBook.getId()))
        return;
    
    if (count == 0)
        return;
    
    m_books[newBook] += count;
    m_booksByID[newBook.getId()] = newBook;
}

std::map<bookshop::BookID, size_t> bookshop::Bookshop::getCatalog() {
    std::map<bookshop::BookID, size_t> out;

    for (auto&& pair : m_books) {
        out[pair.first.getId()] = pair.second;
    }

    return out;
}

bookshop::OrderID bookshop::Bookshop::makeDeliveryOrder(Cart cart, DeliveryMethod dm, PaymentMethod pm, std::string delivery_addr, time_t delivery_time) {
    Order newOrder;

    for (auto& bookOrder : cart.getAllOrderedBooks()) {
        if (m_booksByID.find(bookOrder.id) == m_booksByID.end())
            continue;

        auto& foundBook = m_books[m_booksByID[bookOrder.id]];

        if (foundBook == 0)
            continue;

        newOrder.actualCart.addBook(bookOrder.id, std::min(bookOrder.count, foundBook));
        foundBook -= foundBook > bookOrder.count ? bookOrder.count : foundBook;
    }

    if (newOrder.actualCart.getAllOrderedBooks().empty())
        return 0;
    
    newOrder.initialCart = cart;
    newOrder.deliveryMethod = dm;
    newOrder.paymentMethod = pm;

    if (newOrder.deliveryMethod == DeliveryMethod::COURIER_DELIVERY && delivery_addr.empty())
        return 0;
    
    if (newOrder.deliveryMethod == DeliveryMethod::COURIER_DELIVERY && delivery_time <= std::time(nullptr))
        return 0;

    newOrder.deliveryAddress = delivery_addr;
    newOrder.deliveryTime = delivery_time;

    newOrder.id = s_nextFreeOrderID;
    s_nextFreeOrderID++;

    newOrder.status = OrderStatus::ACCEPTED;

    m_orders[newOrder.id] = newOrder;

    return newOrder.id;
}

bookshop::OrderStatus bookshop::Bookshop::getOrderStatus(OrderID id) {
    if (m_orders.find(id) == m_orders.end())
        return OrderStatus::NO_STATUS;
    return m_orders[id].status;
}

bookshop::Order bookshop::Bookshop::getOrderInfo(OrderID id) {
    if (m_orders.find(id) == m_orders.end())
        return {};
    return m_orders[id];
}

void bookshop::Bookshop::deliver(OrderID id) {
    if (m_orders.find(id) == m_orders.end())
        return;
    
    if (m_orders[id].deliveryMethod == DeliveryMethod::COURIER_DELIVERY && m_orders[id].status == OrderStatus::ACCEPTED)
        m_orders[id].status = OrderStatus::IN_DELIVERY;

    if (m_orders[id].deliveryMethod == DeliveryMethod::SELF_DELIVERY && m_orders[id].status == OrderStatus::ACCEPTED)
        m_orders[id].status = OrderStatus::AWAITING_PICKUP;
}

std::vector<bookshop::BooksPack> bookshop::Bookshop::transferToBuyer(OrderID id) {
    if (m_orders.find(id) == m_orders.end())
        return {};

    if (m_orders[id].deliveryMethod == DeliveryMethod::COURIER_DELIVERY && m_orders[id].status == OrderStatus::IN_DELIVERY)
        m_orders[id].status = OrderStatus::FINISHED;
    else if (m_orders[id].deliveryMethod == DeliveryMethod::SELF_DELIVERY && m_orders[id].status == OrderStatus::AWAITING_PICKUP)
        m_orders[id].status = OrderStatus::FINISHED;
    else return {};

    std::vector<bookshop::BooksPack> out;
    for (auto& bookOrder : m_orders[id].actualCart.getAllOrderedBooks()) {
        out.push_back({m_booksByID[bookOrder.id], bookOrder.count});
    }

    return out;
}

void bookshop::Bookshop::initiateRefund(OrderID id, RefundType refundType, std::string from_addr) {
    if (m_orders.find(id) == m_orders.end())
        return;
    
    auto& order = m_orders[id];

    if (refundType == RefundType::UNDELIVERED_ORDER_REFUND && 
       (order.status == OrderStatus::ACCEPTED ||
        order.status == OrderStatus::AWAITING_PICKUP ||
        order.status == OrderStatus::IN_DELIVERY)) {

        order.refundType = RefundType::UNDELIVERED_ORDER_REFUND;
        order.status = OrderStatus::REFUND_INITIATED;   
    }
    else if (refundType == RefundType::SELF_REFUND && order.status == OrderStatus::FINISHED) {
        order.refundType = RefundType::SELF_REFUND;
        order.status = OrderStatus::REFUND_INITIATED;   
    }
    else if (refundType == RefundType::COURIER_REFUND && order.status == OrderStatus::FINISHED && !from_addr.empty()) {
        order.refundType = RefundType::COURIER_REFUND;
        order.status = OrderStatus::REFUND_INITIATED;  
        order.deliveryAddress = from_addr;
    }

}

void bookshop::Bookshop::deliverRefund(OrderID id) {

}

void bookshop::Bookshop::finishRefund(OrderID id) {

}