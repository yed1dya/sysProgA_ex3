#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

typedef struct _node{
    char*_data;
    struct _node*_next;
} Node;
Node*Node_alloc(char*data, Node*next){
    Node*newNode = (Node*)malloc(sizeof(Node));
    if(newNode==NULL){
        printf("Node malloc failed at line 13: Node*Node_alloc(char*data,Node*next)");
        return NULL;
    }
    newNode->_data = strdup(data);
    newNode->_next = next;
    return newNode;
}
void Node_free(Node*node){
    free(node->_data);
    free(node);
}

typedef struct _StrList{
    Node*_head;
    size_t _size;
} StrList;
StrList*StrList_alloc(){
    StrList*newList = (StrList*)malloc(sizeof(StrList));
    if(newList==NULL){
        printf("Strlist malloc failed at line 32: StrList*StrList_alloc()");
        return NULL;
    }
    newList->_head = NULL;
    newList->_size = 0;
    return newList;
}
void StrList_free(StrList*StrList){
    if(StrList==NULL) return;
    Node*current = StrList->_head;
    Node*next;
    while (current){
        next = current->_next;
        Node_free(current);
        current = next;
    }
    free(StrList);
}

size_t StrList_size(const StrList*StrList){
    return StrList->_size;
}

void StrList_insertAt(StrList*StrList, const char*data, int index){
    if(StrList==NULL) return;
    int size = StrList->_size;
    if(index<0 || index > size) return;
    Node*newNode = Node_alloc(data,NULL);
    if(newNode==NULL){
        printf("node malloc failed at line 61: void StrList_insertAt(StrList*StrList, const char*data, int index)");
        return;
    }
    if(StrList->_head==NULL){
        StrList->_head = newNode;
        return;
    }
    Node*current = StrList->_head;
    if(index==0){
        newNode->_next = current;
        StrList->_head = newNode;
        return;
    }
    int place = 0;
    while(++place < index){
        current = current->_next;
    }
    newNode->_next = current->_next;
    current->_next = newNode;
    StrList->_size++;
}

void StrList_insertLast(StrList*StrList, const char*data){
    if(StrList==NULL) return;
    StrList_insertAt(StrList,data,StrList->_size);
}

char*StrList_firstData(const StrList*StrList){
    if(StrList==NULL) return NULL;
    if(StrList->_head==NULL) return NULL;
    return StrList->_head->_data;
}

void StrList_print(const StrList*StrList){
    if(StrList==NULL){
        printf("\n");
        return;
    }
    if(StrList->_head==NULL){
        printf("\n");
        return;
    }
    Node*current = StrList->_head;
    while(current){
        printf("%s",current->_data);
        current = current->_next;
        if(current){
            printf(" ");
        }
    }
    printf("\n");
}

void StrList_printAt(const StrList*StrList, int index){
    if(StrList==NULL){
        printf("\n");
        return;
    }
    if(StrList->_head==NULL){
        printf("\n");
        return;
    }
    int size = StrList->_size;
    if(index<0 || index>=size) return;
    Node*current = StrList->_head;
    int place = 0;
    while(place++ < index){
        current = current->_next;
    }
    printf("%s\n",current->_data);
}

int StrList_printLen(const StrList*StrList){
    if(StrList==NULL) return 0;
    if(StrList->_head==NULL) return 0;
    Node*current = StrList->_head;
    int length = 0;
    while(current){
        length += strlen(current->_data);
        current = current->_next;
    }
    return length;
}

int StrList_count(StrList*StrList, const char*data){
    if(StrList==NULL) return 0;
    if(StrList->_head==NULL) return;
    int count = 0;
    Node*current = StrList->_head;
    while(current){
        if(strcmp(current->_data, data)==0){
            count++;
        }
        current = current->_next;
    }
    return count;
}

void StrList_remove(StrList*StrList, const char*data){
    if(StrList==NULL) return;
    if(StrList->_head==NULL) return;
    Node*current = StrList->_head;
    Node*next = current->_next;
    while(next){
        if(strcmp(next->_data, data)==0){
            current->_next = next->_next;
            Node_free(next);
            StrList->_size--;
        }
        current = current->_next;
        next = current->_next;
    }
    Node*head = StrList->_head;
    if(strcmp(head->_data,data)==0){
        StrList->_head = head->_next;
        Node_free(head);
        StrList->_size--;
    }
}

void StrList_removeAt(StrList*StrList, int index){
    if(StrList==NULL) return;
    if(StrList->_head==NULL) return;
    if(index<0 || index >= StrList->_size) return;
    Node*current = StrList->_head;
    if(index==0){
        StrList->_head = current->_next;
        Node_free(current);
        StrList->_size--;
    }
    Node*next = current->_next;
    int count = 0;
    while(++count < index){
        current = next;
        next = current->_next;
    }
    current->_next = next->_next;
    Node_free(next);
    StrList->_size--;
}

int StrList_isEqual(const StrList*StrList1, const StrList*StrList2){
    if(StrList1==NULL || StrList2==NULL){
        if(StrList1!=NULL || StrList2!=NULL) return 0;
        return 1;
    }
    if(StrList1->_size != StrList2->_size) return 0;
    Node*a = StrList1->_head;
    Node*b = StrList2->_head;
    while(a){
        if(!b) return 0;
        if(strcmp(a->_data,b->_data)!=0) return 0;
        a = a->_next;
        b = b->_next;
    }
    if(!b) return 1;
    return 0;
}

StrList* StrList_clone(const StrList*StrList){
    if(StrList==NULL) return NULL;
    struct StrList*newList = StrList_alloc();
    if(newList==NULL) return NULL;
    Node*current = StrList->_head;
    while(current){
        StrList_insertLast(newList,current->_data);
        current = current->_next;
    }
    return newList;
}

void StrList_reverse(StrList*StrList){
    if(StrList==NULL) return;
    if(StrList->_size<2) return;
    Node*previous = NULL;
    Node*current = StrList->_head;
    Node*next = NULL;
    while(current){
        next = current->_next;
        current->_next = previous;
        previous = current;
        current = next;
    }
    StrList->_head = previous;
}

void StrList_sort(StrList*StrList){
    if(StrList==NULL) return;
    if(StrList->_size < 2) return;
    Node*node = StrList->_head;
    for(int i=0; i<StrList->_size; i++){
        for(int j=0; j<(StrList->_size)-i-1; j++){
            if(strcmp(node->_data,node->_next->_data) > 0){
                char*t = node->_data;
                node->_data = node->_next->_data;
                node->_next->_data = t;
            }
            node = node->_next;
        }
        node = StrList->_head;
    }
}

int StrList_isSorted(StrList*StrList){
    if(StrList==NULL) return 1;
    if(StrList->_size < 2) return 1;
    Node*node = StrList->_head;
    while(node->_next){
        if(strcmp(node->_data,node->_next->_data) > 0){
            return 0;
        }
        node = node->_next;
    }
    return 1;
}