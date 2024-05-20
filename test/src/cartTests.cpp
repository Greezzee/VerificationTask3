#include "bookshop/cart.hpp"

#include <gtest/gtest.h>

// helpful function for creating completely new book
bookshop::Book createNewUniqueBook() {

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

TEST(CreatingCart, NewCartIsEmpty) 
{
    bookshop::Cart cart;
    ASSERT_TRUE(cart.getAllOrderedBooks().empty());
}

TEST(CreatingCart, AddOneBookToCart)
{
    bookshop::Cart cart;
    bookshop::Book book = createNewUniqueBook();

    cart.addBook(book.getId());
    ASSERT_EQ(cart.getAllOrderedBooks().size(), 1);
    ASSERT_EQ(cart.getAllOrderedBooks().back().id, book.getId());
    ASSERT_EQ(cart.getAllOrderedBooks().back().count, 1);
}

TEST(CreatingCart, AddManyUniqueBooksToCart)
{
    bookshop::Cart cart;
    for (int i = 0; i < 20; i++) {
        bookshop::Book book = createNewUniqueBook();
        cart.addBook(book.getId());
    }

    ASSERT_EQ(cart.getAllOrderedBooks().size(), 20);
}

TEST(CreatingCart, BookID0CantBeAddedToCart)
{
    bookshop::Cart cart;
    cart.addBook(0);
    ASSERT_TRUE(cart.getAllOrderedBooks().empty());
}

TEST(CreatingCart, NotExistingBooksCantBeAddedToCart)
{
    bookshop::Cart cart;
    cart.addBook(9999999999);
    ASSERT_TRUE(cart.getAllOrderedBooks().empty());
}

TEST(CreatingCart, SameBookCanBeAddedToCartManyTimes)
{
    bookshop::Cart cart;
    bookshop::Book book = createNewUniqueBook();
    for (int i = 0; i < 50; i++)
        cart.addBook(book.getId());
    ASSERT_EQ(cart.getAllOrderedBooks().size(), 1);
    ASSERT_EQ(cart.getAllOrderedBooks().at(0).id, book.getId());
    ASSERT_EQ(cart.getAllOrderedBooks().at(0).count, 50);
}

TEST(CreatingCart, AddManySameBooksToCartOnce)
{
    bookshop::Cart cart;
    bookshop::Book book = createNewUniqueBook();

    cart.addBook(book.getId(), 80);
    ASSERT_EQ(cart.getAllOrderedBooks().size(), 1);
    ASSERT_EQ(cart.getAllOrderedBooks().back().id, book.getId());
    ASSERT_EQ(cart.getAllOrderedBooks().back().count, 80);
}

TEST(CreatingCart, AddManyBooksToCartPartially)
{
    bookshop::Cart cart;
    for (int i = 0; i < 20; i++) {
        bookshop::Book book = createNewUniqueBook();
        cart.addBook(book.getId(), i + 1);
    }

    ASSERT_EQ(cart.getAllOrderedBooks().size(), 20);
}

TEST(CreatingCart, Add0BookdsToCart) {
    bookshop::Cart cart;
    bookshop::Book book = createNewUniqueBook();

    cart.addBook(book.getId(), 0);
    ASSERT_TRUE(cart.getAllOrderedBooks().empty());
}

TEST(CreatingCart, Add0BookdsToFilledCart) {
    bookshop::Cart cart;
    bookshop::Book book = createNewUniqueBook();
    cart.addBook(book.getId(), 12);

    cart.addBook(book.getId(), 0);
    ASSERT_EQ(cart.getAllOrderedBooks().size(), 1);
    ASSERT_EQ(cart.getAllOrderedBooks()[0].count, 12);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}