SRC:= $(wildcard *.c)
OBJ:= $(patsubst %.c, %.o, $(SRC))

server: $(OBJ)
	gcc $^ -lpthread -o $@ 

clean:
	rm *.o
