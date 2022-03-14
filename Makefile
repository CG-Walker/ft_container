CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ft_container
SRC_STACK = tester_stack.cpp

all: $(NAME)

$(NAME): $(SRC_STACK)
	$(CPP) $(CPPFLAGS) $^ -o $@
	
STACK : $(SRC_STACK)
		$(CPP) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all