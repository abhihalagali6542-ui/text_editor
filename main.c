#include "txt_editor.h"

#define MAX 100

int main()
{
    EDITOR edit;

    char input[MAX];
    
    char *cmd;
    char *arg;

    editor_init(&edit);

    print_banner();
    print_menu();

    while(1)
    {
        printf("Enter Command: ");
        fgets(input,sizeof(input),stdin);

        cmd = strtok(input," \n");
        arg = strtok(NULL,"\n");

        if(strcmp(cmd,"insert") == 0 && arg!=NULL)
        {
            insert_txt(&edit,arg);
            edit.cursor_line++;
            edit.cursor_col = strlen(arg);
        }
        else if(strcmp(cmd,"print") == 0)
        {
            display(&edit);
        }
        else if(strcmp(cmd,"exit") == 0)
        {
            printf("exiting...\n");
            return 0;
        }
        else
        {
            printf("\ninvalid! re-try:\n\n");
            print_menu();
        }
    }

}