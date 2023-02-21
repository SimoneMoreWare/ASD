#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Item.h"
#include "RecursiveSorting.h"
#define DBG 1

int main(int argc, char *argv[]) {
  int i=0, N, sw;
    Item *a, *b;

  if (argc !=3) {
    printf("Error in command line, correct format: \n");
    printf("client <number of keys> <1 for random input, 0 for for input from keyboard\n");
    exit(1);
  }

  N = atoi(argv[1]);
  sw = atoi(argv[2]);

  a = (Item *)malloc(N*sizeof(Item));

  if (a == NULL) {
    printf("Memory allocation error\n");
    return EXIT_FAILURE;
  }

  b = (Item *)malloc(N*sizeof(Item));

  if (b == NULL) {
    printf("Memory allocation error\n");
    return EXIT_FAILURE;
  }

  if (sw) {
    printf("Filling in the array with random values\n");
    srand(time(NULL));
    for (i = 0; i < N; i++)
      a[i] = ITEMrand();
  }
  else {
    printf("Input array values (key is >=0) \n");
    for (i = 0; i < N; i++)
      a[i] = ITEMscan();
    printf("\n");
  }

#if DBG
  printf("The original array is\n");
  for (i = 0; i <N; i++) {
    printf("a[%d]: ", i);
    ITEMshow(a[i]);
  }
  printf("\n");
#endif

  printf("\nRecursive Sorting Algorithms\n");
  printf("===============\n");
  printf("1. Merge sort\n");
  printf("2. Quicksort\n");
  printf("3. Exit\n");
  printf("Enter your choice : ");
  if(scanf("%d",&i)<=0) {
    printf("Integers only!\n");
    exit(0);
  }
  else {
    switch(i) {
      case 1:     MergeSort(a, b, N);
                  break;
      case 2:     QuickSort(a, N);
                  break;
      case 3:     break;
      default:    printf("Invalid option\n");
    }
  }
  printf("Array a sorted in ascending order for key x is:\n");
  for (i = 0; i <N; i++) {
    printf("a[%d]: ", i);
    ITEMshow(a[i]);
  }
  printf("\n");
  return 0;
}
