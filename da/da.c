//  da.c : partie implantation d'un module polymorphe pour la spécification
//    de tableau dynamique

#include "da.h"

#define DA__CAPACITY_MIN 4
#define DA__CAPACITY_MUL 2

//--- Définition da ------------------------------------------------------------

struct da {
  const void **aref;
  size_t length;
  size_t capacity;
};

//--- Raccourcis da ------------------------------------------------------------
#define IS_EMPTY(p)    ((p)->length == 0)
#define LENGTH(p)      ((p)->length)
#define CAPACITY(p)    ((p)->capacity)

//--- Fonctions da -------------------------------------------------------------

da *da_empty() {
  da *p = malloc(sizeof *p);
  if (p == NULL) {
    return NULL;
  }
  const void **tab = malloc(DA__CAPACITY_MIN * sizeof *(p->aref));
  if (tab == NULL) {
    free(p);
    return NULL;
  }
  p->aref = tab;
  p->capacity = DA__CAPACITY_MIN;
  p->length = 0;
  return p;
}

void da_dispose(da **aptr) {
  if (*aptr == NULL) {
    return;
  }
  free((*aptr)->aref);
  free(*aptr);
  *aptr = NULL;
  return;
}

int da_dispose_element(da *p) {
  for (size_t k = 0; k < LENGTH(p); ++k) {
    free((void *) p->aref[k]);
  }
  return 0;
}

void *da_add(da *p, const void *ref) {
  if (ref == NULL) {
    return NULL;
  }
  if (LENGTH(p) == CAPACITY(p)) {
    if (((sizeof *(p->aref) * p->capacity)) > SIZE_MAX / DA__CAPACITY_MUL) {
      return NULL;
    }
    const void **t
      = realloc(p->aref,
        (sizeof *(p->aref) * p->capacity * DA__CAPACITY_MUL));
    if (t == NULL) {
      return NULL;
    }
    p->aref = t;
    p->capacity *= DA__CAPACITY_MUL;
  }
  p->aref[LENGTH(p)] = ref;
  LENGTH(p) += 1;
  return (void *) ref;
}

void *da_ref(da *p, size_t i) {
  if (p == NULL) {
    return NULL;
  }
  if (i > LENGTH(p)) {
    return NULL;
  }
  return (void *) p->aref[i];
}

size_t da_length(da *p) {
  return IS_EMPTY(p) ? 0 : LENGTH(p);
}

size_t da_capacity(da *p) {
  return IS_EMPTY(p) ? 0 : CAPACITY(p);
}
