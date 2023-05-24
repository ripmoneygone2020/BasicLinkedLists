#ifndef NG_UNIDIRECTIONAL_LIST_H
#define NG_UNIDIRECTIONAL_LIST_H

#include <cstdlib>

namespace NG {
    class ForwardList {
        struct Node {
            void* Data;
            Node* Next;
        };

        static Node* NewNode(void* Data) {
            Node* NewNode = (Node*) malloc(sizeof(Node));
            NewNode->Data = Data;
            NewNode->Next = nullptr;
            return NewNode;
        }

    private:
        Node*        Head;
        unsigned int NodeCount;

    public:
        ForwardList();
        ~ForwardList();

    public:
        void Destroy();

        void PushBack(void* Data);
		void PushFront(void* Data);

		void PopFront();
        void* PopBack();
    };
}

#endif