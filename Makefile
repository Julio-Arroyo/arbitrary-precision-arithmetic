CC = clang
CFLAGS = -I../keygen-jarroyoi/include -Itest -Wall -Wextra -O3
SRC_DIR = ../keygen-jarroyoi/src

io: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

cmp: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

add: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

sub: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

mul: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

div: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

gcd: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

clean:
	rm -f bin/*

