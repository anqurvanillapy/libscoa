#ifndef __LIBSCOA_MSGQ_H
#define __LIBSCOA_MSGQ_H

// FIXME: check the need of introducing boost::lockfree::queue
template <typename T>
class MessageQueue {
public:
    explicit MessageQueue();

    void enqueue(scoa_msg_t& msg);
    void msg_destroy();
private:
    struct Node {
        T msg;
        Node *next;
    };

    Node *head;
    Node *tail;
}

#endif // !__LIBSCOA_MSGQ_H
