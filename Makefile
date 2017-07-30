include ./include/depend.mk

SRC		=	main.c

CFLAGS	+=	-I ./include/

_OBJ	=	$(SRC:.c=.o)

OBJ		=	$(patsubst %,$(ODIR)/%,$(_OBJ))

ISTL_D	=	/usr/local/bin

NAME	=	cbcmaker

all		:	mkobj $(NAME)

$(ODIR)/%.o	:	$(SDIR)/%.c
	$(CC) $(CFLAGS)	-c -o $@ $<

$(NAME)		:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

mkobj		:
	if [ ! -d ./obj/ ]; then mkdir ./obj/; fi

clean		:
	rm -f $(OBJ)

fclean		:	clean
	rm -f $(NAME)

re		:	fclean all

jistl	:	all
	cp $(NAME) $(ISTL_D)

uninstall	:
	rm -f $(patsubst %,$(ISTL_D)/%,$(NAME))

install	:	jistl fclean