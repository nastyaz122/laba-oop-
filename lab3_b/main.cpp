#include <iostream> 
#include <vector> 

class Base {
protected:
    Base() {}
public:
    virtual ~Base() {}
    template<typename T>
    friend void add_to_vector(std::vector<Base*>& v); 
};

class Heir : public Base {
protected:
    Heir() = default;
public:
    virtual ~Heir() {}
    template<typename T>
    friend void add_to_vector(std::vector<Base*>& v);
};

template<typename T>
void add_to_vector(std::vector<Base*>& v) { 
    v.push_back(new T());
}

int main() {
    std::vector<Base*> Bases;
    add_to_vector<Base>(Bases);
    add_to_vector<Heir>(Bases);
    add_to_vector<Base>(Bases);
    add_to_vector<Heir>(Bases);

    for (auto d : Bases) {
        delete d;
    }
    Bases.clear();

    return 0;
}
