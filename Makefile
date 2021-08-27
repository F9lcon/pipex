SRCS		=	main.c parser.c utils.c lib_ft/ft_bzero.c lib_ft/ft_calloc.c lib_ft/ft_lstadd_back.c\
				lib_ft/ft_lstclear.c lib_ft/ft_lstlast.c lib_ft/ft_lstnew.c lib_ft/ft_putchar_fd.c\
				lib_ft/ft_putstr_fd.c lib_ft/ft_split.c lib_ft/ft_strlen.c lib_ft/ft_strncmp.c lib_ft/ft_strnstr.c\
				lib_ft/ft_strdup.c

OBJS		=	${SRCS:.c=.o}

SRCS_B		=	bonus/main_bonus.c bonus/parser_bonus.c bonus/utils_bonus.c\
				bonus/gnl_pipex/get_next_line_pipex.c bonus/gnl_pipex/get_next_line_utils_pipex.c\
				bonus/lib_ft/ft_bzero.c bonus/lib_ft/ft_calloc.c bonus/lib_ft/ft_lstadd_back.c bonus/lib_ft/ft_lstclear.c\
				bonus/lib_ft/ft_lstlast.c bonus/lib_ft/ft_lstnew.c bonus/lib_ft/ft_putchar_fd.c bonus/lib_ft/ft_putstr_fd.c\
				bonus/lib_ft/ft_split.c bonus/lib_ft/ft_strlen.c bonus/lib_ft/ft_strncmp.c bonus/lib_ft/ft_strnstr.c\
				bonus/lib_ft/ft_strdup.c

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

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

x:
	 ./pipex here_doc stop cat cat cat result.txt

fclean: clean
	$(RM) $(NAME)

re:  fclean all
