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

//main_statical_conversion_procedure
void ScalarConverter::convert(const std::string &literal)
{
    bool isSpecial = false; //nan or inf
    double d_val = 0; //base value

    if (literal == "nan" || literal == "nanf" ||
        literal == "inf" || literal == "+inf" || literal == "-inf" ||
        literal == "inff" || literal == "+inff" || literal == "-inff")
    {
        //flag to bypass strict numeric parsing
        isSpecial = true;
        if (literal == "nan" || literal == "nanf")
        {
            d_val = std::numeric_limits<double>::quiet_NaN();
        }
        else if (literal == "-inf" || literal == "-inff")
        {
            d_val = -std::numeric_limits<double>::infinity();
        }
        else
        {
            d_val = std::numeric_limits<double>::infinity();
        }
    }

    //regular nums or individual chars
    if (!isSpecial)
    {
        //unquoted single chars
        if (literal.length() == 1 && !std::isdigit(literal[0]))
        {
            d_val = static_cast<double>(literal[0]);
        }

        //char inside ""
        else if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
        {
            d_val = static_cast<double>(literal[1]);
        }
        //floating point or decimal integers
        else
        {
            //reset errno before parsing to cathch erange
            errno = 0;

            //pointer to locate parsing stoppage point
            char *endptr = NULL;

            //invoke standard parsing utility
            d_val = std::strtod(literal.c_str(), &endptr);

            //catch overflow of double
            if (errno == ERANGE)
            {
                std::cout << "char: impossible" << std::endl;
                std::cout << "int: impossible" << std::endl;
                std::cout << "float: impossible" << std::endl;
                std::cout << "double: impossible" << std::endl;
                return;
            }

            //detect trailing chars or unparsed fractions
            if (endptr == literal.c_str() || *endptr != '\0')
            {
                //check for floar suffix (42f not acceptable without dot)
                //unrecognized char literal formation
                if (!(endptr && *endptr == 'f' && *(endptr + 1) == '\0' &&
                endptr != literal.c_str() && literal.find('.') != std::string::npos))
                {
                    std::cout << "char: impossible" << std::endl;
                    std::cout << "int: impossible" << std::endl;
                    std::cout << "float: impossible" << std::endl;
                    std::cout << "double: impossible" << std::endl;
                    return;
                }
            }
        }
    }

    std::cout << "char: ";

    //make new Nan
    bool isNan = (d_val != d_val);
    bool isInf = (d_val == std::numeric_limits<double>::infinity() || d_val == -std::numeric_limits<double>::infinity());

    //check for stuff that cannot be represented and car extremes
    if (isSpecial || isNan || isInf ||
        d_val < std::numeric_limits<signed char>::min() || d_val > std::numeric_limits<signed char>::max())
    {
        std::cout << "impossible" << std::endl;
    }
    //valid string
    else
    {
        char c = static_cast<char>(d_val);
        //isprint requires unsigned char or EOF
        if (std::isprint(static_cast<unsigned char>(c)))
        {
            std::cout << "'" << c << "'" << std::endl;
        }
        else
        {
            std::cout << "Non displayable" << std::endl;
        }
    }

    std::cout << "int: ";
    if (isSpecial || isNan || isInf ||
        d_val < std::numeric_limits<int>::min() || d_val > std::numeric_limits<int>::max())
    {
        std::cout << "impossible" << std::endl;
    }

    //valid int
    else
    {
        int i = static_cast<int>(d_val);
        std::cout << i << std::endl;
    }

    std::cout << "float: ";
    //separate handling for secial float values
    if (isSpecial)
    {
        if (isNan)
        {
            std::cout << "nanf" << std::endl;
        }
        //negative inf condition
        else if (d_val < 0)
        {
            std::cout << "-inff" << std::endl;
        }
        else //positive_inf_condition
        {
            std::cout << "+inff" << std::endl;
        }
    }
    //standard floating point convertion
    else
    {
        if (d_val > std::numeric_limits<float>::max() || d_val < -std::numeric_limits<float>::max())
        {
            std::cout << "impossible" << std::endl;
        }
        //process with ranges
        else
        {
            float f = static_cast<float>(d_val);
            //check absence of fractional remainder
            if (std::floor(f) == f)
            {
                //one decimal place
                std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
                std::cout.unsetf(std::ios::floatfield);
                std::cout.precision(6);
            }
            //has decimal digits
            else
            {
                std::cout << f << "f" << std::endl; //standard float
            }
        }
    }

    std::cout << "double: "; //print_double_prefix
    //separate handling for special double values
    if (isSpecial)
    {
        if (isNan)
        {
            std::cout << "nan" << std::endl;
        }
        //negative inf
        else if (d_val < 0)
        {
            std::cout << "-inf" << std::endl;
        }
        //positive inf
        else
        {
            std::cout << "+inf" << std::endl;
        }
    }
    //standard double precision display
    else
    {
        double d = d_val;

        //check absence of fractional remainder
        if (std::floor(d) == d)
        {
            //format with one decimal place
            std::cout << std::fixed << std::setprecision(1) << d << std::endl;

            //reset stream precision flags to prevent gobals contamination
            std::cout.unsetf(std::ios::floatfield);

            //reset default precision value
            std::cout.precision(6);
        }
        //has decimal digits
        else
        {
            std::cout << d << std::endl;
        }
    }
}
