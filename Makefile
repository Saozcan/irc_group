NAME = ircserv
SRC_DIR = src
OBJ_DIR = Object
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ_FILES)
		$(CC) $(CPPFLAGS) $^ -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
		mkdir -p $(@D)
		$(CC) $(CPPFLAGS) -c $< -o $@

clean :
		$(RM) $(OBJ_DIR)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
