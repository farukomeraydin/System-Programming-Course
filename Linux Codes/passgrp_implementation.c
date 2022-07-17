int main(void){
    struct passwd* pass;
    while ((pass = csd_getpwent()) != NULL){
        printf("User name: %s\n", pass->pw_name);
        printf("User Id: %lld\n", (long long)pass->pw_uid);
        printf("-------------------\n");
    }
    csd_setpwent();
    while ((pass = csd_getpwent()) != NULL){
        printf("User name: %s\n", pass->pw_name);
        printf("User Id: %lld\n", (long long)pass->pw_uid);
        printf("-------------------\n");
    }

    csd_endpwent();

    printf("csd_getpwnam test...\n");
    if ((pass = csd_getpwnam("omer")) != NULL){
        printf("User name: %s\n", pass->pw_name);
        printf("User Id: %lld\n", (long long)pass->pw_uid);
    }

    return 0;
}
