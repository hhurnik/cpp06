#include "Serializer.hpp"
#include <iostream>

int main()
{
    Data data;

    data.id = 42;
    data.name = "Kasia";

    Data *originalPtr = &data;

    uintptr_t raw = Serializer::serialize(originalPtr);

    Data *restoredPtr = Serializer::deserialize(raw);

    std::cout << "TEST 1: printing hexadecimal representation of original pointer" << std::endl;
    std::cout << "Original pointer : " << originalPtr << std::endl;

    std::cout << "printing decimal integer representation of serialized value" << std::endl;
    std::cout << "Serialized value : " << raw << std::endl;

    std::cout << "printing hexadecimal representation of restored pointer" << std::endl;
    std::cout << "Restored pointer : " << restoredPtr << std::endl;

    if (originalPtr == restoredPtr)
        std::cout << "SUCCESS: pointers are equal" << std::endl;
    else
        std::cout << "FAILURE: pointers are different" << std::endl;

    std::cout << restoredPtr->id << std::endl;
    std::cout << restoredPtr->name << std::endl;

    return 0;
}


/*
Ewaluacja: 
uintptr_t raw = Serializer::serialize(ptr);
Data *newPtr = Serializer::deserialize(raw);
assert(ptr == newPtr);

jesli adresy sa identycxne, xadanie jest wykonane poprawnie
*/