#ifndef TXT_OPS_H
#define TXT_OPS_H

#include "txt_editor.h"

//-----------------------------------------------------------------------------------------------------------------//

int insert_txt(EDITOR *,char *);
int delete_txt(EDITOR *,int);
int copy_txt(EDITOR *,int,int);
int cut_txt(EDITOR *,int,int);
int paste_txt(EDITOR *);

//-----------------------------------------------------------------------------------------------------------------//

#endif