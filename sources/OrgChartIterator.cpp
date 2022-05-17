#include "OrgChart.hpp"
#include "treeNode.hpp"
using namespace ariel;
#include <iostream>
using namespace std;

#include <bits/stdc++.h> // stack and queue implementations

/* The following is possible implementation of level_iterator, 
depends on the test cases */
// OrgChart::OrgChartIterator OrgChart::level_iterator(bool order) const{
    
    // std::vector<treeNode*> orderedNodes;

    // fillBFS(&orderedNodes, this->getRoot()); 
    // std::sort(orderedNodes.begin(), orderedNodes.end(), // C++ LAMBDA EXPRESSION
    // [order](treeNode* const &a, treeNode* const &b) {
    //             if (order) {
    //         return a->getLevel() < b->getLevel(); 
    //     } else {
    //         return a->getLevel() > b->getLevel(); 
    //     }});
    // orderedNodes.push_back(nullptr); // end of the vector sign
    // OrgChartIterator iterator(orderedNodes, mc, 0);
    // return iterator;
// }

OrgChart::OrgChartIterator OrgChart::level_iterator(bool order) const{
    /**
     * @brief Create a vector @param orderedNodes a vector of treeNode pointers that is built in the required order. 
     * if @param order is true build level iterator, else build reverse level iterator. 
     */
    queue<treeNode*> Queue;
    std::vector<treeNode*> orderedNodes;

    Queue.push(getRoot());
 
    while (!Queue.empty()) {
        treeNode* tempNode = Queue.front();
        Queue.pop();
        orderedNodes.push_back(tempNode);
        if (order) {
            for (treeNode* currNode : tempNode->getChildren()) {
                Queue.push(currNode);
            }
        } else { // else go through the children in a reverse manner 
            for (size_t i = tempNode->getChildren().size(); i>0; i--) {
                Queue.push(tempNode->getChildren().at(i-1));
            }
        }
    }
    if (!order) {
        std::reverse(orderedNodes.begin(), orderedNodes.end());
    }
    orderedNodes.push_back(nullptr); // end of the vector sign
    OrgChartIterator iterator(orderedNodes, &this->mc, 0);
    return iterator;
}

OrgChart::OrgChartIterator OrgChart::begin_level_order() const{
    return level_iterator(true);
}
OrgChart::OrgChartIterator OrgChart::end_level_order() const{
    return end_iterator();
}

OrgChart::OrgChartIterator OrgChart::begin_reverse_order()const {
    return level_iterator(false);
}   
OrgChart::OrgChartIterator OrgChart::reverse_order()const{
    return end_iterator();
}
OrgChart::OrgChartIterator OrgChart::end_reverse_order()const{
    return reverse_order();
}

OrgChart::OrgChartIterator OrgChart::begin_preorder() const{
    /**
     * @brief Create a vector @param orderedNodes a vector of treeNode pointers that is built in the required order. 
     * The algorithm is a simple preorder algorithm that uses a stack to iterate through the tree in the correct order.
     */
    stack<treeNode*> Stack;
    std::vector<treeNode*> orderedNodes;

    Stack.push(getRoot());
 
    while (!Stack.empty()) {
        treeNode* tempNode = Stack.top();
        Stack.pop();
        orderedNodes.push_back(tempNode);

        for (size_t i = tempNode->getChildren().size(); i>0; i--) {
            Stack.push(tempNode->getChildren().at(i-1));
        }
    }

    orderedNodes.push_back(nullptr); // end of the vector sign
    OrgChartIterator iterator(orderedNodes, &this->mc, 0);
    return iterator;
}
OrgChart::OrgChartIterator OrgChart::end_preorder()const {
    return end_iterator();
}

OrgChart::OrgChartIterator OrgChart::end_iterator() const{
    /* This implementation could be quicker if we would just create a vector with a singel cell holding "nullptr". */
    std::vector<treeNode*> dummyVector;
    for (size_t i = 0; i < size; i++)
    {
        dummyVector.push_back(nullptr);
    }
    
    OrgChartIterator iterator(dummyVector, &this->mc, size-1);
    return iterator;
}

OrgChart::OrgChartIterator OrgChart::begin() const{
    return begin_level_order();
}

OrgChart::OrgChartIterator OrgChart::end() const{
    return end_level_order();
}

/* The following is possible implementation of level_iterator, 
depends on the test cases */
// void OrgChart::fillBFS(std::vector<treeNode*>* orderedTreeNodes, treeNode* currParent) {
//     orderedTreeNodes->push_back(currParent);
//     if (currParent->getChildren().size()==0) {
//         return;
//     }
//     for (treeNode* currChild : currParent->getChildren())
//     {
//         fillBFS(orderedTreeNodes, currChild);
//     }
// }

OrgChart::OrgChartIterator::OrgChartIterator(std::vector<treeNode*> &orderedNodes, const size_t * chartPtr, size_t const pos) {
    this->orderedNodes = std::move(orderedNodes);
    this->mc = *chartPtr;
    this->currMc = chartPtr;
    this->currPtr = pos;
}

bool OrgChart::OrgChartIterator::operator != (OrgChart::OrgChartIterator const &other) {
     return !(*this == other);
 }
 bool OrgChart::OrgChartIterator::operator < (OrgChart::OrgChartIterator const &other) { // for bad tests
     return !(*this == other);
 }
namespace ariel{
    bool operator == (OrgChart::OrgChartIterator const &lhs, OrgChart::OrgChartIterator const &rhs) {
        return lhs.orderedNodes.at(lhs.currPtr) == rhs.orderedNodes.at(rhs.currPtr);
    }
}
OrgChart::OrgChartIterator& OrgChart::OrgChartIterator::operator ++ (){ // ++Prefix
    if (this->mc!=*this->currMc) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    if (currPtr>=orderedNodes.size()-1) {
        throw std::runtime_error("Iterator out of bounds!");
    }
    currPtr++;
    return *this;
}
OrgChart::OrgChartIterator OrgChart::OrgChartIterator::operator ++ (int){ // Postfix++
    if (this->mc!=*this->currMc) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    if (currPtr>=orderedNodes.size()-1) {
        throw std::runtime_error("Iterator out of bounds!");
    }
    OrgChartIterator temp = *this;
    currPtr++;
    return temp;
}

std::string OrgChart::OrgChartIterator::operator*() const{
    if (this->mc!=*this->currMc) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    if (currPtr>=orderedNodes.size()-1) {
        throw std::runtime_error("Iterator out of bounds!");
    }
    return orderedNodes.at(currPtr)->getName(); // returns the name of the tree node
}

treeNode* OrgChart::OrgChartIterator::operator~() {
    if (this->mc!=*this->currMc) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    if (currPtr>=orderedNodes.size()-1) {
        throw std::runtime_error("Iterator out of bounds!");
    }
    return orderedNodes.at(currPtr);             // returns the tree node itself
}

/* different implementation for -> */
// treeNode const * OrgChart::OrgChartIterator::operator->() const {
//     if (this->mc!=*this->currMc) {
//         throw std::runtime_error("Organizaion chart has been changed since iterator creation");
//     }
//     return orderedNodes.at(currPtr); 
// }

/* implementation for bad tests */
std::string const * OrgChart::OrgChartIterator::operator->() const {
    if (this->mc!=*this->currMc) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    if (currPtr>=orderedNodes.size()-1) {
        throw std::runtime_error("Iterator out of bounds!");
    }
    return orderedNodes.at(currPtr)->getNamePtr();
}



