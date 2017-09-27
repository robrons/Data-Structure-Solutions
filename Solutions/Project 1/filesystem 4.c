#include "filesystem.h"

typedef struct _filesystem_node fsNode;
struct _filesystem_node{
   char c[21],f[2];
   fsNode * parent;
   fsNode * firstchild;
   fsNode * nextsibling;
};
fsNode * newfsNode(char *c, char* f){
  fsNode *fs = (fsNode*)malloc(sizeof(fsNode));
  strcpy(fs->c,c);
  strcpy(fs->f,f);
  fs->firstchild = fs->nextsibling = NULL;
  return fs;
}


typedef struct _filesystemTree fsTree;
struct _filesystemTree{
  fsys fs;
  fsNode * root;
  fsNode * cwd;
};

void fs_cd(fsys*, char*);
void fs_find(fsys*, char*);
void fs_ls(fsys*, char*);
void fs_mkdir(fsys*, char*);
void fs_pwd(fsys*);
void fs_rm(fsys*, char*);
void fs_rmf(fsys*, char*);
void fs_touch(fsys*, char*);
void destroyFileSystem(fsys*);
fsNode * followset(fsNode*, char*, char*, char*);
fsNode * followget(fsNode*, char*, char*);

fsys * newFileSystem(){
  fsTree * f = NULL;
  f = (fsTree*)malloc(sizeof(fsTree));
  f->root = newfsNode("/","D");
  f->root->parent = NULL;
  f->cwd = f->root;
  f->fs.fs_mkdir = fs_mkdir;
  f->fs.fs_cd = fs_cd;
  f->fs.fs_find = fs_find;
  f->fs.fs_ls = fs_ls;
  f->fs.fs_pwd = fs_pwd;
  f->fs.fs_rm = fs_rm;
  f->fs.fs_rmf = fs_rmf;
  f->fs.fs_touch = fs_touch;
  f->fs.destroyFileSystem = destroyFileSystem;
  return (fsys*)f;
}

void fs_mkdir(fsys* f, char* c)
{
fsTree *ft = (fsTree *) f;
if(*c == '/'){
char locn[21];
c++;
followset(ft->root,c, locn, "D");
} else{
char locnm[21];
followset(ft->cwd,c, locnm, "D");
}
}

void _patrc(fsNode* fn){
  if(fn!=NULL){
   _patrc(fn->parent);
    if((strcmp(fn->c,"/")!=0)){
    printf("%s","/");
     printf("%s",fn->c);
    }

}
}

void fs_cd(fsys* f, char* c)
{
fsTree *ft = (fsTree *) f;
if(*c == '/'){
char locn[21];
c++;
ft->cwd = followget(ft->root,c,locn);
} else{
char locnm[21];
fsNode * child = followget(ft->cwd,c, locnm);
ft->cwd = child;
}
}

void fs_find(fsys* f, char* c)
{


}

fsNode * _ls(fsNode* fn){
  while(fn!=NULL){
  printf("%s %s\n",fn->f,fn->c);
  fn = fn->nextsibling;
}
}
void fs_ls(fsys* f, char* c)
{
fsTree *ft = (fsTree *) f;
if(c == NULL&&ft->cwd->parent==NULL){
 printf("Listing For '");
 if(ft->cwd==ft->root){printf("%s","/");}
 _patrc(ft->cwd);
  printf("':\n");
 _ls(ft->cwd->firstchild);
} else if(c == NULL&&ft->cwd->parent!=NULL){
 printf("Listing For '");
 _patrc(ft->cwd);
  printf("':\n");
 _ls(ft->cwd->firstchild);
}
}

void fs_pwd(fsys* f)
{
fsTree *ft = (fsTree *) f;
if(ft->cwd==ft->root){printf("%s","/");}
_patrc(ft->cwd);
printf("\n");
}

fsNode * removeTemp(fsNode * temp, char *path){
 if(strcmp(temp->c, path)==0){
    temp = temp->nextsibling;
} else {
  temp->nextsibling = removeTemp(temp->nextsibling, path);
}
}


