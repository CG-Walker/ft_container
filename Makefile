CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ft_container
SRC_STACK = tester_stack.cpp

all: $(NAME)

$(NAME): $(SRC_STACK)
	$(CPP) $(CPPFLAGS) $^ -o $@
	
stack : $(SRC_STACK)
		$(CPP) $(CPPFLAGS) $^ -o $@
		./stack

clean:
	rm -f $(NAME) stack

fclean: clean

re: fclean all