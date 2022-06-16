NAME		= cerebus_ft_containers

SRC			= main.cpp tester_vector.cpp tester_stack.cpp tester_map.cpp

OBJS		= ${SRC:.cpp=.o}

HEADS		= vector.hpp vector_iterator.hpp utils.hpp reverse_iterator.hpp stack.hpp \
				RedBlackTree.hpp node_tree.hpp map.hpp ft_is_integral.hpp bidirectional_iterator.hpp tester_headers.hpp

CPP			= clang++

RM			= rm -rf

FLAGS		= -Wall -Wextra -Werror -std=c++98 -Wshadow -Wno-shadow

all:		${NAME}

%.o:		%.cpp ${HEADS}
			${CPP} ${FLAGS} -I ./ -c $< -o $@

${NAME}:	${OBJS} ${HEADS}
			${CPP} ${FLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re