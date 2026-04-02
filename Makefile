NAME = matrix
CXX = c++
FLAGS= -Wall -Wextra -Werror -std=c++17

RM = rm
RM_FLAGS = -rf

SRCS_DIR = ./src
INCLUDE = -I include

SRCS = $(SRCS_DIR)/main.cpp

OBJS = ${SRCS:.cpp=.o}

$(NAME): $(OBJS)
		$(CXX) $(FLAGS) $(INCLUDE) $^ -o $@

%.o: %.cpp
	$(CXX) $(FLAGS) $(INCLUDE) -c $< -o $@ 

all: $(NAME)

clean:
	$(RM) $(RM_FLAGS) $(OBJS)

fclean: clean
	$(RM) $(RM_FLAGS) $(NAME)

re: fclean all	
.PHONY: all re clean fclean 
