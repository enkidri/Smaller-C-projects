#ifndef LinkedList
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#define LinkedList

class List 
{
    public:
        void insert(int integer);
        void remove(int index);
        int at(int index) const;
        void print() const;
        ~List(); // destructor
        List(std::initializer_list<int> list); // constructur
        List(List const& other); // COPY list
        List (List&& other); // MOVE
        List& operator = (List const& other); // COPY med  =
        List& operator = (List&& other); // move med =
        bool is_empty() const;
        int get_size() const;
        std::string stringify() const; 

    private:
        struct Node
        {
            int value{}; 
            Node* next_node {}; 

        };
        int size{};
        Node* first_node{};
        void print_helper(Node* const node) const;
    
};

#endif
