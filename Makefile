CFLAGS = -Wall -Wextra -Werror
CC = cc
SRCS_SERVER = server.c
SRCS_CLIENT = client.c
OBJC_s = $(SRCS_SERVER:.c=.o)
OBJC_c = $(SRCS_CLIENT:.c=.o)
NAME = server client
NAMEB = server_bonus client_bonus
OBJC_sb = $(SRCS_SERVERB:.c=.o)
OBJC_cb = $(SRCS_CLIENTB:.c=.o)
SRCS_SERVERB = server_bonus.c
SRCS_CLIENTB = client_bonus.c

$(NAME): $(OBJC_c) $(OBJC_s) $(SRCS_CLIENT) $(SRCS_SERVER)
		@$(CC) $(CFLAGS) $(SRCS_SERVER) -o server
		@$(CC) $(CFLAGS) $(SRCS_CLIENT) -o client


$(NAMEB): $(OBJC_cb) $(OBJC_sb) $(SRCS_CLIENTB) $(SRCS_SERVERB)
		@$(CC) $(CFLAGS) $(SRCS_SERVERB) -o server_bonus
		@$(CC) $(CFLAGS) $(SRCS_CLIENTB) -o client_bonus

all: $(NAME)

bonus: $(NAMEB)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	@rm -f $(OBJC_c) $(OBJC_s) $(OBJC_cb) $(OBJC_sb)
fclean:
	@rm  -f $(NAME) $(OBJC_s) $(OBJC_c) $(OBJC_sb) $(OBJC_cb)
	@rm -f client_bonus server_bonus
re:    clean all
# .INTERMEDIATE: $(OBJC_cb) $(OBJC_c) $(OBJC_sb) $(OBJC_s)