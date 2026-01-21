#include <iostream>
using namespace std;

class Person
{
public:
    void live_a_day()
    {
        get_up();
        work();
        nap();
        work();
        diner();
        entertainment();
        sleep();
    }

    void get_up() { cout << "Get Up" << endl; }
    void nap() { cout << "Nap" << endl; }
    void diner() { cout << "Diner" << endl; }
    void sleep() { cout << "Sleep" << endl; };

    virtual void entertainment() = 0;
    virtual void work() = 0;
};

class Student : public Person
{
    void work()
    {
        cout << "Study" << endl;
    }

    void entertainment() { cout << "Play games" << endl; }
};

class Programmer : public Person
{
    void work()
    {
        cout << "Write Code" << endl;
    }
    void entertainment() { cout << "Watch movies" << endl; }
};

int main()
{
    Programmer s;
    s.live_a_day();
    return 0;
}