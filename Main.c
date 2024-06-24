#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "StrList.h"

char* getString(){
    //printf("getting string:\n");
    char*s = (char*)malloc(sizeof(char));
    if(s==NULL){
        printf("char malloc fail at line 10\n");
        return NULL;
    }
    *s = '\0';
    char c = getchar();
    int length = 0; 
    while(c!=' ' && c!='\n' && c!= EOF){
        s = (char*)realloc(s,length+2);
        if(s==NULL){
            free(s);
            exit(EXIT_FAILURE);
        }
        s[length] = c;
        s[length+1] = 0;
        length++;
        c = getchar();
    }
    //printf("got string: %s\n",s);
    return s;
}

int main(){
    //printf("starting\n");
    StrList*list = StrList_alloc();
    if(list==NULL){
        printf("failed list malloc\n");
        StrList_free(list);
        exit(EXIT_FAILURE);
    }
    int input = -1;
    while(input!=0){
        //printf("a) input: %d, enter input:\n",input);
        scanf("%d",&input);
        //printf("b) input: %d\n",input);
        if(input==1){
            //printf("1) enter length:\n");
            int length = -1;
            scanf("%d",&length);
            getchar();
            //printf("1.1) enter strings:\n");
            for(int i=0; i<length; i++){
                char*s = getString();
                StrList_insertLast(list,s);
                //printf("a) length: %zu\n",StrList_size(list));
            }
            //printf("b) length: %zu\n",StrList_size(list));
            //StrList_print(list);
        }
        if(input==2){
            int index = -1;
            //printf("2) enter index:\n");
            scanf("%d",&index);
            getchar();
            if(index>=0 && index <= StrList_size(list)){
                //printf("2.1) enter string:\n");
                char*s = getString();
                StrList_insertAt(list,s,index);
            }
        }
        if(input==3){
            //printf("3)\n");
            StrList_print(list);
        }
        if(input==4){
            printf("%zu\n",StrList_size(list));
        }
        if(input==5){
            int index = -1;
            //printf("5) enter index:\n");
            scanf("%d",&index);
            getchar();
            if(index>=0 && index < StrList_size(list)){
                StrList_printAt(list,index);
            }
        }
        if(input==6){
            printf("%d\n",StrList_printLen(list));
        }
        if(input==7){
            getchar();
            //printf("7) enter string:\n");
            char*s = getString();
            //printf("counting: %s\n",s);
            printf("%d\n",StrList_count(list,s));
        }
        if(input==8){
            getchar();
            //printf("8) enter string:\n");
            char*s = getString();
            //printf("removing %s\n",s);
            StrList_remove(list,s);
        }
        if(input==9){
            int index = -1;
            //printf("9) enter index:\n");
            scanf("%d",&index);
            getchar();
            StrList_removeAt(list,index);
        }
        if(input==10){
            //printf("10) reversing\n");
            StrList_reverse(list);
        }
        if(input==11){
            //printf("11) erasing\n");
            StrList_print(list);
            while(StrList_size(list)>0){
                StrList_removeAt(list,0);
                //StrList_print(list);
            }
        }
        if(input==12){
            //printf("12) sorting\n");
            StrList_sort(list);
        }
        if(input==13){
            //printf("13) is sorted?\n");
            if(StrList_isSorted(list)==1){
                printf("true\n");
            }else printf("false\n");
        }
    }
    //printf("c) input: %d\n",input);
    StrList_free(list);
    return 0;
}
