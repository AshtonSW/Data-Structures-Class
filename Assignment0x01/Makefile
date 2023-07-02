CC = gcc
CFLAGS = -Wall -g
TARGET = fp1
OBJS = fp1.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

fp1.o: fp1.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
