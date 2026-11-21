#ifndef TXT_EDITOR_H
#define TXT_EDITOR_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 100
#define SUCCESS 0
#define FAILURE -1

typedef long int l_int;

typedef struct node
{
    char txt[MAX];
    struct node *prev;
    struct node *next;
}LINE;

typedef struct
{
    LINE *head;
    LINE *tail;

    l_int cursor_line;
    l_int cursor_col;

    char clipboard[MAX];

}EDITOR;

//-----------------------------------------------------------------------------------------------------------------//

int start_editor(EDITOR *);
void print_banner();
void print_menu();
void editor_init(EDITOR *);
int insert_txt(EDITOR *,char *);
int display_document(EDITOR *);
int delete_txt(EDITOR *,int);
int copy_txt(EDITOR *,int,int);
int cut_txt(EDITOR *,int,int);
int paste_txt(EDITOR *);

//-----------------------------------------------------------------------------------------------------------------//

#endif