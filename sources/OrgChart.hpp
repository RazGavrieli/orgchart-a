#include <vector>
#include <iostream>
#include "treeNode.hpp"

namespace ariel {


    class OrgChart {
        public:
        class OrgChartIterator { // NESTED CLASS
            size_t currPtr;
            size_t mc;
            std::vector<treeNode*> orderedNodes;

            public:
                OrgChartIterator(std::vector<treeNode*> &, size_t, size_t);

                bool operator != (OrgChartIterator const &other);
                friend bool operator == (OrgChartIterator const &lhs, OrgChartIterator const &rhs);
                
                OrgChartIterator& operator ++ (); // ++Prefix
                OrgChartIterator operator ++ (int); // Postfix++
                std::string operator*();
                treeNode* operator~();
                treeNode operator->();

        };                      // END OF NESTED CLASS
        // CLASS OrgChart:
        private:
        treeNode *rootNode;
        size_t mc;
        size_t size;
        size_t maxLevel;
        public:
            OrgChart(); // deafult constructor
            OrgChart(OrgChart &); // copy constructor
            OrgChart(OrgChart &&) noexcept; // move constructor
            OrgChart& add_root(std::string); 
            OrgChart& add_sub(std::string, std::string); 
            ~OrgChart(); // destructor

            OrgChart& operator=(OrgChart);
            OrgChart& operator=(OrgChart&&) noexcept; // move assigemnt operator


            OrgChartIterator begin() const;
            OrgChartIterator end() const;

            OrgChartIterator begin_level_order() const;
            OrgChartIterator end_level_order() const;

            OrgChartIterator begin_reverse_order() const;
            OrgChartIterator reverse_order() const; // end_reverse_order

            OrgChartIterator begin_preorder() const;
            OrgChartIterator end_preorder() const;

            OrgChartIterator end_iterator() const; 
            OrgChartIterator level_iterator(bool) const;

            friend std::ostream& operator << (std::ostream& , OrgChart const &); // output 
            
            /* --- getters --- */
            treeNode* getRoot() const;
            size_t getMc() const;
            size_t getSize() const;

            void fillBFS(std::vector<treeNode*>*, treeNode*); // bfs search over the tree
            
    };
}

