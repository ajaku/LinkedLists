#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
  int data;
  struct node_s *next;
} node_t;

typedef struct list_s {
  node_t *head;
  node_t *tail;
  size_t size;
} list_t;

// functions to implement
list_t *list_alloc(void);                          
void list_free(list_t *list);                       
int list_prepend(list_t *list, int val);           
int list_append(list_t *list, int val);             
int list_insert(list_t *list, int val, size_t pos); 
int list_rm(list_t *list, int *val, size_t pos);
int list_set(list_t *list, int val, size_t pos);
int list_get(list_t *list, int *val, size_t pos);
/* my own fcn */ void list_loop(list_t *list);

list_t *list_alloc(void) {
  return calloc(1,sizeof(list_t));
}

void list_free(list_t *list) {
  node_t *temp;
  while (list->head) {
      temp = list->head;
      list->head = list->head->next;
      free(temp);
  }
  free(list);
}

int list_prepend(list_t *list, int val) {
  node_t *temp = malloc(sizeof(*temp));
  if (!temp) return -1;
  temp->data = val;
  temp->next = list->head;
  list->head = temp;
  if (list->tail == NULL) {
    list->tail = list->head;
  }
  list->size++;
  return 0;
}

int list_append(list_t *list, int val) {
  node_t *temp = malloc(sizeof(*temp));
  if (!temp) return -1;
  temp->data = val;
  temp->next = NULL;

  list->tail = (list->tail) ? (list->tail->next = temp) : (list->head = temp);

  list->size++;
  return 0;
}

int list_insert(list_t *list, int val, size_t pos) {
  if (!pos) return list_prepend(list, val);
  if (pos == list->size) return list_append(list, val);

  if (list->size < pos) return -1;

  node_t *temp = malloc(sizeof(node_t));
  if (!temp) return -1;

  node_t *it = list->head;
  while (--pos) it = it->next;

  temp->next = it->next;
  temp->data = val;
  it->next = temp;

  list->size++;
  return 0;
}

int list_rm(list_t *list, int *val, size_t pos) {
  if (pos > list->size) return -1;

  node_t *it = list->head;

  if (!pos) {
    if (val) *val = it->data;
    list->head = it->next;
    if (list->head) list->tail = NULL;
  } else {
    while (--pos) it = it->next;
    
    if (val) *val = it->next->data;

    node_t *temp = it;  //current node
    it = it->next; //next node
    temp->next = it->next;

    /*if (!it->next) {
      //checking if next node is null
      //if it is null, erase previous node and set node before that to the NULL of tail
      temp->next = NULL;
      list->tail = temp;
      free(it);
      list->size--;
      return 0;
    }*/

    if (!it->next) list->tail = temp;
  }

  free(it);

  list->size--;
  return 0;
}

int list_set(list_t *list, int val, size_t pos) {
  if (pos > list->size) return -1;

  if (pos == list->size - 1) {
    list->tail->data = val;
    return 0;
  }

  node_t *it = list->head;
  while (pos--) it = it->next;

  it->data = val;

  return 0;
}

int list_get(list_t *list, int *val, size_t pos) {
  if (pos > list->size) return -1;

  if (pos == list->size - 1) {
    if (val) *val = list->tail->data;
    return 0;
  }
  
  node_t *it = list->head;
  while (pos--) it = it->next;

  if (val) *val = it->data;

  return 0;
}

void list_loop(list_t *list) {
  node_t *temp;
  temp = list->head;
  while (temp) {
    printf("%d\n", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

int main(void) {
  list_t *list = list_alloc();  
  puts("append 4");
  list_append(list, 4);
  list_loop(list);
  puts("prepend 10");
  list_prepend(list, 10);
  list_loop(list);
  puts("prepend 20");
  list_prepend(list, 20);
  list_loop(list);
  puts("append 5");
  list_append(list, 5);
  list_loop(list);
  puts("insert 100 at 2");
  list_insert(list, 100, 2);
  list_loop(list);
  int removed;
  /*list_rm(list, &removed, 3);
  printf("removed: %d\n", removed);
  puts("set 21 at 3");
  list_set(list, 21, 3);
  list_loop(list);
  puts("getting at 3");
  int get;
  list_get(list, &get, 3);
  printf("Got\t%d\n", get);*/
  list_rm(list,&removed, 3);
  list_loop(list);
  list_append(list, 4);
  list_loop(list);
  list_free(list);
}
