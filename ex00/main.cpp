#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
    // Check if exactly one argument was provided
    if (argc != 2)
    {
        std::cout << "Usage: ./convert <literal>" << std::endl;
        return (1);
    }

    // Call the static conversion method
    ScalarConverter::convert(argv[1]);

    return (0);
}