NAME = minishell
CC = gcc
CFLAGS 	:= -Wall  -Wextra -Werror -fsanitize=address -I./readline -I./readline/include -I.
SRC = minishell.c ft_split.c parser.c builtin.c utils.c memory.c command.c ft_pwd.c redirections.c files.c \
quotes.c redirections2.c parser2.c signals.c debug.c pipes.c env.c env2.c env3.c env4.c memory2.c heredoc.c \
ft_echo.c parser3.c parser4.c test_input.c ft_cd.c ft_strtrim.c pipes2.c

HEADER = minishell.h
OBJS = $(SRC:.c=.o)
CFLAGSREADLINE := -L./readline -lreadline 
LDLIBS := -lreadline -lncurses
RLMAKE := readline/Makefile

all : $(NAME)

$(RLMAKE) :
	cd ./readline;\
		./configure;\
	cd ..
	
$(NAME) : $(OBJS) $(RLMAKE)

	make -C readline 2>&1 >/dev/null 
	@echo "Readline compiled\n"
	$(CC) $(CFLAGS) $(OBJS) readline/libhistory.a readline/libreadline.a $(LDLIBS) -o $(NAME)
	# $(CC) $(CFLAGSREADLINE) $(CFLAGS) $(OBJS)readline/libhistory.a readline/libreadline.a -o $(NAME)
	@echo "Minishell compiled !\n"

$(OBJS): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -c $(SRC) 

clean :
	rm -rf $(OBJS)
	make clean -C readline

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re