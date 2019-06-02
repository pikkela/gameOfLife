OBJECTS = zero.o first_board.o print_first_board.o check_rules.o print_new_board.o read_states.o read_land_states.o start_game.o save_game.o main.o
CC = gcc
CFLAGS = -lncurses
PROG = game_of_life

$(PROG): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROG) $(CFLAGS)

zero.o: zero.c Header.h
	$(CC) -c zero.c

first_board.o: first_board.c Header.h
	$(CC) -c first_board.c

print_first_board.o: print_first_board.c Header.h
	$(CC) -c print_first_board.c

check_rules.o: check_rules.c Header.h
	$(CC) -c check_rules.c

print_new_board.o: print_new_board.c Header.h
	$(CC) -c print_new_board.c

read_states.o: read_states.c Header.h
	$(CC) -c read_states.c

read_land_states.o: read_land_states.c Header.h
	$(CC) $(CFLAGS) -c read_land_states.c

start_game.o: start_game.c Header.h
	$(CC) -c start_game.c

save_game.o: save_game.c Header.h
	$(CC) -c save_game.c

main.o: main.c Header.h
	$(CC) -c main.c


clean:
	rm -f *.o prog
