#include "list.h"

/*
* Создание списка с N готовыми элементами
* unsigned n - количество = 0
*/
LinkedList::LinkedList(unsigned n) {
    LinkedNode* current = 0;
    LinkedNode* next = 0;
    for (unsigned i = 1; i <= n; i++) {
        current = new LinkedNode;
        current->next = next;
        if (next)
            next->prev = current;
        next = current;
    }

    head = current;
    len = n;
}

/*
* Вернуть длину списка.
*/
unsigned LinkedList::size() {
    return len;
}

/*
* Пересчитать длину списка.
*/
unsigned LinkedList::length() {
    unsigned length = 0;
    LinkedNode* node = head;
    while (node) {
        length++;
        node = node->next;
    }
    return length;
}

/*
* Удалить элемент по индексу. При индексе > length список не будет изменён.
* unsigned index - индекс в списке
*/
void LinkedList::remove(unsigned index) {
    if (index == 0) {
        LinkedNode* item = head->next;
        delete head;
        if (item)
            item->prev = 0;
        head = item;
        len--;
    }
    else {
        LinkedNode* prevItem = node_at(index - 1);
        if (prevItem) {
            LinkedNode* delItem = prevItem->next;
            prevItem->next = delItem->next;

            if (prevItem->next)
                prevItem->next->prev = prevItem;
            delete delItem;
            len--;
        }
    }
}

/*
* Удалить элемент по значению. При ненайденном значении ничего не произойдёт.
* int value - элемент в списке
*/
void LinkedList::remove(int value) {
    int idx = search(value);
    if (idx != -1)
        remove((unsigned)idx);
}

/*
* Очистить список.
*/
void LinkedList::clear() {
    LinkedNode* next;
    LinkedNode* current = head;
    while (current) {
        next = current->next;
        delete current;
        current = next;
    }
    head = 0;
    len = 0;
}

/*
* Получить элемент по индексу. При индексе > length будет возвращён нулевой указатель.
* unsigned index - индекс в списке
*/
int LinkedList::at(unsigned index) {
    LinkedNode* node = node_at(index);
    return node == 0 ? 0 : node->value;
}

/*
* Поиск элемента в списке. Если не найден, вернёт -1.
* int value - элемент в списке
*/
int LinkedList::search(int value) {
    LinkedNode* node = head;
    unsigned index = 0;
    while (node) {
        if (node->value == value)
            return index;
        index++;
        node = node->next;
    }
    return -1;
}

/*
* Получить LinkedNode по индексу. При индексе > length будет возвращён нулевой указатель.
* unsigned index - индекс в списке
*/
LinkedNode* LinkedList::node_at(unsigned index) {
    LinkedNode* node = head;
    while (node && (index--))
        node = node->next;
    return node;
}

/*
* Вставить элемент по индексу. При индексе > length элемент будет добавлен в конец списка.
* unsigned index - индекс в списке
* int value - элемент
*/
void LinkedList::insert(unsigned index, int value) {
    LinkedNode* item = new LinkedNode;
    item->value = value;
    if (!head)
        head = item;
    else if (index == 0) {
        LinkedNode* first = head;
        head = item;
        item->next = first;
        first->prev = item;
    }
    else {
        LinkedNode* prev = head;
        index--;
        while (prev->next && (index--))
            prev = prev->next;
        item->prev = prev;
        item->next = prev->next;
        if (prev->next)
            prev->next->prev = item;
        prev->next = item;
    }
    len++;
}

/*
* Вставить элемент в конец списка.
* int value - элемент
*/
void LinkedList::append(int value) {
    insert(len, value);
}

/*
* Поменять элементы местами по индексу. При одинаковых индексах или при одном индексе > length список не будет изменён.
* unsigned index1 - первый индекс в списке
* unsigned index2 - второй индекс в списке
*/
void LinkedList::swap(unsigned index1, unsigned index2) {
    LinkedNode* node1 = node_at(index1);
    LinkedNode* node2 = node_at(index2);
    if (index1 == index2 || !node1 || !node2)
        return;
    
    if (node1->prev)
        node1->prev->next = node2;
    if (node2->prev)
        node2->prev->next = node1;
    std::swap(node1->prev, node2->prev);
    if (node2->next)
        node2->next->prev = node1;
    if (node1->next)
        node1->next->prev = node2;
    std::swap(node1->next, node2->next);

    if (head == node1)
        head = node2;
    else if (head == node2)
        head = node1;
}

/*
* Поменять элементы местами по значению. При ненайденных элементах ничего не произойдёт.
* int value1 - первый элемент в списке
* int value2 - второй элемент в списке
*/
void LinkedList::swap(int value1, int value2) {
    int idx1 = search(value1);
    int idx2 = search(value2);
    if (idx1 == -1 || idx2 == -1)
        return;
    swap((unsigned)idx1, (unsigned)idx2);
}

std::ostream& operator<<(std::ostream& os, LinkedList s) {
    os << "List[";
	LinkedNode* h = s.head;
    if (s.head != 0)
        while (true) {
            os << h->value;
            if (h->next) {
                os << ", ";
                h = h->next;
            } else break; 
        }
    os << "]";
	return os;
}