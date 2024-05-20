#ifndef BOOK_H_
#define BOOK_H_

#include <string>

namespace bookshop
{
    using BookID = size_t;

    class Book
    {
    public:

        static bool isBookExists(BookID id);

        std::string getTitle() const;
        std::string getAuthor() const;
        std::string getPublisher() const;
        std::string getGenre() const;
        size_t getPrice() const;
        int getReleaseYear() const;
        BookID getId() const;

    protected:

        void setTitle(const std::string& title);
        void setAuthor(const std::string& author);
        void setPublisher(const std::string& publisher);
        void setGenre(const std::string& genre);
        void setPrice(size_t price);
        void setReleaseYear(int release_year);
        void initID();

        friend Book createBook(const std::string& title, const std::string& author, const std::string& publisher,
                               const std::string& genre, size_t price, int release_year);
    private:
        std::string m_title = "", m_author = "", m_publisher = "", m_genre = "";
        int m_releaseYear = 0; // negative numbers mean BC, positive - AD
        size_t m_price = 0;
        BookID m_id = 0;

        static size_t s_nextFreeID;      
    };

    Book createBook(const std::string& title, const std::string& author, const std::string& publisher,
                    const std::string& genre, size_t price, int release_year);
}

#endif  // BOOK_H_