#include <iostream>
#include <fstream> // file di testo

using namespace std;

ifstream input("input.txt");

void stampa(int array[], int size)
{
   for (int i = 0; i < size; i++)
      cout << array[i] << " ";
   cout << endl;
}

void merge(int *array, int first, int mid, int last)
{
   int i, j, k, nLeft, nRight;
   nLeft = mid - first + 1;
   nRight = last - mid;
   int larr[nLeft], rarr[nRight];
   for (i = 0; i < nLeft; i++)
      larr[i] = array[first + i];
   for (j = 0; j < nRight; j++)
      rarr[j] = array[mid + 1 + j];

   i = 0;
   j = 0;
   k = first;

   while (i < nLeft && j < nRight)
   {
      if (larr[i] < rarr[j])
      {
         array[k] = larr[i];
         i++;
      }
      else
      {
         array[k] = rarr[j];
         j++;
      }
      k++;
   }
   while (i < nLeft)
   {
      array[k] = larr[i];
      i++;
      k++;
   }
   while (j < nRight)
   {
      array[k] = rarr[j];
      j++;
      k++;
   }
}
void mergeSort(int *array, int first, int last)
{
   if (first < last)
   {
      int mid = (last + first) / 2;
      mergeSort(array, first, mid);
      mergeSort(array, mid + 1, last);
      merge(array, first, mid, last);
   }
}

void mergeK(int *array, int k, int primi[], int last)
{
   int index[k];
   for (int i = 0; i < k; i++)
   {
      index[i] = primi[i];
   }
   int tmp[last-primi[0]+1];
   int min, posMin;
   for (int i = primi[0]; i <= last; i++)
   {
      min = INT16_MAX;
      posMin=0;
      for (int j = 0; j < k - 1; j++)
      {
         if (index[j] < primi[j + 1])
         {
            if (array[index[j]] < min)
            {
               posMin = j;
               min = array[index[j]];
            }
         }
      }
      if (index[k - 1] <= last)
      {
         if (array[index[k - 1]] < min)
         {
            posMin = k - 1;
            min = array[index[k - 1]];
         }
      }
      tmp[i]=min;
      index[posMin]++;
   }
   for (int i = 0; i <= last; i++)
   {
      array[i+primi[0]]=tmp[i];
   }
   stampa(tmp, sizeof(tmp));
}

void mergeSortK(int *array, int first, int last, int k)
{
   if (first < last)
   {
      int distanza = (last - first) / k + 1;
      int primi[k];
      primi[0] = first;
      for (int i = 1; i < k; i++)
      {
         primi[i] = primi[i - 1] + distanza;
         mergeSortK(array, primi[i - 1], primi[i] - 1, k);
      }
      mergeSortK(array, primi[k - 1], last, k);
      mergeK(array, k, primi, last);
   }
}
int main()
{
   int n;
   input >> n;
   int arr[n];
   for (int i = 0; i < n; i++)
   {
      input >> arr[i];
   }
   mergeSortK(arr, 0, n - 1, 2);
   stampa(arr, n);
}