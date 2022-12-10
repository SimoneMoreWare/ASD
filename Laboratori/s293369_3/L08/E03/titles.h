//
// Created by simone on 08/12/22.
//

#ifndef UNTITLED16_TITLES_H
#define UNTITLED16_TITLES_H

#define MAXC 21
#include "datetime.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "quotazioni.h"

typedef struct title *Title;
typedef struct listtitle *LISTTITLE;

LISTTITLE readfile(FILE *fp,LISTTITLE l);
int keygreater(char *a,char *b);
LISTTITLE LISTinit();
void list_display(LISTTITLE l);
Title title_init();
void SearchTitle(LISTTITLE l);
void SearchTitleQuotationFromDate(LISTTITLE l);
void SearchTitleQuotationMINMAXFromRangeDate(LISTTITLE l);
void SearchTitleQuotationMINMAXFromAllPeriod(LISTTITLE l);
#endif //UNTITLED16_TITLES_H
