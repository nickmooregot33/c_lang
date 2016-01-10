OBJECTS= ls.o stderr.o logerr.o

ls: apue.h $(OBJECTS) 
	gcc -o ls ls.o stderr.o logerr.o

ls.o: apue.h 
stderr.o: apue.h 
logerr.o: apue.h 

.PHONY: clean
clean: 
	rm ls $(OBJECTS)
