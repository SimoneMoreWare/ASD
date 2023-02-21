void powerset(int pos, Item *items, int *sol, int k, int cap, 
              int curr_cap, int curr_value, int *best_val, 
              int *best_sol) {
  int j;

  if (pos >= k) {
    if (curr_value > *best_val) {
      for (j = 0; j < k; j++)
        best_sol[j] = sol[j];
      *best_val = curr_value;
    }
    return;
  }

  if ((curr_cap + items[pos].size) < cap) {
    sol[pos] = 1;
    curr_cap += items[pos].size;
    curr_value += items[pos].value;
    powerset(pos+1, items, sol, k, cap, curr_cap, curr_value, 
	     best_val, best_sol);
    curr_cap -= items[pos].size;
    curr_value -= items[pos].value;
  }

  sol[pos] = 0;
  powerset(pos+1, items, sol, k, cap, curr_cap, curr_value, 
           best_val, best_sol);

}



