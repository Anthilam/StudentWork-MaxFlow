#include "array.h"

/*
 * Create an empty array
 */
void array_create(struct array *self) {
  self->data = NULL;
  self->capacity = 0;
  self->size = 0;
}

/*
 * Destroy an array
 */
void array_destroy(struct array *self) {
  if (self != NULL) {
    free(self->data);
    self->size = 0;
    self->capacity = 0;
  }
}

/*
 * Compare the array to another array (content and size)
 */
bool array_equals(const struct array *self, const int *content, size_t size) {
  if (self->size != size) {
    return false;
  }
  else {
    for (int i = 0; i < size; ++i) {
      if (self->data[i] != content[i]) {
        return false;
      }
    }
  }
  return true;
}

/*
 * Add an element at the end of the array
 */
void array_add(struct array *self, int value) {
  if (self->size == self->capacity) {
    if (self->capacity == 0) {
      self->capacity++;
    }
    self->capacity *= 2;
    int *data = calloc(self->capacity, sizeof(int));
    memcpy(data, self->data, self->size * sizeof(int));
    free(self->data);
    self->data = data;
  }
  self->data[self->size] = value;
  ++self->size;
}

/*
 * Insert an element in the array (preserving the order)
 */
void array_insert(struct array *self, int value, size_t index) {
  if (index >= self->size) {
    array_add(self, value);
  }
  else {
    int tmp  = 0;
    int tmp2 = 0;
    array_add(self, 0);
    for (int i = index; i < self->size - 1; ++i) {
      if (i == index) {
        tmp = self->data[i + 1];
        self->data[i + 1] = self->data[i];
      }
      else {
        tmp2 = self->data[i + 1];
        self->data[i + 1] = tmp;
        tmp = tmp2;
      }
    }
    self->data[index] = value;
  }
}

/*
 * Remove an element in the array (preserving the order)
 */
void array_remove(struct array *self, size_t index) {
  for (size_t i = index + 1; i < self->size; ++i) {
    self->data[i - 1] = self->data[i];
  }
  --self->size;
}

/*
 * Get a pointer to the element at the specified index in the array
 */
int *array_get(const struct array *self, size_t index) {
  if (self->data == NULL) {
    return NULL;
  }
  return &self->data[index];
}

/*
 * Tell if the array is empty
 */
bool array_is_empty(const struct array *self) {
  if (self->size == 0) {
    return true;
  }
  return false;
}

/*
 * Get the size of the array
 */
size_t array_size(const struct array *self) {
  return self->size;
}

/*
 * Search for an element in the array.
 */
size_t array_search(const struct array *self, int value) {
  size_t i = 0;
  while (i < self->size && self->data[i] != value) {
    ++i;
  }
  return i;
}

/*
 * Search for an element in the sorted array.
 */
size_t array_binary_search(const struct array *self, int value, size_t lo, size_t hi) {
  if (lo == hi) {
    return self->size;
  }

  size_t mid = (lo + hi) / 2;
  if (value < self->data[mid]) {
    return array_binary_search(self, value, lo, mid);
  }

  if (self->data[mid] < value) {
    return array_binary_search(self, value, mid + 1, hi);
  }

  return mid;
}

size_t array_search_sorted(const struct array *self, int value) {
  return array_binary_search(self, value, 0, self->size);
}

/*
 * Import an array
 */
void array_import(struct array *self, const int *other, size_t size) {
  while (self->size != 0) {
    array_remove(self, 0);
  }
  for (int i = 0; i < size; ++i) {
    array_add(self, other[i]);
  }
}

/*
 * Print an array to stdout
 */
void array_dump(const struct array *self) {
  printf("{ ");
  for (int i = 0; i < self->size; ++i) {
    printf("%d ", self->data[i]);
  }
  printf("}\n");
}

/*
 * Tell if the array is sorted
 */
bool array_is_sorted(const struct array *self) {
  for (int i = 1; i < self->size; ++i) {
    if (self->data[i] < self->data[i - 1]) {
      return false;
    }
  }
  return true;
}

/*
 * Swap two values in an array
 */
void array_swap(struct array *self, size_t i, size_t j) {
  int tmp = self->data[i];
  self->data[i] = self->data[j];
  self->data[j] = tmp;
}

/*
 * Sort the array with selection sort
 */
void array_selection_sort(struct array *self) {
  for (size_t i = 0; i < self->size - 1; ++i) {
    size_t j = i;
    for (size_t k = j + 1; k < self->size; ++k) {
      if (self->data[k] < self->data[j]) {
        j = k;
      }
    }
    array_swap(self, i, j);
  }
}

