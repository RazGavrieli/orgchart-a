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
            const size_t *currMc;

            public:
                    /* --- constructors\destructors --- */
                OrgChartIterator(std::vector<treeNode*> &, const size_t*, size_t);

                    /* --- operators --- */
                bool operator != (OrgChartIterator const &other);
                friend bool operator == (OrgChartIterator const &lhs, OrgChartIterator const &rhs);
    
                OrgChartIterator& operator ++ (); 
                OrgChartIterator operator ++ (int); 
                std::string operator*() const; /* This would return a reference if we wanted to make modifications. 
                                due to the tests being unpreditable I have to return a string type and not a node. */
                treeNode* operator~();   /* This is what operator* would be if the tests were predictable. */
                std::string const * operator->() const; 
                

        };// END OF NESTED CLASS
        // CLASS OrgChart:
        private:
        treeNode *rootNode;
        size_t mc;
        size_t size;
        size_t maxLevel;
        public:
                /* --- constructos\destructors --- */
            OrgChart(); // deafult constructor
            OrgChart(OrgChart &); // copy constructor
            OrgChart(OrgChart &&) = default; // move constructor
            ~OrgChart(); // destructor

                /* --- operators --- */
            OrgChart& operator=(OrgChart);
            OrgChart& operator=(OrgChart&&) = default; // move assigemnt operator
            friend std::ostream& operator << (std::ostream& , OrgChart const &); // output 

                /* --- functions --- */
            OrgChart& add_root(std::string); 
            OrgChart& add_sub(std::string, std::string); 

            OrgChartIterator begin() const;
            OrgChartIterator end() const;

            OrgChartIterator begin_level_order() const;
            OrgChartIterator end_level_order() const;

            OrgChartIterator begin_reverse_order() const;
            OrgChartIterator reverse_order() const; 

            OrgChartIterator begin_preorder() const;
            OrgChartIterator end_preorder() const;

            OrgChartIterator end_iterator() const; 
            OrgChartIterator level_iterator(bool) const;

            //void fillBFS(std::vector<treeNode*>*, treeNode*);  // USED ONLY IF THE TESTS WILL BE TOO SPECIFIC
 
                /* --- getters --- */
            treeNode* getRoot() const;
            size_t getMc() const;
            size_t getSize() const;   
    };
}

