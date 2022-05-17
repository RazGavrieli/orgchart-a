    #pragma once
    
    #include <vector>
    #include <iostream>
    
    class treeNode {
        treeNode *parentNode;
        std::vector<treeNode*> childNodes;

        std::string name;
        size_t level; // as in parent.level + 1

        public:
        /* --- constructors --- */
            treeNode(std::string &, treeNode*); 
            treeNode(std::string &);
            //~treeNode();
        /* --- getters --- */
            std::string getName() const;
            const std::string* getNamePtr() const;
            size_t getLevel() const;
            treeNode* getParent() const;
            std::vector<treeNode*> getChildren() const;
            size_t size() const;

        /* --- setters --- */
            void addChild(treeNode *); 
            void setName(std::string &);

        /* --- functions --- */
            treeNode* searchFor(std::string &);
            friend std::ostream& operator << (std::ostream& , treeNode const &);
    };