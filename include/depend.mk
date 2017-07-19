CC		=	gcc

AR		=	ar rc

DEBUG		=	true

WALL		=	true

RELEASE		=	false

ALLOW_LSEEK	=	true

ALLOW_OPEN	=	true

OPTI_FLAG	=	-O2

MSTATIC		=	true

ifeq	($(WALL),true)
 CFLAGS		+=	-W -Wall -Wextra
endif

ifeq	($(RELEASE),true)
 CFLAGS		+=	$(OPTI_FLAG)
 CFLAGS		+=	-Werror -Wno-unused-result
 DEBUG		=	false
else
 CFLAGS		+=	-O0
endif

ifeq	($(DEBUG),true)
 CFLAGS		+=	-g
endif

ODIR		=	obj

SDIR		=	src
