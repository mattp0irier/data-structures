#include <iostream>
#include <stdlib.h>

template <typename elmtype>
class CDA {
    private:
        int size, capacity, front, ordered;
        elmtype error, *array;

        // Array Resizing
        void increaseCapacity() {
            int tempOrdered = ordered; // keep order so not lost when using access brackets
            capacity *= 2; // double capacity
            elmtype* newA = new elmtype[capacity];
            for(int i = 0; i < size; i++) {
                newA[i] = array[(front + i) % size]; // copy items to front of new array
            }
            delete[] array; // delete old array
            array = newA;
            front = 0;
            ordered = tempOrdered;
        }
        void decreaseCapacity() {
            int tempOrdered = ordered; // keep order so not lost when using access brackets
            if(capacity / 2 >= 4) capacity /= 2;	// half capacity...if statement to prevent capacity from going below 4
            elmtype* newA = new elmtype[capacity];
            for(int i = 0; i < size; i++) {
                newA[i] = array[(front + i) % (capacity*2)]; // copy items to front of new array
            }
            delete[] array; // delete old array
            array = newA;
            front = 0;
            ordered = tempOrdered;
        }

        // Merge Sort
        void mergeSortMerge(elmtype values[], int start, int middle, int end, elmtype temp[]) {
            int index1 = start;
            int index2 = middle + 1;
            int tempNextIndex = start; // index to place next value in temp array

            // sort into temp while both halves have values
            while(index1 <= middle && index2 <= end) {
                if(values[(front + index1) % capacity] > values[(front + index2) % capacity]) { // if value from first half is greater than value from second half
                    temp[tempNextIndex] = values[(front + index1) % capacity]; // add to new array
                    index1++;
                }
                else { // else value from second half is greater
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
                // call merge sort on each half
                mergeSortRecursive(values, start, middle, temp);
                mergeSortRecursive(values, middle + 1, end, temp);
                // call merge
                mergeSortMerge(values, start, middle, end, temp);
            }
        }

        // Binary Search
        int binarySearch(int start, int end, elmtype e) {
            if(ordered == 1) { // if ascending order
                if(end >= start) {
                    int middle = (start + end) / 2;
                    if (array[(front + middle) % capacity] == e) { // if equal, value found
                        return middle;
                    }
                    if (array[(front + middle) % capacity] > e) { // if array value is greater than search key, search lower half
                        return binarySearch(start, middle - 1, e);
                    }
                    return binarySearch(middle + 1, end, e); // else search upper half
                }
                return -1;
            }
            if(ordered == -1) { // if descending order
                if(end >= start) {
                    int middle = (start + end) / 2;
                    if (array[(front + middle) % capacity] == e) {  // if equal, value found
                        return middle;
                    }
                    if (array[(front + middle) % capacity] < e) { // if array value is less than search key, search first half
                        return binarySearch(start, middle - 1, e);
                    }
                    return binarySearch(middle + 1, end, e); // else search second half
                }
                return -1;
            }
            return -1;
        }

        // Quickselect
        elmtype quickSelect(elmtype selectArray[], int front, int back, int k) {
            if(front == back) { // base case
                return selectArray[front];
            }
            int pivotIndex = rand() % (back - front + 1) + front; // choose random pivot
            // swap pivot to back
            elmtype pivot = selectArray[pivotIndex];
            elmtype tempSwap = selectArray[back];
            selectArray[back] = selectArray[pivotIndex];
            selectArray[pivotIndex] = tempSwap;
            int nextIndex = front;
            for(int i = front; i < back; i++) {
                // if elements are less than the pivot, move them to left half of array
                if (selectArray[i] < pivot) {
                    tempSwap = selectArray[i];
                    selectArray[i] = selectArray[nextIndex];
                    selectArray[nextIndex] = tempSwap;
                    nextIndex++;
                }
            }
            // swap element at midpoint and pivot
            tempSwap = selectArray[back];
            selectArray[back] = selectArray[nextIndex];
            selectArray[nextIndex] = tempSwap;
            pivotIndex = nextIndex;
            // if value of interest equals value at "midpoint"
            if(k == pivotIndex + 1) {
                return selectArray[k - 1];
            }
            else if ((k < pivotIndex + 1)) { // else if value of interest is less than "midpoint", call quickselect on left "half"
                return quickSelect(selectArray, front, pivotIndex - 1, k);
            }
            else { // else value of interest is greater than "midpoint", call quickselect on right "half"
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
            array = new elmtype[capacity]; // create new array
            for(int i = 0; i < size; i++) {
                array[i] = src.array[(src.front + i) % src.capacity]; // copy elements to front of new array
            }
            ordered = src.ordered;
        }
        CDA& operator=(const CDA& src) {
            if(this != &src) {
                delete[] array; // delete existing array
                capacity = src.capacity;
                size = src.size;
                front = 0;
                array = new int[capacity]; // create new array
                for(int i = 0; i < size; i++) {
                    array[i] = src.array[(src.front + i) % src.capacity]; // copy elements to front of new array
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
            ordered = 0; // clear ordered when [] operator used, since the array may no longer be ordered
            return array[(front + i) % capacity];
        }

        // get function same as operator (added for BHeaps)
        elmtype& get(int i) {
            if(i < 0 || i >= size) {
                cout << "Error: Index " << i << " is out of bounds" << endl;
                return error;
            }
            ordered = 0;  // clear ordered when get used, since the array may no longer be ordered
            return array[(front + i) % capacity];
        }

        // Add
        void AddEnd(elmtype v) {
            if (size == capacity) { // if array is full, increase size
                increaseCapacity();
            }
            // if element breaks order, clear ordered flag
            if((ordered == 1 && (array[((front+size) % capacity) - 1] > v)) || (ordered == -1 && (array[((front+size) % capacity) - 1] < v))) {
                ordered = 0;
            }
            // add element to next slot in array
            array[(front+size) % capacity] = v;
            size++;
            if(size == 2) { // when size is 2, the array should be checked for order
                SetOrdered();
            }
        }
        void AddFront(elmtype v) {
            if (size == capacity) { // if array is full, increase size
                increaseCapacity();
            }
            // if element breaks order, clear ordered flag
            if((ordered == 1 && (array[front] < v)) || (ordered == -1 && (array[front] > v))) {
                ordered = 0;
            }
            if(front != 0) { // if front of array is not 0, then element can be added at the beginning
                array[front-1] = v;
                front--;
            }
            else { // if front is currently 0, element must be added to end of array
                array[capacity-1] = v;
                front = capacity - 1;
            }
            size++;
            if(size == 2) { // check order when size is 2
                SetOrdered();
            }
        }

        // Delete
        void DelEnd() {
            if(size != 0) { // check that array has elements
                size--;
                if(capacity > 4 && capacity / size >= 4) { // if capacity should be reduced, reduce capacity
                    decreaseCapacity();
                }
                if(size == 2) { // check order if size is 2
                    SetOrdered();
                }
            }
            else {
                cout << "Error: The array is empty" << endl;
            }
        }
        void DelFront() {
            if(size != 0) { // check that array has elements
                if(front != capacity - 1) { // if front is not the back, simply move the front pointer
                    front++;
                }
                else { // if array is back, set front to beginning of array
                    front = 0;
                }
                size--;
                if(capacity > 4 && capacity / size >= 4) { // check if capacity should be reduced
                    decreaseCapacity();
                }
                if(size == 2) { // check order when size is 2
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
                if (array[(front + i) % capacity] > array[(front + i + 1) % capacity]) { // if element is greater than the next element, array cannot be ascending
                    ascending = false;
                }
                if (array[(front + i) % capacity] < array[(front + i + 1) % capacity]) { // if element is less than next element, array cannot be descending
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
            // error check
            if (size == 0) {
                cout << "Error: The array is empty" << endl;
                return error;
            }
            if (k > size || k <= 0) {
                cout << "Error: out of bounds" << endl;
                return error;
            }
            // if array is ordered, simply select the kth element
            if (ordered == 1) {
                return array[(front + k - 1) % capacity];
            }
            if (ordered == -1) {
                return array[(front + (size - k)) % capacity];
            }
            // else call quickSelect
            elmtype* selectArray = new elmtype[size]; // temp array for quickSelect
            for(int i = 0; i < size; i++) {
                selectArray[i] = array[(front + i) % capacity];
            }
            elmtype value = quickSelect(selectArray, 0, size - 1, k);
            delete[] selectArray;
            return value;
        }
        void InsertionSort() {
            for(int i = 1; i < size; i++) { // for entire array
                elmtype current = array[(front + i) % capacity];
                int check = i - 1;
                while(check >= 0 && current > array[(front + check) % capacity]) { // shift elements down until current element is less than the next element
                    array[(front + check + 1) % capacity] = array[(front + check) % capacity];
                    check--;
                }
                array[(front + check + 1) % capacity] = current; // return current element to array
            }
            ordered = -1; // now in descending order, so set flag
        }
        void MergeSort() {
            elmtype* tempArray = new elmtype[size]; // temp array for mergeSort
            mergeSortRecursive(array, 0, size - 1, tempArray); // first recursive call
            ordered = -1; // now in descending order, so set flag
            delete[] tempArray;
        }
        void CountingSort(int m) {
            int* count = new int[m+1];
            elmtype* copyOfArray = new elmtype[size]; // tmep array for problem
            for(int i = 0; i < m+1; i++) { // array to hold counts of each integer
                count[i] = 0;
            }
            for(int i = 0; i < size; i++) { // copy array to front of temp array
                copyOfArray[i] = array[(front + i) % capacity];
                count[copyOfArray[i]]++; // count digits
            }
            int total = 0; // value to keep track of where values should be inserted 
            for(int i = m; i >= 0; i--) { // for each digit, adjust count value for number of items greater than that digit
                int temp = count[i]; 
                count[i] = total;
                total += temp;
            }
            for(int i = 0; i < size; i++) {  // copy values back into new array
                array[(front + count[copyOfArray[i]]) % capacity] = copyOfArray[i]; // add current value in copiedArray proper spot in original array
                count[copyOfArray[i]]++; // increase count so the next element of that digit is placed in the proper spot
            }
            delete[] copyOfArray;
            ordered = -1; // set ordered flag to decreasing
        }

        // Search
        int Search(elmtype e) {
            if(ordered == 1 || ordered == -1) { // use binary search if array is ordered
                return binarySearch(0, size - 1, e);
            }
            else { // else use linear search
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
