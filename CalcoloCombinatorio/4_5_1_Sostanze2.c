...

void gen_sorted_ids();

...

int sost_phase[N+1];
int sorted_ids[MAX];


main() {

  ...

  gen_sorted_ids();

  solve (1);

  ...

}

void gen_sorted_ids() {
  int i, j, t;

  /* ordinamento iniziale */
  for (i = 0; i < n_sost; i++) {
    sorted_ids[i] = i;
  }

  /* insertion sort: fase e prezzo */
  for (i = 1; i < n_sost; i++) {
    t = sorted_ids[i];
    for (j = i-1; 
         j >= 0 && (vett[sorted_ids[j]].phase<vett[t].phase || 
                    vett[sorted_ids[j]].price<vett[t].price);
         j--)
      sorted_ids[j+1] = sorted_ids[j];
    sorted_ids[j+1] = t;
  }

  /* indici a sotto-gruppi della stessa fase */
  sost_phase[0] = 0;
  for (i = 0, j = 1; i < n_sost; i++) {
    /* cerca prima sostanza di fase j */
    if (vett[sorted_ids[i]].phase == j) {
      sost_phase[j++] = i;
    }
  }
  sost_phase[j] = n_sost;
  
}

void solve (int phase) {
  int	i, t, j, is_inc;

  if (phase > N) {
    if (tot_price < min_price) {
      min_price = tot_price;
      save_solution();
    }
    return;
  }

  for (t = sost_phase[phase]; t < sost_phase[phase+1]; t++) {
    i = sorted_ids[t];

    is_inc = 0;
    /* controlla incompatibilita' con sostanze gia' selezionate */
    for (j = 1; j < phase; j++)
      if (incomp[solut[j]][i] == 1)
        is_inc = 1;
    if (is_inc != 1) {
      solut[phase] = i;
      tot_price += vett[i].price;
      /* pruning */
      if (tot_price < min_price)
        solve (phase+1);
      tot_price -= vett[i].price;
    }
  }
}

