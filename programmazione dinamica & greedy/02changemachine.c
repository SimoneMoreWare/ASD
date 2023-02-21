#include <stdio.h>
#include <stdlib.h>

int main() {
  int numden, *denomination, *coins, amount, i;

  printf("Enter number of denominations: ");
  scanf("%d", &numden);

  denomination = calloc(numden, sizeof(int));
  coins = calloc(numden, sizeof(int));

  printf("Enter denominations in cents in decreasing order\n");
  for (i=0; i<numden; i++) {
    printf("denomination[%d] = ", i);
    scanf("%d", &denomination[i]);
  }

  printf("Enter change in cents:");
  scanf("%d", &amount);

  for (i=0; i < numden; i++) {
    coins[i] = amount / denomination[i];
    amount = amount - (amount/denomination[i])*denomination[i];
    printf("Number of  %d cent coins = %d \n", denomination[i], coins[i]);
  }
  return 0;
}


