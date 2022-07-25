#include "functions.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 20
#define P_LENGTH 100

List* init(){
    List* list=createList();

    insert(list,"func1",func1_cli,func1,"func1 does nothing function: func1 <int> <int>");
    insert(list,"func2",func2_cli,func2,"func2 does nothing function");
    insert(list,"func3",func3_cli,func3,"func3 does nothing function");
    insert(list,"func4",func4_cli,func4,"func4 does nothing function");
    insert(list,"func5",func5_cli,func5,"func5 does nothing function");
}
List* createList(){
    List* list=(List*)malloc(sizeof(List));

    list->head=list->tail=NULL;
    return list;
}
void insert(List*list, char*name,genericFunc_cli func_cli,genericFunc func,char* help){
    Func* n=(Func*)malloc(sizeof(Func));
    n->func_cli=func_cli;
    n->func=func;
    n->help=strdup(help);
    n->name=strdup(name);
    n->next=NULL;

    if(list->head==NULL){
        list->head=list->tail=n;
        return;
    }
    list->tail->next=n;
    list->tail=n;
}
void getCommandAndActive(){

    List*list=init();
    char cmd[N+P_LENGTH+1];
    char **params;
    gets(cmd);
    Func* function;


    while(strcmp(cmd,"end")){
    params=(char **)calloc(N,sizeof(char*));
    int n=getParams(cmd,params);


    if(!(function=getFunc(list,params[0]))){
        printf("no such a command\n");
    }
    else{
        if(params[1]&&!strcmp(params[1],"-help"))
         {
            puts(function->help);
        }
        else{
            funcs_params funcs;
    int ans=function->func_cli(n-1,params+1,&funcs);
    if(!ans){
        printf("faild, help:");
        puts(function->help);
    }
    else{
        function->func(&funcs);
    }
   }
}
        free(params);
        gets(cmd);

    }
}
int getParams(char* cmd, char** params){
    int len=N;
    int i=0;

    char* token;
    token=strtok(cmd," ");
    while(token!=NULL){
        if(!strcmp(token," ")){
            token=strtok(NULL," ");
            continue;
        }
        if(i==len){
            params=(char**)realloc(params,len*1.5);
            len*=1.5;
        }
        params[i++]=strdup(token);
        token=strtok(NULL," ");
    }
    return i;
}
Func* getFunc(List*list,char*name){
    Func* ptr=list->head;
    while(ptr!=NULL){
        if(!strcmp(ptr->name,name))
            return ptr;
        ptr=ptr->next;
    }
    return NULL;
}
void func1(funcs_params* funcs){
printf("int func1 x=%d, y=%d \n", funcs->func1.x,funcs->func1.y);
}
void func2(funcs_params* funcs){
      printf("func2\n");
}
void func3(funcs_params* funcs){
      printf("func3\n");
}
void func4(funcs_params* funcs){
      printf("func4\n");
}
void func5(funcs_params* funcs){
      printf("func5\n");
}
int func1_cli(int n,char** params,funcs_params* funcs){
    if(n!=2){
        printf("error not fiten number of arguments\n");
        return 0;
    }
    int x=0, y=0;
    if(isInt(params[0]))
    x=atoi(params[0]);
    else
       { printf("unexpected type\n");
        return 0;}
    if(isInt(params[1]))
        y=atoi(params[1]);
    else
    {
        printf("unexpected type\n");
        return 0;
    }

    func1_params p={
    .x=x,
    .y=y};//fitten srtuct
    funcs->func1=p;

    return 1;
}
int func2_cli(int n,char**,funcs_params*){printf("in func2_cli\n");}
int func3_cli(int n,char**,funcs_params*){printf("in func3_cli\n");}
int func4_cli(int n,char**,funcs_params*){printf("in func4_cli\n");}
int func5_cli(int n,char**,funcs_params*){printf("in func5_cli\n");}
int isInt(char* params){
    for(int i=0;i<strlen(params);i++){
        if(!isdigit(params[i]))
            return 0;
    }
    return 1;
}
