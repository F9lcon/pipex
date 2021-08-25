SRCS		=	main.c parser.c utils.c lib_ft/ft_bzero.c lib_ft/ft_calloc.c lib_ft/ft_lstadd_back.c\
				lib_ft/ft_lstclear.c lib_ft/ft_lstlast.c lib_ft/ft_lstnew.c lib_ft/ft_putchar_fd.c\
				lib_ft/ft_putstr_fd.c lib_ft/ft_split.c lib_ft/ft_strlen.c lib_ft/ft_strncmp.c lib_ft/ft_strnstr.c\
				lib_ft/ft_strdup.c

SRCS_B		=	bonus/main_bonus.c bonus/parser_bonus.c bonus/utils_bonus.c\
				bonus/gnl_pipex/get_next_line_pipex.c bonus/gnl_pipex/get_next_line_utils_pipex.c\
				lib_ft/ft_bzero.c lib_ft/ft_calloc.c lib_ft/ft_lstadd_back.c lib_ft/ft_lstclear.c\
				lib_ft/ft_lstlast.c lib_ft/ft_lstnew.c lib_ft/ft_putchar_fd.c lib_ft/ft_putstr_fd.c lib_ft/ft_split.c\
				lib_ft/ft_strlen.c lib_ft/ft_strncmp.c lib_ft/ft_strnstr.c lib_ft/ft_strdup.c

NAME		=	pipex

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

HEADER		=	pipex.h

HEADER_B	=	bonus/pipex_bonus.h

.PHONY:	all clean fclean re bonus

all: $(NAME)

$(NAME): $(SRCS) $(HEADER)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

bonus: $(SRCS_B) $(HEADER_B)
	$(CC) $(CFLAGS) $(SRCS_B) -o $(NAME)

clean:
	$(RM) $(NAME)

x:
	 ./pipex here_doc stop cat cat cat result.txt

fclean: clean
	$(RM) $(NAME)

re:  fclean all
