#include "LinkedList.h"
#include <initializer_list>
using namespace std;

List :: List(std::initializer_list<int> list)
{
    first_node = nullptr;
    for (int i: list)
    {
        this -> insert(i);
    }
}

List :: ~List()
{

    Node* tmp{first_node};
    int total_length = this -> get_size();
    if (first_node != nullptr)
    {
        for (int i = 0; i < total_length; i++)
        {
            this -> remove(0);
        }
    }
}

List :: List(List const& other) //Copy constructor
{
    Node* current{other.first_node};
    int current_value{};
    while (current != nullptr)
    {
        current_value = current -> value;
        this -> insert(current_value);
        current = current -> next_node;
    }
}
List :: List (List&& other) //move constructor
{
    first_node = other.first_node;
    size = other.size;
    other.first_node = nullptr;
}

List& List::operator=(List const& other) //copy assigment
{
    List list_copy{other};
    List tmp{};
    tmp.size = size;
    tmp.first_node = first_node;

    first_node = list_copy.first_node;
    list_copy.first_node = nullptr;

    return *this;
}

List& List::operator = (List&& other) //Move assignment
{
    List temp{};
    temp.first_node = first_node; //Låter den gamla listan gå out-of-scope
    temp.size = size; 
    first_node = other.first_node;
    other.first_node = nullptr;
    size = other.size;

    return *this;
}


int List :: get_size() const
{
    return size;
}

void List::insert(int integer)
{
    ++size;
    Node* tmp{new Node{integer}};
    if ((first_node == nullptr) || (first_node -> value >= integer)) //Sätt in första värdet eller lägg längst fram i listan
    {
        tmp -> next_node = first_node;
        first_node = tmp;
    }
    else 
    {
        Node* next{first_node};
        Node* current{first_node};
        while((integer > (next -> value))) //Itererar till rätt position i listan.
        {   
            current = next;
            next = next -> next_node;
            if (next == nullptr)
            {
                break;
            }
        }
        if (next == nullptr) //Sätt in noden genom att flytta på pekare
        {
            current -> next_node = tmp;
        }
        else
        {
            tmp -> next_node = next;
            current -> next_node = tmp;
        }
    }
}

bool List::is_empty() const
{
    if (first_node == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void List::print() const
{
    if (!((*this).is_empty()))   
    {
        cout << "[";
        print_helper(first_node);
        cout << "]";   
    }

}
void List::print_helper(Node* const node) const
{
    if (node != nullptr)
    {
        cout << to_string(node -> value);
        if (node -> next_node != nullptr){cout << ", ";}
        print_helper(node -> next_node);
    }
}


void List :: remove(int index) 
{
    int counter{};
    Node* current{first_node};
    Node* next{first_node};
    Node* tmp{};
    --size;

    if (index == 0)  
    {
        tmp = next -> next_node;
        delete next;
        first_node  = tmp;
    }
    else 
    {
        while (counter < index) 
        {
            current = next;
            next = next -> next_node;
            ++counter;
        }

        tmp = next -> next_node; 
        delete next;
        current -> next_node = tmp;

    }
}

int List :: at(int index) const
{
    int counter{};
    Node* current{first_node};
    while (counter < index) // loopar genom listan till rätt plats
    {
        current = current -> next_node;
        ++counter;
    }
    return current -> value; 

}

string List::stringify() const
{
    int current_val{};
    string list_string{"["};
    for (int val=0; val<size; val++)
    {
        current_val = this -> at(val);
        if (val==size-1)
        {
            list_string = list_string + to_string(current_val);
            break;
        }
        list_string = list_string + to_string(current_val) + ", ";
    }
    list_string = list_string + "]";

    return list_string;
}












