#include "../ForwardList.h"

namespace NG {
    ForwardList::ForwardList() {
        Head = nullptr;
        NodeCount = 0;
    }

    ForwardList::~ForwardList() {
        Destroy();

        Head = nullptr;
        NodeCount = 0;
    }

    void ForwardList::Destroy() {
        Node* Temp = nullptr;
        while(Head) {
            Temp = Head;
            Head = Head->Next;

            free(Temp);
        }
    }

    void ForwardList::PushBack(void* Data) {
        if(Data) {
            Node* NodeToPush = ForwardList::NewNode(Data);
            if(!Head)
                Head = NodeToPush;
            else {
                Node* TempNode = Head;
                while(TempNode->Next)
                    TempNode = TempNode->Next;

                TempNode->Next = NodeToPush;
            }

            NodeCount++;
        }
    }

    void ForwardList::PushFront(void* Data) {
        if(Data) {
            Node* NodeToPush = ForwardList::NewNode(Data);
            if(!Head)
                Head = NodeToPush;
            else {
                NodeToPush->Next = Head;
                Head = NodeToPush;
            }

            NodeCount++;
        }
    }

    void* ForwardList::PopBack() {
        Node* Temp = Head;
        while(Temp->Next)
            Temp = Temp->Next;

        void* UserData = Temp->Data;

        free(Temp);
        NodeCount--;

        return UserData;
    }

    void ForwardList::PopFront() {
        if(Head) {
            Node* Temp = Head->Next;

            free(Head);
            Head = Temp;
            NodeCount--;
        }
    }
}