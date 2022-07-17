#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "passgrp.h"

#define MAX_LINE_CHAR   4096

static int is_all_ws(const char* str);


static FILE* g_f; //Dosya açıksa bir daha açılmayacak. Onun için statik yaptık

struct passwd* csd_getpwent(void){
    static struct passwd pass;
    static char buf[MAX_LINE_CHAR];
    char* str;
    int i;

    if (g_f == NULL)
        if ((g_f = fopen("/etc/passwd", "r")) == NULL)
            return NULL;

    do //Hepsi white space olan satırları atladık
        if (fgets(buf, MAX_LINE_CHAR, g_f) == NULL)
            return NULL;
    while(is_all_ws(buf));

    for (str = strtok(buf, ":"), i = 0; str != NULL; str = strtok(NULL, ":"), ++i)
        switch(i){
            case 0:
                pass.pw_name = str;
                break;
            case 1:
                pass.pw_passwd = str;
                break;
            case 2:
                pass.pw_uid = (uid_t)strtol(str, NULL, 10);
                break;
            case 3:
                pass.pw_uid = (gid_t)strtol(str, NULL, 10);
                break;
            case 4:
                pass.pw_gecos = str;
                break;
            case 5:
                pass.pw_dir = str;
                break;
            case 6:
                pass.pw_shell = str;
                break;     
        }
        return &pass;
}
void csd_setpwent(void){
    fseek(g_f, 0, SEEK_SET);
}

void csd_endpwent(void){
    if (g_f != NULL)
        fclose(g_f);

    g_f = NULL;
}

struct passwd* csd_getpwnam(const char* name){
    struct passwd* pass;
    while ((pass = csd_getpwent()) != NULL)
        if (!strcmp(name, pass->pw_name)){
            csd_endpwent();
            return pass;
        }

    csd_endpwent();
    return NULL;
}
struct passwd* csd_getpwuid(uid_t uid){
    struct passwd* pass;
    csd_endpwent();

    while ((pass = csd_getpwent()) != NULL)
        if (uid == pass->pw_uid)
            return pass;
    return NULL;
}


static int is_all_ws(const char* str){
    while(*str != '\0'){
        if (!isspace(*str))
            return 0;
        ++str;
    }
    return 1;
}
