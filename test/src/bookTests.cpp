#include "bookshop/book.hpp"

#include <gtest/gtest.h>

TEST(BookCreateTest, NormalBook)
{
  std::string name = "Some book";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = 1811;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_NE(book.getId(), 0); // book is created successfully

  // book is filled correctly
  ASSERT_STREQ(book.getTitle().c_str(), name.c_str());
  ASSERT_STREQ(book.getAuthor().c_str(), author.c_str());
  ASSERT_STREQ(book.getPublisher().c_str(), publisher.c_str());
  ASSERT_STREQ(book.getGenre().c_str(), genre.c_str());

  ASSERT_EQ(book.getPrice(), price);
  ASSERT_EQ(book.getReleaseYear(), releaseYear);
}

TEST(BookCreateTest, BookNotCreatedIsIncorrect) {
  bookshop::Book book;
  ASSERT_EQ(book.getId(), 0);
}

TEST(BookCreateTest, NamelessBookForbid)
{
  std::string name = "";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = 1811;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_EQ(book.getId(), 0);
}

TEST(BookCreateTest, BookWithoutAuthorIsOK)
{
  std::string name = "Some book";
  std::string author = "";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = 1811;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_NE(book.getId(), 0); // book is created successfully

  // book is filled correctly
  ASSERT_STREQ(book.getTitle().c_str(), name.c_str());
  ASSERT_STREQ(book.getAuthor().c_str(), author.c_str());
  ASSERT_STREQ(book.getPublisher().c_str(), publisher.c_str());
  ASSERT_STREQ(book.getGenre().c_str(), genre.c_str());

  ASSERT_EQ(book.getPrice(), price);
  ASSERT_EQ(book.getReleaseYear(), releaseYear);
}

TEST(BookCreateTest, BookWithoutPublisherIsOK)
{
  std::string name = "Some book";
  std::string author = "Pushkin";
  std::string publisher = "";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = 1811;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_NE(book.getId(), 0); // book is created successfully

  // book is filled correctly
  ASSERT_STREQ(book.getTitle().c_str(), name.c_str());
  ASSERT_STREQ(book.getAuthor().c_str(), author.c_str());
  ASSERT_STREQ(book.getPublisher().c_str(), publisher.c_str());
  ASSERT_STREQ(book.getGenre().c_str(), genre.c_str());

  ASSERT_EQ(book.getPrice(), price);
  ASSERT_EQ(book.getReleaseYear(), releaseYear);
}

TEST(BookCreateTest, BookWithoutGenreIsOK)
{
  std::string name = "Some book";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "";
  size_t price = 20;
  int releaseYear = 1811;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_NE(book.getId(), 0); // book is created successfully

  // book is filled correctly
  ASSERT_STREQ(book.getTitle().c_str(), name.c_str());
  ASSERT_STREQ(book.getAuthor().c_str(), author.c_str());
  ASSERT_STREQ(book.getPublisher().c_str(), publisher.c_str());
  ASSERT_STREQ(book.getGenre().c_str(), genre.c_str());

  ASSERT_EQ(book.getPrice(), price);
  ASSERT_EQ(book.getReleaseYear(), releaseYear);
}

TEST(BookCreateTest, BookCanBeFree)
{
  std::string name = "Some book";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 0;
  int releaseYear = 1811;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_NE(book.getId(), 0); // book is created successfully

  // book is filled correctly
  ASSERT_STREQ(book.getTitle().c_str(), name.c_str());
  ASSERT_STREQ(book.getAuthor().c_str(), author.c_str());
  ASSERT_STREQ(book.getPublisher().c_str(), publisher.c_str());
  ASSERT_STREQ(book.getGenre().c_str(), genre.c_str());

  ASSERT_EQ(book.getPrice(), price);
  ASSERT_EQ(book.getReleaseYear(), releaseYear);
}

TEST(BookCreateTest, BookCanBeVeryExpensive) {
  std::string name = "Some book";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 99999999999999;
  int releaseYear = 1811;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_NE(book.getId(), 0); // book is created successfully

  // book is filled correctly
  ASSERT_STREQ(book.getTitle().c_str(), name.c_str());
  ASSERT_STREQ(book.getAuthor().c_str(), author.c_str());
  ASSERT_STREQ(book.getPublisher().c_str(), publisher.c_str());
  ASSERT_STREQ(book.getGenre().c_str(), genre.c_str());

  ASSERT_EQ(book.getPrice(), price);
  ASSERT_EQ(book.getReleaseYear(), releaseYear);
}

