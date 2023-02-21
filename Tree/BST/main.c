#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#include "Item.h"
#include "BST.h"

int main() {
  char sel[2], *sc;
  int r, stop = 0;
  BST bst = NULL;
  Item x;
  Key k;

  do {
        printf("\n\n Select operation:\n");
        printf("\tA: Create BST\n");
        printf("\tB: Insert item in leaf (iterative)\n");
        printf("\tC: Insert item in leaf (recursive)\n");
        printf("\tD: Insert item in root\n");
        printf("\tE: Search for item with given key\n");
        printf("\tF: Delete item with given key\n");
        printf("\tG: Minimum-key item\n");
        printf("\tH: Maximum-key item\n");
        printf("\tI: Select item with given rank\n");
        printf("\tJ: Predecessor of item with given key\n");
        printf("\tK: Successor of item with given key\n");
        printf("\tL: Preorder visit\n");
        printf("\tM: Inorder visit\n");
        printf("\tN: Postorder visit\n");
        printf("\tO: Balance BST\n");
        printf("\tP: Destroy BST\n");
        printf("\tZ: Exit\n");
        scanf("%s", sel);
        for (sc=sel; !isalpha(*sc); sc++);

        *sc = toupper(*sc);

        switch(*sc) {
            case 'A': {
                if (bst == NULL)
                  bst = BSTinit();
            }
            break;
            case 'B': {
                x = ITEMscan();
                if (bst == NULL)
                  bst = BSTinit();
               BSTinsert_leafI(bst, x);
            }
            break;
            case 'C': {
                x = ITEMscan(stdin);
                if (bst == NULL)
                  bst = BSTinit();
                BSTinsert_leafR(bst, x);
            }
            break;
            case 'D': {
                x = ITEMscan(stdin);
                if (bst == NULL)
                  bst = BSTinit();
                BSTinsert_root(bst, x);
            }
            break;
            case 'E': {
                printf("Input key: ");
                k = KEYscan();
                x = BSTsearch(bst, k);
                if (ITEMcheckNull(x))
                  printf("Item with given key not found\n");
                else
                  ITEMstore(x);
            }
            break;
            case 'F': {
                printf("Input key: ");
                k = KEYscan();
                x = BSTsearch(bst, k);
                if (ITEMcheckNull(x))
                  printf("Item with given key not found!\n");
                else
                  BSTdelete(bst, k);
            }
            break;
            case 'G': {
                printf("Mininum-key item: ");
                ITEMstore(BSTmin(bst));
            }
            break;
            case 'H': {
                printf("Maximum-key item: ");
                ITEMstore(BSTmax(bst));
            }
            break;
            case 'I': {
                printf("Input rank: ");
                scanf("%d", &r);
                if (r >= BSTcount(bst))
                  printf("rank outside range \n");
                else {
                  printf("Item of rank %d is: ", r);
                  ITEMstore(BSTselect(bst, r));
                }
            }
            break;
            case 'J': {
                printf("Input key: ");
                k = KEYscan();
                x = BSTpred(bst, k);
                if (ITEMcheckNull(x))
                  printf("predecessor doesn't exist\n");
                else
                  ITEMstore(x);
            }
            break;
            case 'K': {
                printf("Input key: ");
                k = KEYscan();
                x = BSTsucc(bst, k);
                if (ITEMcheckNull(x))
                  printf("successor doesn't exist\n");
                else
                  ITEMstore(x);
            }
            break;
            case 'L': {
                printf("Preorder visit:\n");
                BSTvisit(bst, PREORDER);
            }
            break;
            case 'M': {
                printf("Inorder visit:\n");
                BSTvisit(bst, INORDER);
            }
            break;
            case 'N': {
                printf("Postorder visit:\n");
                BSTvisit(bst, POSTORDER);
            }
            break;
            case 'O': {
                printf("\nBST balanced!\n");
                BSTbalance(bst);
            }
            break;
            case 'P': {
                printf("\nBST destroyed!\n");
                stop = 1;
                BSTfree(bst);
            }
            break;
            case 'Z': {
                stop = 1;
                BSTfree(bst);
            }
            break;
                default:
                printf("Invalid selection!\n");
        }
  } while(!stop);

  return 0;
}
