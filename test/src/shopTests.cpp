#include <gtest/gtest.h>
#include <chrono>
#include "bookshop/shop.hpp"

bookshop::Book createNewUniqueBook() 
{
    static size_t s_id = 0;
    s_id++;

    std::string name = "Some book" + std::to_string(s_id);
    std::string author = "Pushkin" + std::to_string(s_id);
    std::string publisher = "Book Company Inc." + std::to_string(s_id);
    std::string genre = "Drama" + std::to_string(s_id);
    size_t price = 20 + s_id;
    int releaseYear = -2000 + s_id;

    return bookshop::createBook(name, author, publisher, genre, price, releaseYear);
}

TEST(CreateNewShop, NewShopIsEmpty)
{
    bookshop::Bookshop shop;
    ASSERT_TRUE(shop.getCatalog().empty());
}

TEST(AddNewBookToShop, AddOneBook)
{
    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();

    shop.addBook(book);
    auto catalog = shop.getCatalog();
    ASSERT_EQ(catalog.size(), 1);
    ASSERT_NE(catalog.find(book.getId()), catalog.end());
    ASSERT_EQ(catalog[book.getId()], 1);
}

TEST(AddNewBookToShop, AddZeroBooks)
{
    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();

    shop.addBook(book, 0);
    auto catalog = shop.getCatalog();
    ASSERT_TRUE(catalog.empty());
}

TEST(AddNewBookToShop, AddSeveralEqualBooks)
{
    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();

    shop.addBook(book, 28);
    auto catalog = shop.getCatalog();
    ASSERT_EQ(catalog.size(), 1);
    ASSERT_NE(catalog.find(book.getId()), catalog.end());
    ASSERT_EQ(catalog[book.getId()], 28);
}

TEST(AddNewBookToShop, AddSeveralDifferentBooks)
{
    bookshop::Bookshop shop;

    for (int i = 0; i < 20; i++) {
        bookshop::Book book = createNewUniqueBook();
        shop.addBook(book);
    }

    auto catalog = shop.getCatalog();
    ASSERT_EQ(catalog.size(), 20);
    for (auto book_data : catalog)
        ASSERT_EQ(book_data.second, 1);
}

TEST(AddNewBookToShop, AddNotCreatedBook)
{
    bookshop::Bookshop shop;
    bookshop::Book book;

    shop.addBook(book);
    auto catalog = shop.getCatalog();
    ASSERT_TRUE(catalog.empty());
}

TEST(OrderBook, OrderDelivery)
{
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1;
    cart1.addBook(book.getId(), 10);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);
    

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::ACCEPTED);
    auto order1 = shop.getOrderInfo(id1);
    ASSERT_EQ(order1.id, id1);
    ASSERT_EQ(order1.deliveryAddress, delivery_addr);
    ASSERT_EQ(order1.deliveryMethod, bookshop::DeliveryMethod::SELF_DELIVERY);
    ASSERT_EQ(order1.deliveryTime, delivery_time);
    ASSERT_EQ(order1.paymentMethod, bookshop::PaymentMethod::UPON_RECEIVING);
    ASSERT_EQ(order1.initialCart.getAllOrderedBooks(), cart1.getAllOrderedBooks());
    ASSERT_EQ(order1.actualCart.getAllOrderedBooks(), cart1.getAllOrderedBooks());
}

TEST(OrderBook, OrderTwoDeliveries) {
        std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1, cart2;
    cart1.addBook(book.getId(), 10);
    cart2.addBook(book.getId(), 7);

    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);
    
    bookshop::OrderID id2 = shop.makeDeliveryOrder(cart2, 
                                bookshop::DeliveryMethod::COURIER_DELIVERY,
                                bookshop::PaymentMethod::UPON_CONTACT,
                                delivery_addr,
                                delivery_time);

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::ACCEPTED);
    ASSERT_EQ(shop.getOrderStatus(id2), bookshop::OrderStatus::ACCEPTED);

    auto order1 = shop.getOrderInfo(id1);
    auto order2 = shop.getOrderInfo(id2);

    ASSERT_EQ(order1.deliveryMethod, bookshop::DeliveryMethod::SELF_DELIVERY);
    ASSERT_EQ(order1.paymentMethod, bookshop::PaymentMethod::UPON_RECEIVING);

    ASSERT_EQ(order2.deliveryMethod, bookshop::DeliveryMethod::COURIER_DELIVERY);
    ASSERT_EQ(order2.paymentMethod, bookshop::PaymentMethod::UPON_CONTACT);
}

TEST(OrderBook, OrderDecreaseBooksCountInCatalog) {
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1;
    cart1.addBook(book.getId(), 10);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);

    ASSERT_EQ(shop.getCatalog().at(book.getId()), 20);
}

TEST(OrderBook, OrderMoreThanShopHave) {
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1;
    cart1.addBook(book.getId(), 40);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);

    ASSERT_EQ(shop.getCatalog().at(book.getId()), 0);

    bookshop::Order order = shop.getOrderInfo(id1);

    ASSERT_EQ(order.initialCart.getAllOrderedBooks(), cart1.getAllOrderedBooks());
    ASSERT_NE(order.actualCart.getAllOrderedBooks(), cart1.getAllOrderedBooks());
    ASSERT_EQ(order.actualCart.getAllOrderedBooks()[0].count, 30);
}

