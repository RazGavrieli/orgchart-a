#include "OrgChart.hpp"
#include "treeNode.hpp"
using namespace ariel;
#include <iostream>
using namespace std;

#include <bits/stdc++.h> // stack

OrgChart::OrgChart() {
    mc = 0;
    size = 1;
    rootNode = nullptr;
}

OrgChart::OrgChart(OrgChart &other) {
    mc = 0;
    size = other.size;
    rootNode = other.rootNode;
}

OrgChart& OrgChart::add_root(std::string new_name) {
    treeNode *newNode = new treeNode(new_name); 

    rootNode = newNode;
    mc++;
    return *this;
}

OrgChart& OrgChart::add_sub(std::string parent_name, std::string new_name) {

    treeNode *parentNode = rootNode->searchFor(parent_name);
    if (parentNode==nullptr) {
        throw std::runtime_error("The wanted name was not found in the tree");
    }
    treeNode *newNode = new treeNode(new_name, parentNode); 
    parentNode->addChild(newNode);
    mc++;
    size++;
    return *this;
}

OrgChart::~OrgChart() {
    for (auto it = begin_reverse_order(); it != reverse_order(); ++it)
    {
        delete ~it;
    }
}

OrgChart& OrgChart::operator=(OrgChart other) {
    mc = 0;
    size = other.size;
    rootNode = other.rootNode;
    return *this;
}

OrgChart::OrgChart(OrgChart&& other) noexcept{
    mc = 0;
    size = other.size;
    rootNode = other.rootNode;

    other.rootNode = nullptr;
    other.mc = 0;
    other.size = 0;
}

OrgChart& OrgChart::operator=(OrgChart&& other) noexcept
{
   if (this != &other)
   {
      // Free the existing resource.
      delete this->rootNode;

      // Copy the data pointer and its length from the
      // source object.
      rootNode = other.rootNode;
      size = other.size;

      // Release the data pointer from the source object so that
      // the destructor does not free the memory multiple times.
      other.rootNode = nullptr;
      other.size = 0;
   }
   return *this;
}

treeNode* OrgChart::getRoot() const{  return rootNode; }
size_t OrgChart::getMc() const {    return mc;}
size_t OrgChart::getSize() const {    return size;}

OrgChart::OrgChartIterator OrgChart::level_iterator(bool order) const{
    // std::vector<treeNode*> orderedNodes;

    // fillBFS(&orderedNodes, this->getRoot()); 
    // std::sort(orderedNodes.begin(), orderedNodes.end(), // C++ LAMBDA EXPRESSION
    // [order](treeNode* const &a, treeNode* const &b) {
    //             if (order) {
    //         return a->getLevel() < b->getLevel(); 
    //     } else {
    //         return a->getLevel() > b->getLevel(); 
    //     }});
    // orderedNodes.push_back(nullptr); // end of the vector que
    // OrgChartIterator iterator(orderedNodes, mc, 0);
    // return iterator;

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
        } else {
            for (size_t i = tempNode->getChildren().size(); i>0; i--) {
                Queue.push(tempNode->getChildren().at(i-1));
            }
        }
    }
    if (!order) {
        std::reverse(orderedNodes.begin(), orderedNodes.end());
    }
    orderedNodes.push_back(nullptr); // end of the vector que
    OrgChartIterator iterator(orderedNodes, mc, 0);
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

OrgChart::OrgChartIterator OrgChart::begin_preorder() const{
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

    orderedNodes.push_back(nullptr); // end of the vector que
    OrgChartIterator iterator(orderedNodes, mc, 0);
    return iterator;
}
OrgChart::OrgChartIterator OrgChart::end_preorder()const {
    return end_iterator();
}

OrgChart::OrgChartIterator OrgChart::end_iterator() const{
    std::vector<treeNode*> dummyVector;
    for (size_t i = 0; i < size; i++)
    {
        dummyVector.push_back(nullptr);
    }
    
    OrgChartIterator iterator(dummyVector, mc, size-1);
    return iterator;
}

OrgChart::OrgChartIterator OrgChart::begin() const{
    return begin_level_order();
}

OrgChart::OrgChartIterator OrgChart::end() const{
    return end_level_order();
}

void OrgChart::fillBFS(std::vector<treeNode*>* orderedTreeNodes, treeNode* currParent) {
    orderedTreeNodes->push_back(currParent);
    if (currParent->getChildren().size()==0) {
        return;
    }
    for (treeNode* currChild : currParent->getChildren())
    {
        fillBFS(orderedTreeNodes, currChild);
    }
}

namespace ariel {
    std::ostream& operator <<(std::ostream& os, OrgChart const& self) {
        /*
            THIS IS OBVIOUSLY TEMPORARY IMPLEMENTATION
        */
            // os << "\tTREE:\n";
            // os << "\t" << self.getRoot()->getName() << "\n";
            // std::vector<treeNode*> level3;
            // for (size_t i = 0; i < self.getRoot()->getChildren().size(); i++)
            // {
            //     os << self.getRoot()->getChildren().at(i)->getName() << "\t";
            //     for (size_t j = 0; j < self.getRoot()->getChildren().at(i)->getChildren().size(); j++)
            //     {
            //         level3.push_back(self.getRoot()->getChildren().at(i)->getChildren().at(j));     
            //     }   
            // }
            // os << "\n";
            // for (size_t i = 0; i < level3.size(); i++)
            // {
            //     os << level3.at(i)->getName() << "\t";
            // }
        /* 
            END OF TEMPORARY IMPLEMENTATION
        */
            size_t last_level = 0;
            for (auto it = self.begin(); it != self.end(); ++it)
            {
                treeNode* currNode = ~it;
                if (currNode->getLevel()!=last_level) {
                    os << "\n";
                }
                last_level = currNode->getLevel();
                os << "\t" << currNode->getName() << "\t";
            }
            
            return os;
    }
}



OrgChart::OrgChartIterator::OrgChartIterator(std::vector<treeNode*> &orderedNodes, size_t const mc, size_t const pos) {
    this->orderedNodes = std::move(orderedNodes);
    this->mc = mc;
    this->currPtr = pos;
}

bool OrgChart::OrgChartIterator::operator != (OrgChart::OrgChartIterator const &other) {
     return !(*this == other);
 }
namespace ariel{
    bool operator == (OrgChart::OrgChartIterator const &lhs, OrgChart::OrgChartIterator const &rhs) {
        return lhs.orderedNodes.at(lhs.currPtr) == rhs.orderedNodes.at(rhs.currPtr);
    }
}
OrgChart::OrgChartIterator& OrgChart::OrgChartIterator::operator ++ (){ // ++Prefix
    if (this->mc!=mc) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    if (currPtr>=orderedNodes.size()-1) {
        throw std::runtime_error("Iterator out of bounds!");
    }
    currPtr++;
    return *this;
}
OrgChart::OrgChartIterator OrgChart::OrgChartIterator::operator ++ (int){ // Postfix++
    if (this->mc!=mc) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    if (currPtr>=orderedNodes.size()-1) {
        throw std::runtime_error("Iterator out of bounds!");
    }
    OrgChartIterator temp = *this;
    currPtr++;
    return temp;
}

std::string OrgChart::OrgChartIterator::operator*() {
    if (this->mc!=mc) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    return orderedNodes.at(currPtr)->getName();
}

treeNode* OrgChart::OrgChartIterator::operator~() {
    if (this->mc!=mc) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    return orderedNodes.at(currPtr);
}
