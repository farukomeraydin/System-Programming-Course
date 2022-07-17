#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

int main (){
    struct passwd *pwd;
    struct group *grp;

    while((pwd = getpwent()) != NULL)
        printf("%s\n", pwd->pw_name);


    endpwent();

    printf("-----------------\n");

    while ((grp = getgrent()) != NULL)
        printf("%s\n", grp->gr_name);

    endgrent();
    
    return 0;
}
