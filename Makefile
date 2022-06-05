NAME = containers

SRC = main.cpp
HEAD = Stack.hpp

OBJS = $(SRC:.cpp=.o)

CXX = clang++
RM = rm -rf

FLAGS = -Wall -Wextra -Werror -std=c++98

%.o: %.cpp	$(HEAD) Makefile
			@$(CXX) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(HEAD)
			$(CXX) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY: 	all run clean fclean re