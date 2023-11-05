CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = a_star_algo.c handle_map.c readline.c my_mouse.c min_heap.c my_mouse.h
TARGET = my_mouse

all : $(TARGET)

$(TARGET) : $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all