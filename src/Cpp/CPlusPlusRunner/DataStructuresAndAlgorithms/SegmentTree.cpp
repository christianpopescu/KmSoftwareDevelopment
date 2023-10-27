#include <iostream>
#include <vector>
using namespace std;


int getSum(int l, int r, vector<int> arr, int n);
int getSumVerif(int l, int r, vector<int> a);
void add(int index, int value, vector<int>& arr, int n);

int main()
{
    cout << "Segment tree" << endl;

    vector<int>  a {5, 7, 9, 20, 1, 7};
    int n = static_cast<int> (a.size());
    int nn = 2*n;
    vector<int> segmentTree;
    // fill segment tree
    segmentTree.resize(nn, 0);

    for (int i{0}; i < n; ++i)
        segmentTree[i + n] = a[i];
    for (int i{ nn - 1 }; i > 1; --i)

        segmentTree[i / 2] += segmentTree[i];



    cout << getSum(0, 5, segmentTree, 6) << endl;
    cout << getSumVerif(0, 5, a) << endl;

    add(5, 6, segmentTree, 6);
    a[5] += 6;
    cout << getSum(0, 5, segmentTree, 6) << endl;
    cout << getSumVerif(0, 5, a) << endl;

    cout << "Segment tree end" << endl;
    return 0;
}

int getSum(int l, int r, vector<int> arr, int n)
{
    l += n;
    r += n;
    int s{ 0 };
    while (l <= r) {
        if (l % 2 == 1) s += arr[l++];
        if (r % 2 == 0) s += arr[r--];
        l /= 2;
        r /= 2;
    }
    return s;
}

int getSumVerif(int l, int r, vector<int> a)
{
    int sum{ 0 };
    for (int i{ l }; i <= r; ++i)
        sum += a[i];
    return sum;

}

void add(int index, int value, vector<int>& arr, int n)
{
    index += n;
    arr[index] += value;
    for (index /= 2; index > 1; index /= 2)
    {
        arr[index] = arr[2 * index] + arr[2 * index + 1];
    }
}