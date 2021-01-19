#目标：依赖
#命令
#阶段一
#all: main.c sub.c add.c
#	gcc main.c sub.c add.c -o app
#
#
#
#阶段二 从上往下建立依赖，从下往上执行命令
#app: add.o sub.o main.o
#	gcc add.o sub.o main.o -o app
#add.o:add.c
#	gcc -c add.c
#sub.o:sub.c
#	gcc -c sub.c 
#main.o:main.c
#	gcc -c main.c
#阶段三
#obj = add.o sub.o main.o
src = $(wildcard *.c) 
obj = $(patsubst %.c,%.o,$(src))
app:$(obj)
	gcc $(obj) -o app
#$@表示目标，$<表示第一个依赖，
%.o:%.c
	gcc -c $^ -o $@


#阶段四
#CPPFLAGS = -Iinclude 
#CFLAGS = -g -Wall 
#LDFLAGS =  
#CC = gcc 

#src = $(wildcard *.c) 
#obj = $(patsubst %.c,%.o,$(src))
#target = app
#$(target):$(obj)
#	$(CC) $^ $(LDFLAGS) -o $@
#%.o:%.c
#	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@











#伪目标
.PHONY:clean
clean:
	-rm -f *.o
#加 “-” 即使命令出错也继续运行
	-rm -f app
	
test:
	@echo "clean done!"
#加上@ 不显示命令本身
	@echo $(src)
	@echo $(obj)
	
