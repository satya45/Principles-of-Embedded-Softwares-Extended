sprint: main.o help.o allocate.o dispmem.o free.o write.o inverttime.o writetime.o verifytime.o specifymem.o 
	gcc -o sprint main.o help.o allocate.o dispmem.o free.o write.o inverttime.o writetime.o verifytime.o specifymem.o 

main.o: main.c ../inc/help.h ../inc/main.h ../inc/allocate.h ../inc/dispmem.h ../inc/free.h ../inc/write.h ../inc/inverttime.h ../inc/writetime.h ../inc/verifytime.h 
	gcc -c main.c 

help.o: help.c ../inc/help.h
	gcc -c help.c

allocate.o: allocate.c ../inc/allocate.h ../inc/dispmem.h ../inc/free.h
	gcc -c allocate.c

dispmem.o: dispmem.c ../inc/dispmem.h ../inc/allocate.h ../inc/write.h
	gcc -c dispmem.c

free.o: free.c ../inc/free.h ../inc/allocate.h
	gcc -c free.c

write.o: write.c ../inc/write.h ../inc/allocate.h ../inc/specifymem.h
	gcc -c write.c

inverttime.o: inverttime.c ../inc/inverttime.h ../inc/allocate.h ../inc/writetime.h ../inc/specifymem.h
	gcc -c inverttime.c

writetime.o: writetime.c ../inc/writetime.h ../inc/allocate.h
	gcc -c writetime.c

verifytime.o: verifytime.c ../inc/verifytime.h ../inc/writetime.h ../inc/allocate.h ../inc/specifymem.h
	gcc -c verifytime.c

specifymem.o: specifymem.c ../inc/specifymem.h ../inc/allocate.h
	gcc -c specifymem.c


test: sprint test.txt
	./sprint < test.txt

clean:
	rm sprint main.o help.o allocate.o dispmem.o free.o write.o inverttime.o writetime.o verifytime.o specifymem.o
 
