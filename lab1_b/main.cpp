#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Leaks {
	~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

class Car {
private:
	const std::string _model;
public:
	Car(const std::string& model) : _model(model) {}

	virtual ~Car() {}

	const std::string& getModel()
	{
		return _model;
	}
};

class Mercedes : public Car {
public:
	Mercedes(const std::string& model) : Car(model) {}
	virtual ~Mercedes() {
		std::cout << "Mercedes " << getModel() << " " << std::endl;
	}
};

class Honda :public Car {
public:
	Honda(const std::string& model) : Car(model) {}
	virtual ~Honda() {
		std::cout << "Honda" << getModel() << " " << std::endl;
	};
};

class BMW :public Car {
public:
	BMW(const std::string& model) : Car(model) {}
	virtual ~BMW() {
		std::cout << "BMW" << getModel() << " " << std::endl;
	};
};

int main() {

	std::string path = "cars.txt";
	std::ifstream file;
	file.open(path);
	if (!file.is_open()) {
		std::cout << "Error" << std::endl;
	}
	else
	{
		std::cout << "Open!" << std::endl;
	}
	std::vector <Car*> cars;
	std::string _brand;
	std::string _model;

	while (file >> _brand >> _model) {

		if (_brand == "Mercedes")
		{
			cars.push_back(new Mercedes(_model));
		}
		else if (_brand == "BMW")
		{
			cars.push_back(new BMW(_model));
		}
		else if (_brand == "Honda") {
			cars.push_back(new Honda(_model));
		}
	}

	file.close();

	for (auto Car : cars)
	{
		delete Car;
	}

	return 0;
}
