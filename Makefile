CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ft_container
SRC_STACK = tester_stack.cpp
SRC_VECTOR = tester_vector.cpp

all: $(NAME)

$(NAME): $(SRC_STACK)
	$(CPP) $(CPPFLAGS) $^ -o $@

stack_exec :$(SRC_STACK)
			@$(CPP) $(CPPFLAGS) $^ -o $@
			@./stack_exec

stack : 
		@rm -rf stack_exec
		@make stack_exec

vector_exec :	$(SRC_VECTOR) 
				@$(CPP) $(CPPFLAGS) $^ -o $@
				@./vector_exec
vector : 
		@rm -f vector_exec
		@make vector_exec

clean:
	rm -f $(NAME) stack_exec vector_exec

fclean: clean

re: fclean all