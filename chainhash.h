#include<iostream>
#include <list>

using namespace std;

const int maxColision = 3;
const float maxFillFactor = 0.5;

template<typename TK, typename TV>
class ChainHash
{
private:
	struct Entry {
		TK key;
		TV value;
		size_t hashcode;
		Entry(TK _key, TV _value) {
			key = _key; value = _value;
		}
		Entry() {
			key = NULL;
			value = NULL;
		}
	};
	
	list<Entry> *array;
	int capacity;//tamanio del array
	int size;//cantidad de elementos totales

public:
	ChainHash() {
		// TODO: asignar un tamanio inicial al array
		capacity = 10;
		this->array = new list<Entry>[capacity];
		size = 0;
	}

	void set(TK key, TV value) {
		if (fillFactor() >= maxFillFactor) { rehashing();}
		
		size_t hashcode = getHashCode(key);
		int index = hashcode % capacity;
		for (auto ite = array[index].begin(); ite != array[index].end(); ++ite) {
			if ((*ite).key == key) {
				(*ite).value = value;
				return;
			}
		}
		if (array[index].size() == maxColision) {
			for (int i = 0; i < capacity; i++) {
				++index;
				index = index % capacity;
				if (array[index].size() != maxColision) {
					array[index].push_front(Entry(key, value));
					size++;
					return;
				}
			}
		}

		array[index].push_front(Entry(key, value));	
		size++;
		//TODO: insertar el Entry(key, value) en index, manejando colisiones
		
	}

	TV get(TK key) {
		size_t hashcode = getHashCode(key);
		int index = hashcode % capacity;
		Entry* res = searchList(array[index], key);
		if (res != nullptr) { return res->value; }
		else { throw("No existe"); }
			 
	}
	TV searchList(Entry arr,TK key) {
		for (auto ite = arr.begin(); ite != arr.end(); ite++) {
			if (key == (*ite).key) {
				return (*ite).value;
			}
		}
	}
	/*void remove(TK key) {
		size_t hashcode = getHashCode(key);
		int index = hashcode % capacity;
		for (auto ite = array[index].begin(); ite != array[index].end(); ite++) {
			if (key == (*ite).key) {
				array[index].remove(*ite);
				--size;
				break;			
			}
		}
	}
	*/
	int bucket_count() {
		return capacity;
	}
	size_t bucket_size(int index) {
		return array[index].size();
	}
	auto begin(int index) {
		return array[index].begin();
	}
	auto end(int index) {
		return array[index].end();
	}
	//TODO: implementar el operador corchete [ ]

private:
	double fillFactor() {
		return size*1.0 / (capacity * maxColision);
	}

	size_t getHashCode(TK key) {
		std::hash<TK> ptr_hash;
		return ptr_hash(key);
	}

	void rehashing() {
		
		list<Entry>* temp = new list<Entry>[capacity];
			for (int i = 0; i < capacity; i++) {
				for (auto ite = array[i].begin(); ite != array[i].end(); ++ite) {
					temp[i].push_front(Entry((*ite).key, (*ite).value));
				}
			}
		delete[]array;
		array = new list<Entry>[(2 * capacity) + 1];
		
		
		size = 0;
		capacity = (capacity * 2) + 1;

		for (int i = 0; i <(capacity/2)-1;++i) {
			for (auto ite = temp[i].begin();ite!=temp[i].end();++ite) {
				set((*ite).key, (*ite).value);
			}
		}

	}
	
};

