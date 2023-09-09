#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DESC_SIZE 256
#define KEY_SIZE 256
#define BUF_SIZ 512

#define FNAME "log"

struct node_st{
    struct node_st * ch[26];
    char desc[DESC_SIZE];
};
int get_word(FILE * fp, char* key, char* desc){
    char buf[BUF_SIZ];
    char *retp;
    // while (1) {
    //     retp= fgets(buf, BUF_SIZ, fp);
    //     if (retp == NULL) {
    //         printf("retp == NULL\n");
    //         return -1;
    //     }
    //     if (buf[0]=='\n') {
    //         break;
    //     }

    // }
    retp= fgets(buf, BUF_SIZ, fp);
    if (retp == NULL) {
        return -1;
    }
    int i,j;
    for (i=0; i<KEY_SIZE-1 && buf[i]!=':'; i++) {
       key[i]= buf[i];
    }
    key[i]= '\0';
    i++;
    for (j=0; j<DESC_SIZE-1 && buf[i]!='\0'; j++,i++) {
       desc[j]= buf[i];
    }
    desc[j]='\0';
    return 0;

}
struct node_st * newnode(){
    struct node_st * node;
    node =malloc(sizeof((*node)));
    if (node==NULL) {
        return NULL;
    }
    node->desc[0] = '\0';
    
    for (int i=0; i<26; i++) {
        node->ch[i]=NULL;
    }
    return node;

}
char * find(struct node_st *root,char *key){
    if (root==NULL) {
        return NULL;
    }
    if (*key=='\0') {
        return root->desc;
    }
    return find(root->ch[*key -'a'], key+1);


}
int  insert(struct node_st **root, char *key, char *desc){
    if (*root==NULL) {
        *root= newnode();
        if (*root == NULL) {
            return -1;
        }
    }
    if (*key =='\0') {
        strcpy((*root)->desc, desc);
        return 0;
    }
    return insert((*root)->ch+*key-'a',key+1,desc);
}
int main(){
    FILE *fp;
    struct node_st *tree=NULL;
    fp=fopen(FNAME, "r");
    char desc[DESC_SIZE]={'\0'};
    char key[KEY_SIZE]={'\0'};
    char * datap;

    if (fp==NULL) {
        fprintf(stderr, "fopen():error\n");
        exit(1);
    }
    int ret;
    while (1) {
        // 这里是一次把一行给读出来，然后分别写入key和desc里。所以在get_word里面就不需要while循环
       ret = get_word(fp,key,desc);
       if (ret==-1) {
        break;
       }
       insert(&tree, key,desc);
    }
    datap=find(tree,"donkey");
    if (datap==NULL) {
        printf("Can not find!\n");
    }else {
        puts(datap);
    }
    fclose(fp);
    exit(0);
}