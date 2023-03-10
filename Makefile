NAME = ircserv
SRC = main.cpp\
	src/channel/Channel.cpp\
	src/command/ACommand.cpp\
	src/command/CommandExecuter.cpp\
	src/server/Server.cpp\
	src/user/AUser.cpp\
	src/user/NormalUser.cpp
CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
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