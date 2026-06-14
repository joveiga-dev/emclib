CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

INCLUDES = -I../../core/include \
           -I../../include

SRCS = test_ringbuf.c \
	   ../../core/src/emc_ringbuf.c

OBJS = $(SRCS:.c=.o)

TARGET = test_ringbuf

ifeq ($(OS), Windows_NT)
	RM = del /Q
	EXE = .exe
else
	RM = rm -f
	EXE =
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	$(RM) *.o
	$(RM) $(TARGET)$(EXE)
	$(RM) ..\..\core\src\*.o


run: $(TARGET)
	./$(TARGET)$(EXE)

.PHONY: all clean run


