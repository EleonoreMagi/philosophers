NAME = philo

SRCS 	= 	process_init.c \
			philo.c \
			utilities.c 

HEADER	=	philo.h

OBJ		=	$(patsubst %.c, %.o, $(SRCS))

CC 		= 	gcc
CFLAGG 	= 	-Wall -Wextra -Werror -I$(HEADER)

all		:	${NAME}

$(NAME)	:	$(OBJ)	$(HEADER)
	$(CC) $(CFLAGG) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	rm -f $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

