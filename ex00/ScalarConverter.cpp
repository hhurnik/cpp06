#include "ScalarConverter.hpp"
#include <cerrno>
#include <cctype>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
    (void)src;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &src)
{
    (void)src;
    return *this;
}

ScalarConverter::~ScalarConverter() {}

LiteralType ScalarConverter::detectType(const std::string &literal)
{
    if (isPseudoLiteral(literal))
        return PSEUDO_TYPE;

    if (isCharLiteral(literal))
        return CHAR_TYPE;

    if (isIntegerLiteral(literal))
        return INT_TYPE;

    if (isFloatLiteral(literal))
        return FLOAT_TYPE;

    if (isDoubleLiteral(literal))
        return DOUBLE_TYPE;

    return INVALID_TYPE;
}

bool ScalarConverter::isPseudoLiteral(const std::string &s)
{
    if (s == "nan" || s == "nanf" || s == "+inf" || s == "-inf" || s == "+inff" || s == "-inff")
        return true;
    return false;
}

//both a and 'a'
bool ScalarConverter::isCharLiteral(const std::string &s)
{
    if (s.length() == 1 && !std::isdigit(s[0]))
        return true;

    if (s.length() == 3 && s[0] == '\'' && s[2] == '\'')
        return true;

    return false;
}

//42, -42, +42, 0
bool ScalarConverter::isIntegerLiteral(const std::string &s)
{
    if (s.empty())
        return false;

    size_t i = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;

    if (i == s.length())
        return false;

    while (i < s.length())
    {
        if (!std::isdigit(s[i]))
            return false;

        i++;
    }
    return true;
}

//42.0f, 0.0f, -1.5f OK
//42f, 42.0f, 42.0fabc NOT OKAY
// bool ScalarConverter::isFloatLiteral(const std::string &s)
// {
//     if (s.length() < 3)
//         return false;

//     if (s[s.length() - 1] != 'f')
//         return false;

//     bool dotFound = false;
//     bool digitFound = false;

//     size_t i = 0;

//     if (s[i] == '+' || s[i] == '-')
//         i++;

//     while (i < s.length() - 1)
//     {
//         if (std::isdigit(s[i]))
//         {
//             digitFound = true;
//         }
//         else if (s[i] == '.')
//         {
//             if (dotFound)
//                 return false;

//             dotFound = true;
//         }
//         else
//         {
//             return false;
//         }

//         i++;
//     }

//     if (digitFound && dotFound)
//         return true;
//     return false;
// }

bool ScalarConverter::isFloatLiteral(const std::string &s)
{
    if (s.empty())
        return false;

    if (s[s.length() - 1] != 'f')
        return false;

    size_t i = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;

    bool digitBeforeDot = false;
    bool digitAfterDot = false;
    bool dotFound = false;

    while (i < s.length() - 1)
    {
        if (std::isdigit(s[i]))
        {
            if (!dotFound)
                digitBeforeDot = true;
            else
                digitAfterDot = true;
        }
        else if (s[i] == '.')
        {
            if (dotFound)
                return false;

            dotFound = true;
        }
        else
        {
            return false;
        }

        i++;
    }

    return (digitBeforeDot &&
            dotFound &&
            digitAfterDot);
}

//42.0, 4.2, 0.0, -3.14 OK
//42.0f, 42.0abc, 4..2 NOT OKAY
// bool ScalarConverter::isDoubleLiteral(const std::string &s)
// {
//     bool dotFound = false;
//     bool digitFound = false;

//     size_t i = 0;

//     if (s[i] == '+' || s[i] == '-')
//         i++;

//     while (i < s.length())
//     {
//         if (std::isdigit(s[i]))
//         {
//             digitFound = true;
//         }
//         else if (s[i] == '.')
//         {
//             if (dotFound)
//                 return false;

//             dotFound = true;
//         }
//         else
//         {
//             return false;
//         }

//         i++;
//     }

//     return (digitFound && dotFound);
// }

bool ScalarConverter::isDoubleLiteral(const std::string &s)
{
    if (s.empty())
        return false;

    size_t i = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;

    bool dotFound = false;
    bool digitBeforeDot = false;
    bool digitAfterDot = false;

    while (i < s.length())
    {
        if (std::isdigit(s[i]))
        {
            if (!dotFound)
                digitBeforeDot = true;
            else
                digitAfterDot = true;
        }
        else if (s[i] == '.')
        {
            if (dotFound)
                return false;

            dotFound = true;
        }
        else
        {
            return false;
        }

        i++;
    }

    return (digitBeforeDot && dotFound && digitAfterDot);
}

