#include "bookshop/book.hpp"

#define CUR_YEAR 2024
#define EARLIEST_RELEASE_YEAR -3000

bookshop::BookID bookshop::Book::s_nextFreeID = 1;

std::string bookshop::Book::getTitle() {
    return m_title;
}
std::string bookshop::Book::getAuthor() {
    return m_author;
}
std::string bookshop::Book::getPublisher() {
    return m_publisher;
}
std::string bookshop::Book::getGenre() {
    return m_genre;
}
size_t bookshop::Book::getPrice() {
    return m_price;
}
int bookshop::Book::getReleaseYear() {
    return m_releaseYear;
}
bookshop::BookID bookshop::Book::getId() {
    return m_id;
}

void bookshop::Book::setTitle(const std::string& title) {
    m_title = title;
}
void bookshop::Book::setAuthor(const std::string& author) {
    m_author = author;
}
void bookshop::Book::setPublisher(const std::string& publisher) {
    m_publisher = publisher;
}
void bookshop::Book::setGenre(const std::string& genre) {
    m_genre = genre;
}
void bookshop::Book::setPrice(size_t price) {
    m_price = price;
}
void bookshop::Book::setReleaseYear(int release_year) {
    m_releaseYear = release_year;
}
void bookshop::Book::initID() {
    m_id = Book::s_nextFreeID;
    Book::s_nextFreeID++;
}

bookshop::Book bookshop::createBook(const std::string& title, const std::string& author, const std::string& publisher,
                          const std::string& genre, size_t price, int release_year) {

        Book newBook;
        
        if (title.empty())
            return newBook;
        
        if (release_year < EARLIEST_RELEASE_YEAR || release_year > CUR_YEAR)
            return newBook;

        newBook.setAuthor(author);
        newBook.setGenre(genre);
        newBook.setPrice(price);
        newBook.setPublisher(publisher);
        newBook.setReleaseYear(release_year);
        newBook.setTitle(title);

        newBook.initID();

        return newBook;
    }