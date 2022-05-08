#include <vector>
#include <iostream>
#include "treeNode.hpp"

class OrgChartIterator;
namespace ariel {


    class OrgChart {
        treeNode *rootNode;
        size_t mc;
        size_t size;
        public:
            OrgChart();
            OrgChart& add_root(std::string); // may return and get pointers\references
            OrgChart& add_sub(std::string, std::string); // may return and get pointers\references
            OrgChartIterator begin_level_order();
            OrgChartIterator end_level_order();

            OrgChartIterator begin_reverse_order();
            OrgChartIterator reverse_order(); // end_reverse_order

            OrgChartIterator begin_preorder();
            OrgChartIterator end_preorder();

            void fillBFS(std::vector<treeNode*>*, treeNode*);

            friend std::ostream& operator << (std::ostream& , OrgChart const &); // output 
            /* --- getters --- */
            treeNode* getRoot() const;
            size_t getMc() const;
            size_t getSize() const;
    };
}

class OrgChartIterator {
    size_t currPtr;
    size_t mc;
    std::vector<treeNode*> orderedNodes;
    ariel::OrgChart* organizationChart;

    public:
        OrgChartIterator(std::vector<treeNode*> &, size_t const, ariel::OrgChart*);
        OrgChartIterator(std::vector<treeNode*> &, size_t const, ariel::OrgChart*, size_t const);
        bool operator != (OrgChartIterator const &other);
        friend bool operator == (OrgChartIterator const &lhs, OrgChartIterator const &rhs);

        OrgChartIterator& operator ++ (); // ++Prefix
        OrgChartIterator operator ++ (int); // Postfix++

        treeNode operator*();

};