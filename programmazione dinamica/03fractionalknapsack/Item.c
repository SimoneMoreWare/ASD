#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMscan() {
  Item A;
  printf("name, weight, value: ");
  scanf("%s %f %f", A.name, &(A.weight), &(A.value));
  A.ratio = A.value/A.weight;
  return A;
}

void ITEMstore(Item A) {
  printf("name= %s \t weight= %.2f \t value = %.2f \t fract= %.2f \n", A.name, A.weight, A.value, A.fract);
}

int ITEMeq(Item A, Item B) {
  return (A.ratio == B.ratio);
}

int ITEMgt(Item A, Item B) {
  return (A.ratio > B.ratio);
}

Key KEYgetW(Item A) {
  return (A.weight);
}

Key KEYgetV(Item A) {
  return (A.value);
}

Key KEYgetF(Item A) {
  return (A.fract);
}

void   KEYsetF(Item *pA, float f) {
  pA->fract = f;
}
