EXE=servjeu
CC=gcc
CFLAGS=-pthread -Iinclude/
LDFLAGS=
SRC=src/server.c 
OBJ=$(SRC:.c=.o)
TAR=$(EXE)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJ) $(EXE) $(TAR).tar.bz2 pid.conf

export:
	git archive HEAD --prefix=$(TAR)/ | bzip2 > $(TAR).tar.bz2

.PHONY: all clean export

