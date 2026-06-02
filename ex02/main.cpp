#include "Base.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

Base *generate(void);
void identify(Base *p);
void identify(Base &p);

int main()
{
    std::srand(std::time(NULL));

    //several tests
    for (int i = 0; i < 10; i++)
    {
        std::cout << "------------------" << std::endl;

        //generate random object
        Base *ptr = generate();

        std::cout << "Pointer identify: ";
        identify(ptr);

        std::cout << "Reference identify: ";
        identify(*ptr);

        delete ptr;
    }

    return (0);
}