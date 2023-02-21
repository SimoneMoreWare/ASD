#ifndef IBST_H_DEFINED
#define IBST_H_DEFINED

#define PREORDER  -1
#define INORDER    0
#define POSTORDER  1

typedef struct  intervalbinarysearchtree *IBST;

IBST	IBSTinit();
void    IBSTfree(IBST ibst);
int		IBSTcount(IBST ibst);
int     IBSTempty(IBST ibst);
void 	IBSTinsert(IBST ibst,Item x);
Item	IBSTsearch(IBST ibst,Item x);
void	IBSTdelete(IBST ibst, Item x);
void	IBSTvisit(IBST ibst, int strategy);

#endif
