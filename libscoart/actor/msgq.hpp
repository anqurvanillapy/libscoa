#ifndef __LIBSCOA_MSGQ_HPP
#define __LIBSCOA_MSGQ_HPP

template <typename T>
class Msgq {
public:
    explicit Msgq();
private:
    struct Node {
        T msg;
        Node *next;
    };

    Node *head;
    Node *tail;
}

#endif // !__LIBSCOA_MSGQ_HPP
