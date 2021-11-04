// ALGO2 IS1 222B LAB01
// Aleksander Wojciechowski
// wa49444@zut.edu.pl

#include "pch.h"
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

using namespace std;

template <typename T>

class List {
public:
	struct node {
		T dane;
		node* next, *prev;
		node() {
			next = nullptr;
			prev = nullptr;
		}
	};

	List() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	~List() {
		delete_all();
	}

	int get_size() {
		return size;
	}

	void new_node_back(const T& dane) {
		node* n = new node;
		n->dane = dane;
		n->next = nullptr;
		if (tail == nullptr) {
			n->prev = nullptr;
			head = n;
			tail = n;
		}
		else {
			n->prev = tail;
			tail->next = n;
			tail = n;
		}
		size++;
	}

	void new_node_front(const T& dane) {
		node* n = new node;
		n->dane = dane;
		n->prev = nullptr;
		if (head == nullptr) {
			n->prev = nullptr;
			head = n;
			tail = n;
		}
		else {
			n->next = head;
			head->prev = n;
			head = n;
		}
		size++;
	}

	void new_node_ordered(const T& dane) {

		node* n = new node;
		n->dane = dane;
		if (head == nullptr) {
			n->next = nullptr;
			n->prev = nullptr;
			head = n;
			tail = n;
			size++;
			return;
		}

		if (dane < head->dane) {
			new_node_front(dane);
			return;
		}
		else if (tail->dane < dane || tail->dane == dane) {
			new_node_back(dane);
			return;
		}


		node* ptr = head;
		while (ptr) {
			if (ptr->dane < dane && dane < ptr->next->dane) {
				n->prev = ptr;
				n->next = ptr->next;
				ptr->next->prev = n;
				ptr->next = n;
				size++;
				return;
			}
			else if (ptr->dane == dane) {
				n->prev = ptr;
				n->next = ptr->next;
				ptr->next->prev = n;
				ptr->next = n;
				size++;
				return;
			}

			ptr = ptr->next;
		}

	}

	void delete_last() {
		if (size == 0) {
			cout << "Brak elementow do usuniecia" << endl;
		}
		else if (size == 1) {
			delete_all();
			/*head = tail = nullptr;
			size--;*/
		}
		else {
			node* temp = tail;
			tail = temp->prev;
			tail->next = nullptr;
			delete temp;
			size--;
		}
	}

	void delete_first() {
		if (size == 0) {
			cout << "Brak elementow do usuniecia" << endl;
		}
		else if (size == 1) {
			delete_all();
		}
		else {
			node* temp = head;
			head = temp->next;
			head->prev = nullptr;
			delete temp;
			size--;
		}
	}

	node* find_node(const T& key) {
		node* ptr = head;
		while (ptr) {
			if ((ptr->dane == key)) {
				return ptr;
			}
			else {
				ptr = ptr->next;
			}
		}
		return nullptr;
	}

	T find_element(int n) {
		node* ptr;
		if (size / 2 > n) {
			ptr = head;
			int i = 0;
			while (ptr && i < n) {
				ptr = ptr->next;
				i++;
			}
		}
		else {
			ptr = tail;
			int i = size - 1;
			while (ptr && i > n) {
				ptr = ptr->prev;
				i--;
			}
		}

		if (!ptr) {
			abort();
		}

		return ptr->dane;
	}

	bool find_and_delete(const T& key) {

		node* ptr = head;
		while (ptr) {
			if ((ptr->dane == key)) {
				if (ptr == head) {
					this->delete_first();

					return 1;
				}
				else if (ptr == tail) {
					this->delete_last();
					return 1;
				}
				else {
					
					ptr->prev->next = ptr->next;
					ptr->next->prev = ptr->prev;
					delete ptr;
					size--;
					return 1;
				}

			}
			else {
				ptr = ptr->next;
			}
		}
		return 0;

	}

	void swap_element(int n, const T& new_data) {
		node* ptr = head;
		int i = 0;
		while (ptr && i < n) {
			ptr = ptr->next;
			i++;
		}
		if (ptr) {
			ptr->dane = new_data;
		}
	}

	void delete_all() {
		if (size == 0) {
			cout << "Lista pusta" << endl;
		}
		else if (size == 1) {
			delete head;
			size--;
		}
		else {
			node* tmp = head;
			while (tmp) {
				tmp = tmp->next;
				delete head;
				head = tmp;
				size--;
			}
			tail = nullptr;
			delete tmp;
		}

	}

	string display_list(int n = 0) {
		node* ptr = head;
		int i = 0;
		ostringstream output = "";
		if (!n) {
			n = size;
		}
		while (ptr && i < n) {
			output << "Node: " << i << ", ADDR: " << ptr << endl;
			output << ptr->dane << endl;
			//output = output + "Node: " + to_string(i) + "\n" + ptr->dane.convert_to_str() + "\n \n";
			i++;
			ptr = ptr->next;
		}
		return output.str();
	}


private:
	node* head, *tail;
	unsigned int size;
};




struct listData {
	int d1;
	char d2;
};

ostream& operator << (ostream& out, const listData& obj) {
	out << "{d1: " << obj.d1 << endl << "d2: " << obj.d2 << "}";
	return out;
}

bool operator < (const listData& a, const listData& b) {
	return a.d1 < b.d1 || a.d1 == b.d1 && a.d2 < b.d2;
}

bool operator ==(const listData& a, const listData& b) {
	return (!(a < b) && !(b < a));
}




int main()
{
	const int MAX_ORDER = 4;
	List<listData>* lista = new List<listData>();
	listData* data = new listData();

	srand(time(NULL));
	for (int o = 1; o <= MAX_ORDER; o++) {

		const int n = pow(10, o);

		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			data->d1 = rand() % 1000;
			data->d2 = 'a' + rand() % 26;
			lista->new_node_ordered(*data);
		}
		clock_t t2 = clock();

		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "============================================================" << endl;
		cout << "Rozmiar listy: " << lista->get_size() << endl;
		cout << "Dodawanie czas calkowity: " << time << endl;
		cout << "Dodawanie czas sredni na pojedyncza operacje: " << time / n << endl;


		const int m = pow(10, 4);

		t1 = clock();
		for (int i = 0; i < m; i++) {
			data->d1 = rand() % 1000;
			data->d2 = 'a' + rand() % 26;
			lista->find_and_delete(*data);
		}
		t2 = clock();
		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "------------------------------------------------------------" << endl;
		cout << "Rozmiar listy: " << lista->get_size() << endl;
		cout << "Usuwanie czas calkowity: " << time << endl;
		cout << "Usuwanie czas sredni na pojedyncza operacje: " << time / m << endl;
		cout << "============================================================" << "\n\n\n";

		lista->delete_all();
	}

	delete lista;
	delete data;
}