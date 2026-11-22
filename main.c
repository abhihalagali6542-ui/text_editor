#include "txt_editor.h"

int main()
{
    EDITOR edit;
    editor_init(&edit);
    print_banner();
    print_menu();
    start_editor(&edit);
}