/*
 * Sort the array with bubble sort
 */
void array_bubble_sort(struct array *self) {
  for (size_t i = 0; i < self->size - 1; ++i) {
    for (size_t j = self->size - 1; j > i; --j) {
      if (self->data[j] < self->data[j - 1]) {
        array_swap(self, j, j - 1);
      }
    }
  }
}

/*
 * Sort the array with insertion sort
 */
void array_insertion_sort(struct array *self) {
  for (size_t i = 1; i < self->size; ++i) {
    int x = self->data[i];
    size_t j = i;
    while (j > 0 && self->data[j - 1] > x) {
      self->data[j] = self->data[j - 1];
      --j;
    }
    self->data[j] = x;
  }
}

/*
 * Sort the array with quick sort
 */
void array_rec_quick_sort(struct array *self, int a, int b) {
  if (a >= b) {
    return;
  }

  int pivot = self->data[a];
  int i = a + 1, j = b;
  while (i < j) {
    while (i < j && self->data[j] >= pivot) {
      --j;
    }
    while (i < j && self->data[i] <= pivot) {
      ++i;
    }
    if (i < j) {
      array_swap(self, i, j);
    }
  }

  if (self->data[a] > self->data[i]) {
    array_swap(self, a, i);
    array_rec_quick_sort(self, a, i - 1);
    array_rec_quick_sort(self, i + 1, b);
  }
  else {
    array_rec_quick_sort(self, a + 1, b);
  }
}

void array_quick_sort(struct array *self) {
  array_rec_quick_sort(self, 0, self->size - 1);
}

/*
 * Insert a value in a heap
 */
void array_heap_insert(struct array *self, size_t n, int value) {
  size_t i = n;
  self->data[i] = value;
  while (i > 0) {
    size_t j = (i - 1) / 2;
    if (self->data[i] < self->data[j]) {
      break;
    }
    array_swap(self, i, j);
    i = j;
  }
}

/*
 * Remove a value from a heap
 */
void array_heap_remove(struct array *self, size_t n) {
  self->data[0] = self->data[n - 1];
  size_t i = 0;
  while (i < (n - 1) / 2) {
    size_t lt = 2 * i + 1;
    size_t rt = 2 * i + 2;
    if (self->data[i] > self->data[lt] && self->data[i] > self->data[rt]) {
      break;
    }
    size_t j = (self->data[lt] > self->data[rt]) ? lt : rt;
    array_swap(self, i, j);
    i = j;
  }
}

/*
 * Sort the array with heap sort
 */
void array_heap_sort(struct array *self) {
  for (size_t i = 0; i < self->size; ++i) {
    int value = self->data[i];
    array_heap_insert(self, i, value);
  }
  for (size_t i = 0; i < self->size; ++i) {
    int value = self->data[0];
    array_heap_remove(self, self->size - i);
    self->data[self->size - i - 1] = value;
  }
}

/*
 * Tell if the array is a heap
 */
bool array_is_heap(const struct array *self) {
  if (self->data == NULL) {
    return true;
  }
  for (int i = 0; i < self->size; ++i) {
    if (self->size >= 2*i+2) {
      if (self->data[i] < self->data[2*i+1]) {
        return false;
      }
      if (self->size >= 2*i+3) {
        if (self->data[i] < self->data[2*i+2]) {
          return false;
        }
      }
    }
  }
  return true;
}

/*
 * Add a value into the array considered as a heap
 */
void array_heap_add(struct array *self, int value) {
  size_t i = self->size;
  array_add(self, value);
  while (i > 0) {
    size_t j = (i-1)/2;
    if (self->data[i] < self->data[j]) {
      break;
    }
    array_swap(self, i, j);
    i = j;
  }
}

/*
 * Get the value at the top of the heap
 */
int array_heap_top(const struct array *self) {
  return *array_get(self, 0);
}

/*
 * Remove the top value in the array considered as a heap
 */
void array_heap_remove_top(struct array *self) {
  self->data[0] = self->data[self->size-1];
  array_remove(self, self->size-1);
  size_t i = 0;
  while (i < self->size/2) {
    size_t lt = 2*i+1;
    size_t rt = 2*i+2;
    if (self->data[i] > self->data[lt] && self->data[i] > self->data[rt]) {
      break;
    }
    size_t j = (self->data[lt] > self->data[rt]) ? lt : rt;
    array_swap(self, i, j);
    i = j;
  }
}
