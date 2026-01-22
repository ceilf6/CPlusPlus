#include <iostream>

#include "container.h"
#include "vector.h"

using namespace std;
using namespace TD;

class A {
private:
    int a;
    int b;

public:
    A() : a(1), b(2) { }
    A(const int & a, const int & b) : a(a), b(b) { }
};


int main()
{

    // IMPOSSIBLE !! Car Container est virtuel pure !
    //Container ctr;

    Vector<int> vectorInt(100, 0); // Vecteur de 100 integers = 0
    Vector<float> vectorFloat(100, 1.0); // Vecteur de 100 integers = 1.0
    Vector<A> vectorA(100, A()); // Vecteur de 100 A
    Vector<A> vectorA2(100, A(3, 4)); // Vecteur de 100 A (a=3, b=4)



    return 0;
}