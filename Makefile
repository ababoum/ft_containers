CXX			= @c++

CXXFLAGS	= -Wall -Werror -Wextra -g -std=c++98

NAME 		= ft_containers
NAME_STD	= std_containers
NAME_OFFICIAL = official_containers

SRCS		= main.cpp
SRCS_42		= official_main.cpp

INCL		= vector.hpp \
				map.hpp \
				stack.hpp \
				set.hpp \
				iterators/iterators_traits.hpp \
				iterators/random_access_iterator.hpp \
				iterators/reverse_iterator.hpp \
				pairs/pair.hpp \
				rb_tree/RBT.hpp \
				rb_tree/RBT_set.hpp \
				utils/enable_if.hpp \
				utils/equal.hpp \
				utils/integral_constant.hpp \
				utils/is_integral.hpp \
				utils/lexicographical_compare.hpp

OBJS		= $(SRCS:.cpp=.o)
OBJS_42		= $(SRCS_42:.cpp=.o)

all:		$(NAME)

$(NAME):	 $(INCL) $(SRCS)
			$(CXX) $(CXXFLAGS) $(SRCS) -DFT -o $(NAME)
			@echo "\033[1;32m\e[1m $(NAME)\e[0m\033[32m executable is compiled and ready.\e[0m"

std:	$(NAME_STD)

$(NAME_STD): $(SRCS)
			$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME_STD)
			@echo "\033[1;32m\e[1m $(NAME_STD)\e[0m\033[32m executable is compiled and ready.\e[0m"

official:	$(NAME_OFFICIAL)

$(NAME_OFFICIAL): $(SRCS_42)
			$(CXX) $(CXXFLAGS) $(SRCS_42) -o $(NAME_OFFICIAL)
			@echo "\033[1;32m\e[1m $(NAME_OFFICIAL)\e[0m\033[32m executable is compiled and ready.\e[0m"

diff:
			time ./$(NAME) > ft.out
			time ./$(NAME_STD) > std.out
			diff ft.out std.out

clean:		
			@rm -f $(OBJS) $(OBJS_42)
			@echo "\033[1;36m .o files successfully deleted.\e[0m"

fclean: 	clean
			@rm -f $(NAME) $(NAME_STD) $(NAME_OFFICIAL)
			@echo "\033[1;36m $(NAME) executable successfully deleted.\e[0m"

re: 		fclean ${NAME}

.PHONY: clean fclean all re