#include <vector>
#include <iostream>
#include "treeNode.hpp"

namespace ariel {


    class OrgChart {
        treeNode *rootNode;

        public:
            OrgChart add_root(std::string); // may return and get pointers\references
            OrgChart add_sub(std::string, std::string); // may return and get pointers\references

            friend std::ostream& operator << (std::ostream& , OrgChart const &); // output 
            /* --- getters --- */
                treeNode* getRoot() const;
    };


}