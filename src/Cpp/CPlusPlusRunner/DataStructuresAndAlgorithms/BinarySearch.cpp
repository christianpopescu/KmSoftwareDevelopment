#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


//ToDo: Refactor to create binary search pattern for egality, inegality in general case 

/* 
*  Find last less than 4
*  To process the case where variable not in list !!!!
*/
int BinarySearch(vector<int>& a, int l, int r)
{
    int m;
    while (l < r - 1)
    {
        m = (r + l) / 2;
        if (a[m] < 4)
        {
            return BinarySearch(a, m , r);
        }
        else
        {
            return BinarySearch(a, l, m);
        }
    }
    return l;
}


int main()
{
    cout << "Binary search" << endl;

    vector<int> a  {8, 5, 7, 29, 5, 67, 7, 34};
    sort(begin(a), end(a));
    cout << BinarySearch(a, 0, 8) << endl;

    return 0;
}