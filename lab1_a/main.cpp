#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <vector>
#include <string>

struct Leaks {
	~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;


enum class Type {
	Art, Tech
};

void Print();

class Book
{
	friend void Print();
public:
	Book(const std::string& avtor, const std::string& title, Type bookType) :
		_avtor(avtor), _title(title), _bookType(bookType)
	{}
	Type GetType() const
	{
		return _bookType;
	}

private:
	const std::string _avtor;
	const std::string _title;
	const Type _bookType;
};

class Library
{

public:
	bool addbook(const std::string& avtor, const std::string& title, Type bookType)
	{
		if (avtor.empty() || title.empty()) {

			std::cout << "dannye ne correctny" << std::endl;
			return false;
		}
		else {
			b.emplace_back(title, avtor, bookType);
		}
	}
	void PrintSwitch() {
		int art = 0;
		int tech = 0;
		for (Book i : b) {
			switch (i.GetType())
			{
			case Type::Art:
				++art;
				break;
			default:
				++tech;
				break;
			}
		}
		std::cout << "Art: " << art << std::endl;
		std::cout << "Tech: " << tech << std::endl;
	}
	void PrintForeach() {
		int art = 0;
		int tech = 0;
		for (Book i : b)
		{
			if (i.GetType() == Type::Art)
			{
				++art;
			}
			else
			{
				++tech;
			}
		}
		std::cout << "Art: " << art << std::endl;
		std::cout << "Tech: " << tech << std::endl;
	}
private:
	std::vector <Book> b;
};


int main()
{
	Library library;

	library.addbook("Pushkin", "Ruslan and Ludmila", Type::Art);
	library.addbook("Klaus Iglberger", "C++ Software Design", Type::Tech);
	library.addbook("Rainer Grimm", "C++ Core Guidelines", Type::Tech);

	library.PrintSwitch();

	std::cout << "---------------------" << std::endl;

	library.PrintForeach();

	return 0;
}
