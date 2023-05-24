#include "../BidirectionalList.h"

namespace NG {
	BidirectionalList::BidirectionalList() {
		Nodes[LIST_HEAD] = nullptr;
		Nodes[LIST_TAIL] = nullptr;
		NodeCount		 = 0;
	}

	BidirectionalList::~BidirectionalList() {
		Destroy();
		NodeCount = 0;
	}

	void BidirectionalList::Destroy() {
		Node* Temp = nullptr;
		while(Nodes[LIST_HEAD]) {
			Temp = Nodes[LIST_HEAD];
			Nodes[LIST_HEAD] = Nodes[LIST_HEAD]->Nodes[NodeIndex::NEXT];

			delete Temp;
			Temp = nullptr;
		}
	}

	void BidirectionalList::Swap(Node* LeftNode, Node* RightNode) {
		Node* LeftPreviousNode = LeftNode->Nodes[NodeIndex::PREVIOUS];
		Node* LeftNextNode = LeftNode->Nodes[NodeIndex::NEXT];

		LeftNode->Nodes[NodeIndex::PREVIOUS] = RightNode->Nodes[NodeIndex::PREVIOUS];
		LeftNode->Nodes[NodeIndex::NEXT] = RightNode->Nodes[NodeIndex::NEXT];

		RightNode->Nodes[NodeIndex::PREVIOUS] = LeftPreviousNode;
		RightNode->Nodes[NodeIndex::NEXT] = LeftNextNode;
	} 

	void BidirectionalList::InsertAt(Node* At, void* Data) {
		if(At) {
			Node* Node = BidirectionalList::NewNode(Data);
			Node->Data = Data;

			Node->Nodes[NodeIndex::PREVIOUS] = At->Nodes[NodeIndex::PREVIOUS];
			Node->Nodes[NodeIndex::NEXT] = At;
			At->Nodes[NodeIndex::PREVIOUS] = Node;

			NodeCount++;
		}
	}

	void BidirectionalList::InsertItemAtFromStart(void* Data, unsigned int Offset) {
		if(Offset == 0)
			PushFront(Data);
		else if(Offset == NodeCount)
			PushBack(Data);
		else {
			if(Nodes[LIST_HEAD] && Data) {
				Node* Node = Nodes[LIST_HEAD];
				for(unsigned int I = 0; I < Offset; I++)
					Node = Node->Nodes[NodeIndex::NEXT];

				InsertAt(Node, Data);
			}
		}
	}

	void BidirectionalList::InsertItemAtFromEnd(void* Data, unsigned int Offset) {
		if(Offset == 0)
			PushBack(Data);
		else if(Offset == NodeCount)
			PushFront(Data);
		else {
			if(Nodes[LIST_TAIL] && Data) {
				Node* NodeToInsert = Nodes[LIST_TAIL];
				for(unsigned int I = 0; I < Offset; I++)
					NodeToInsert = NodeToInsert->Nodes[NodeIndex::PREVIOUS];

				InsertAt(NodeToInsert, Data);
			}
		}
	}

	void BidirectionalList::Remove(Node* NodeToRemove) {
		if(NodeToRemove->Nodes[NodeIndex::PREVIOUS])
			NodeToRemove->Nodes[NodeIndex::PREVIOUS]->Nodes[NodeIndex::NEXT] = NodeToRemove->Nodes[NodeIndex::NEXT];
		else {
			// this is the head node
			if(NodeToRemove->Nodes[NodeIndex::NEXT]) 
				Nodes[LIST_HEAD] = NodeToRemove->Nodes[NodeIndex::NEXT];
		}

		if(NodeToRemove->Nodes[NodeIndex::NEXT])
			NodeToRemove->Nodes[NodeIndex::NEXT]->Nodes[NodeIndex::PREVIOUS] = NodeToRemove->Nodes[NodeIndex::PREVIOUS];
		else {
			// this is the tail node
			if(NodeToRemove->Nodes[NodeIndex::PREVIOUS])
				Nodes[LIST_TAIL] = NodeToRemove->Nodes[NodeIndex::PREVIOUS];
		}

		free(NodeToRemove);
		NodeCount--;
	}

	void BidirectionalList::RemoveFromStart(unsigned int Offset) {
		if(Offset == 0)
			PopFront();
		else  {
			if(Nodes[LIST_HEAD]) {
				Node* NodeToRemove = Nodes[LIST_HEAD];
				for(unsigned int I = 0; I < Offset; I++)
					NodeToRemove = NodeToRemove->Nodes[NodeIndex::NEXT];

				Remove(NodeToRemove);
			}
		}
	}

	void BidirectionalList::RemoveFromEnd(unsigned int Offset) {
		if(Offset == 0)
			PopBack();
		else {
			if(Nodes[LIST_TAIL]) {
				Node* Node = Nodes[LIST_TAIL];
				for(unsigned int I = 0; I < Offset; I++)
					Node = Node->Nodes[NodeIndex::PREVIOUS];

				Remove(Node);
			}
		}
	}

	void BidirectionalList::Push(Node* NodeToPush, Node*& At, NodeIndex AtNodeIndex) {
		if(!At) {
			At = NodeToPush;
			if(NodeCount == 1) {
				Nodes[LIST_HEAD]->Nodes[NodeIndex::NEXT] = At;
				Nodes[LIST_TAIL]->Nodes[NodeIndex::PREVIOUS] = Nodes[LIST_HEAD];
			}
		}
		else {
			NodeToPush->Nodes[(AtNodeIndex + 1) % 2] = At;
			At->Nodes[AtNodeIndex] = NodeToPush;
			At = NodeToPush;
		}

		NodeCount++;
	}

	void BidirectionalList::PushFront(void* Data) {
		if(Data) {
			Node* Node = BidirectionalList::NewNode(Data);
			Push(Node, Nodes[LIST_HEAD], NodeIndex::PREVIOUS);
		}
	}

	void BidirectionalList::PushBack(void* Data) {
		if(Data) {
			Node* NodeToPush = BidirectionalList::NewNode(Data);
			NodeIndex AtNodeIndex = NodeCount == 0 ? LIST_HEAD : LIST_TAIL;
			Push(NodeToPush, Nodes[AtNodeIndex], NodeIndex::NEXT);
		}
	}

	void* BidirectionalList::PopFront() {
		if(Nodes[LIST_HEAD]) {
			void* DataToReturn = Nodes[LIST_HEAD]->Data;
			Remove(Nodes[LIST_HEAD]);

			return DataToReturn;
		}

		return nullptr;
	}

	void* BidirectionalList::PopBack() {
		Node* NodeToRemove = nullptr;
		void* DataToReturn = nullptr;

		if(!Nodes[LIST_TAIL] && Nodes[LIST_HEAD]) {
			DataToReturn = Nodes[LIST_HEAD]->Data;
			NodeToRemove = Nodes[LIST_HEAD];
		}
		else {
			DataToReturn = Nodes[LIST_TAIL]->Data;
			NodeToRemove = Nodes[LIST_TAIL];
		}

		Remove(NodeToRemove);
		return DataToReturn;
	}

	void* BidirectionalList::PeekBack() {
		if(!Nodes[LIST_TAIL] && Nodes[LIST_HEAD])
			return Nodes[LIST_HEAD]->Data;
		
		return Nodes[LIST_TAIL]->Data;
	}

	void* BidirectionalList::PeekFront() {
		if(Nodes[LIST_HEAD])
			return Nodes[LIST_HEAD]->Data;
		return nullptr;
	}
}