void fs_rm(fsys* f, char* path)
{
fsTree *ft = (fsTree *) f;
if(*path == '/'){
    char locnm[21];
    path++;
    fsNode * temp = followget(ft->root,path, locnm);
    if(temp == NULL){printf("%s\n","Remove Error: Cannot remove file or directory.");
   } else if(temp->firstchild!=NULL){printf("%s","Remove Error: directory '");
     _patrc(temp);
     printf("%s\n","' is not empty.");
   } else {
        temp->parent->firstchild = removeTemp(temp->parent->firstchild,locnm);
        free(temp);
   }
}
else{
    char locnm[21];
    fsNode * temp = followget(ft->cwd,path, locnm);
    if(temp == NULL){printf("%s\n","Remove Error: Cannot remove file or directory.");
   } else if(temp->firstchild!=NULL){printf("%s","Remove Error: directory '");
     _patrc(temp);
     printf("%s\n","' is not empty.");
   } else {
        temp->parent->firstchild = removeTemp(temp->parent->firstchild,locnm);
        free(temp);
   }

   }

}

void fs_rmf(fsys* f, char* path)
{
fsTree *ft = (fsTree *) f;
if(*path == '/'){
    char locn[21];
    path++;
    fsNode * temp = followget(ft->root,path, locn);
    if(temp == NULL){printf("%s\n","Remove Error: Cannot remove file or directory.");
    }else {
        temp->parent->firstchild = removeTemp(temp->parent->firstchild,locn);
        free(temp);
   }
}
else{
    char locnm[21];
    fsNode * temp = followget(ft->cwd,path, locnm);
    if(temp == NULL){printf("%s\n","Remove Error: Cannot remove file or directory.");
    }else {
        temp->parent->firstchild = removeTemp(temp->parent->firstchild,locnm);
        free(temp);
   }

   }
}

void fs_touch(fsys* f, char* c)
{
fsTree *ft = (fsTree *) f;
if(*c == '/'){
char locn[21];
c++;
followset(ft->root,c, locn, "F");
} else{
char locnm[21];
followset(ft->cwd,c, locnm, "F");
}
}

fsNode * setChild(fsNode * fn, char * locnm, fsNode * parent, char* f){
if(fn==NULL){
fsNode* temp = newfsNode(locnm,f);
temp->parent = parent;
return temp;
}
else
{
 fn->nextsibling = setChild(fn->nextsibling, locnm, parent, f);
}
}

fsNode * getChild(fsNode * fn, char * locnm){
if(fn==NULL){return NULL;}
else if(strcmp(fn->c,locnm)==0)
{
return fn;
}
else if(fn->nextsibling!=NULL)
{
 getChild(fn->nextsibling, locnm);
}
else {
return NULL;
}
}

char * remLocNm(char * path, char * locnm){
  if(*path=='\0'){
  *locnm  = '\0';
  return NULL;
  }
  while(*path!= '/' && *path != '\0'){
    *locnm = *path;
    locnm ++;
    path ++;
  }
  *locnm = '\0';
  if(*path == '/') path++;
  return path;
}
void recFollow(fsNode* temp, char * remain, char * locnm, char * f){
if(temp->nextsibling==NULL){
    followset(temp, remain, locnm, f);
} else
    {
     recFollow(temp->nextsibling, remain, locnm, f);
    }
}
fsNode * followset(fsNode* fn, char* path, char* locnm, char* f)
{
if((strcmp(fn->f,"F")==0)){
 printf("%s\n","Make Dir Error: Cannot create directory.");
 return NULL;
}
if(*path == '\0') {return NULL;}
char *remain = remLocNm(path, locnm);
if(strcmp(locnm,"..")==0){if(fn->parent!=NULL){
return followset(fn->parent,remain,locnm, f);
}else {
return followset(fn,remain, locnm, f);
}
}
if(strcmp(locnm,".")==0){ return followset(fn,remain, locnm, f);}
fn->firstchild = setChild(fn->firstchild,locnm, fn,f);
if(*remain!='\0'){
fsNode * temp = fn->firstchild;
recFollow(temp,remain,locnm, f);
}
}

fsNode * followget(fsNode* fn, char* path, char* locnm)
{

if(*path == '\0') {return fn;}
char *remain = remLocNm(path, locnm);
if(strcmp(locnm,"..")==0){if(fn->parent!=NULL){
return followget(fn->parent,remain,locnm);
}else {
return followget(fn,remain, locnm);
}
}
if(strcmp(locnm,".")==0){ return followget(fn,remain, locnm);}
fsNode * child = getChild(fn->firstchild, locnm);
if(*remain=='\0'){return child;}
if(*remain!='\0'){ followget(child,remain, locnm);}
}


void destroyFileSystem(fsys* f)
{


}
