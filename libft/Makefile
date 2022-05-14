
NAME = libft.a
CC = cc
CINCLUDES = -I includes -I .
CFLAGS = -Wall -Wextra -Werror $(CINCLUDES)

SRC = ft_atoi.c\
		ft_atoll.c	\
		ft_isascii.c \
		ft_strlcpy.c \
		ft_strnstr.c \
		ft_toupper.c \
		ft_isalnum.c \
		ft_isdigit.c \
		ft_strchr.c  \
		ft_strlen.c  \
		ft_strrchr.c \
		ft_isalpha.c \
		ft_isprint.c \
		ft_strlcat.c \
		ft_strncmp.c \
		ft_tolower.c \
		ft_calloc.c  \
		ft_memset.c  \
		ft_strdup.c  \
		ft_memchr.c  \
		ft_memcpy.c  \
		ft_memccpy.c \
		ft_memmove.c \
		ft_strjoin.c \
		ft_bzero.c   \
		ft_memcmp.c  \
		ft_split.c	 \
		ft_itoa.c	\
		ft_substr.c \
		ft_strtrim.c\
		ft_strmapi.c \
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_isspace.c\
		ft_rev_str.c\
		ft_itoa_base.c\
		ft_strljoin.c\
		ft_l_itoa_base.c\
		ft_ll_itoa_base.c\
		ft_sh_itoa_base.c\
		ft_lstnew.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_front.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstclear.c\
		ft_lstmap.c\
		get_next_line.c\
		get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -f $(NAME) $(OBJ)

re : fclean
	make all 

so :
	$(CC) -c $(CFLAGS) -fPIC $(SRC) $(SRCBONUS)
	$(CC) -shared -o libft.so $(OBJ) $(OBJBONUS)

.PHONY : fclean clean re all
