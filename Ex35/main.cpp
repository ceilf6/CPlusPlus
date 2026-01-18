#include <iostream>
#include "vector.h"

using namespace TD;

int main()
{
    try
    {
        Vector<int> v(3, 5);
        v.push_back(10);
        v.push_back(20);

        for (size_t i = 0; i < v.size(); ++i)
            std::cout << v[i] << " ";
        std::cout << std::endl;

        v.pop_back();
        std::cout << "Back: " << v.back() << std::endl;

        v.clear();
        std::cout << "Empty: " << v.empty() << std::endl;
    }
    catch (const ContainerException &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}