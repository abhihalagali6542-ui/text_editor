#include "txt_ops.h"

//-----------------------------------------------------------------------------------------------------------------//

int insert_txt(EDITOR *edit,char *txt)
{
    LINE *newnode = malloc(sizeof(LINE));
    if(newnode == NULL)
    {
        printf("\n[ FAILURE ] Unable to insert txt\n\n");
        return FAILURE;
    }
    strcpy(newnode->txt,txt);
    newnode->prev = NULL;
    newnode->next = NULL;

    if(edit->head == NULL && edit->tail == NULL)
    {
        edit->head = newnode;
        edit->tail = newnode;
        edit->cursor_line++;
        edit->cursor_col = strlen(txt);
        return SUCCESS;
    }
    LINE *temp = edit->tail;
    temp->next = newnode;
    newnode->prev = temp;
    edit->tail = newnode;
    
    edit->cursor_line++;
    edit->cursor_col = strlen(txt);
    return SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------//

int delete_txt(EDITOR *edit,int pos)
{
    LINE *temp = edit->tail;
    if(pos<=0 || edit->cursor_col<pos)
    {
        printf("\n[ ERROR ] Invalid input:\ndelete's num_chars should be positive\n\n");
        return FAILURE;
    }

    temp->txt[edit->cursor_col-pos]='\0';
    edit->cursor_col = edit->cursor_col-pos;
    return SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------//

int copy_txt(EDITOR *edit,int start,int end)
{
    //printf("start: %d\nend: %d\n",start,end);
    if(start < 0 || end <= start || end > edit->cursor_col)
    {
        printf("\n[ ERROR ] Invalid position\n\n");
        return FAILURE;
    }
    LINE *temp = edit->tail;
    int j=0;
    for(int i=start;i<end;i++)
    {
       edit->clipboard[j++] = temp->txt[i];
    }
    edit->clipboard[j]='\0';
    return SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------//

int cut_txt(EDITOR *edit,int start,int end)
{
    //printf("start: %d\nend: %d\n",start,end);
    if(start < 0 || end <= start || end > edit->cursor_col)
    {
        printf("\n[ ERROR ] Invalid position\n\n");
        return FAILURE;
    }
    LINE *temp = edit->tail;
    int j=0;
    for(int i=start;i<end;i++)
    {
       edit->clipboard[j++] = temp->txt[i];
    }
    strcpy(&temp->txt[start],&temp->txt[end]);
    edit->clipboard[j]='\0';
    return SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------//

int paste_txt(EDITOR *edit)
{
    if(edit->clipboard[0] == '\0')
    {
        printf("\n[ INFO ] Clipboard is empty\n\n");
        return FAILURE;
    }
    LINE *temp = edit->tail;
    strcat(temp->txt,edit->clipboard);
    edit->cursor_col = strlen(temp->txt);
    return SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------//