TEST(BookCreateTest, BookCanBeWrittenInYear0)
{
  std::string name = "Some book";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = 0;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_NE(book.getId(), 0); // book is created successfully

  // book is filled correctly
  ASSERT_STREQ(book.getTitle().c_str(), name.c_str());
  ASSERT_STREQ(book.getAuthor().c_str(), author.c_str());
  ASSERT_STREQ(book.getPublisher().c_str(), publisher.c_str());
  ASSERT_STREQ(book.getGenre().c_str(), genre.c_str());

  ASSERT_EQ(book.getPrice(), price);
  ASSERT_EQ(book.getReleaseYear(), releaseYear);
}

TEST(BookCreateTest, BookCanBeWrittenInBC)
{
  std::string name = "Some book";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = -180;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_NE(book.getId(), 0); // book is created successfully

  // book is filled correctly
  ASSERT_STREQ(book.getTitle().c_str(), name.c_str());
  ASSERT_STREQ(book.getAuthor().c_str(), author.c_str());
  ASSERT_STREQ(book.getPublisher().c_str(), publisher.c_str());
  ASSERT_STREQ(book.getGenre().c_str(), genre.c_str());

  ASSERT_EQ(book.getPrice(), price);
  ASSERT_EQ(book.getReleaseYear(), releaseYear);
}

TEST(BookCreateTest, BookCannotBeWrittenInFuture)
{
  std::string name = "Name";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = 2516;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_EQ(book.getId(), 0);
}

TEST(BookCreateTest, BookCannotBeWrittenBefore3000BC)
{
  std::string name = "Name";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = -4106;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_EQ(book.getId(), 0);
}

TEST(MultipleBookCreate, BooksAlwaysHaveDifferentID)
{
  std::string name1 = "Some book", name2 = "Other book";
  std::string author1 = "Pushkin", author2 = "Esenin";
  std::string publisher1 = "Book Company Inc.", publisher2 = "Babylon Library";
  std::string genre1 = "Drama", genre2 = "Comedy";
  size_t price1 = 20, price2 = 10;
  int releaseYear1 = 1811, releaseYear2 = 1910;

  bookshop::Book book1 = bookshop::createBook(name1, author1, publisher1, genre1, price1, releaseYear1);
  bookshop::Book book2 = bookshop::createBook(name2, author2, publisher2, genre2, price2, releaseYear2);

  ASSERT_NE(book1.getId(), book2.getId());
}

TEST(MultipleBookCreate, BooksCanHaveIdenticalFieldsButStillDifferent)
{
  std::string name1 = "Some book", name2 = "Some book";
  std::string author1 = "Pushkin", author2 = "Pushkin";
  std::string publisher1 = "Book Company Inc.", publisher2 = "Book Company Inc.";
  std::string genre1 = "Drama", genre2 = "Drama";
  size_t price1 = 20, price2 = 20;
  int releaseYear1 = 1811, releaseYear2 = 1811;

  bookshop::Book book1 = bookshop::createBook(name1, author1, publisher1, genre1, price1, releaseYear1);
  bookshop::Book book2 = bookshop::createBook(name2, author2, publisher2, genre2, price2, releaseYear2);

  ASSERT_NE(book1.getId(), book2.getId());
}

TEST(BookCopying, BookCanBeCopied) {
  std::string name = "Some book";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = 1811;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);
  bookshop::Book copy = book;

  ASSERT_EQ(book.getId(), copy.getId()); // book is created successfully

  // book is filled correctly
  ASSERT_STREQ(book.getTitle().c_str(), copy.getTitle().c_str());
  ASSERT_STREQ(book.getAuthor().c_str(), copy.getAuthor().c_str());
  ASSERT_STREQ(book.getPublisher().c_str(), copy.getPublisher().c_str());
  ASSERT_STREQ(book.getGenre().c_str(), copy.getGenre().c_str());

  ASSERT_EQ(book.getPrice(), copy.getPrice());
  ASSERT_EQ(book.getReleaseYear(), copy.getReleaseYear());
}

TEST(BookExistance, CreatedBookExists) {
  std::string name = "Some book";
  std::string author = "Pushkin";
  std::string publisher = "Book Company Inc.";
  std::string genre = "Drama";
  size_t price = 20;
  int releaseYear = 1811;

  bookshop::Book book = bookshop::createBook(name, author, publisher, genre, price, releaseYear);

  ASSERT_TRUE(bookshop::Book::isBookExists(book.getId()));
}

TEST(BookExistance, BookID0NotExists) {
  ASSERT_FALSE(bookshop::Book::isBookExists(0));
}

TEST(BookExistance, BookWithVeryHighIDNotExists) {
  ASSERT_FALSE(bookshop::Book::isBookExists(9999999));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
