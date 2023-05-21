#include <string>
#include <iostream>
#include <vector>
#include <list>
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h> 
struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

class A {
public:
    std::string s;

    A() {
        std::cout << "Конструктор по умолчанию класса A" << std::endl;
    }

    A(const char* a) : s(a) {
        std::cout << "Пользовательский конструктор класса A" << std::endl;
        std::cout << s << std::endl;
    }

    A(const A& other) : s(other.s) {
        std::cout << "Конструктор копирования класса A" << std::endl;
    }

    A(A&& other): s(std::move(other.s)) {
        std::cout << "Конструктор перемещения класса A" << std::endl;
    }

    virtual ~A() {
        std::cout << "Деструктор класса A" << std::endl;
        std::cout << typeid(*this).name() << std::endl;
    }
};

class B : public A {
public:
    B() {
        std::cout << "Конструктор класса B" << std::endl;
    }

    B(const char* a) : A(a) {
        std::cout << "Пользовательский конструктор класса B" << std::endl;
        std::cout << a << std::endl;
    }

    B(const B& other) : A(other) {
        std::cout << "Конструктор копирования класса B" << std::endl;
    }

    B(B&& other): A(std::move(other)) {
        std::cout << "Конструктор перемещения класса B" << std::endl;
    }

    ~B() {
        std::cout << "Деструктор класса B" << std::endl;
        std::cout << typeid(*this).name() << std::endl;
    }
};

void del(std::vector<A*>& v) {
    for (int i = 0; i < v.size(); i++)
        delete v[i];
    v.clear(); // Очистить вектор
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::list<A*> l;
    l.push_back(new A("first"));
    l.push_back(new B("second"));

    std::vector<A*> v;
    for (auto it = l.begin(); it != l.end(); ++it) {
        v.push_back(new A(**it)); // Копирование элементов из списка в вектор
    }

    del(v); // Удаление элементов вектора

    for (auto it = l.begin(); it != l.end(); ++it) {
        delete* it; // Удаление элементов списка
    }
    l.clear(); // Очистить список

    return 0;
}
