
int **fragmt(unsigned int *arr, const size_t size) {
  int **ret = new int *[2];
  /* ls */
  *ret[0] = pcopy(arr, 0, size / 2 + 1);
  /* rs */
  *ret[1] = pcopy(arr, size / 2 + 1, size);
  return ret;
}

int pcopy(const unsigned int *arr, unsigned int &beg, unsigned int &end) {
  int *ret = new int[end];

  for (int i = beg; i < end; ++i)
    ret[i] = arr[i];

  return *ret;
}

/* TODO */
/* merge arrays of pointers */
/* int pmerge(const int arr, int* arr, int &size1, int &size2) { */

/* } */
