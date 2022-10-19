using namespace std;

void swap(int *v, int i, int j){
   int tmp=v[i];
   v[i] = v[j];
   v[j] = tmp;
}

void reverse_array(int *v, int i, int j)
{
   if (i < j)
   {
      swap(v,i,j);
      reverse_array(v, i + 1, j - 1);
   }
}

void ruota_array(int *v, int N, int shift)
{
   if (shift < 0)
   {
      shift = N + shift;
   }
   shift %= N;
   reverse_array(v, 0, N - 1);
   reverse_array(v, 0, shift - 1);
   reverse_array(v, shift, N - 1);
}

string stampa_array(int v[], int N)
{
   string s = "";
   for (int i = 0; i < N; i++)
   {
      s += to_string(v[i]) + " ";
   }
   s += "\n";
   return s;
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

void merge_sort_ricorsione(int *array, int first, int last)
{
   if (first < last)
   {
      int mid = (last + first) / 2;
      merge_sort_ricorsione(array, first, mid);
      merge_sort_ricorsione(array, mid + 1, last);
      merge(array, first, mid, last);
   }
}

void merge_sort(int *array, int n)
{
   merge_sort_ricorsione(array, 0, n - 1);
}

int binary_reserch_rec(int *array, int i, int j, int e)
{
   if (i > j) return -1;
   else
   {
      int mid = (i + j) / 2;
      if(array[mid]==e) return mid;
      else{
         if(array[mid]>e) return binary_reserch_rec(array, i, mid-1, e);
         else return binary_reserch_rec(array, mid+1, j, e);
      }
   }
}

int binary_reserch(int *array, int N, int e){
   return binary_reserch_rec(array, 0, N-1, e);
}

int sottosequenza_max(int *v, int N){
   int seqTmp=0, seqMax=0;
   for(int i = 0; i<N; i++){
        seqTmp += lista[i];
        if(seqTmp > seqMax) seqMax=seqTmp; 
        else if(seqTmp < 0) seqTmp = 0;
   }
   return seqMax;
}