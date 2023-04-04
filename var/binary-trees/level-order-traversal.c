#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
  
};

struct node* insert( struct node* root, int data ) {
		
	if(root == NULL) {
	
        struct node* node = (struct node*)malloc(sizeof(struct node));

        node->data = data;

        node->left = NULL;
        node->right = NULL;
        return node;
	  
	} else {
      
		struct node* cur;
		
		if(data <= root->data) {
            cur = insert(root->left, data);
            root->left = cur;
		} else {
            cur = insert(root->right, data);
            root->right = cur;
		}
	
		return root;
	}
}
#define MAX_DEPTH 500

struct list_el {
  struct list_el *next;
  int data;
};

struct list {
  struct list_el* first;
  struct list_el* last;
};

struct list list_make(){
  struct list list;
  list.first = 0;
  list.last = 0;
  
  return list;
}

void list_append(struct list* list, int data) {
  struct list_el* new_el = malloc(sizeof(struct list_el));
  new_el->data = data;
  new_el->next = 0;
  
  if (list->first == 0) {
    list->first = new_el;
    list->last = new_el;
  } else {
    list->last->next = new_el;
    list->last = new_el;
  }
}

struct list levels[MAX_DEPTH] = {0};

void visit(struct node* node, int level) {
  if (node == 0) {
    return;
  }
  
  list_append(&levels[level], node->data);
  visit(node->left, level + 1);
  visit(node->right, level + 1);  
}

void levelOrder( struct node *root) {
  visit(root, 0);
  
  for (int l = 0; l < MAX_DEPTH; l++) {
    struct list_el *el = levels[l].first;
    if (el == 0) {
      break;
    }
    
    while(el) {
      printf("%d ", el->data);
      el = el->next;
    }
  }
}


int main() {
  
    struct node* root = NULL;
    
    int t;
    int data;

    scanf("%d", &t);

    while(t-- > 0) {
        scanf("%d", &data);
        root = insert(root, data);
    }
  
	levelOrder(root);
    return 0;
}
