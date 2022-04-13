#include <iostream>
#include <stdlib.h>
using namespace std;

template <typename elmtype>
class CDA {
    private:
        int size, capacity, front, ordered;
        elmtype error, *array;

        // Array Resizing
        void increaseCapacity() {
            int tempOrdered = ordered;
            capacity *= 2;
            elmtype* newA = new elmtype[capacity];
            for(int i = 0; i < size; i++) {
                newA[i] = array[(front + i) % size];
            }
            delete[] array;
            array = newA;
            front = 0;
            ordered = tempOrdered;
        }
        void decreaseCapacity() {
            int tempOrdered = ordered;
            if(capacity / 2 >= 4) capacity /= 2;	// Prevent capacity from going below 4
            elmtype* newA = new elmtype[capacity];
            for(int i = 0; i < size; i++) {
                newA[i] = array[(front + i) % (capacity*2)];
            }
            delete[] array;
            array = newA;
            front = 0;
            ordered = tempOrdered;
        }

        // Merge Sort
        void mergeSortMerge(elmtype values[], int start, int middle, int end, elmtype temp[]) {
            int index1 = start;
            int index2 = middle + 1;
            int tempNextIndex = start;

            // sort into temp while both halves have values
            while(index1 <= middle && index2 <= end) {
                if(values[(front + index1) % capacity] > values[(front + index2) % capacity]) {
                    temp[tempNextIndex] = values[(front + index1) % capacity];
                    index1++;
                }
                else {
                    temp[tempNextIndex] = values[(front + index2) % capacity];
                    index2++;
                }
                tempNextIndex++;
            }
            // if any half has remaining values, copy them in
            while(index1 <= middle) {
                temp[tempNextIndex] = values[(front + index1) % capacity];
                index1++;
                tempNextIndex++;
            }
            while(index2 <= end) {
                temp[tempNextIndex] = values[(front + index2) % capacity];
                index2++;
                tempNextIndex++;
            }

            // copy back to original
            for(int i = start; i <= end; i++) {
                values[(front + i) % capacity] = temp[i];
            }
        }
        void mergeSortRecursive(elmtype values[], int start, int end, elmtype temp[]) { 
            if(start < end) {
                int middle = (start + end) / 2;
                mergeSortRecursive(values, start, middle, temp);
                mergeSortRecursive(values, middle + 1, end, temp);
                mergeSortMerge(values, start, middle, end, temp);
            }
        }

        // Binary Search
        int binarySearch(int start, int end, elmtype e) {
            if(ordered == 1) {
                if(end >= start) {
                    int middle = (start + end) / 2;
                    if (array[(front + middle) % capacity] == e) {
                        return middle;
                    }
                    if (array[(front + middle) % capacity] > e) {
                        return binarySearch(start, middle - 1, e);
                    }
                    return binarySearch(middle + 1, end, e);
                }
                return -1;
            }
            if(ordered == -1) {
                if(end >= start) {
                    int middle = (start + end) / 2;
                    if (array[(front + middle) % capacity] == e) {
                        return middle;
                    }
                    if (array[(front + middle) % capacity] < e) {
                        return binarySearch(start, middle - 1, e);
                    }
                    return binarySearch(middle + 1, end, e);
                }
                return -1;
            }
            return -1;
        }

        // Quickselect
        elmtype quickSelect(elmtype selectArray[], int front, int back, int k) {
            if(front == back) {
                return selectArray[front];
            }
            int pivotIndex = rand() % (back - front + 1) + front;
            elmtype pivot = selectArray[pivotIndex];
            elmtype tempSwap = selectArray[back];
            selectArray[back] = selectArray[pivotIndex];
            selectArray[pivotIndex] = tempSwap;
            int nextIndex = front;
            for(int i = front; i < back; i++) {
                if (selectArray[i] < pivot) {
                    tempSwap = selectArray[i];
                    selectArray[i] = selectArray[nextIndex];
                    selectArray[nextIndex] = tempSwap;
                    nextIndex++;
                }
            }
            tempSwap = selectArray[back];
            selectArray[back] = selectArray[nextIndex];
            selectArray[nextIndex] = tempSwap;
            pivotIndex = nextIndex;
            if(k == pivotIndex + 1) {
                return selectArray[k - 1];
            }
            else if ((k < pivotIndex + 1)) {
                return quickSelect(selectArray, front, pivotIndex - 1, k);
            }
            else {
                return quickSelect(selectArray, pivotIndex + 1, back, k);
            }
        }
    public:
        // Constructors
        CDA() {
            array = new elmtype[1];
            size = 0;
            capacity = 1;
            front = 0;
            ordered = 0;
        }
        CDA(int s) {
            array = new elmtype[s];
            size = s;
            capacity = s;
            front = 0;
            ordered = 0;
        }

        // Destructor
        ~CDA() {
            delete[] array;
        }

        // Copy Constructor and Copy Assignment Constructor
        CDA(const CDA &src) {
            capacity = src.capacity;
            size = src.size;
            front = 0;
            array = new elmtype[capacity];
            for(int i = 0; i < size; i++) {
                array[i] = src.array[(src.front + i) % src.capacity];
            }
            ordered = src.ordered;
        }
        CDA& operator=(const CDA& src) {
            if(this != &src) {
                delete[] array;
                capacity = src.capacity;
                size = src.size;
                front = 0;
                array = new int[capacity];
                for(int i = 0; i < size; i++) {
                    array[i] = src.array[(src.front + i) % src.capacity];
                }
                ordered = src.ordered;
            }
            return *this;
        }

