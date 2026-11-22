#include "txt_editor.h"
#include "txt_ops.h"
#include "file_ops.h"

//-----------------------------------------------------------------------------------------------------------------//

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
        if(cmd == NULL)
        {
            continue;
        }
        arg = strtok(NULL,"\n");

        if(!strcmp(cmd,"insert"))
        {
            if(arg==NULL)
            {
                if(insert_txt(edit,"")==SUCCESS)
                {
                    printf("\n[ SUCCESS ] blank inserted\n\n");
                }
                continue;
            }
            if(insert_txt(edit,arg)==SUCCESS)
            {
                printf("\n[ SUCCESS ] text inserted\n\n");
            }
        }
        else if(!strcmp(cmd,"print"))
        {
            display_document(edit);
        }
        else if(!strcmp(cmd,"delete"))
        {
            if(arg==NULL)
            {
                printf("\n[ ERROR ] Invalid input:\n");
                printf("delete <num_chars> - Delete characters before the cursor\n\n");
                continue;
            }
            int pos = atoi(arg);
            if(delete_txt(edit,pos)==SUCCESS)
                printf("\n[ SUCCESS ] text deleted\n\n");

        }
        else if(!strcmp(cmd,"copy"))
        {
            char *start = strtok(arg," ");
            char *end = strtok(NULL,"");
            if(start == NULL || end == NULL)
            {
                printf("\n[ ERROR ] Invalid input:\n");
                printf("copy <startpos> <endpos> - Copy selected characters to clipboard\n\n");
                continue;
            }
            // printf("start: %s\nend: %s\n",start,end);
            if(copy_txt(edit,atoi(start),atoi(end))==SUCCESS)
                printf("\n[ SUCCESS ] text copied\n\n");
        }
        else if(!strcmp(cmd,"cut"))
        {
            char *start = strtok(arg," ");
            char *end = strtok(NULL,"");
            if(start == NULL || end == NULL)
            {
                printf("\n[ ERROR ] Invalid input:\n");
                printf("cut <startpos> <endpos> - Cut selected characters and store in clipboard\n\n");
                continue;
            }
            if(cut_txt(edit,atoi(start),atoi(end))==SUCCESS)
                printf("\n[ SUCCESS ] text cut\n\n");
        }
        else if(!strcmp(cmd,"paste"))
        {
            if(paste_txt(edit)==SUCCESS)
                printf("\n[ SUCCESS ] text pasted\n\n");
        }
        else if(!strcmp(cmd,"save"))
        {
            if(arg==NULL)
            {
                printf("\n[ ERROR ] Invalid input:\n");
                printf("save <file_name> - Save the current document to a file\n\n");
                continue;
            }
            if(save_file(edit,arg)==SUCCESS)
                printf("\n[ SUCCESS ] file saved\n\n");
        }
        else if(!strcmp(cmd,"open"))
        {
            if(arg==NULL)
            {
                printf("\n[ ERROR ] Invalid input:\n");
                printf("open  <file_name> - Open an existing .txt file\n\n");
                continue;
            }
            if(open_file(edit,arg)==SUCCESS)
                printf("\n[ SUCCESS ] file opned\n\n");
        }
        else if(!strcmp(cmd,"close"))
        {
            close_file(edit);
        }
        else if(!strcmp(cmd,"exit"))
        {
            printf("exiting...\n");
            return SUCCESS;
        }
        else if(!strcmp(cmd,"help"))
        {
            printf("[ HELP MENU ] \n");
            print_menu();
        }
        else
        {
            printf("\n[ ERROR ] invalid! re-try:\n\n");
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
    printf("8. save <file_name> - Save the current document to a file\n");
    printf("9. open  <file_name> - Open an existing .txt file\n");
    printf("10. close - Close the current document\n");
    printf("11. print - Print the current document\n");
    printf("12. exit - Exit the text editor Enter command:\n\n");
}

//-----------------------------------------------------------------------------------------------------------------//

void editor_init(EDITOR *edit)
{
    edit->head=NULL;
    edit->tail=NULL;
    edit->cursor_line=0;
    edit->cursor_col=0;
    edit->clipboard[0]='\0';
    edit->fname[0]='\0';
    edit->fptr=NULL;
}

//-----------------------------------------------------------------------------------------------------------------//

int display_document(EDITOR *edit)
{
    printf("\n|----------------------------------------------------------------------------------------------------|\n");
    LINE *temp = edit->head;
    if(temp==NULL)
        printf("[ INFO ] Empty document\n");
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
