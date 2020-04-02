TARGET=httpd

CC=gcc
RM=rm
CFLAGS=-Wall
OBJS=httpd.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

all: $(TARGET)

clean:
	$(RM) $(OBJS) $(TARGET)
