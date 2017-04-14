// Program to print all combination of size r in an array of size n
#include <stdio.h>

// Enumerate all combinations of size <= r in (0, 1, ..., n) and print to file "combinations.txt"
// Credit to: http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
/* 
   data[] ---> Temporary array to store current combination
   start & end ---> Staring and Ending indexes in arr[]
   index  ---> Current index in data[]
   r ---> Maximum size of a combination to be printed */

void combination(FILE *f, int data[], int start, int end, int index, int r)
{
    // Current combination is ready to be printed, print it
    if (index == r || start > end )
    {
        for (int j=0; j<index; j++){
            if(data[j] < end) fprintf(f, "%d ", data[j]);
        }      
        fprintf(f, "\n");
        return;
    }
 
    // replace index with all possible elements. The condition
    for (int i=start; i<=end; i++)
    {
        data[index] = i;
        combination(f, data, i+1, end, index+1, r);
    }
}


// Driver program to test above functions
int main()
{
    int r = 3; //number of malware
    int n = 50; //n benign files, n+1 possible positions (0, 1, 2, 3, ..., n), treat "n+1" as eof
    int data[r];

    FILE *f = fopen("combinations.txt", "w");
    combination(f, data, 0, n+1, 0, r);

    fclose(f);
}





