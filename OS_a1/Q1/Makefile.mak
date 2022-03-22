Question_1: 
	gcc -S a1.c
	gcc a1.s -o a1.o
	./a1.o


	gcc -S a2.c
	gcc -o a2.o -pthread a2.s
	./a2.o