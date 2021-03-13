#include <string>
#include <iostream>
#include <vector>

// PPP ch 9 exercises

using namespace std;
struct Date {
	public:
	int year;
	int month;
	int day;
};


class Book {
	public:
		Book(string i, string t, string a) :isbn(i), title(t), author(a) {}
		Book() {}
		void check_out() {
			checked_out = true;
		}
		void check_in() {
			checked_out = false;
		}
		void set_isbn(string s) {
			//check vs regex or something
		}
		bool operator==( const Book* b) {
			return this->isbn == b->isbn;
		}
		bool operator!=( const Book* b) {
			return this->isbn != b->isbn;
		}
	//private:
		string isbn;
		string title;
		string author;
		Date copyright_date;
		bool checked_out;
		enum Genre { fiction, nonfiction, periodical, biography, children };
		enum Genre genre;
};
class Patron {
	public:
		void setfee(int fee) {fee_owed = fee;if (fee_owed > 0) owes_fee = true;}
	string name;
	int card_number;
	double fee_owed;
	bool owes_fee;
};
ostream& operator<<(ostream& os, const Book& b) {
	return os << b.isbn << " " << b.author << " " << b.title << b.genre << endl;
}
class Library {
	public:
		void add_book(Book b) { books.push_back(b);}
		void add_patron(Patron p) { patrons.push_back(p);}
		void check_out(Patron p, Book b) {
			Transaction t;
			t.book = b;
			t.patron = p;
			Date d;
			t.date = d;
			transactions.push_back(t);
		}
		void list_books() {
			for(auto a = books.begin();a != books.end();a++) {
				cout << *a;
			}
		}
		vector<Book> books;
		vector<Patron> patrons;
		struct Transaction {
			Book book;
			Patron patron;
			Date date;
		};
		vector<Transaction> transactions;


	
};
int main() {
	Book b;
	b.isbn = "1-2-3-4";
	b.title = "Moby Dick";
	b.author = "Herman Melville";
	b.genre = Book::Genre::fiction;
	cout << b << endl;

	Book c("2-2-2-2", "War and Peace", "that guy");
	c.genre = Book::Genre::nonfiction;
	cout << c;

	Library lib;
	Patron bob;
	lib.add_book(b);
	lib.list_books();








}
