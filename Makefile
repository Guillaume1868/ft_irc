NAME 	=	ircserv

FILES	=	main Server User Display/Display Channel ACommand Command/Ping Command/UserCmd Command/Pass Command/Mode Command/Nick Command/Join Command/Privmsg Command/Quit Command/Kick Command/Notice Command/Part

SRC		=	$(addprefix srcs/, $(FILES:$(FILE_EXTENSION)=.c))
OBJ		=	$(addprefix objs/, ${FILES:$(FILE_EXTENSION)=.o})
CC		=	c++

RM		=	rm -f

GREEN       =   \e[38;5;118m
YELLOW      =   \e[38;5;226m
RESET       =   \e[0m
_SUCCESS    =   [$(GREEN)SUCCESS$(RESET)]
_INFO       =   [$(YELLOW)INFO$(RESET)]

all:	header $(NAME)

objs/%.o: srcs/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) -Wall -Wextra -Werror -std=c++98 -g -c $< -o $@
	@printf "$(_INFO) OBJ $@ compiled.\n"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -Wall -Wextra -Werror -std=c++98 -g -o $(NAME)
	@printf "$(_SUCCESS) $(NAME) ready.\n"

clean:
	@ $(RM) $(OBJ)
	@printf "$(_INFO) $(OBJ) removed.\n"

fclean: clean
	@ $(RM) $(NAME)
	@printf "$(_INFO) $(NAME) removed.\n"
re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re

header:
	@printf "$(GREEN)"
	@echo " __   __  _______  ___   _  _______ "
	@echo "|  |_|  ||   _   ||   | | ||       |"
	@echo "|       ||  |_|  ||   |_| ||    ___|"
	@echo "|       ||       ||      _||   |___ "
	@echo "|       ||       ||     |_ |    ___|"
	@echo "| ||_|| ||   _   ||    _  ||   |___ "
	@echo "|_|   |_||__| |__||___| |_||_______|"
	@printf "Project $(NAME)\n"
	@printf "Last commit : "
	@echo $$(git log -1 --format=%cd --date=relative)
	@printf "              "
	@echo  $$(git log -1 --format=%B --date=relative)
	@printf "$(RESET)"
