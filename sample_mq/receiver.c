#include "../util/message_queues.h"

int main() {
    int msg_id = setup_message_queue();
    char received_message[MSG_SIZE];

    receive_message(msg_id, 1, received_message);
    printf("Message received: %s\n", received_message);

    cleanup_message_queue();
    return 0;
}