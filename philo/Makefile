NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

FILES = philo \
		start \
		utils \
		eat \
		utils_mutex \
		utils_mutex_1 \
		utils_mutex_2

SRCS_DIR = ./

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS = ${SRCS:.c=.o}

${NAME}:
	${CC} ${CFLAGS} ${SRCS} -o $@ -g

all: ${NAME} 
${NAME}: ${OBJS}

sanitize: ${NAME}
	${CC} ${SRCS} -o $^ -g -fsanitize=thread

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}
	
re: fclean all

.PHONY: all clean fclean re sanitize
