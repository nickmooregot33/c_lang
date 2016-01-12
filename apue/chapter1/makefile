OBJECTS=  stderr.o logerr.o 

all: cp ls cp.2 pid shell error uid

ls: apue.h ls.o $(OBJECTS) 
	gcc -o ls ls.o stderr.o logerr.o
cp: apue.h cp.o $(OBJECTS)
	gcc -o cp cp.o stderr.o logerr.o
cp.2: apue.h cp.2.o $(OBJECTS)
	gcc -o cp.2 cp.2.o stderr.o logerr.o
pid: apue.h pid.o
	cc -o pid pid.o
shell: apue.h shell.o stderr.o logerr.o
	cc -o shell shell.o stderr.o logerr.o
error: apue.h error.o 
	cc -o error error.o 
uid: apue.h uid.o
	cc -o uid uid.o

ls.o: apue.h 
cp.o: apue.h
stderr.o: apue.h 
logerr.o: apue.h 
pid.o: apue.h
shell.o: apue.h
error.o: apue.h
uid: apue.h

.PHONY: clean
clean: 
	rm ls cp error cp.2 ls.o cp.o cp.2.o shell shell.o error.o uid uid.o pid pid.o $(OBJECTS)