TEST(OrderBook, OrderOnlyBooksShopDoesntHave) {
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();

    bookshop::Cart cart1;
    cart1.addBook(book.getId());
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);

    ASSERT_EQ(id1, 0);
}

TEST(OrderBook, OrderWithEmptyCart) {
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1;
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);

    ASSERT_EQ(id1, 0);
}

TEST(OrderBook, OrderButAllBooksRanOut) {
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 1);

    bookshop::Cart cart1;
    cart1.addBook(book.getId(), 1);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);

    bookshop::OrderID id2 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);

    ASSERT_EQ(id2, 0);
}

TEST(OrderBook, OrderCourierToThePast) {
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) - 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1;
    cart1.addBook(book.getId(), 3);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::COURIER_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);

    ASSERT_EQ(id1, 0);
}

TEST(OrderBook, OrderCourierWithoutAddr) {
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book);

    bookshop::Cart cart1;
    cart1.addBook(book.getId());
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::COURIER_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                "",
                                delivery_time);

    ASSERT_EQ(id1, 0);
}

TEST(OrderBook, OrderBooksShopDoesntHave) {
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book1 = createNewUniqueBook();
    bookshop::Book book2 = createNewUniqueBook();

    shop.addBook(book1, 30);

    bookshop::Cart cart1;
    cart1.addBook(book1.getId(), 5);
    cart1.addBook(book2.getId(), 6);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);

    bookshop::Order order = shop.getOrderInfo(id1);

    ASSERT_EQ(order.initialCart.getAllOrderedBooks(), cart1.getAllOrderedBooks());
    ASSERT_NE(order.actualCart.getAllOrderedBooks(), cart1.getAllOrderedBooks());
    ASSERT_EQ(order.actualCart.getAllOrderedBooks().size(), 1);
    ASSERT_EQ(order.actualCart.getAllOrderedBooks()[0].count, 5);
}

TEST(DeliverBook, FullCourierDeliveryPath)
{
    std::string delivery_addr = "Pushkin's street";
    time_t delivery_time = std::time(nullptr) + 60 * 60 * 24;

    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1;
    cart1.addBook(book.getId(), 5);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::COURIER_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                delivery_addr,
                                delivery_time);

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::ACCEPTED);

    shop.deliver(id1);

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::IN_DELIVERY);

    auto books = shop.transferToBuyer(id1);

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::FINISHED);

    ASSERT_EQ(books.size(), 1);
    ASSERT_EQ(books[0].book.getId(), book.getId());
    ASSERT_EQ(books[0].count, 5);
}

TEST(DeliverBook, FullSelfDeliveryPath)
{
    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1;
    cart1.addBook(book.getId(), 5);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                "", 0);

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::ACCEPTED);

    shop.deliver(id1);

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::AWAITING_PICKUP);

    auto books = shop.transferToBuyer(id1);

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::FINISHED);

    ASSERT_EQ(books.size(), 1);
    ASSERT_EQ(books[0].book.getId(), book.getId());
    ASSERT_EQ(books[0].count, 5);
}

TEST(DeliverBook, TransferBeforeDelivery)
{
    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1;
    cart1.addBook(book.getId(), 5);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                "", 0);

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::ACCEPTED);

    auto books = shop.transferToBuyer(id1);

    ASSERT_TRUE(books.empty());
}

TEST(DeliverBook, DeliverAfterTransfer)
{
    bookshop::Bookshop shop;
    bookshop::Book book = createNewUniqueBook();
    shop.addBook(book, 30);

    bookshop::Cart cart1;
    cart1.addBook(book.getId(), 5);
    bookshop::OrderID id1 = shop.makeDeliveryOrder(cart1, 
                                bookshop::DeliveryMethod::SELF_DELIVERY,
                                bookshop::PaymentMethod::UPON_RECEIVING,
                                "", 0);

    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::ACCEPTED);

    shop.deliver(id1);
    auto books = shop.transferToBuyer(id1);
    shop.deliver(id1);
    ASSERT_EQ(shop.getOrderStatus(id1), bookshop::OrderStatus::FINISHED);
}

TEST(DeliverBook, StatusOfUnexistingOrder)
{
    bookshop::Bookshop shop;

    ASSERT_EQ(shop.getOrderStatus(999999999), bookshop::OrderStatus::NO_STATUS);
}

TEST(DeliverBook, InfoOfUnexistingOrder)
{
    bookshop::Bookshop shop;
    bppkshop::Order order = shop.getOrderInfo(99999999);
    ASSERT_EQ(order.id, 0);
}

TEST(DeliverBook, DeliverUnexistingProject)
{
    bookshop::OrderID id = 99999999;
    bookshop::Bookshop shop;
    shop.deliver(id);
    ASSERT_EQ(shop.getOrderStatus(id), bookshop::OrderStatus::NO_STATUS);
}

TEST(DeliverBook, TransferUnexistingProject)
{
    bookshop::OrderID id = 99999999;
    bookshop::Bookshop shop;
    auto bookpack = shop.transferToBuyer(id);
    ASSERT_EQ(shop.getOrderStatus(id), bookshop::OrderStatus::NO_STATUS);
    ASSERT_TRUE(bookpack.empty());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}