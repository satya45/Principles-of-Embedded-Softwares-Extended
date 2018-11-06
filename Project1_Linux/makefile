sprint: main.o help.o allocate.o dispmem.o free.o write.o inverttime.o writetime.o verifytime.o specifymem.o 
	gcc -o sprint main.o help.o allocate.o dispmem.o free.o write.o inverttime.o writetime.o verifytime.o specifymem.o 

main.o: main.c help.h main.h allocate.h dispmem.h free.h write.h inverttime.h writetime.h verifytime.h 
	gcc -c main.c 

help.o: help.c help.h
	gcc -c help.c

allocate.o: allocate.c allocate.h dispmem.h free.h
	gcc -c allocate.c

dispmem.o: dispmem.c dispmem.h allocate.h write.h
	gcc -c dispmem.c

free.o: free.c free.h allocate.h
	gcc -c free.c

write.o: write.c write.h allocate.h specifymem.h
	gcc -c write.c

inverttime.o: inverttime.c inverttime.h allocate.h writetime.h specifymem.h
	gcc -c inverttime.c

writetime.o: writetime.c writetime.h allocate.h
	gcc -c writetime.c

verifytime.o: verifytime.c verifytime.h writetime.h allocate.h specifymem.h
	gcc -c verifytime.c

specifymem.o: specifymem.c specifymem.h allocate.h
	gcc -c specifymem.c


test: sprint test.txt
	./sprint < test.txt

clean:
	rm sprint main.o help.o allocate.o dispmem.o free.o write.o inverttime.o writetime.o verifytime.o specifymem.o
 
