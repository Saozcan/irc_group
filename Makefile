NAME = fixed
SRC = main.cpp\
	../Channel.cpp\
	../ACommand.hpp\
	../CommandExecuter.cpp\
	../Server.cpp\
	../AUser.cpp\
	../NormalUser.cpp
CC = c++
CPPFLAGS = -Wall -Wextra  -std=c++98
RM = rm -rf
OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CPPFLAGS) $(SRC) -o $(NAME)

clean :
		$(RM) $(OBJ)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re