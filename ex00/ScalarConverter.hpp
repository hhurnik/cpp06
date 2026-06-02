#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <cmath>

class ScalarConverter 
{
    private:
        //orthodox canonical form constructors made private to prevent instantiation
        ScalarConverter();
        ScalarConverter(const ScalarConverter &src);
        ScalarConverter &operator=(const ScalarConverter &src);
        ~ScalarConverter();

    public:
        static void convert(const std::string &literal);
};

#endif