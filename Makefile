SRCS		= main.cpp tester_vector.cpp tester_stack.cpp tester_map.cpp

OBJS		= ${SRCS:.cpp=.o}

HEADERS		= vector.hpp stack.hpp vector_iterator.hpp utils.hpp utils.hpp reverse_iterator.hpp RedBlackTree.hpp node_tree.hpp map.hpp ft_is_integral.hpp bidirectional_iterator.hpp tester_headers.hpp

NAME		= ft_container

CPP			= clang++

RM			= rm -rf

CPPFLAGS	= -Wall -Wextra -Werror -std=c++98 -Wshadow -Wno-shadow

all:		${NAME}

%.o:		%.cpp ${HEADER}
			${CPP} ${CPPFLAGS} -I ./ -c $< -o $@

${NAME}:	${OBJS} ${HEADER}
			${CPP} ${CPPFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re