FC = gcc
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic
LINK = -lrt

NAME1 = cw9
THREADS = 5
SECTIONS = 5
LIB = threads

EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o


LIB1 = $(LIB).c


%.o: %.c
	$(FC) $(CFLAGS) -c $<

%.x: %.o
	$(FC) $(CFLAGS) -o $@ $^
	chmod +x $@

.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1) $(LIB1)
	$(FC) -o $@ $(LFLAGS) $^ $(LINK)
	chmod +x $@



.PHONY: run-cw8

run-cw9: $(EXEC1) 
	./$(EXEC1) $(THREADS) $(SECTIONS)

help:
	@echo "make run-cw9		Kompiluje i uruchamia program cw9.c"
	@echo "make all			Kompiluje program cw9.c"
	@echo "make clean  		Usuwa pliki .x, .o"

.PHONY: clean
clean:
	@-rm *.x *.o  