void sierpinski(punto a, punto b, punto c, int iter) {
  disegna_triangolo(a, b, c);
  if (iter == 0) return;
  sierpinski(a, punto_medio(a,b), punto_medio(a,c), iter-1);
  sierpinski(b, punto_medio(b,a), punto_medio(b,c), iter-1);
  sierpinski(c, punto_medio(c,a), punto_medio(c,b), iter-1);
}

