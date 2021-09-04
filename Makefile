SRCS		=	main.c parser.c utils.c lib_ft/ft_bzero.c lib_ft/ft_calloc.c lib_ft/ft_lstadd_back.c\
				lib_ft/ft_lstclear.c lib_ft/ft_lstlast.c lib_ft/ft_lstnew.c lib_ft/ft_putchar_fd.c\
				lib_ft/ft_putstr_fd.c lib_ft/ft_split.c lib_ft/ft_strlen.c lib_ft/ft_strncmp.c lib_ft/ft_strnstr.c\
				lib_ft/ft_strdup.c

OBJS		=	${SRCS:.c=.o}

SRCS_B		=	bonus/main_bonus.c bonus/parser_bonus.c bonus/utils_bonus.c\
				bonus/gnl_pipex/get_next_line_bonus.c bonus/gnl_pipex/get_next_line_utils_bonus.c\
				bonus/lib_ft/ft_bzero_bonus.c bonus/lib_ft/ft_calloc_bonus.c bonus/lib_ft/ft_lstadd_back_bonus.c\
				bonus/lib_ft/ft_lstclear_bonus.c bonus/lib_ft/ft_lstlast_bonus.c bonus/lib_ft/ft_lstnew_bonus.c\
				bonus/lib_ft/ft_putchar_fd_bonus.c bonus/lib_ft/ft_putstr_fd_bonus.c bonus/lib_ft/ft_split_bonus.c\
				bonus/lib_ft/ft_strlen_bonus.c bonus/lib_ft/ft_strncmp_bonus.c bonus/lib_ft/ft_strnstr_bonus.c\
				bonus/lib_ft/ft_strdup_bonus.c

OBJS_B		=	${SRCS_B:.c=.o}

NAME		=	pipex

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

HEADER		=	pipex.h

HEADER_B	=	bonus/pipex_bonus.h

.PHONY:	all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJS_B) $(HEADER_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

x:
	 ./pipex new.txt cat cat result.txt

fclean: clean
	$(RM) $(NAME)

re:  fclean all
