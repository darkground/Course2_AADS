#include "vector.h"

/*
* Создать динамический массив.
* unsigned cap = 1 - изначальная вместимость
*/
Vector::Vector(unsigned cap) {
	arr = new int[cap];
	capacity = cap;
	length = 0;
}

/*
* Очистить динамический массив.
*/
void Vector::clear() {
	delete[] arr;
	arr = new int[1];
	capacity = 1;
	length = 0;
}

/*
* Добавить элемент в конец массива.
* int data - данные
*/
void Vector::append(int data) {
	if (length == capacity)
		resize(capacity * 2);
	arr[length] = data;
	length++;
}


/*
* Изменить вместимость динамического массива.
* unsigned capacity - вместимость (< length)
*/
void Vector::resize(unsigned cap) {
	if (cap <= capacity)
		return;
	int* temp = new int[cap];

	for (unsigned i = 0; i < capacity; i++)
		temp[i] = arr[i];

	delete[] arr;
	capacity = cap;
	arr = temp;
}


/*
* Получить элемент динамического массива по индексу.
* unsigned index - индекс
*/
int Vector::at(unsigned index) {
	return arr[index];
}

/*
* Поиск элемента в динамическом массиве. Если не найден, вернёт -1.
* int value - элемент в списке
*/
int Vector::search(int value) {
	for (int i = 0; i < length; i++)
		if (arr[i] == value)
			return i;
	return -1;
}


/*
* Вставить элемент в динамический массив по индексу.
* unsigned index - индекс
* int data - элемент
*/
void Vector::insert(unsigned index, int data) {
	if (length == capacity)
		resize(capacity * 2);
	length++;

	for (unsigned i = length; i > index; i--)
		arr[i] = arr[i - 1];
	arr[index] = data;
}

/*
* Удалить элемент из динамического массива по значению. При ненайденном элементе ничего не произойдёт.
* int value - элемент
*/
void Vector::remove(int value) {
	int idx = search(value);
    if (idx != -1)
        remove(idx);
}

/*
* Удалить элемент из динамического массива по индексу.
* unsigned index - индекс
*/
void Vector::remove(unsigned index) {
	for (unsigned i = index; i <= length - 1; i++)
		arr[i] = arr[i + 1];
	arr[length - 1] = 0;
	length--;
}

/*
* Поменять элементы в динамическом массиве местами, зная их индексы.
* unsigned index1 - индекс 1
* unsigned index2 - индекс 2
*/
void Vector::swap(unsigned index1, unsigned index2) {
	std::swap(arr[index1], arr[index2]);
}

/*
* Поменять элементы в динамическом массиве местами. При ненайденных элементах ничего не произойдёт.
* int value1 - первый элемент в списке
* int value2 - второй элемент в списке
*/
void Vector::swap(int value1, int value2) {
	int idx1 = search(value1);
    int idx2 = search(value2);
    if (idx1 == -1 || idx2 == -1)
        return;
    swap(idx1, idx2);
}

/*
* Получить длину массива
*/
unsigned Vector::size() {
	return length;
}

/*
* Получить вместимость массива
*/
unsigned Vector::cap() {
	return capacity;
}

std::ostream& operator<<(std::ostream& os, Vector s) {
	unsigned sz = s.size();
	os << "Vec[";
	for (unsigned i = 0; i < sz; i++) {
		os << s.arr[i];
		if (i != sz - 1)
			os << ", ";
	}
	os << "]";
	return os;
}