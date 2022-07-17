#ifndef PASSGRP_H_
#define PASSGRP_H_

struct passwd {
    char   *pw_name;       /* username */
    char   *pw_passwd;     /* user password */
    uid_t   pw_uid;        /* user ID */
    gid_t   pw_gid;        /* group ID */
    char   *pw_gecos;      /* user information */
    char   *pw_dir;        /* home directory */
    char   *pw_shell;      /* shell program */
};

struct passwd* csd_getpwnam(const char* name);
struct passwd* csd_getpwuid(uid_t uid);
void csd_endpwent(void);
struct passwd* csd_getpwent(void);
void csd_setpwent(void);

#endif
