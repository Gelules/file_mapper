CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wvla -Werror
OBJ = file_mapper.o
STATIC = file_mapper.a
SHARED = file_mapper.so

all: $(OBJ) $(STATIC) $(SHARED)

obj: $(OBJ)

static: $(STATIC)

shared: $(SHARED)

$(OBJ):

$(STATIC): $(OBJ)
	$(AR) csr $@ $^

$(SHARED): $(OBJ)
	$(CC) $^ -fPIC -shared -o $@

clean:
	$(RM) $(OBJ) $(STATIC) $(SHARED)
