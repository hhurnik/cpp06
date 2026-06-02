#ifndef BASE_HPP
#define BASE_HPP

//abstract base class for RTTI testing
class Base
{
    public:

        //virtual destructor is REQUIRED, otherwise dynamic_cast will not work correctly
        virtual ~Base();
};

#endif