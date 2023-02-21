#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#include "Item.h"
#include "BST.h"

int main(int argc, char **argv) {
  char sel[5], fname[100], name[MAXC], *sc;
  int stop = 0;
  BST bst = NULL;
  FILE *fin, *fout;
  Item x = NULL;

  do {
        printf("\n\n * Select operation?\n");
        printf("\tA: Create new BST\n");
        printf("\tB: Display number of nodes\n");
        printf("\tC: Insert in leaf\n");
        printf("\tD: Insert in root\n");
        printf("\tE: Search for node\n");
        printf("\tF: Display MIN\n");
        printf("\tG: Display MAX\n");
        printf("\tH: Visit IN ORDER\n");
        printf("\tI: Visit in PRE ORDER\n");
        printf("\tJ: Visit in POST ORDER\n");
        printf("\tK: Display tree height\n");
        printf("\tL: Display number of leaves\n");
        printf("\tM: Store to file\n");
        printf("\tN: Load from file\n");
        printf("\tZ: Exit\n");
        scanf("%s", sel);

        for (sc=sel; !isalpha(*sc); sc++);

        *sc = toupper(*sc);

        switch(*sc) {
            case 'A': {
                if (bst == NULL) {
                  bst = BSTinit();
                  if (bst == NULL)
                    exit(-1);
                }
            }
            break;
            case 'B': {
                if (bst == NULL) {
                  bst = BSTinit();
                  if (bst == NULL)
                    exit(-1);
                }
                printf("Number of nodes = %d\n", BSTcount(bst));
            }
            break;
            case 'C': {
                x = ITEMscan(stdin);
                if (x == NULL)
                  exit(-1);
                if (bst == NULL) {
                  bst = BSTinit();
                  if (bst == NULL)
                    exit(-1);
                }
                BSTinsert_leaf(bst, x);
                ITEMfree(x);
            }
            break;
            case 'D': {
                x = ITEMscan(stdin);
                if (x == NULL)
                  exit(-1);
                if (bst == NULL) {
                  bst = BSTinit();
                  if (bst == NULL)
                    exit(-1);
                }
                BSTinsert_root(bst, x);
                ITEMfree(x);
            }
            break;
            case 'E': {
                printf("Input product name: ");
                scanf("%s", name);
                x = ITEMfill(name, -1);
                if (x == NULL)
                  exit(-1);
                ITEMstore(stdout, BSTsearch(bst, x));
                ITEMfree(x);
            }
            break;
            case 'F': {
                ITEMstore(stdout,BSTmin(bst));
            }
            break;
            case 'G': {
                ITEMstore(stdout,BSTmax(bst));
            }
            break;
            case 'H': {
                BSTsort(bst, stdout, INORDER);
            }
            break;
            case 'I': {
                BSTsort(bst, stdout, PREORDER);
            }
            break;
            case 'J': {
                BSTsort(bst, stdout, POSTORDER);
            }
            break;
            case 'K': {
                printf("Height: %d\n", BSTheight(bst));
            }
            break;
            case 'L': {
                printf("Number of leaves: %d\n", BSTleaves(bst));
            }
            break;
            case 'M': {
                printf("Output file name\n");
                scanf("%s", fname);
                fout = fopen(fname, "w");
                if (fout != NULL) {
                    BSTsort(bst, fout, INORDER);
                    fclose(fout);
                }
            }
            break;
            case 'N': {
                printf("Input file name\n");
                scanf("%s", fname);
                fin = fopen(fname, "r");
                if (fin != NULL) {
                    bst = BSTload(fin, bst);
                    if (bst == NULL)
                      exit(-1);
                    fclose(fin);
                }
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
