OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -std=c11 -g
OBJS = Node.c RBT.c DatabaseBuilder.c main.c

all : database

clean : 
	rm -rf $(OBJS) database

database : $(OBJS)
	gcc $(LOPTS) Node.c RBT.c DatabaseBuilder.c main.c -o database
