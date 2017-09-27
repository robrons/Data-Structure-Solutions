#include <stdio.h>
#include <stdlib.h>
#include "filesystem.h"

int main()
{
 char command[21];
 fsys *fs = NULL;
 fs = newFileSystem();
 while(scanf("%s", command) > 0)
 {
 if(strcmp(command, "ls") == 0)
 {
 fs->fs_ls(fs, NULL);
 }else if(strcmp(command, "mkdir") == 0)
 {
 char path[21];
 scanf("%s", path);
 fs->fs_mkdir(fs,path);
 }else if(strcmp(command, "cd") == 0)
 {
 char path[21];
 scanf("%s", path);
 fs->fs_cd(fs,path);
 }else if(strcmp(command, "touch") == 0){
 char path[21];
 scanf("%s", path);
 fs->fs_touch(fs,path);
 }else if(strcmp(command, "pwd") == 0){
 fs->fs_pwd(fs);
 }
 }
    return 0;
}
