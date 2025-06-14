#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <string>
#include <iostream>

template <class T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T *data; // Pointer to the student profile
        Node *next;
        Node *prev;
    };
    Node *head;
    Node *tail;
    Node *current; // Pointer to the current student profile for browsing

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        current = nullptr; // Initialize current to nullptr
    }

    ~DoublyLinkedList()
    {
        Node *nodePtr = head;
        while (nodePtr != nullptr)
        {
            Node *next = nodePtr->next; // Assuming T has a next pointer
            delete nodePtr;
            nodePtr = next;
        }
    }
    void insertNode(T *&newData)
    {
        Node *newNode = new Node;
        newNode->data = newData;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr && tail == nullptr) // If the list is empty
        {
            head = newNode;
            tail = newNode;
            current = newNode; // Set current to the first node
        }
        else
        {
            Node *currentPtr = head;
            while (currentPtr != nullptr && currentPtr->data->getStudentName() < newNode->data->getStudentName()) // Assuming T has a getStudentName method
            {
                currentPtr = currentPtr->next; // Move to the next node
            }

            if (currentPtr == head) // Insert at the beginning
            {
                newNode->next = head;
                head->prev = newNode; // Assuming T has a prev pointer
                head = newNode;
                current = newNode; // Set current to the new head
            }
            else if (currentPtr == nullptr) // Insert at the end
            {
                tail->next = newNode;
                newNode->prev = tail; // Assuming T has a prev pointer
                tail = newNode;
            }
            else // Insert in the middle
            {
                newNode->next = currentPtr;
                newNode->prev = currentPtr->prev; // Assuming T has a prev pointer
                currentPtr->prev->next = newNode;
                currentPtr->prev = newNode;
            }
        }
    }

    void browseForward()
    {

        if (current == nullptr) // If current is not set
        {
            throw "Current node is not set.\n"; // Throw an error if current is nullptr
            return;
        }

        if (current->next == nullptr) // If current is the last node
        {
            throw "Already at the end of the list.\n"; // Throw an error if already at the end
            return;
        }

        current = current->next; // Move to the next node
        return;
    }

    void browseBackward()
    {
        if (current == nullptr) // If current is not set
        {
            throw "Current node is not set.\n"; // Throw an error if current is nullptr
            return;
        }

        if (current->prev == nullptr) // If current is the last node
        {
            throw "Already at the end of the list.\n"; // Throw an error if already at the end
            return;
        }

        current = current->prev; // Move to the next node
        return;
    }

    T *getCurrentNode() const
    {
        if (current == nullptr)
        {
            return nullptr; // Return nullptr if current is not set
        }
        return current->data; // Return the current node
    }

    T *searchByName(std::string name)
    {
        Node *nodePtr = head;
        while (nodePtr != nullptr)
        {
            if (nodePtr->data->getStudentName() == name) // Assuming T has a getStudentName method
            {
                return nodePtr->data; // Return the found node
            }
            nodePtr = nodePtr->next; // Move to the next node
        }
        throw "Student profile not found.\n"; // Throw an error if not found
        return nullptr;                       // Return nullptr if not found
    }

    void deleteNode(T *&node)
    {
        if (head == nullptr) // If the list is empty
        {
            throw "List is empty. Cannot delete node.\n";
            return;
        }
        if (node == nullptr) // If the node to delete is nullptr
        {
            throw "Node to delete is nullptr.\n";
            return;
        }
        Node *nodePtr = head;
        while (nodePtr != nullptr)
        {
            if (nodePtr->data == node) // Assuming T has an operator== defined
            {
                if (nodePtr == head) // If it's the head node
                {
                    head = nodePtr->next;
                    if (head != nullptr)
                        head->prev = nullptr; // Update the new head's prev pointer
                }
                else if (nodePtr == tail) // If it's the tail node
                {
                    tail = nodePtr->prev;
                    if (tail != nullptr)
                        tail->next = nullptr; // Update the new tail's next pointer
                }
                else // If it's a middle node
                {
                    nodePtr->prev->next = nodePtr->next;
                    nodePtr->next->prev = nodePtr->prev;
                }
                delete nodePtr; // Delete the node
                return;         // Exit after deleting the node
            }
            nodePtr = nodePtr->next; // Move to the next node
        }
        throw "Node not found in the list.\n"; // Throw an error if not found
    }

    void displayAllNodes()
    {
        Node *nodePtr = head;
        if (nodePtr == nullptr)
        {
            throw "List is empty. Cannot display nodes.\n"; // Throw an error if the list is empty
            return;
        }
        while (nodePtr != nullptr)
        {
            nodePtr->data->printProfile(); // Assuming T has a printProfile method
            nodePtr = nodePtr->next;       // Move to the next node
        }
    }

    int getCount() const
    {
        int count = 0;
        Node *nodePtr = head;
        while (nodePtr != nullptr)
        {
            count++;
            nodePtr = nodePtr->next; // Move to the next node
        }
        return count; // Return the count of nodes
    }
};

#endif