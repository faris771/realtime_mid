CC = gcc
CFLAGS = -I../util
LDFLAGS = -lrt

SENDER_SRC = sample_mq/sender.c
RECEIVER_SRC = sample_mq/receiver.c
UTIL_SRC = util/message_queues.h

SENDER_OBJ = $(SENDER_SRC:.c=.o)
RECEIVER_OBJ = $(RECEIVER_SRC:.c=.o)

TARGETS = sender receiver

all: $(TARGETS)

sender: $(SENDER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

receiver: $(RECEIVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(UTIL_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) $(SENDER_OBJ) $(RECEIVER_OBJ)

run: all
	./receiver &
	sleep 1
	./sender

.PHONY: all clean run