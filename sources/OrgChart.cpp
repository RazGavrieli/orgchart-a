#include "OrgChart.hpp"
#include "treeNode.hpp"
using namespace ariel;
#include <iostream>
using namespace std;



OrgChart OrgChart::add_root(std::string new_name) {
    treeNode *newNode = new treeNode(new_name); // consider using new? 
    rootNode = newNode;
    return *this;
}

OrgChart OrgChart::add_sub(std::string parent_name, std::string new_name) {
    treeNode *parentNode = rootNode->searchFor(parent_name);
    if (parentNode==nullptr) {
        throw std::runtime_error("The wanted name was not found in the tree");
    }
    treeNode *newNode = new treeNode(new_name, parentNode); // consider using new?
    parentNode->addChild(newNode);
    return *this;
}

treeNode* OrgChart::getRoot() const{  return rootNode; }

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
            
            
            return os;
    }
}

