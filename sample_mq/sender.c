#include "../util/message_queues.h"

int main() {
    int msg_id = setup_message_queue();
    const char *message = "Hello from sender!";

    send_message(msg_id, 1, message);
    printf("Message sent: %s\n", message);

    return 0;
}