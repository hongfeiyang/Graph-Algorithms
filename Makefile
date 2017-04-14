# # # # # # #
# Makefile for assignment 1
#
# created 29 Jan 2017
# Matt Farrugia <matt.farrugia@unimelb.edu.au>
#

CC     = gcc
CFLAGS = -Wall -Wextra
EXE    = a1
OBJ    = main.o traverse.o graph.o list.o stack.o queue.o
#									add any new files here ^

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: traverse.h graph.h
traverse.o: traverse.h graph.h list.h stack.h queue.h
graph.o: graph.h

stack.o: stack.h list.h
queue.o: queue.h list.h
list.o: list.h


test1:
	./$(EXE) -p 1 -s 12 -d 4 -f vicroads.txt
test2:
	./$(EXE) -p 2 -s 12 -d 4 -f vicroads.txt
test3:
	./$(EXE) -p 3 -s 12 -d 4 -f vicroads.txt
test4:
	./$(EXE) -p 4 -s 12 -d 4 -f vicroads.txt
test5:
	./$(EXE) -p 5 -s 12 -d 4 -f vicroads.txt

checkoutput1:
	./$(EXE) -p 1 -s 12 -d 4 -f vicroads.txt > p1output.txt
	diff p1output.txt vic-p1-s12.txt
	rm p1output.txt

checkoutput2:
	./$(EXE) -p 2 -s 12 -d 4 -f vicroads.txt > p2output.txt
	diff p2output.txt vic-p2-s12.txt
	rm p2output.txt

checkoutput3:
	./$(EXE) -p 3 -s 12 -d 4 -f vicroads.txt > p3output.txt
	diff p3output.txt vic-p3-s12-d4.txt
	rm p3output.txt

checkoutput4:
	./$(EXE) -p 4 -s 12 -d 4 -f vicroads.txt > p4output.txt
	diff p4output.txt vic-p4-s12-d4.txt
	rm p4output.txt

checkoutput5:
	./$(EXE) -p 5 -s 12 -d 4 -f vicroads.txt > p5output.txt
	diff p5output.txt vic-p5-s12-d4.txt
	rm p5output.txt


clean:
	rm -f $(OBJ) $(EXE)

STUDENTNUM = 783661
SUBMISSION = Makefile report.pdf main.c graph.h graph.c traverse.h traverse.c \
			 list.h list.c stack.h stack.c queue.h queue.c
#									add any new files here ^
submission: $(SUBMISSION)
	tar -czvf $(STUDENTNUM).tar.gz $(SUBMISSION)