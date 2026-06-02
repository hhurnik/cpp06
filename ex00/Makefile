NAME = convert

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp \
       ScalarConverter.cpp

OBJS = main.o \
       ScalarConverter.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

main.o: main.cpp ScalarConverter.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

ScalaeConverter.o: ScalarConverter.cpp ScalarConverter.hpp
	$(CXX) $(CXXFLAGS) -c ScalarConverter.cpp -o ScalarConverter.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re