        // define [] operator
        elmtype& operator[](int i) {
            if(i < 0 || i >= size) {
                cout << "Error: Index " << i << " is out of bounds" << endl;
                return error;
            }
            ordered = 0;
            return array[(front + i) % capacity];
        }

        // Add
        void AddEnd(elmtype v) {
            if (size == capacity) {
                increaseCapacity();
            }
            if((ordered == 1 && (array[((front+size) % capacity) - 1] > v)) || (ordered == -1 && (array[((front+size) % capacity) - 1] < v))) {
                ordered = 0;
            }
            array[(front+size) % capacity] = v;
            size++;
            if(size == 2) {
                SetOrdered();
            }
        }
        void AddFront(elmtype v) {
            if (size == capacity) {
                increaseCapacity();
            }
            if((ordered == 1 && (array[front] < v)) || (ordered == -1 && (array[front] > v))) {
                ordered = 0;
            }
            if(front != 0) {
                array[front-1] = v;
                front--;
            }
            else {
                array[capacity-1] = v;
                front = capacity - 1;
            }
            size++;
            if(size == 2) {
                SetOrdered();
            }
        }

        // Delete
        void DelEnd() {
            if(size != 0) {
                size--;
                if(capacity > 4 && capacity / size >= 4) {
                    decreaseCapacity();
                }
                if(size == 2) {
                    SetOrdered();
                }
            }
            else {
                cout << "Error: The array is empty" << endl;
            }
        }
        void DelFront() {
            if(size != 0) {
                if(front != capacity - 1) {
                    front++;
                }
                else {
                    front = 0;
                }
                size--;
                if(capacity > 4 && capacity / size >= 4) {
                    decreaseCapacity();
                }
                if(size == 2) {
                    SetOrdered();
                }
            }
            else {
                cout << "Error: The array is empty" << endl;
            }
        }

        // Return some info
        int Length() {
            return size;
        }
        int EmptySlots() {
            return capacity-size;
        }

        // Clear
        void Clear() {
            delete[] array;
            array = new elmtype[1];
            size = 0;
            capacity = 1;
            front = 0;
            ordered = 0;
        }

        // Ordering and Selection
        int Ordered() {
            return ordered;
        }
        int SetOrdered() {
            bool ascending = true;
            bool descending = true;
            for(int i = 0; i < size - 1; i++) {
                if (array[(front + i) % capacity] > array[(front + i + 1) % capacity]) {
                    ascending = false;
                }
                if (array[(front + i) % capacity] < array[(front + i + 1) % capacity]) {
                    descending = false;
                }
            }
            if (ascending) {
                ordered = 1;
            }
            else if (descending) {
                ordered = -1;
            }
            else {
                ordered = 0;
            }
            return ordered;
        }
        elmtype Select(int k) {
            if (size == 0) {
                cout << "Error: The array is empty" << endl;
                return error;
            }
            if (k > size || k <= 0) {
                cout << "Error: out of bounds" << endl;
                return error;
            }
            if (ordered == 1) {
                return array[(front + k - 1) % capacity];
            }
            if (ordered == -1) {
                return array[(front + (size - k)) % capacity];
            }
            elmtype* selectArray = new elmtype[size];
            for(int i = 0; i < size; i++) {
                selectArray[i] = array[(front + i) % capacity];
            }
            elmtype value = quickSelect(selectArray, 0, size - 1, k);
            delete[] selectArray;
            return value;
        }
        void InsertionSort() {
            for(int i = 1; i < size; i++) {
                elmtype current = array[(front + i) % capacity];
                int check = i - 1;
                while(check >= 0 && current > array[(front + check) % capacity]) {
                    array[(front + check + 1) % capacity] = array[(front + check) % capacity];
                    check--;
                }
                array[(front + check + 1) % capacity] = current;
            }
            ordered = -1;
        }
        void MergeSort() {
            elmtype* tempArray = new elmtype[size];
            mergeSortRecursive(array, 0, size - 1, tempArray);
            ordered = -1;
            delete[] tempArray;
        }
        void CountingSort(int m) {
            int* count = new int[m+1];
            elmtype* copyOfArray = new elmtype[size];
            for(int i = 0; i < m+1; i++) {
                count[i] = 0;
            }
            for(int i = 0; i < size; i++) {
                copyOfArray[i] = array[(front + i) % capacity];
                count[copyOfArray[i]]++;
            }
            int total = 0;
            for(int i = m; i >= 0; i--) {
                int temp = count[i];
                count[i] = total;
                total += temp;
            }
            for(int i = 0; i < size; i++) {
                array[(front + count[copyOfArray[i]]) % capacity] = copyOfArray[i];
                count[copyOfArray[i]]++;
            }
            delete[] copyOfArray;
            ordered = -1;
        }

        // Search
        int Search(elmtype e) {
            if(ordered == 1 || ordered == -1) {
                return binarySearch(0, size - 1, e);
            }
            else {
                for(int i = 0; i < size; i++) {
                    if(array[(front + i) % capacity] == e) {
                        return i;
                    }
                }
                return -1;
            }
        }

        // TESTING CODE
        // print the array
        void printArray() {
            cout << "Size: " << size << endl;
            cout << "Capacity: " << capacity << endl;
            cout << "Front: " << front << endl;
            cout << "Ordered: " << ordered << endl;
            cout << "Array:" << endl;
            cout << "[ ";
            for (int i = 0; i < capacity; i++) {
                cout << array[i] << " ";
            }
            cout << "]" << endl;
        }

};
