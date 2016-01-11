OBJECTS=  stderr.o logerr.o 

all: cp ls cp.2

ls: apue.h ls.o $(OBJECTS) 
	gcc -o ls ls.o stderr.o logerr.o
cp: apue.h cp.o $(OBJECTS)
	gcc -o cp cp.o stderr.o logerr.o
cp.2: apue.h cp.2.o $(OBJECTS)
	gcc -o cp.2 cp.2.o stderr.o logerr.o
pid: apue.h pid.o
	cc -o pid pid.o

ls.o: apue.h 
cp.o: apue.h
stderr.o: apue.h 
logerr.o: apue.h 
pid.o: apue.h

.PHONY: clean
clean: 
	rm ls cp cp.2 ls.o cp.o cp.2.o $(OBJECTS)
