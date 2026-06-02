NAME = serializer

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp \
       Serializer.cpp

OBJS = main.o \
       Serializer.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

main.o: main.cpp Serializer.hpp Data.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Serializer.o: Serializer.cpp Serializer.hpp Data.hpp
	$(CXX) $(CXXFLAGS) -c Serializer.cpp -o Serializer.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re