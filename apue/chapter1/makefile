OBJECTS= ls.o stderr.o logerr.o cp.o

all: cp ls 

ls: apue.h $(OBJECTS) 
	gcc -o ls ls.o stderr.o logerr.o
cp: apue.h $(OBJECTS)
	gcc -o cp cp.o stderr.o logerr.o

ls.o: apue.h 
cp.o: apue.h
stderr.o: apue.h 
logerr.o: apue.h 


.PHONY: clean
clean: 
	rm ls cp $(OBJECTS)
