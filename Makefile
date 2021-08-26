SRCS		=	main.c parser.c utils.c lib_ft/ft_bzero.c lib_ft/ft_calloc.c lib_ft/ft_lstadd_back.c\
				lib_ft/ft_lstclear.c lib_ft/ft_lstlast.c lib_ft/ft_lstnew.c lib_ft/ft_putchar_fd.c\
				lib_ft/ft_putstr_fd.c lib_ft/ft_split.c lib_ft/ft_strlen.c lib_ft/ft_strncmp.c lib_ft/ft_strnstr.c\
				lib_ft/ft_strdup.c

OBJS		=	${SRCS:.c=.o}

SRCS_B		=	bonus/main_bonus.c bonus/parser_bonus.c bonus/utils_bonus.c\
				bonus/gnl_pipex/get_next_line_pipex.c bonus/gnl_pipex/get_next_line_utils_pipex.c\
				lib_ft/ft_bzero.c lib_ft/ft_calloc.c lib_ft/ft_lstadd_back.c lib_ft/ft_lstclear.c\
				lib_ft/ft_lstlast.c lib_ft/ft_lstnew.c lib_ft/ft_putchar_fd.c lib_ft/ft_putstr_fd.c lib_ft/ft_split.c\
				lib_ft/ft_strlen.c lib_ft/ft_strncmp.c lib_ft/ft_strnstr.c lib_ft/ft_strdup.c

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

%c%o:
	${GCC} -c $< -o ${<:.c=.o}

bonus: $(OBJS_B) $(HEADER_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME)

clean:
	$(RM) $(OBJS)

x:
	 ./pipex here_doc stop cat cat cat result.txt

fclean: clean
	$(RM) $(NAME)

re:  fclean all
