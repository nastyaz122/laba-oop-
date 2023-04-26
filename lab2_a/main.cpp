#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

class Class1 {
public:
    Class1() {
        std::cout << "Constructor Class1" << std::endl;
    }
    Class1(const Class1& other) {
        std::cout << "Copy Constructor Class1" << std::endl;
    }
    virtual ~Class1() {
        std::cout << "Destuctor Class1" << std::endl;
    }
};

class Class2 :public Class1 {
public:
    Class2() {
        std::cout << "Constructor Class2" << std::endl;
    }
    Class2(const Class2& other) :Class1(other) {
        std::cout << "Copy Constructor Class2" << std::endl;
    }
   virtual ~Class2() {
        std::cout << "Destuctor Class2" << std::endl;
    }
};

void my_copy(std::vector<Class1*>& Object, std::vector<Class1*>& DataBase) {
    for (const auto obj : Object) {
        Class2* derived = dynamic_cast<Class2*>(obj);
        if (derived)
            DataBase.push_back(new Class2(*derived));
        else
            DataBase.push_back(new Class1(*derived));
    }
}
int main() {

    std::vector<Class1*> Object;
    std::vector<Class1*> DataBase;
    Class1 obj1;
    Class1 obj2;
    std::cout << "Class1 create" << std::endl;
    Class2 obj3;
    Class2 obj4;
    std::cout << "Class2 create" << std::endl;
    Object.push_back(&obj1);
    Object.push_back(&obj2);
    Object.push_back(&obj3);
    Object.push_back(&obj4);
    my_copy(Object, DataBase);
        for (const auto obj : DataBase) {
            std::cout << typeid(*obj).name() << std::endl;
            delete obj;
        }
        return 0;
    }
