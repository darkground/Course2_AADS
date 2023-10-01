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
        item->prev = 0;
        head = item;
        len--;
    }
    else {
        LinkedNode* prevItem = at(index - 1);
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
* Удалить список И все его элементы.
* unsigned index - индекс в списке
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
}

/*
* Получить элемент по индексу. При индексе > length будет возвращён нулевой указатель.
* unsigned index - индекс в списке
*/
LinkedNode* LinkedList::at(unsigned index) {
    LinkedNode* node = head;
    while (node && (index--))
        node = node->next;
    return node;
}

/*
* Вставить элемент по индексу. При индексе > length элемент будет добавлен в конец списка.
* unsigned index - индекс в списке
*/
LinkedNode* LinkedList::insert(unsigned index, int value) {
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
    return item;
}

/*
* Вставить элемент в конец списка.
*/
LinkedNode* LinkedList::append(int value) {
    return insert(len, value);
}

/*
* Поменять элементы местами по индексу. При одинаковых индексах или при одном индексе > length список не будет изменён.
* unsigned index1 - первый индекс в списке
* unsigned index2 - второй индекс в списке
*/
void LinkedList::swap(unsigned index1, unsigned index2) {
    LinkedNode* node1 = at(index1);
    LinkedNode* node2 = at(index2);
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

std::ostream& operator<<(std::ostream& os, LinkedList s) {
	LinkedNode* h = s.head;
	while (h) {
		os << h->value << " ";
		h = h->next;
	}
	return os;
}