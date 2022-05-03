#include "Class.h" 

List::List() {
    size = 0;
    head = nullptr;
}

List::~List() {
    clear();
}

void List::push_back(int newnumber) {
    if (!head) head = new Node(newnumber); 
    else {
        Node* current = head;
        while (current->next) current = current->next; 
        current->next = new Node(newnumber); 
    }
    size++;
    savesize = size;
}

void List::push_front(int newnumber) {
    if (!head) head = new Node(newnumber); 
    else {
        Node* first = new Node(newnumber); 
        first->next = head; 
        head = first; 
    }
    size++;
    savesize = size;
}

void List::pop_back() {
    if (head) {
        Node* current = head, * previous = nullptr;
        while (current->next)
        {
            previous = current; 
            current = current->next; 
        }
        delete current; 
        current = nullptr;
        if (previous) previous->next = current;
        else head = nullptr;
        size--;
        savesize = size;
    }
}

void List::pop_front() {
    if (head) {
        Node* current = head->next;
        delete head;
        head = current;
        size--;
        savesize = size;
    }
}

void List::insert(int newnumber, size_t index) {
    if (size >= index + 1) {
        Node* current = head;
        if (!index) push_front(newnumber); 
        else
        {
            for (size_t i = 1; i < index; i++, current = current->next); 
            Node* newelem = new Node(newnumber); 
            newelem->next = current->next; 
            current->next = newelem;
            size++;
            savesize = size;
        }
    }
}

bool List::contains(int number) {
    Node* current = head;
    while (current) {
        if (current->number == number)
            return true;
        current = current->next;
    }
    return false;
}

int List::get_elem(size_t index) {
    if (size >= index + 1) {
        Node* current = head;
        for (size_t i = 0; i < index; i++, current = current->next); 
        return current->number; 
    }
    else
        throw out_of_range("Error! Index is entered incorrectly"); 
}

void List::remove(size_t index) {
    if (size >= index + 1) {
        if (index == 0) pop_front();
        else if (index + 1 == size) pop_back(); 
        else {
            Node* current = head, * next;
            for (size_t i = 1; i < index - 1; i++, current = current->next); 
            next = current->next;
            current->next = next->next;
            delete next;
            next = nullptr;
            size--;
            savesize = size;
        }
    }
}

size_t List::get_size() {
    return size;
}

void List::clear() {
    while (size && head) pop_front();
}

void List::set(size_t index, int newnumber) {
    if (size >= index + 1) {
        Node* current = head;
        for (size_t i = 0; i < index; i++, current = current->next); 
        current->number = newnumber;
    }
}

bool List::isEmpty() {
    return head == nullptr;
}

ostream& operator<< (ostream& out, const List& list) {
    List current;
    current.head = list.head;
    while (current.head) {
        out << current.head->number;
        if (current.head->next) out << ',';
        current.head = current.head->next;
    }
    current.size = 0;  
    return out;
}

void List::push_front(List newlist) {
    if (newlist.head) {
        Node* current = newlist.head;
        List main;
        while (current) {
            main.push_back(current->number);
            current = current->next;
        }
        current = head;
        while (current) {
            main.push_back(current->number);
            current = current->next;
        }
        clear(); 
        head = main.head;
        size = main.size;
        savesize = size;
        main.size = 0; 
        newlist.size = 0; 
    }
}

void List::save_list()
{
    size = 0;
}

List& List::operator=(List list)
{
    this->head = list.head;
    list.head = nullptr;
    this->size = list.savesize;
    this->savesize = list.savesize;
    list.size = 0;
    return *this;
}


Map::~Map() {
	clear();
	delete nill;
	nill = nullptr;
}

