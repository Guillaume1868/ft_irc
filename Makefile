NAME 	=	ircserv

FILES	=	main

SRC		=	$(addprefix src/, $(FILES:$(FILE_EXTENSION)=.c))
OBJ		=	$(addprefix objs/, ${FILES:$(FILE_EXTENSION)=.o})
_INC	=	-Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
INC		=	-Lmlx -lmlx -framework OpenGL -framework AppKit
CC		=	gcc

RM		=	rm -f

GREEN       =   \e[38;5;118m
YELLOW      =   \e[38;5;226m
RESET       =   \e[0m
_SUCCESS    =   [$(GREEN)SUCCESS$(RESET)]
_INFO       =   [$(YELLOW)INFO$(RESET)]

all:	header $(NAME)

objs/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -Wall -Wextra -Werror -g -c $< -o $@
	@printf "$(_INFO) OBJ $@ compiled.\n"

$(NAME): $(OBJ)
	@$(MAKE) -C mlx
	@$(CC) $(OBJ) $(INC) -g -o $(NAME)
	@printf "$(_SUCCESS) $(NAME) ready.\n"

clean:
	@ $(RM) $(OBJ)
	@printf "$(_INFO) $(OBJ) removed.\n"

fclean: clean
	# @ $(MAKE) clean -C mlx
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