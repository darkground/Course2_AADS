#include <iostream>
#include "list.h"
#include <stack>

int main() {
    LinkedList arr(10, 50, -50);

    std::cout << "Unsorted array: " << arr << std::endl;
    
    arr.sort(SortingAlgorithm::TIM);

    std::cout << "Sorted array: " << arr << std::endl;

    return 0;
}