#include <iostream>
#include <vector>

using namespace std;


//todo: to implement the modifiable heap

void Heapify(vector<int>& arr, int i, int heapSize = -2) {
    if (heapSize == 0) return;
    int n = arr.size();
    if (heapSize > 0) n = heapSize;
    if (i > n - 1) return;
    int l { 2 * i };
    int r{ 2 * i + 1 };
    int greatest = i;
    if (l < n) {
        if (arr[l] > arr[i]) greatest = l;
        if (r < n && arr[r] > arr[greatest]) greatest = r;
    }
    if (greatest != i) {
        swap(arr[greatest], arr[i]);
        Heapify(arr, greatest, heapSize);
    }

}

void MakeHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i{ n / 2 }; i >= 0 ; --i) {
        Heapify(arr, i);
    }

}

void HeapSort(vector<int>& arr) {
    MakeHeap(arr);
    int n = arr.size();
    for (int i{ n - 1 }; i > 0; i--) {
        swap(arr[0], arr[i]);
        Heapify(arr, 0, i-1);
    }

}


int main()
{
    cout << "Heap" << endl;

    vector<int> vec { 25, 7, 1, 2, 3, 4, 5, 14, 32};

//    MakeHeap(vec);
    HeapSort(vec);
    return 0;
}