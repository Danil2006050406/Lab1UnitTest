#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <functional>

// Включаємо заголовки класів
#include "../Book.h"
#include "../User.h"
#include "../Loan.h"
#include "../Library.h"
#include "../LibraryUtils.h"

// Допоміжні функції для роботи з часом
static time_t days_from_now(int days) {
    return time(nullptr) + (time_t)days * 24 * 60 * 60;
}

static time_t days_ago(int days) {
    return time(nullptr) - (time_t)days * 24 * 60 * 60;
}

// =================================================================
// 1. Book and EBook Tests
// =================================================================

// 1) Book availability: checkout/checkin toggles isAvailable
TEST(BookTest, AvailabilityAndToggle) {
    Book b("AA", "Auth", "ISBN-A", 2000, 1);
    EXPECT_TRUE(b.isAvailable());
    EXPECT_TRUE(b.checkout());
    EXPECT_FALSE(b.isAvailable());
    b.checkin();
    EXPECT_TRUE(b.isAvailable());
}

// 2) Book::matchesTitle should be case-insensitive and substring-based
TEST(BookTest, TitleMatching) {
    Book b("The Lord Of The Rings", "J.R.R. Tolkien", "1", 1954, 4);
    EXPECT_TRUE(b.matchesTitle("lord"));
    EXPECT_TRUE(b.matchesTitle("RINGS"));
    EXPECT_FALSE(b.matchesTitle("hobbit"));
}

// 3) Book::isOldEdition with threshold
TEST(BookTest, OldEditionCheck) {
    Book b("X", "Y", "2", 1995, 1);
    EXPECT_TRUE(b.isOldEdition(2000));
    EXPECT_FALSE(b.isOldEdition(1990));
}

// 4) EBook download info + availability semantics
TEST(EBookTest, BasicFunctionality) {
    EBook eb("E", "A", "E-1", 2020, "https://cdn/ebook", 12.5);
    EXPECT_TRUE(eb.isAvailable());
    eb.getDownloadInfo(); 
    EXPECT_TRUE(eb.checkout());
    EXPECT_FALSE(eb.isAvailable());
}

// =================================================================
// 2. Reader Tests
// =================================================================

// 5) Reader can't borrow same book twice
TEST(ReaderTest, BorrowDuplicatePrevention) {
    Reader r("R1","U1","r1@mail");
    EXPECT_TRUE(r.borrow("I-1"));
    EXPECT_FALSE(r.borrow("I-1"));
}

// 6) Reader returnBook works only for borrowed items
TEST(ReaderTest, ReturnBookSemantics) {
    Reader r("R2","U2","r2@mail");
    EXPECT_FALSE(r.returnBook("I-2"));
    EXPECT_TRUE(r.borrow("I-2"));
    EXPECT_TRUE(r.returnBook("I-2"));
    EXPECT_FALSE(r.returnBook("I-2")); // now it's gone
}

// =================================================================
// 3. Library Tests
// =================================================================

// 7) Library add/find book/reader
TEST(LibraryTest, AddAndFindEntities) {
    Library lib;
    lib.addBook(Book("B1","A","I-3",2001,2));
    lib.addReader(Reader("R3","U3","r3@mail"));
    EXPECT_NE(lib.findBookByISBN("I-3"), nullptr);
    EXPECT_NE(lib.findReaderById("U3"), nullptr);
    EXPECT_EQ(lib.findBookByISBN("NO"), nullptr);
    EXPECT_EQ(lib.findReaderById("NO"), nullptr);
}

// 8) Library::issueBook success path decrements copies
TEST(LibraryTest, IssueBookSuccess) {
    Library lib;
    lib.addBook(Book("B2","A","I-4",2002,1));
    lib.addReader(Reader("R4","U4","r4@mail"));
    EXPECT_TRUE(lib.issueBook("I-4","U4"));
    Book* b = lib.findBookByISBN("I-4");
    ASSERT_NE(b, nullptr);
    EXPECT_FALSE(b->isAvailable());
}

// 9) Library::issueBook returns false if book/reader missing
TEST(LibraryTest, IssueBookMissingEntities) {
    Library lib;
    lib.addBook(Book("B3","A","I-5",2003,1));
    // Reader missing
    EXPECT_FALSE(lib.issueBook("I-5","U5")); 
    lib.addReader(Reader("R5","U5","r5@mail"));
    // Book missing
    EXPECT_FALSE(lib.issueBook("NOISBN","U5"));
}

// 10) Library::issueBook not available or duplicate borrow
TEST(LibraryTest, IssueBookNotAvailableOrDuplicate) {
    Library lib;
    lib.addBook(Book("B4","A","I-6",2004,1)); // Only 1 copy
    lib.addReader(Reader("R6","U6","r6@mail"));
    
    EXPECT_TRUE(lib.issueBook("I-6","U6")); 
    
    // Книга недоступна
    EXPECT_FALSE(lib.issueBook("I-6","U6b")); 

    lib.addBook(Book("B4b","A","I-7",2005,1));
    lib.addReader(Reader("R6b","U6b","r6b@mail"));
    EXPECT_TRUE(lib.issueBook("I-7","U6b"));
    
    // Читач вже має книгу (дублікат)
    EXPECT_FALSE(lib.issueBook("I-7","U6b")); 
}

// 11) Library::returnBook success increments copies
TEST(LibraryTest, ReturnBookSuccess) {
    Library lib;
    lib.addBook(Book("B5","A","I-8",2006,1));
    lib.addReader(Reader("R7","U7","r7@mail"));
    EXPECT_TRUE(lib.issueBook("I-8","U7"));
    EXPECT_TRUE(lib.returnBook("I-8","U7"));
    Book* b = lib.findBookByISBN("I-8");
    ASSERT_NE(b, nullptr);
    EXPECT_TRUE(b->isAvailable());
}

// 12) Library::returnBook fails if reader doesn't have the book
TEST(LibraryTest, ReturnBookReaderDoesNotHave) {
    Library lib;
    lib.addBook(Book("B6","A","I-9",2007,1));
    lib.addReader(Reader("R8","U8","r8@mail"));
    EXPECT_FALSE(lib.returnBook("I-9","U8")); 
}

// =================================================================
// 4. Loan and Utils Tests
// =================================================================

// 13) Loan daysLeft positive for future due date
TEST(LoanTest, DaysLeftFuture) {
    Loan L("L1","I-10","U9", time(nullptr), days_from_now(3));
    int dl = L.daysLeft();
    EXPECT_GE(dl, 1); 
    EXPECT_FALSE(L.isOverdue());
}

// 14) Loan overdue and daysLeft=0 for past due
TEST(LoanTest, OverdueAndReturned) {
    Loan L("L2","I-11","U10", days_ago(7), days_ago(2));
    EXPECT_TRUE(L.isOverdue());
    EXPECT_EQ(L.daysLeft(), 0);
    L.markReturned();
    EXPECT_TRUE(L.isReturned());
    EXPECT_FALSE(L.isOverdue()); 
}

// 15) LibraryUtils::issueBookToReader orchestration + duplicate prevention
TEST(LibraryUtilsTest, IssueBookToReader) {
    Book b("B7","A","I-12",2008,1);
    Reader r("R9","U11","r9@mail");
    EXPECT_TRUE(issueBookToReader(b, r));  
    EXPECT_FALSE(issueBookToReader(b, r)); 
    EXPECT_FALSE(b.isAvailable());
}