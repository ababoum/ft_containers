CXX			= @c++

CXXFLAGS	= -Wall -Werror -Wextra -g -std=c++98

NAME 		= test_containers

SRCS		= main.cpp

INCL		= vector.hpp \
				map.hpp \
				stack.hpp \
				set.hpp \
				iterators/iterators_traits.hpp \
				iterators/random_access_iterator.hpp \
				iterators/reverse_iterator.hpp \
				pairs/pair.hpp \
				rb_tree/RBT.hpp \
				utils/enable_if.hpp \
				utils/equal.hpp \
				utils/integral_constant.hpp \
				utils/is_integral.hpp \
				utils/lexicographical_compare.hpp

OBJS		= $(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS) $(INCL)
			$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)
			@echo "\033[1;32m\e[1m $(NAME)\e[0m\033[32m executable is compiled and ready.\e[0m"

clean:		
			@rm -f $(OBJS)
			@echo "\033[1;36m .o files successfully deleted.\e[0m"

fclean: 	clean
			@rm -f $(NAME)
			@echo "\033[1;36m $(NAME) executable successfully deleted.\e[0m"

re: 		fclean ${NAME}

.PHONY: clean fclean all re