void Map::insert(int newkey, int newvalue) {
	Node* current = head;
	count++;
	if (!head) {
		head = new Node(newkey, newvalue, true);
		head->left = nill;
		head->right = nill;
	}
	else {
		while (true) if (newkey > current->key && current != nill) {
			if (current->right && current->right != nill)
				current = current->right;
			else {
				current->right = new Node(newkey, newvalue);
				current->right->parent = current;
				current = current->right;
				current->left = nill;
				current->right = nill;
				break;
			}
		}
		else if ((newkey != current->key && current != nill) || (newkey == current->key && current == nill)) {
			if (current->left && current->left != nill)
				current = current->left;
			else {
				current->left = new Node(newkey, newvalue);
				current->left->parent = current;
				current = current->left;
				current->left = nill;
				current->right = nill;
				break;
			}
		}
		else throw std::invalid_argument("Error! Keys must be different!!");
		while (current->parent)
			if (current->parent->parent && !current->parent->isblack) {
				if (current->parent->parent->left == current->parent) {
					if (current->parent->parent->right)
						if (!current->parent->parent->right->isblack) {
							current->parent->isblack = true;
							current->parent->parent->right->isblack = true;
							current->parent->parent->isblack = false;
							current = current->parent->parent;
						}
					if (current->parent) {
						if (current->parent->isblack)
							break;
						if (current == current->parent->right) {
							left_turn(current);
							current = current->left;
						}
						if (current->parent->isblack)
							break;
						if (current->parent->parent) {
							current->parent->isblack = true;
							current->parent->parent->isblack = false;
							right_turn(current->parent);
						}
					}
				}
				else if (current->parent == current->parent->parent->right) {
					if (!current->parent->parent->left->isblack) {
						current->parent->parent->left->isblack = true;
						current->parent->parent->right->isblack = true;
						current->parent->parent->isblack = false;
						current = current->parent->parent;
					}
					else if (current->parent->left == current) {
						right_turn(current);
						current = current->left;
						current->isblack = true;
						current->parent->isblack = false;
						left_turn(current->parent);
					}
				}
			}
			else break;
		while (current->parent)
			current = current->parent;
		head = current;
		head->isblack = true;
	}
}

void Map::remove(int key) {
	Node* current = head, * remove;
	Node* currentforbalance = nullptr;
	bool isblackremove = false;
	count--;
	if (current) while (current->key != key && current != nill)
	{
		if (key > current->key) {
			current = current->right;
			continue;
		}
		else if (key < current->key) {
			current = current->left;
			continue;
		}
	}
	if (!current)
		throw std::invalid_argument("Error! Array is empty!!!!");
	else if (current == nill) throw std::invalid_argument("Error! Key not found!!!");
	if (current != nill) {
		remove = current;
		isblackremove = remove->isblack;
		if (current->right == nill && current->left == nill) {
			if (current->parent) {
				current = current->parent;
				if (current->left == remove)
					current->left = nill;
				else
					current->right = nill;
				nill->parent = current;
				currentforbalance = nill;
				delete remove;
			}
			else {
				delete head;
				head = nullptr;
				current = head;
				isblackremove = false;
			}
		}
		else if (current->left == nill && current->right) {
			currentforbalance = current->right;
			if (current->parent) {
				current = current->parent;
				if (current->left == remove) {
					current->left = remove->right;
					current->left->parent = current;
				}
				else {
					current->right = remove->right;
					current->right->parent = current;
				}
				delete remove;
			}
			else {
				head = head->right;
				delete remove;
				head->parent = nullptr;
				current = head;
				current->isblack = true;
			}
		}
		else if (current->right == nill && current->left) {
			currentforbalance = current->left;
			if (current->parent) {
				current = current->parent;
				if (current->left == remove) {
					current->left = remove->left;
					current->left->parent = current;
				}
				else {
					current->right = remove->left;
					current->right->parent = current;
				}
				delete remove;
			}
			else {
				head = head->left;
				delete remove;
				head->parent = nullptr;
				current = head;
				current->isblack = true;
			}
		}
		else if (current->left != nill && current->right != nill && current->left && current->right) {
			current = current->right;
			while (current->left != nill)
				current = current->left;
			currentforbalance = current->right;
			isblackremove = current->isblack;
			if (current->parent == remove)
				currentforbalance->parent = current;
			else {
				current->parent->left = currentforbalance;
				if (currentforbalance->parent)
					currentforbalance->parent = current->parent;
			}
			if (remove->parent) {
				if (remove->parent->left == remove)
					remove->parent->left = current;
				else
					remove->parent->right = current;
			}
			current->left = remove->left;
			if (remove->left->parent != nill)
				remove->left->parent = current;
			if (current != remove->right)
				current->right = remove->right;
			current->parent = remove->parent;
			if (!remove->parent)
				head = current;
			current->isblack = isblackremove;
			delete remove;
		}
	}
	if (isblackremove && head && currentforbalance) {
		while (currentforbalance->parent) {
			if (currentforbalance->parent->left == currentforbalance) {
				current = currentforbalance->parent->right;
				if (current) {
					if (!current->isblack) {
						current->isblack = true;
						current->parent->isblack = false;
						left_turn(current);
						current = currentforbalance->parent->right;
					}
					if (current->left && current->right) if (current->left->isblack == current->right->isblack && current->left->isblack) {
						current->isblack = false;
						currentforbalance = currentforbalance->parent;
					}
					else if (current->right->isblack) {
						current->left->isblack = true;
						current->isblack = false;
						right_turn(current->left);
						current = currentforbalance->parent->right;
					}
					else {
						current->isblack = currentforbalance->parent->isblack;
						currentforbalance->parent->isblack = true;
						current->right->isblack = true;
						left_turn(current);
					}
					while (current->parent)
						current = current->parent;
					head = current;
					currentforbalance = head;
				}
			}
			else {
				current = currentforbalance->parent->left;
				if (!current->isblack) {
					current->isblack = true;
					current->parent->isblack = false;
					right_turn(current);
					current = currentforbalance->parent->left;
				}
				if (current->left->isblack == current->right->isblack && current->left->isblack) {
					current->isblack = false;
					currentforbalance = currentforbalance->parent;
				}
				else if (current->right->isblack) {
					current->left->isblack = true;
					current->isblack = false;
					left_turn(current->left);
					current = currentforbalance->parent->right;
				}
				else {
					current->isblack = currentforbalance->parent->isblack;
					currentforbalance->parent->isblack = true;
					current->right->isblack = true;
					right_turn(current);
				}
				while (current->parent)
					current = current->parent;
				head = current;
				currentforbalance = head;
			}
			currentforbalance->isblack = true;
		}
	}
	if (nill) nill->parent = nullptr;
}

