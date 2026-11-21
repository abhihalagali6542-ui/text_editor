#include"txt_editor.h"

//-----------------------------------------------------------------------------------------------------------------//

void print_banner()
{
    printf("\n|=============================================================================================|\n");
    printf("                                    TEXT EDITOR v1.0\n");
    printf("|=============================================================================================|\n");
}

//-----------------------------------------------------------------------------------------------------------------//

void print_menu()
{
    printf("\nText Editor Commands:\n"); 
    printf("1. insert <text> - Add text as a new line at the end\n");
    printf("2. delete <num_chars> - Delete characters before the cursor\n"); 
    printf("3. undo - Undo the last operation\n");
    printf("4. redo - Redo the last undone operation\n"); 
    printf("5. print - Print the current document\n");
    printf("6. exit - Exit the text editor Enter command:\n\n");
}

//-----------------------------------------------------------------------------------------------------------------//

void editor_init(EDITOR *edit)
{
    edit->head=NULL;
    edit->tail=NULL;
    edit->cursor_line=0;
    edit->cursor_col=0;
}

//-----------------------------------------------------------------------------------------------------------------//

int insert_txt(EDITOR *edit,char *txt)
{
    LINE *newnode = malloc(sizeof(LINE));
    if(newnode == NULL)
        return 0;
    strcpy(newnode->txt,txt);
    newnode->prev = NULL;
    newnode->next = NULL;

    if(edit->head == NULL && edit->tail == NULL)
    {
        edit->head = newnode;
        edit->tail = newnode;
        return 0;
    }
    LINE *temp = edit->tail;
    temp->next = newnode;
    newnode->prev = temp;
    edit->tail = newnode;
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------//

int display(EDITOR *edit)
{
    printf("\n|----------------------------------------------------------------------------------------------------|\n");
    LINE *temp = edit->head;
    if(temp==NULL)
        printf("EMPTY\n");
    int i=1;
    while(temp)
    {
        printf("line %d: ",i++);
        printf("%s\n",temp->txt);
        temp=temp->next;
    }
    printf("Cursor position: Line %ld, Column %ld\n",edit->cursor_line,edit->cursor_col);
    printf("|----------------------------------------------------------------------------------------------------|\n");
}

//-----------------------------------------------------------------------------------------------------------------//
