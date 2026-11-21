#include "txt_editor.h"

#define MAX 100

int main()
{
    EDITOR edit;

    editor_init(&edit);

    print_banner();
    print_menu();
    start_editor(&edit);
}