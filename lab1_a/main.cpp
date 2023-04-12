#include <iostream>
#include <vector>
#include <string>

enum class Type {
	Art, Tech
};

class Book
{
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

			std::cout << "The data is not correct" << std::endl;
			return false;
		}
		else {
			book.emplace_back(title, avtor, bookType);
			return true;
		}
	}
	void PrintSwitch() {
		int ArtCount = 0;
		int TechCount = 0;
		for (Book i : book) {
			switch (i.GetType())
			{
			case Type::Art:
				++ArtCount;
				break;
			default:
				++TechCount;
				break;
			}
		}
		std::cout << "Art: " << ArtCount << std::endl;
		std::cout << "Tech: " << TechCount << std::endl;
	}
	void PrintForeach() {
		int ArtCount = 0;
		int TechCount = 0;
		for (Book i : book)
		{
			if (i.GetType() == Type::Art)
			{
				++ArtCount;
			}
			else if (i.GetType() == Type::Tech)
			{
				++TechCount;
			}
		}
		std::cout << "Art: " << ArtCount << std::endl;
		std::cout << "Tech: " << TechCount << std::endl;
	}
private:
	std::vector <Book> book;
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

