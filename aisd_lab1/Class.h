#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

class List {
public:
    List();
    ~List();
    void push_back(int newnumber);
    void push_front(int newnumber);
    void pop_back();
    void pop_front();
    void insert(int newnumber, size_t index);
	void remove(size_t index);
	void clear();
    bool contains(int number);
    int get_elem(size_t index);
    size_t get_size();
    void set(size_t index, int newnumber);
    bool isEmpty();
    void push_front(List newlist);
    void save_list();
    List& operator=(List Listnum);
    friend ostream& operator<< (ostream& out, const List& list);
private:
    class Node {
    public:
        int number;
        class Node* next;
        Node(int newnumber = 0, Node* next = nullptr) {
            this->next = next;
            this->number = newnumber;
        }
        ~Node() {};
    };
    Node* head;

    size_t size;
    size_t savesize;
};


class Map {
public:
	~Map();
	void insert(int key, int value);
	void remove(int key);

	int find(int key);

	List get_keys();
	List get_values();

	void clear();
	void print();
private:
	class Node {
	public:
		int key, value;
		bool isblack;

		Node* left;
		Node* right;
		Node* parent;
		Node(int newkey, int newvalue, bool newcolor = false, Node* newparent = nullptr, Node* newleft = nullptr, Node* newright = nullptr) {
			this->key = newkey;
			this->value = newvalue;
			this->isblack = newcolor;
			this->left = newleft;
			this->right = newright;
			this->parent = newparent;
		}
	};
	Node* head = nullptr;
	int count = 0;
	Node* nill = new Node(0, 0, true);

	void left_turn(Node* swivel);
	void right_turn(Node* swivel);
	List get_keys_or_value(bool iskeys);
};