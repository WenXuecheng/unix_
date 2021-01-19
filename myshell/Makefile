CPPFLAGS =  
CFLAGS = -g 
LDFLAGS = 
CC = gcc
src = $(wildcard *.c)
obj = $(patsubst %.c,%.o,$(src))
target = app
$(target):$(obj)
	$(CC) $^ $(LDFLAGS) -o $@
%.o:%.c	
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@


.PHONY:clean
clean:
	-rm -f *.o
	-rm -f app


