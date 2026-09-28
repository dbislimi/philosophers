LIBFT_PATH 	= ./libft
LIBFT      	= $(LIBFT_PATH)/libft.a

PHILO_PATH  = ./srcs/mandatory

SRCS 	= ${addprefix ${PHILO_PATH}/, main.c parsing.c init.c philo_utils.c routine_philo.c routine_philo_utils.c routine_checker.c time.c}
OBJS 	= ${SRCS:.c=.o}


NAME 	= philo
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=thread
RM 		= rm -rf
INCLUDES = -Iincludes

all : ${NAME}

${NAME} : ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

$(LIBFT):
	${MAKE} -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
	
clean:
	@${MAKE} clean --silent -C ${LIBFT_PATH}
	@${RM} ${OBJS}
	@printf "MAKEFILE CLEAN\n"

fclean: clean
	@${MAKE} fclean --silent -C ${LIBFT_PATH}
	@${RM} ${NAME}
	@printf "MAKEFILE FCLEAN\n"

re: fclean all

.PHONY: all clean fclean re