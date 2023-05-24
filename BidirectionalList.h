#ifndef NG_BIDIRECTIONAL_LIST_H
#define NG_BIDIRECTIONAL_LIST_H

#include <cstdlib>
#include <cassert>

namespace NG {
	class BidirectionalList {
	public:
		enum NodeIndex {
            PREVIOUS = 0,
            NEXT     = 1
        };

	private:
        struct Node {
            Node* Nodes[2];
            void* Data;
        };

        static Node* NewNode(void* Data) {
            Node* NewNode = (Node*) malloc(sizeof(Node));
            NewNode->Nodes[NodeIndex::PREVIOUS] = nullptr;
            NewNode->Nodes[NodeIndex::NEXT] = nullptr;
            NewNode->Data = Data;
            return NewNode;
        }

	private:
		Node* 		 Nodes[2];
		unsigned int NodeCount;

	public:
		BidirectionalList();
		~BidirectionalList();

	private:
		void Swap(Node* LeftNode, Node* RightNode);
		void Remove(Node* NodeToRemove);

		void InsertAt(Node* At, void* Data);
		void Push(Node* NodeToPush, Node*& At, NodeIndex AtNodeIndex);

	public:
		void Destroy();

		void InsertItemAtFromStart(void* Data, unsigned int Offset = 0);
		void InsertItemAtFromEnd(void* Data, unsigned int Offset = 0);

		void RemoveFromStart(unsigned int Offset = 0);
		void RemoveFromEnd(unsigned int Offset = 0);

		void PushFront(void* Data);
		void PushBack(void* Data);

		void* PopBack();
		void* PopFront();

		void* PeekBack();
		void* PeekFront();

	private:
		BidirectionalList(BidirectionalList const& Other) = delete;
		BidirectionalList(BidirectionalList&& Other) = delete;

		void operator=(BidirectionalList const& Other) = delete;
		void operator=(BidirectionalList&& Other) = delete;
	};

	#define LIST_HEAD BidirectionalList::NodeIndex::PREVIOUS
	#define LIST_TAIL BidirectionalList::NodeIndex::NEXT
}

#endif