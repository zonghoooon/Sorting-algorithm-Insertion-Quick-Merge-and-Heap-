// Sort shuffled 100,000 integer using Insertion, Quick, Merge, and Quick sort algorithm

#include <iostream>
#include <random>
#include <ctime>
using namespace std;
#define NUM 100000
int list[NUM];

class Sort {
private:
    int sorted[NUM + 1];
    int Quick_partition(int first, int last) {
        int pivot, low, high;
        low = first;
        high = last + 1;
        pivot = list[first];

        do {
            do {
                low++;
            } while (low <= last && list[low] < pivot);
            do {
                high--;
            } while (high >= first && list[high] > pivot);
            if (low < high) swap(list[low], list[high]);
        } while (low < high);
        swap(list[first], list[high]);
        return high;
    }

    void Merge_set(int first, int mid, int last) {
        int a = first;
        int b = mid + 1;
        int c = first;
        while (a <= mid && b <= last) {
            if (list[a] <= list[b]) sorted[c++] = list[a++];
            else sorted[c++] = list[b++];
        }
        if (a > mid) {
            for (int i = b; i <= last; i++) sorted[c++] = list[i];
        }
        else {
            for (int i = a; i <= mid; i++) sorted[c++] = list[i];
        }
        for (int i = first; i <= last; i++) list[i] = sorted[i];
    } 
    void Heap_Insert_max_heap(int key, int size) {
        int i = ++size;
        while ((i != 1) && (key > sorted[i / 2])) {
            sorted[i] = sorted[i / 2];
            i /= 2;
        }
        sorted[i] = key;
    } 
    int Selection_partition(int arr[], int first, int last, int pivot, bool linear) {
        int low, high;
        low = first;
        high = last + 1;
        if (!linear) pivot = arr[first];
        else {
            for (int i = first; i <= last; i++) {
                if (arr[i] == pivot) {
                    swap(arr[first], arr[i]);
                    break;
                }
            }
        }//locate the piivot front

        do {
            do {
                low++;
            } while (low <= last && arr[low] < pivot);
            do {
                high--;
            } while (high >= first && arr[high] > pivot);
            if (low < high) swap(arr[low], arr[high]);
        } while (low < high);
        swap(arr[first], arr[high]);
        return high;
    }
    

public:
    void Insertion() {
        int key, j;
        for (int i = 1; i < NUM; i++) {
            key = list[i];
            for (j = i - 1; j >= 0 && list[j] > key; j--) {
                list[j + 1] = list[j];
            }
            list[j + 1] = key;
        }
    }
    void Quick(int first, int last) {
        if (first < last) {
            int q = Quick_partition(first, last);
            Quick(first, q - 1);
            Quick(q + 1, last);
        }
    }
    void Merge(int first, int last) {
        if (first < last) {
            int mid = (first + last) / 2;
            Merge(first, mid);
            Merge(mid + 1, last);
            Merge_set(first, mid, last);
        }
    }
    void Heap() {
        int parent, child, item, temp;
        int count = NUM;
        for (int i = 0; i < NUM; i++) Heap_Insert_max_heap(list[i], i);
        for (int i = NUM - 1; i >= 0; i--) {
            parent = 1;
            child = 2;
            item = sorted[1];
            temp = sorted[count--];
            while (child <= count) {
                if ((child < count) && (sorted[child] < sorted[child + 1])) child++;
                if (temp >= sorted[child]) break;
                sorted[parent] = sorted[child];
                parent = child;
                child *= 2;
            }
            sorted[parent] = temp;
            list[i] = item;
        }
    }
   
    bool Sort_checker() {
        for (int i = 0; i < NUM - 1; i++) {
            if (list[i] > list[i + 1]) return false;
        }
        return true;
    }

}; 

class Array {
private:
    void Shuffle(int list[]) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, NUM - 1);
        int ran;
        for (int i = 0; i < NUM; i++) {
            ran = dis(gen);
            swap(list[i], list[ran]);
        }
    }
public:
    void Make() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(1, 10);
        int temp = 0;
        for (int i = 0; i < NUM; i++) {
            temp += dis(gen);
            list[i] += temp;
        }
        Shuffle(list);
    }
};
int main()
{
    int choose;
    bool selection = false;
    Sort sort = Sort();
    Array array = Array();
    array.Make();

    cout << "Choose the algorithm\n" << "1. Insertion\n" << "2. Quick\n" << "3. Merge\n" << "4. Heap\n";
    cin >> choose;
    clock_t t = clock();

    switch (choose) {
    case 1:
        sort.Insertion();
        break;
    case 2:
        sort.Quick(0, NUM - 1);
        break;
    case 3:
        sort.Merge(0, NUM - 1);
        break;
    case 4:
        sort.Heap();
        break;
    default:
        cout << "Wrong number.\n";
        return 1;
    }

    t = clock() - t;
    cout << t << "ms" << endl;

    int temp;
    cout << "Enter '0' to verify that the sorting is correct" << endl;
    cin >> temp;
    if (temp == 0) {
        if (sort.Sort_checker()) cout << "sorting is correct" << endl;
        else cout << "sorting is not correct." << endl;
    }

    cout << "Enter '0' to see the sorted array" << endl;
    cin >> temp;
    if (temp == 0) {
        for (int i = 0; i < NUM; i++) {
            cout << list[i] << " ";
            if ((i + 1) % 15 == 0) cout << endl;
        }
    }

}

/*result
        (first test running time, second test running time, third test running time)

        1. Insertion Sort:  (3188ms, 3206ms, 3095ms)
        2. Quick Sort: (9ms, 10ms, 10ms)
        3. Merge Sort: (14ms, 11ms, 13ms)
        4. Heap Sort: (14ms, 14ms, 13ms)
*/