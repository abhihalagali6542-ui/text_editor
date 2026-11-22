#include "file_ops.h"
#include "txt_ops.h"

//-----------------------------------------------------------------------------------------------------------------//

int open_file(EDITOR *edit,char *fname)
{
    char *dot=strrchr(fname,'.');
    if(dot == NULL || strcmp(dot,".txt")!=0)
    {
        printf("\n[ ERROR ] file format should be '.txt'\n\n");
        return FAILURE;
    }
    strcpy(edit->fname,fname);
    edit->fptr = fopen(edit->fname,"r");
    if(edit->fptr == NULL)
    {
        printf("\n[ FAILURE ] Unable to open file\n\n");
        return FAILURE;
    }
    char txt[MAX];
    while(fgets(txt, sizeof(txt), edit->fptr))
    {
        txt[strcspn(txt, "\n")] = '\0';
        if (insert_txt(edit, txt)==FAILURE)  
        {
            printf("\n[ FAILURE ] while loading file\n\n");
            fclose(edit->fptr);
            return FAILURE;
        }
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------//

int save_file(EDITOR *edit,char *fname)
{
    char *dot=strrchr(fname,'.');
    if(dot == NULL || strcmp(dot,".txt")!=0)
    {
        printf("\n[ ERROR ] file format should be '.txt'\n\n");
        return FAILURE;
    }
    FILE *fptr = fopen(fname,"w");
    if(fptr == NULL)
    {
        printf("\n[ FAILURE ] Unable to open file\n\n");
        return FAILURE;
    }
    LINE *temp = edit->head; 
    while(temp)
    {
        fprintf(fptr,"%s\n",temp->txt);
        temp = temp->next;
    }
    fclose(fptr);
    return SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------//

int close_file(EDITOR *edit)
{
    remove(edit->fname);
    fclose(edit->fptr);
    save_file(edit,edit->fname);
    printf("\n[ SUCCESS ] file closed\n\n");
}

//-----------------------------------------------------------------------------------------------------------------//
