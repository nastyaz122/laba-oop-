#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Car {
public:
	std::string _brand;
	std::string _model;

	Car(const std::string& brand, const std::string& model) :
		_brand(brand), _model(model) {}
};

int main() {

	setlocale(LC_ALL, "ru");

	std::string path = "cars.txt";
	std::ifstream file;
	file.open(path);
	if (!file.is_open()) {
		std::cout << "error" << std::endl;
	}
	else
	{
		std::cout << "open!" << std::endl;
	}
	std::vector <Car> cars;

	std::string _brand;
	std::string _model;

	while (file >> _brand >> _model) {
		cars.push_back(Car(_brand, _model));
	}

	for (int i = 0; i < cars.size(); i++) {
		std::cout << "Марка: " << cars[i]._brand << ", Модель: " << cars[i]._model << std::endl;
	}
	file.close();
	return 0;
}
