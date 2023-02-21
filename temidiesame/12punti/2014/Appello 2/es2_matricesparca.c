
typedef struct {
  int col;
  float val;
  struct row_list* next;
} row_list;

typedef struct {
  int NR;
  int NC;
  row_list** rows;
} matr_t;

void MATRwrite(matr_t* M, int r, int c, float val) {
  // Crea un nuovo elemento della lista
  row_list* new_element = malloc(sizeof(row_list));
  new_element->col = c;
  new_element->val = val;
  new_element->next = NULL;

  // Inserisci l'elemento nella lista della riga r
  row_list* current = M->rows[r];
  if (current == NULL) {
    // La riga è vuota, inserisci l'elemento come primo elemento
    M->rows[r] = new_element;
  } else {
    // Cerca l'ultimo elemento della lista
    while (current->next != NULL) {
      current = current->next;
    }
    // Aggiungi l'elemento alla fine della lista
    current->next = new_element;
  }
}