int Map::find(int key) {
	Node* current = head;
	while (current != nill) {
		if (key < current->key)
			current = current->left;
		else if (key > current->key)
			current = current->right;
		else break;
	}
	if (current == nill)
		throw std::invalid_argument("Error! Key not found!!");
	return current->value;
}

List Map::get_keys() {
	return get_keys_or_value(true);
}

List Map::get_values() {
	return get_keys_or_value(false);
}

void Map::clear() {
	while (head != nill && head)
		remove(head->key);
}

void Map::print() {
	List listkeys, listvalues;
	listkeys = get_keys();
	listvalues = get_values();
	for (int i = 0; i < listkeys.get_size(); i++) {
		cout << listkeys.get_elem(i) << " -> " << listvalues.get_elem(i) << endl;
	}
}

void Map::left_turn(Node* swivel) {
	Node* parent = swivel->parent;
	parent->right = swivel->left;
	if (swivel->left != nill) swivel->left->parent = parent;
	swivel->parent = parent->parent;
	if (!parent->parent)
		head = swivel;
	else {
		if (parent == parent->parent->left)
			parent->parent->left = swivel;
		else
			parent->parent->right = swivel;
	}
	parent->parent = swivel;
	swivel->left = parent;
}

void Map::right_turn(Node* swivel) {
	Node* parent = swivel->parent;
	parent->left = swivel->right;
	if (swivel->right != nill) swivel->right->parent = parent;
	swivel->parent = parent->parent;
	if (!parent->parent)
		head = swivel;
	else {
		if (parent == parent->parent->right)
			parent->parent->right = swivel;
		else
			parent->parent->left = swivel;
	}
	parent->parent = swivel;
	swivel->right = parent;
}

List Map::get_keys_or_value(bool iskeys) {
	if (head) {
		List list;
		Node* current = head;
		while (count > list.get_size() && current) {
			while (current->left != nill && current->left) {
				if (iskeys) list.push_back(current->key);
				else list.push_back(current->value);
				current = current->left;
			}
			if (current->right != nill && current->right) {
				if (iskeys) list.push_back(current->key);
				else list.push_back(current->value);
				current = current->right;
				continue;
			}
			else {
				if (iskeys) list.push_back(current->key);
				else list.push_back(current->value);
			}
			while (current->parent && count > list.get_size()) {
				current = current->parent;
				if (current->right != nill && current->right) {
					if (iskeys) {
						if (!list.contains(current->right->key)) {
							current = current->right;
							break;
						}
					}
					else if (!list.contains(current->right->value)) {
						current = current->right;
						break;
					}
				}
				if (current->left) {
					if (iskeys) {
						if (!list.contains(current->left->key)) {
							current = current->right;
							break;
						}
					}
					else if (!list.contains(current->left->value)) {
						current = current->right;
						break;
					}
				}
			}
		}
		list.save_list();
		return list;
	}
	throw out_of_range("Error! The tree does not exist!");
}