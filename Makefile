CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ft_container
SRC_STACK = tester_stack.cpp
SRC_VECTOR = tester_vector.cpp

all: $(NAME)

$(NAME): $(SRC_STACK)
	$(CPP) $(CPPFLAGS) $^ -o $@
	
stack : $(SRC_STACK)
		$(CPP) $(CPPFLAGS) $^ -o $@
		./stack
vector : $(SRC_VECTOR)
		$(CPP) $(CPPFLAGS) $^ -o $@
		./vector

clean:
	rm -f $(NAME) stack vector

fclean: clean

re: fclean all