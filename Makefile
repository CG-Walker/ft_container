CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ft_container
SRC_STACK = Testers/tester_stack.cpp
SRC_VECTOR = Testers/tester_vector.cpp
SRC_MAP = Testers/tester_map.cpp

all: 			$(NAME)

$(NAME):		
				$(CPP) $(CPPFLAGS) $^ -o $@
				./ft_container

stack_exec :	$(SRC_STACK)
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

map_exec :		$(SRC_MAP) 
				@$(CPP) $(CPPFLAGS) $^ -o $@
				@./map_exec
map :	
				@rm -rf map_exec
				@make map_exec

clean:
				rm -f $(NAME) stack_exec vector_exec

fclean: 		clean

re: 			fclean all