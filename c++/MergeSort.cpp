#include<iostream>
#include <fstream> // file di testo

using namespace std;

ifstream input("input.txt");

void stampa(int array[], int size) {
   for(int i = 0; i<size; i++)
      cout << array[i] << " ";
   cout << endl;
}

void merge(int *array, int first, int mid, int last) {
   int i, j, k, nLeft, nRight;
   nLeft = mid-first+1; nRight = last-mid;
   int larr[nLeft], rarr[nRight];
   for(i = 0; i<nLeft; i++)
      larr[i] = array[first+i];
   for(j = 0; j<nRight; j++)
      rarr[j] = array[mid+1+j];

   i = 0; j = 0; k = first;

   while(i < nLeft && j<nRight) {
      if(larr[i] < rarr[j]) {
         array[k] = larr[i];
         i++;
      }else{
         array[k] = rarr[j];
         j++;
      }
      k++;
   }
   while(i<nLeft) {
      array[k] = larr[i];
      i++; k++;
   }
   while(j<nRight) {
      array[k] = rarr[j];
      j++; k++;
   }
}
void mergeSort(int *array, int first, int last) {
   int mid;
   if(first < last) {
      mid = (last+first)/2;
      mergeSort(array, first, mid);
      mergeSort(array, mid+1, last);
      merge(array, first, mid, last);
   }
}
int main() {
   int n;
   input >> n;
   int arr[n];
   for(int i = 0; i<n; i++) {
      input >> arr[i];
   }
   mergeSort(arr, 0, n-1);  
   stampa(arr, n);
}