void ScalarConverter::convert(const std::string &literal)
{
    LiteralType type = detectType(literal);

    if (type == INVALID_TYPE)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    // ============================================================
    // PSEUDO LITERALS
    // ============================================================

    if (type == PSEUDO_TYPE)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;

        if (literal == "nan" || literal == "nanf")
        {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        }
        else if (literal == "-inf" || literal == "-inff")
        {
            std::cout << "float: -inff" << std::endl;
            std::cout << "double: -inf" << std::endl;
        }
        else
        {
            std::cout << "float: +inff" << std::endl;
            std::cout << "double: +inf" << std::endl;
        }

        return;
    }

    // ============================================================
    // CHAR INPUT
    // ============================================================

    if (type == CHAR_TYPE)
    {
        char value;

        // support both: a and 'a'
        if (literal.length() == 1)
            value = literal[0];
        else
            value = literal[1];

        int i = static_cast<int>(value);
        float f = static_cast<float>(value);
        double d = static_cast<double>(value);

        std::cout << "char: '" << value << "'" << std::endl;

        std::cout << "int: " << i << std::endl;

        std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;

        std::cout << "double: " << d << std::endl;

        return;
    }

    // ============================================================
    // INT INPUT
    // ============================================================

    if (type == INT_TYPE)
    {
        errno = 0;

        long value = std::strtol(literal.c_str(), NULL, 10);

        if (errno == ERANGE || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
        {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
            return;
        }

        int i = static_cast<int>(value);
        char c = static_cast<char>(i);
        float f = static_cast<float>(i);
        double d = static_cast<double>(i);

        std::cout << "char: ";

        if (!std::isprint(static_cast<unsigned char>(c)))
            std::cout << "Non displayable" << std::endl;
        else
            std::cout << "'" << c << "'" << std::endl;

        std::cout << "int: " << i << std::endl;
        std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
        std::cout << "double: " << d << std::endl;

        return;
    }

    // ============================================================
    // FLOAT INPUT
    // ============================================================

    if (type == FLOAT_TYPE)
    {
        float value = std::strtof(literal.c_str(), NULL);

        char c = static_cast<char>(value);
        int i = static_cast<int>(value);
        double d = static_cast<double>(value);

        std::cout << "char: ";

        if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max() ||
            std::floor(value) != value)
        {
            std::cout << "impossible" << std::endl;
        }
        else if (!std::isprint(static_cast<unsigned char>(c)))
        {
            std::cout << "Non displayable" << std::endl;
        }
        else
        {
            std::cout << "'" << c << "'" << std::endl;
        }

        std::cout << "int: ";

        if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max() ||
            std::floor(value) != value)
        {
            std::cout << "impossible" << std::endl;
        }
        else
        {
            std::cout << i << std::endl;
        }

        std::cout << "float: " << std::fixed << std::setprecision(1) << value << "f" << std::endl;

        std::cout << "double: " << d << std::endl;

        return;
    }

    // ============================================================
    // DOUBLE INPUT
    // ============================================================

    if (type == DOUBLE_TYPE)
    {
        double value = std::strtod(literal.c_str(), NULL);

        char c = static_cast<char>(value);
        int i = static_cast<int>(value);
        float f = static_cast<float>(value);

        std::cout << "char: ";

        if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max() ||
            std::floor(value) != value)
        {
            std::cout << "impossible" << std::endl;
        }
        else if (!std::isprint(static_cast<unsigned char>(c)))
        {
            std::cout << "Non displayable" << std::endl;
        }
        else
        {
            std::cout << "'" << c << "'" << std::endl;
        }

        std::cout << "int: ";

        if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max() ||
            std::floor(value) != value)
        {
            std::cout << "impossible" << std::endl;
        }
        else
        {
            std::cout << i << std::endl;
        }

        std::cout << "float: ";

        if (value > std::numeric_limits<float>::max() ||
            value < -std::numeric_limits<float>::max())
        {
            std::cout << "impossible" << std::endl;
        }
        else
        {
            std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
        }

        std::cout << "double: " << std::fixed << std::setprecision(1) << value << std::endl;

        return;
    }
}