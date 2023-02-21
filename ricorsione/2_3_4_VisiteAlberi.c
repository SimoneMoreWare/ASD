void sortinorderR(link h, link z) {
  if (h == z)
    return;
  sortinorderR(h->l, z);
  printf("%s", h->name);
  sortinorderR(h->r, z);
}

void sortpostorderR(link h, link z) {
  if (h == z)
    return;
  sortpostorderR(h->l, z);
  sortpostorderR(h->r, z);
  printf("%s", h->name);
}

void sortpreorderR(link h, link z) {
  if (h == z)
    return;
  printf("%s", h->name);
  sortpreorderR(h->l, z);
  sortpreorderR(h->r, z);
}
