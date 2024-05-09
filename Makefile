CC = clang
ROOT_DIR = ../keygen-jarroyoi
CFLAGS = -I$(ROOT_DIR)/include -Itest -Wall -Wextra -O3
SRC_DIR = $(ROOT_DIR)/src


io: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

cmp: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

add: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

sub: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

mul: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

div: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

gcd: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

inv_mod: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

montgomery: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

exp_mod: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

is_prime: $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_aux.c $(SRC_DIR)/number_theory.c $(ROOT_DIR)/src-given/random.c 
	$(CC) $(CFLAGS) -o bin/$@ test/$@.c $^

all: io cmp add sub mul div gcd inv_mod montgomery exp_mod is_prime

clean:
	rm -rf bin/*

