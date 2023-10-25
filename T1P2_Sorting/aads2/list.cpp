#include "list.h"
#include <iostream>

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
* Создание списка из инициализирующего списка
*/
LinkedList::LinkedList(std::initializer_list<int> init) {
    for(int v : init) {
        append(v);
    }
}

/*
* Деструктор списка
*/
LinkedList::~LinkedList() {
    clear();
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

void LinkedList::random(unsigned n, int max, int min) {
    clear();
    LinkedNode* current = 0;
    LinkedNode* next = 0;
    for (unsigned i = 1; i <= n; i++) {
        current = new LinkedNode;
        current->value = min + (rand() % (max - min + 1));
        current->next = next;
        if (next)
            next->prev = current;
        next = current;
    }

    head = current;
    len = n;
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
int& LinkedList::at(unsigned index) {
    LinkedNode* node = node_at(index);
    if (node == 0)
        throw std::runtime_error("Out of bounds");
    return node->value;
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

void LinkedList::insertionSort(int left, int right) {
    for (int i = left + 1; i < right; i++) {
        int key = at(i);
        int j = i - 1;
        while (j >= left && at(j) > key) {
            at(j + 1) = at(j);
            j--;
        }

        at(j + 1) = key;
    }
}

/*
* Элемент сортировки слиянием
* int l - Левый предел
* int m - Середина
* int r - Правый предел
*/
void LinkedList::merge(int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;

    LinkedList left(len1);
    LinkedList right(len2);

    for (int i = 0; i < len1; i++)
        left.at(i) = at(l + i);
    for (int i = 0; i < len2; i++)
        right.at(i) = at(m + i + 1);

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        at(k++) = (left[i] <= right[j]) ? left.at(i++) : right[j++];
    }

    while (i < len1)
        at(k++) = left[i++];
    while (j < len2)
        at(k++) = right[j++];
}

/*
* Cортировка списка слиянием
* int l - Левый предел
* int r - Правый предел
*/
void LinkedList::mergeSort(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(l, m);
        mergeSort(m + 1, r);

        merge(l, m, r);
    }
}

/*
* Бинарный поиск в списке. Работает только на отсортированных массивах
* int start - Левый предел
* int len - Длина диапазона
* int val - Число для поиска
*/
int LinkedList::bSearch(int start, int len, int val) {
    int lo = start;
    int hi = len;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (at(mid) < val)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo - start;
}

/*
* Бинарный поиск в списке. Работает только на отсортированных массивах
* int val - Число для поиска
*/
int LinkedList::bSearch(int val) {
    return bSearch(0, len - 1, val);
}

const int MAX_GALLOP = 7;

/*
* Подсчёт minrun для текущего массива
*/
int LinkedList::minrun() {
    int n = len;
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

/*
* Элемент сортировки слиянием для TimSort
* int l - Левый предел
* int m - Середина
* int r - Правый предел
*/
void LinkedList::timMerge(int l, int m, int r) {
    int len1 = m - l;
    int len2 = r - m;

    LinkedList left(len1);
    LinkedList right(len2);

    for (int i = 0; i < len1; i++)
        left[i] = at(l + i);
    for (int i = 0; i < len2; i++)
        right[i] = at(m + i);

    int i = 0, j = 0, k = l;
    int skipL = 0, skipR = 0;
    bool noGallop = false;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            at(k++) = left[i++];
            skipL++;
            skipR = 0;
            if (skipL >= MAX_GALLOP && !noGallop) {
                int sId = left.bSearch(i, len1, right[j]);
                for (int x = i; x < sId; x++)
                    at(k++) = left[i++];
                noGallop = true;
                skipL = 0;
            }
        } else {
            at(k++) = right[j++];
            skipR++;
            skipL = 0;
            if (skipR >= MAX_GALLOP && !noGallop) {
                int sId = right.bSearch(j, len2, left[i]);
                for (int x = j; x < sId; x++)
                    at(k++) = right[j++];
                noGallop = true;
                skipR = 0;
            }
        }
    }

    while (i < len1)
        at(k++) = left[i++];
    while (j < len2)
        at(k++) = right[j++];
}

/*
* Timsort.
*/
void LinkedList::timSort() {
    if (len < 2)
        return;

    int minRun = minrun();

    for (int i = 0; i < len; i += minRun) {
        int end = std::min(i + minRun, (int)len);
        insertionSort(i, end);
    }
    for (int size = minRun; size < len; size = 2 * size) {
        for (int left = 0; left < len; left += 2 * size) {
            int mid = std::min(left + size, (int)len);
            int right = std::min(left + 2 * size, (int)len);
            if (mid != right)
                timMerge(left, mid, right);
        }
    }
}

/*
* Поиск максимального значения в списке
*/
int LinkedList::max() {
    if (head == 0)
        return 0;
    int max = head->value;
    LinkedNode* node = head;
    while (node) {
        if (node->value > max)
            max = node->value;
        node = node->next;
    }
    return max;
}

/*
* Поиск минимального значения в списке
*/
int LinkedList::min() {
    if (head == 0)
        return 0;
    int min = head->value;
    LinkedNode* node = head;
    while (node) {
        if (node->value < min)
            min = node->value;
        node = node->next;
    }
    return min;
}

/*
* Сортировка Radix для младшего бита (LSD)
*/
void LinkedList::radixLSDSort() {
    if (head == 0)
        return;
    
    int maxv = head->value;
    LinkedNode* node = head;
    while (node) {
        if (node->value < 0)
            return;
        if (node->value > maxv)
            maxv = node->value;
        node = node->next;
    }

    int exp = 1;
    int n = size();

    LinkedList output(n);
    
    while (maxv / exp > 0) {
        LinkedList count(10);
        for (int i = 0; i < n; i++)
            count[(at(i) / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            output[count[(at(i) / exp) % 10] - 1] = at(i);
            count[(at(i) / exp) % 10]--;
        }

        for (int i = 0; i < n; i++)
            at(i) = output[i];
        
        exp *= 10;
    }
}

/*
* Развернуть список
*/
void LinkedList::reverse() {
    reverse(0, size() - 1);
}

/*
* Развернуть список
* unsigned start - Левый предел
* unsigned end - Правый предел
*/
void LinkedList::reverse(unsigned start, unsigned end) {
    while (start < end) {
        swap(start, end);
        start++;
        end--;
    }
}

/*
* Сортировать список
* SortingAlgorithm alg - Сортировочный алгоритм
*/
void LinkedList::sort(SortingAlgorithm alg = TIM) {
    switch (alg) {
        case MERGE:
            mergeSort(0, size() - 1);
            break;
        case TIM:
            timSort();
            break;
        case INSERTION:
            insertionSort(0, size());
            break;
        case RADIXLSD:
            radixLSDSort();
            break;
    }
}

int& LinkedList::operator[](unsigned index) {
    return at(index);
}

std::ostream& operator<<(std::ostream& os, LinkedList& s) {
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