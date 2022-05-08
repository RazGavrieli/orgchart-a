#include "OrgChart.hpp"
#include "treeNode.hpp"
using namespace ariel;
#include <iostream>
using namespace std;

OrgChart::OrgChart(){
    mc = 0;
    size = 1;
    rootNode = nullptr;
}

OrgChart& OrgChart::add_root(std::string new_name) {
    treeNode *newNode = new treeNode(new_name); // consider using new? 
    rootNode = newNode;
    mc++;
    return *this;
}

OrgChart& OrgChart::add_sub(std::string parent_name, std::string new_name) {
        mc++;
    size++;
    treeNode *parentNode = rootNode->searchFor(parent_name);
    if (parentNode==nullptr) {
        throw std::runtime_error("The wanted name was not found in the tree");
    }
    treeNode *newNode = new treeNode(new_name, parentNode); // consider using new?
    parentNode->addChild(newNode);

    return *this;
}

treeNode* OrgChart::getRoot() const{  return rootNode; }
size_t OrgChart::getMc() const {    return mc;}
size_t OrgChart::getSize() const {    return size;}

OrgChartIterator OrgChart::begin_level_order() {
    std::vector<treeNode*> orderedNodes;
    /* 
    BFS MAGIC 
    */
    fillBFS(&orderedNodes, this->getRoot()); // DOES NOT WORK WELL
    orderedNodes.push_back(nullptr); // end of the vector sign
    OrgChartIterator iterator(orderedNodes, mc, this);
    return iterator;
}
OrgChartIterator OrgChart::end_level_order() {
    std::vector<treeNode*> orderedNodes;
    for (size_t i = 0; i < size; i++)
    {
        orderedNodes.push_back(nullptr);
    }
    
    OrgChartIterator iterator(orderedNodes, mc, this, size-1);
    return iterator;
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
            os << "\tTREE:\n";
            os << "\t" << self.getRoot()->getName() << "\n";
            std::vector<treeNode*> level3;
            for (size_t i = 0; i < self.getRoot()->getChildren().size(); i++)
            {
                os << self.getRoot()->getChildren().at(i)->getName() << "\t";
                for (size_t j = 0; j < self.getRoot()->getChildren().at(i)->getChildren().size(); j++)
                {
                    level3.push_back(self.getRoot()->getChildren().at(i)->getChildren().at(j));     
                }   
            }
            os << "\n";
            for (size_t i = 0; i < level3.size(); i++)
            {
                os << level3.at(i)->getName() << "\t";
            }
            /* 
            END OF TEMPORARY IMPLEMENTATION
            */
            return os;
    }
}

OrgChartIterator::OrgChartIterator(std::vector<treeNode*> &orderedNodes, size_t const mc, OrgChart* organizationChart) {
    this->orderedNodes = std::move(orderedNodes);
    this->mc = mc;
    this->organizationChart = organizationChart;
    this->currPtr = 0;
}

OrgChartIterator::OrgChartIterator(std::vector<treeNode*> &orderedNodes, size_t const mc, OrgChart* organizationChart, size_t const pos) {
    this->orderedNodes = std::move(orderedNodes);
    this->mc = mc;
    this->organizationChart = organizationChart;
    this->currPtr = pos;
}

bool OrgChartIterator::operator != (OrgChartIterator const &other) {
     return !(*this == other);
 }

bool operator == (OrgChartIterator const &lhs, OrgChartIterator const &rhs) {
    return lhs.orderedNodes.at(lhs.currPtr) == rhs.orderedNodes.at(rhs.currPtr);
}

OrgChartIterator& OrgChartIterator::operator ++ (){ // ++Prefix
    if (mc!=organizationChart->getMc()) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    currPtr++;
    return *this;
}
OrgChartIterator OrgChartIterator::operator ++ (int){ // Postfix++
    if (mc!=organizationChart->getMc()) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    OrgChartIterator temp = *this;
    currPtr++;
    return temp;
}

treeNode OrgChartIterator::operator*() {
    if (mc!=organizationChart->getMc()) {
        throw std::runtime_error("Organizaion chart has been changed since iterator creation");
    }
    return *orderedNodes.at(currPtr);
}
