#include "OrgChart.hpp"
#include "treeNode.hpp"
using namespace ariel;
#include <iostream>
using namespace std;


OrgChart::OrgChart() {
    mc = 0;
    size = 0;
    rootNode = nullptr;
}

OrgChart::OrgChart(OrgChart &other) {
    mc = 0;
    size = other.size;
    rootNode = other.rootNode;
}

OrgChart& OrgChart::add_root(std::string new_name) {
    /**
     * @brief Creates a new root for the Organization Chart with the given @param new_name.
     * If the root already exists, only change it's name using setName treeNode's setter. 
     */
    if (rootNode != nullptr) {
        rootNode->setName(new_name);
        return *this;
    }
    treeNode *newNode = new treeNode(new_name); 
    rootNode = newNode;
    mc++;
    size++;
    return *this;
}

OrgChart& OrgChart::add_sub(std::string parent_name, std::string new_name) {
    /**
     * @brief Add subordinate to a given parent name of node. 
     * If the parent name was not found in the tree throw an exception. 
     */
    if (rootNode==nullptr) {
        throw std::runtime_error("The tree has no root!");
    }
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
    /**
     * @brief Destructor for the Organization Chart. Only the nodes themselfs are on the heap.
     * Iterate through the nodes in a reverse order and delete them from the heap.
     */
    if (this->rootNode==nullptr) {
        return;
    }
    for (auto it = begin_reverse_order(); it != reverse_order(); ++it)
    {
        delete ~it;
    }
}

OrgChart& OrgChart::operator=(OrgChart const &other) {
    if(this == &other) {
      return *this;
    }
    mc = other.mc;
    size = other.size;
    rootNode = other.rootNode;
    return *this;
}

namespace ariel {
    std::ostream& operator <<(std::ostream& os, OrgChart const& self) {
            size_t last_level = 0;
            for (auto it = self.begin(); it != self.end(); ++it)
            {
                treeNode* currNode = ~it;
                if (currNode->getLevel()!=last_level) {
                    os << "\n";
                }
                last_level = currNode->getLevel();
                os << " " << currNode->getName() << " ";
            }
            
            return os;
    }
}

treeNode* OrgChart::getRoot() const{  return rootNode; }
size_t OrgChart::getMc() const {    return mc;}
size_t OrgChart::getSize() const {    return size;}

