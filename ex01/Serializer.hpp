#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include "Data.hpp"

class Serializer
{
    //private to prevent initialising, cloning, copyinr, deletion of instances
    private:
        Serializer();
        Serializer(const Serializer &src);
        Serializer &operator=(const Serializer &src);
        ~Serializer();

    public:
        static uintptr_t serialize(Data* ptr); //convert pointer to integer
        static Data* deserialize(uintptr_t raw); //convert integer back to pointer
};

#endif