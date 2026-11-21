#include"txt_editor.h"


int start_editor(EDITOR *edit)
{
    char input[MAX];
    char *cmd;
    char *arg;

    while(1)
    {
        printf("Enter Command: ");
        fgets(input,sizeof(input),stdin);

        cmd = strtok(input," \n");
        arg = strtok(NULL,"\n");

        if(!strcmp(cmd,"insert"))
        {
            if(arg==NULL)
            {
                insert_txt(edit,"");
                edit->cursor_line++;
                edit->cursor_col = 0;
                continue;
            }
            insert_txt(edit,arg);
            edit->cursor_line++;
            edit->cursor_col = strlen(arg);
        }
        else if(!strcmp(cmd,"print"))
        {
            display_document(edit);
        }
        else if(!strcmp(cmd,"delete"))
        {
            if(arg==NULL)
            {
                printf("\nInvalid input:\n");
                printf("delete <num_chars> - Delete characters before the cursor\n\n");
                continue;
            }
            int pos = atoi(arg);
            if(delete_txt(edit,pos)==FAILURE)
                printf("\nInvalid input:\ndelete's num_chars should be positive\n\n");

        }
        else if(!strcmp(cmd,"copy"))
        {
            char *start = strtok(arg," ");
            char *end = strtok(NULL,"");
            if(start == NULL || end == NULL)
            {
                printf("\nInvalid input:\n");
                printf("copy  <startpos> <endpos> - Copy selected characters to clipboard\n\n");
                continue;
            }
            // printf("start: %s\nend: %s\n",start,end);
            copy_txt(edit,atoi(start),atoi(end));
        }
        else if(!strcmp(cmd,"cut"))
        {
            char *start = strtok(arg," ");
            char *end = strtok(NULL,"");
            if(start == NULL || end == NULL)
            {
                printf("\nInvalid input:\n");
                printf("cut   <startpos> <endpos> - Cut selected characters and store in clipboard\n\n");
                continue;
            }
            cut_txt(edit,atoi(start),atoi(end));
        }
        else if(!strcmp(cmd,"paste"))
        {
            paste_txt(edit);
        }
        else if(!strcmp(cmd,"exit"))
        {
            printf("exiting...\n");
            return SUCCESS;
        }
        else
        {
            printf("\ninvalid! re-try:\n\n");
            print_menu();
        }
    }
}


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
    printf("3. copy  <startpos> <endpos> - Copy selected characters to clipboard\n");
    printf("4. cut   <startpos> <endpos> - Cut selected characters and store in clipboard\n");
    printf("5. paste - Insert clipboard content at cursor position\n");
    printf("6. undo - Undo the last operation\n");
    printf("7. redo - Redo the last undone operation\n"); 
    printf("8. print - Print the current document\n");
    printf("9. exit - Exit the text editor Enter command:\n\n");
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
        return FAILURE;
    strcpy(newnode->txt,txt);
    newnode->prev = NULL;
    newnode->next = NULL;

    if(edit->head == NULL && edit->tail == NULL)
    {
        edit->head = newnode;
        edit->tail = newnode;
        return SUCCESS;
    }
    LINE *temp = edit->tail;
    temp->next = newnode;
    newnode->prev = temp;
    edit->tail = newnode;
    return SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------//

int display_document(EDITOR *edit)
{
    printf("\n|----------------------------------------------------------------------------------------------------|\n");
    LINE *temp = edit->head;
    if(temp==NULL)
        printf("empty document\n");
    int i=1;
    while(temp)
    {
        printf("line %d: ",i++);
        printf("%s\n",temp->txt);
        temp=temp->next;
    }
    printf("Cursor position: Line %ld, Column %ld\n",edit->cursor_line,edit->cursor_col);
    printf("|----------------------------------------------------------------------------------------------------|\n\n");
}

//-----------------------------------------------------------------------------------------------------------------//

int delete_txt(EDITOR *edit,int pos)
{
    LINE *temp = edit->tail;
    if(pos<=0 || edit->cursor_col<pos)
        return FAILURE;

    temp->txt[edit->cursor_col-pos]='\0';
    edit->cursor_col = edit->cursor_col-pos;
    return SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------//

int copy_txt(EDITOR *edit,int start,int end)
{
    LINE *temp = edit->tail;
    int j=0;
    for(int i=start;i<end;i++)
    {
       edit->clipboard[j++] = temp->txt[i];
    }
    edit->clipboard[j]='\0';
}

//-----------------------------------------------------------------------------------------------------------------//

int cut_txt(EDITOR *edit,int start,int end)
{
    LINE *temp = edit->tail;
    int j=0;
    for(int i=start;i<end;i++)
    {
       edit->clipboard[j++] = temp->txt[i];
    }
    strcpy(&temp->txt[start],&temp->txt[end]);
    edit->clipboard[j]='\0';
}

//-----------------------------------------------------------------------------------------------------------------//

int paste_txt(EDITOR *edit)
{
    LINE *temp = edit->tail;
    strcat(temp->txt,edit->clipboard);
    edit->cursor_col = strlen(temp->txt);
}

//-----------------------------------------------------------------------------------------------------------------//
