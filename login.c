#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h" // to read and write to the shadow filr

int
checkpasswd(char *filename, char *user, char *passwd)
{
    int fd, n;
    char buf[512];
    char line[128];
    int linelen = 0;

    fd = open(filename, O_RDONLY);
    if(fd < 0)
        return 0;

    while((n = read(fd, buf, sizeof(buf))) > 0){
        for(int i = 0; i < n; i++){
            if(buf[i] == '\n'){
                line[linelen] = '\0';

                char *p = strchr(line, ':');
                if(p){
                    *p = '\0';
                    if(!strcmp(user, line) &&
                       !strcmp(passwd, p + 1)){
                        close(fd);
                        return 1;
                    }
                }

                linelen = 0;
            }
            else if(linelen < sizeof(line) - 1){
                line[linelen++] = buf[i];
            }
        }
    }

    close(fd);
    return 0;
}

int main(void)
{

    char username[64];
    char password[64];

    printf(1, "\nxv6 login\n");
    printf(1, "Username: ");
    gets(username, 64);

    printf(1, "Password: ");
    gets(password, 64);


    int len = strlen(username);
    if(len > 0 && username[len-1] == '\n')
        username[len-1] = 0;

    len = strlen(password);
    if(len > 0 && password[len-1] == '\n')
        password[len-1] = 0;

    if(checkpasswd("shadow", username, password)){
      char home_dir[64];
      strcpy(home_dir, "/home/");      
      mkdir(home_dir);      
      strcpy(home_dir + strlen(home_dir), username);
      mkdir(home_dir);

      printf(1,"\nWelcome %s!\n", username);

      char *args[] = {"sh", 0};
      exec(args[0], args);
      printf(1, "login: exec sh failed\n");
      exit(); 
    } 
      
    printf(1, "login: wrong username or password\n");
    exit();

}