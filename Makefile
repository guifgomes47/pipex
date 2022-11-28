NAME	= pipex

FILES	   = main.c	check_args.c get_path.c utils.c

SRC_PATH	= src/
OBJ_PATH	= obj/
INC_PATH	= include/
OBJ_DIRS	= obj/
LIBFT_PATH	  = lib/libft/
LIBFT_INC	   = $(LIBFT_PATH)include/

LIBFT	   = $(LIBFT_PATH)libft.a

CC	  = cc
CFLAGS	  = -Wall -Wextra -Werror
CFLAGS	  += -I $(INC_PATH) -I $(LIBFT_INC) -g

LIB_FLAGS	   = -lft

RM	  = rm -rf

SRC	 = $(addprefix $(SRC_PATH), $(FILES))
OBJ	 = $(addprefix $(OBJ_PATH), $(FILES:.c=.o))

COLOR_W	 = \e[00m
COLOR_R	 = \e[31m
COLOR_G	 = \e[32m

all : $(NAME)

$(OBJ_DIRS):
	mkdir -p $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJ_DIRS) $(OBJ) $(LIBFT)
	@printf "$(COLOR_G)Making $(NAME)\n$(COLOR_W)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(LIBFT_PATH) $(LIB_FLAGS)
	@printf "$(COLOR_G)Done\n$(COLOR_W)"

clean :
	@printf "$(COLOR_R)Cleaning $(NAME) objects...\n$(COLOR_W)"
	$(RM) $(OBJ)
	$(RM) $(OBJ_DIRS)
	@printf "$(COLOR_G)Done\n$(COLOR_W)"

fclean : clean
	@printf "$(COLOR_R)Cleaning $(NAME)\n$(COLOR_W)"
	$(RM) $(NAME)
	@printf "$(COLOR_G)Done\n$(COLOR_W)"

re : fclean all

.PHONY: all clean fclean re