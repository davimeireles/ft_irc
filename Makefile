#	====================		Directories		====================
FOLDER = sources
_SUBFOLDERS = Server User Utils Commands
HEADERS = includes
OBJECTS_DIRECTORY = objects
VPATH = $(FOLDER) $(addprefix $(FOLDER)/, $(_SUBFOLDERS))

#	====================		Files      		====================

NAME = ircserv

FILES = main.cpp \
		helper.cpp CommandHandler.cpp \
		Server.cpp Channel.cpp Command.cpp \
		Client.cpp \
		Invite.cpp Join.cpp Kick.cpp Mode.cpp Nick.cpp \
		Part.cpp Pass.cpp Privmsg.cpp Quit.cpp Topic.cpp \
		User.cpp Authenticate.cpp Ping.cpp Who.cpp \

OBJECTS = $(addprefix $(OBJECTS_DIRECTORY)/, $(FILES:%.cpp=%.o))

#	====================		Flags      		====================

COMPILER = c++

I = -I $(HEADERS)

FLAGS = -Wall -Wextra -Werror -g -std=c++98

WBLOCK = --no-print-directory

RM = rm -rf

#	====================		Colors     		====================

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
MAGENTA = \033[0;35m
CYAN = \033[0;36m

B_RED = \033[1;31m
B_GREEN = \033[1;32m
B_BLUE = \033[1;34m
L_BLUE = \033[1;94m
B_YELLOW = \033[1;33m
B_MAGENTA = \033[1;35m
B_CYAN = \033[1;36m

RESET = \033[0m

#	====================		Rules      		====================

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@echo "[$(CYAN)Executable$(RESET)] $(GREEN)$(NAME)$(RESET)"
	@$(COMPILER) $(FLAGS) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIRECTORY)/%.o: %.cpp
	@echo "[$(CYAN)Compiling$(RESET)] $(FLAGS) $(GREEN)$<$(RESET)"
	@$(COMPILER) $(FLAGS) $(I) -c $< -o $@

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

clean:
	@$(RM) $(OBJECTS_DIRECTORY)
	@echo "$(B_YELLOW)$(NAME)$(RESET):$(YELLOW) binary files deleted$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(B_YELLOW)$(NAME)$(RESET):$(YELLOW) deleted$(RESET)"

re: fclean all

leak: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 6697 42Porto!

.PHONY: all clean fclean re leak