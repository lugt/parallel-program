#include<iostream>
#include<omp.h>
#include<ctime>
#include <cstdlib>
#include<vector>
using namespace std;

int partition(int *arr, int low_index, int high_index)
{
    int left, right, middle;
    middle = arr[low_index];
    left= low_index + 1;
    right= high_index;
    while(left <= right)
    {
        while(left < high_index && middle >= arr[left])
            left++;
        while(middle < arr[right])
            right--;
        if(left < right)
        {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
        else
        {
            int temp= arr[low_index];
            arr[low_index] = arr[right];
            arr[right]= temp;
            return(right);
        }
    }
}

void quicksort(int *arr, int low_index, int high_index)
{
    int right;

    if(low_index < high_index)
    {
        right = partition(arr, low_index, high_index);

        quicksort(arr, low_index, right - 1);

        quicksort(arr, right + 1, high_index);

    }
}


int main()
{
    int n = 1000000,i;
    srand(time(0));
    int *arr = new int[n];
    for(i=0;i < n;i++)
    {
        arr[i] = rand() % n + 1;
    }
    quicksort(arr, 0, n - 1);
    //    cout<<"Elements of array after sorting \n";
    for(int i = 0; i < n; i++)
    {
          cout<<arr[i]<<"\t";
    }

    //    cout<<"\n";
}
