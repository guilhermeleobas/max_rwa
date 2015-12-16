/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

template <class T>
inline void exchange(T& a, T& b) {
  T aux = a;
  a = b;
  b = aux;
}

template <class T>
int partition(double key[], T permut[], int left, int right) {
  double val =key[left];
  int lm = left-1;
  int rm = right+1;
  while (true) {
    do {
      rm--;
    } while (key[rm] > val);

    do {
      lm++;
    } while (key[lm] < val);
    if (lm < rm) {
      exchange<double>(key[rm], key[lm]);
      exchange<T>(permut[rm], permut[lm]);
    } else {
      return rm;
    }
  }
}

// Ordena os cromossomos (permut[]) pelo valor das chaves (key[]).
template <class T>
void quickSort(double key[], T permut[], int left, int right) {
  if (left < right) {
    int split_pt = partition<int>(key, permut, left, right);
    quickSort(key, permut, left, split_pt);
    quickSort(key, permut, split_pt+1, right);
  }
}

#endif  // _QUICKSORT_H_
