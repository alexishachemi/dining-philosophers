NAME	=	dining-philosophers

TMPDIR	=	.tmp

SRC		=	$(shell find src -type f -name '*.c')

OBJ		=	$(SRC:%.c=$(TMPDIR)/%.o)

CFLAGS	+=	-Wall -Wextra -Iinclude

$(NAME): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

all: $(NAME)

clean:
	rm -rf $(TMPDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(TMPDIR)/%.o:	%.c
	@mkdir -p $(@D)
	gcc -o $@ -c $< $(CFLAGS)

.PHONY: all clean fclean re
