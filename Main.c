#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "StrList.h"

void clearInput(){
   char c;
   while((c=getchar())!='\n'&&c!=EOF);
}

char* getString(){
    char*s = (char*)malloc(sizeof(char));
    *s = "\0";
    char c = getchar();
    int length = 0; 
    while(c!=" " && c!="\n" && c!= EOF){
        s = (char*)realloc(s,length+2);
        if(s==NULL){
            free(s);
            exit(EXIT_FAILURE);
        }
        *(s+length) = c;
        *(s+length) = "\0";
        c = getchar();
    }
    return s;
}

int main(){
    StrList*list = StrList_alloc();
    if(list==NULL){
        StrList_free(list);
        exit(EXIT_FAILURE);
    }
    int input = -1;
    while(input!=0){
        clearInput();
        scanf("%d",&input);
        if(input==1){
            clearInput();
            int length = -1;
            scanf("%d",&length);
            clearInput();
            for(int i=0; i<length; i++){
                char*s = getString();
                StrList_insertLast(list,s);
            }
        }
        if(input==2){
            clearInput();
            int index = -1;
            scanf("%d",&index);
            if(index>=0 && index < StrList_size(list)){
                clearInput();
                char*s = getString();
                StrList_insertAt(list,s,index);
            }
        }
        if(input==3){
            StrList_print(list);
        }
        if(input==4){
            printf("%d\n",StrList_printLen(list));
        }
        if(input==5){
            clearInput();
            int index = -1;
            scanf("%d",&index);
            if(index>=0 && index < StrList_size(list)){
                StrList_printAt(list,index);
            }
        }
        if(input==6){
            printf("%d\n",StrList_printLen(list));
        }
        if(input==7){
            clearInput();
            char*s = getString();
            printf("%d\n",StrList_count(list,s));
        }
        if(input==8){
            clearInput();
            char*s = getString();
            StrList_remove(list,s);
        }
        if(input==9){
            clearInput();
            int index = -1;
            scanf("%d",&index);
            StrList_removeAt(list,index);
        }
        if(input==10){
            StrList_reverse(list);
        }
        if(input==11){
            while(StrList_size(list)>0){
                StrList_removeAt(list,0);
            }
        }
        if(input==12){
            StrList_sort(list);
        }
        if(input==13){
            if(StrList_isSorted(list)==1){
                printf("true\n");
            }else printf("false\n");
        }
    }
    StrList_free(list);
    return 0;
}