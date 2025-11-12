#include "PersonManager.hpp"

int main()
{
    PersonManager pm;

    pm.emplace("Alice", 20);
    pm.emplace("Bob", 25);
    pm.add(Person("Bobby", 100));

    std::cout << "== People List ==" << std::endl;
    pm.print();

    std::cout << "\n== After reset ==" << std::endl;
    pm.clear();
    pm.print();

    return 0;
}