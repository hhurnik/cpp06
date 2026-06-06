#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <cmath>

enum LiteralType
{
    CHAR_TYPE,
    INT_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    PSEUDO_TYPE,
    INVALID_TYPE
};

class ScalarConverter 
{
    private:
        //orthodox canonical form constructors made private to prevent instantiation
        ScalarConverter();
        ScalarConverter(const ScalarConverter &src);
        ScalarConverter &operator=(const ScalarConverter &src);
        ~ScalarConverter();

        static LiteralType detectType(const std::string &literal);

        static bool isCharLiteral(const std::string &literal);
        static bool isIntegerLiteral(const std::string &literal);
        static bool isFloatLiteral(const std::string &literal);
        static bool isDoubleLiteral(const std::string &literal);
        static bool isPseudoLiteral(const std::string &literal);

    public:
        static void convert(const std::string &literal);
};

#endif