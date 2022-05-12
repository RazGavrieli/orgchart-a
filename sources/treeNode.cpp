#include "treeNode.hpp"
#include <iostream>

treeNode::treeNode(std::string &new_name, treeNode* new_parent) {
    name = std::move(new_name);
    parentNode = new_parent;
    level = new_parent->getLevel()+1;
}

treeNode::treeNode(std::string &new_name) {
    name = std::move(new_name);
    parentNode = nullptr;
    level = 0;
}

// treeNode::~treeNode() {
//     for (size_t i = 0; i < childNodes.size(); i++)
//     {
//         delete childNodes.at(i);
//     }
// }

std::string treeNode::getName() const { return name;}
size_t treeNode::getLevel() const { return level;}
treeNode* treeNode::getParent() const { return parentNode;}
std::vector<treeNode*> treeNode::getChildren() const { return childNodes;}
size_t treeNode::size() const { return name.size();}

void treeNode::addChild(treeNode * new_node) {
    if (new_node->getParent()!=this) {
        throw std::runtime_error("Can't add new_node to this node because it not it's child node.");
    }
    childNodes.push_back(new_node);
}

void treeNode::setName(std::string & new_name) {
    name = std::move(new_name);
}

treeNode* treeNode::searchFor(std::string & name) {
    if (getName() == name) {
        return this;
    }
    treeNode* res = nullptr;
    for (treeNode* currChild : getChildren())
    {
        res = currChild->searchFor(name);
        if (res != nullptr) {
            return res;
        }
    }
    return res;
}


std::ostream& operator << (std::ostream& os, treeNode const & self) {
    os << self.getName();
    return os;
}
