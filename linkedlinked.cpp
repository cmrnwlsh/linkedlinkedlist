#include<iostream>
#include<string>

using namespace std;

template<typename T>
class Node {
public:
    explicit Node(T data, Node *next = nullptr, Node *prev = nullptr) :
            next(next),
            prev(prev),
            data(data) {}

    Node *next;
    Node *prev;
    T data;

};

template<typename T>
class DoublyLinkedList {
    Node<T> *head;
    Node<T> *tail;

public:

    DoublyLinkedList() :
            head(nullptr),
            tail(nullptr) {}

    void insert(T data) {
        if (this->head == nullptr) {
            this->head = this->tail = new Node<T>(data);
            return;
        }

        Node<T> *current = this->head;
        while (data > current->data && current->next != nullptr)
            current = current->next;

        if (this->tail == this->head) {
            if (data <= current->data)
                this->head = current->prev = new Node<T>(data, current, current->prev);
            else
                this->tail = current->next = new Node<T>(data, nullptr, current);
        } else if (this->head == current) {
            if (data <= current->data)
                this->head = current->prev = new Node<T>(data, current, current->prev);
            else
                current->next = new Node<T>(data, nullptr, current);
        } else if (this->tail == current) {
            if (data <= current->data)
                current->prev = current->prev->next = new Node<T>(data, current, current->prev);
            else
                this->tail = current->next = new Node<T>(data, nullptr, current);
        } else if (data >= current->data)
            current->next = current->next->prev = new Node<T>(data, current->next, current);
        else
            current->prev = current->prev->next = new Node<T>(data, current, current->prev);
    };

    bool searchDelete(T data) {
        Node<T> *current = this->head;
        Node<T> *next = current->next;
        bool found = false;

        while (current != nullptr) {
            if (data == current->data) {
                if (this->tail == this->head) {
                    delete current;
                    this->tail = this->head = nullptr;
                } else if (this->head == current) {
                    delete current;
                    next->prev = nullptr;
                    this->head = next;
                } else if (this->tail == current) {
                    current->prev->next = nullptr;
                    this->tail = current->prev;
                    delete current;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                }
                found = true;
            }
            current = next;
            if (current) next = current->next;
        }
        return found;
    };

    void print() {
        Node<T> *current = this->head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << ".\n";
    };

    void backwardsPrint() {
        Node<T> *current = this->tail;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->prev;
        }
        cout << ".\n";
    }

    ~DoublyLinkedList() {
        Node<T> *current = this->head;
        while (current != nullptr) {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }
        this->head = this->tail = nullptr;
    }

};
