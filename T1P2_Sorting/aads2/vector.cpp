#include "vector.h"

/*
* Создать динамический массив.
* unsigned cap = 1 - изначальная вместимость
*/
Vector::Vector(unsigned cap) {
	arr = new int[cap]{};
	capacity = cap;
	length = 0;
}

/*
* Деструктор динамического массива
*/
Vector::~Vector() {
	delete[] arr;
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


void Vector::random(unsigned n, int max, int min) {
    delete[] arr;
	arr = new int[n];
	capacity = n;
	length = n;
    for (unsigned i = 0; i < n; i++) {
		at(i) = min + (rand() % (max - min + 1));
    }
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
int& Vector::at(unsigned index) {
	return arr[index];
}

/*
* Поиск элемента в динамическом массиве. Если не найден, вернёт -1.
* int value - элемент в списке
*/
int Vector::search(int value) {
	for (unsigned i = 0; i < length; i++)
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
	for (unsigned i = length; i > index; i--)
		arr[i] = arr[i - 1];
	arr[index] = data;
	length++;
}

/*
* Удалить элемент из динамического массива по значению. При ненайденном элементе ничего не произойдёт.
* int value - элемент
*/
void Vector::remove(int value) {
	int idx = search(value);
    if (idx != -1)
        remove((unsigned)idx);
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
    swap((unsigned)idx1, (unsigned)idx2);
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

/*
* Сортировка вставками
*/
void Vector::insertionSort(int left, int right) {
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
void Vector::merge(int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;

    Vector left(len1);
    Vector right(len2);

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
* Cортировка массива слиянием
* int l - Левый предел
* int r - Правый предел
*/
void Vector::mergeSort(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(l, m);
        mergeSort(m + 1, r);

        merge(l, m, r);
    }
}

/*
* Бинарный поиск в массиве. Работает только на отсортированных массивах
* int start - Левый предел
* int len - Длина диапазона
* int val - Число для поиска
*/
int Vector::bSearch(int start, int len, int val) {
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
* Бинарный поиск в массиве. Работает только на отсортированных массивах
* int val - Число для поиска
*/
int Vector::bSearch(int val) {
    return bSearch(0, length - 1, val);
}

const int MAX_GALLOP = 7;

/*
* Подсчёт minrun для текущего массива
*/
int Vector::minrun() {
    int n = length;
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
void Vector::timMerge(int l, int m, int r) {
    int len1 = m - l;
    int len2 = r - m;

    Vector left(len1);
    Vector right(len2);

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
void Vector::timSort() {
    if (length < 2)
        return;

    int minRun = minrun();

    for (int i = 0; i < length; i += minRun) {
        int end = std::min(i + minRun, (int)length);
        insertionSort(i, end);
    }
    for (int sz = minRun; sz < length; sz = 2 * sz) {
        for (int left = 0; left < length; left += 2 * sz) {
            int mid = std::min(left + sz, (int)length);
            int right = std::min(left + 2 * sz, (int)length);
            if (mid != right)
                timMerge(left, mid, right);
        }
    }
}

/*
* Поиск максимального значения в массиве
*/
int Vector::max() {
	int max = arr[0];
	for (int i = 1; i < length; i++) {
		if (arr[i] > max)
			max = arr[i];
	}
    return max;
}

/*
* Поиск минимального значения в массиве
*/
int Vector::min() {
    int min = arr[0];
	for (int i = 1; i < length; i++) {
		if (arr[i] > min)
			min = arr[i];
	}
    return min;
}

/*
* Сортировка Radix для младшего бита (LSD)
*/
void Vector::radixLSDSort() {
    int maxv = arr[0];
	for (int i = 1; i < length; i++) {
		if (arr[i] < 0)
            return;
        if (arr[i] > maxv)
			maxv = arr[i];
	}

    int exp = 1;
    int n = size();

    Vector output(n);
    
    while (maxv / exp > 0) {
        Vector count(10);
        for (int i = 0; i < n; i++)
            count[(at(i) / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int x = count[(at(i) / exp) % 10] - 1;
            output[x] = at(i);
            count[(at(i) / exp) % 10]--;
        }

        for (int i = 0; i < n; i++)
            at(i) = output[i];
        
        exp *= 10;
    }
}

/*
* Развернуть массив
*/
void Vector::reverse() {
    reverse(0, size() - 1);
}

/*
* Развернуть массив
* unsigned start - Левый предел
* unsigned end - Правый предел
*/
void Vector::reverse(unsigned start, unsigned end) {
    while (start < end) {
        swap(start, end);
        start++;
        end--;
    }
}

/*
* Сортировать массив
* SortingAlgorithm alg - Сортировочный алгоритм
*/
void Vector::sort(SortingAlgorithm alg = TIM) {
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

int& Vector::operator[](unsigned index) {
    return at(index);
}

std::ostream& operator<<(std::ostream& os, Vector& s) {
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