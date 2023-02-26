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
  list_t *list;
  list = (list_t *)malloc(sizeof(list_t));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void list_free(list_t *list) {
  node_t *temp;
  while(list->head != NULL) {
      temp = list->head;
      list->head = list->head->next;
      free(temp);
  }
  free(list);
}

int list_prepend(list_t *list, int val) {
  node_t *temp = (node_t *)malloc(sizeof(node_t));
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
  node_t *temp = (node_t *)malloc(sizeof(node_t));
  temp->data = val;
  temp->next = NULL;
  if(list->tail) {
    list->tail->next = temp;
    list->tail = temp;
    list->size++;
    return 0;
  }
  list->head = temp;
  list->tail = temp;
  list->size++;
  return 0;
}

/*int list_insert(list_t *list, int val, size_t pos) {
  if (!list->head) {
    list_prepend(list, val);
  }
  if (list->size < pos) {
    printf("Linked list is not large enough\n");
  } else {

    if (pos == 0) {
      list_prepend(list, val);
    } else {
      node_t *temp = malloc(sizeof(node_t));
      node_t *it;
      temp->data = val;
      int counter = 0;
      it = list->head;
      while (counter < pos - 1) {
        it = it->next;
        counter++;
      }
      temp->next = it->next;
      it->next = temp;
      list->size++;
    }
  }
  return 0;
}*/

int list_insert(list_t *list, int val, size_t pos) {
  if(!list->head || pos == 0) { list_prepend(list, val); return 0; }
  if(list->size < pos) { return 1; }

  int i = 0;
  node_t *temp = malloc(sizeof(node_t));
  node_t *it;
  temp->data = val;
  it = list->head;
  while(i < pos-1) {
    it = it->next;
    i++;
  }
  temp->next = it->next;
  it->next = temp;
  list->size++;
  return 0;
}

int list_rm(list_t *list, int *val, size_t pos) {
  if(!list->head) { return 1; }
  if(pos == list->size) { 
    int stored = list->tail->data;
    free(list->tail); 
    return stored;
  }
 
  int i = 0;
  node_t *temp;
  temp = list->head;
  while(i < pos-1){
    temp = temp->next;
    i++;
  }
  int stored = temp->next->data;
  temp = temp->next->next;
  free(temp->next);
  return stored;
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
  list_append(list, 4);
  list_loop(list);
  list_prepend(list, 10);
  list_loop(list);
  list_prepend(list, 20);
  list_loop(list);
  list_append(list, 5);
  list_loop(list);
  list_insert(list, 100, 2);
  list_loop(list);
  // 20, 10, 100, 4, 5
  int removed = list_rm(list, &removed, 0);
  // 20, 10, 4, 5
  list_loop(list);
  list_free(list);
}
