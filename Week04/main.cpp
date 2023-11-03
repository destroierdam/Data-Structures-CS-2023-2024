#include <iostream>
#include <utility>

struct Node {
    int data;
    Node* next;
};

void printList(Node *first){
    while(first != nullptr){
        std::cout << first->data << " -> ";
        first = first->next;
    }
    std::cout <<"nullptr\n";
}



Node* findMiddle(Node* head) {
    Node *slow = head, *fast = head;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
    }

    return slow;
}

void makeRange(int beginData, int endData, Node*& first, Node*& last) {
    Node * rangeBegin = new Node{beginData, nullptr};
    Node * cur = rangeBegin;
    for(int i = beginData + 1; i < endData; i++){
        cur->next = new Node{i, nullptr};
        cur = cur->next;
    }
    first = rangeBegin;
    last = cur;
}

void fillGaps(Node *first){
    if(first == nullptr || first->next == nullptr){
        return;
    }
    while(first->next != nullptr){
        if(first->data < first->next->data - 1) {
            Node *rangeBegin, *rangeEnd;
            makeRange(first->data + 1, first->next->data, rangeBegin, rangeEnd);
            rangeEnd->next = first->next;
            first->next = rangeBegin;
            first = rangeEnd;
        } else{
            first = first->next;
        }
    }
}



int main() {
    Node* list1 = new Node {1, new Node {5, new Node {6, new Node {11, nullptr}}}}; 
    fillGaps(list1);
    printList(list1);
    //std::cout << findMiddle(list1)->data << std::endl;
    // delete (std::exchange(list1, list1->next));
    // list1 = list1->next;
    //std::cout << findMiddle(list1->next)->data << std::endl;
    //std::cout << findMiddle(list1)->data << std::endl;

    return 0;
}