#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX(i, j) (((i) > (j)) ? (i) : (j))
#define NAMESIZE 32
#define FNAME "/tmp/out"
struct score_st{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};
struct node_st{
    char data;
    struct node_st *l, *r;
};
int save_(struct node_st * root, FILE * fp){
    fputc('(',fp);
    // if error 省略了
    if (root==NULL) {
        fputc(')',fp);
        return 0;
    // if error 省略了
    }
    fputc(root->data,  fp);
    // if error 省略了
    save_(root->l, fp);
    save_(root->r, fp);
    fputc(')',  fp);
    // if error 省略了
    return 0;
}
static int save(struct node_st *root, const char * path){
    FILE * fp;
    fp= fopen(path, "w");
    if (fp==NULL) {
        return -1;
    }
    save_(root, fp);
    fclose(fp);
    return 0;

}
// 不要把char当作参数传递，而是使用int
int insert(struct node_st ** root,int data){
    struct node_st *node;
    if (*root == NULL) {
        node= malloc(sizeof(*node));
        if(node == NULL){
            return -1;
        }
        // 这里这样写，没有问题，是因为结构体复制的是，会直接生成一个全新的副本，但是也有一个前提
        // 结构体里面定义的是字符数组，如果定义的是字符指针就会有问题，定义成字符指针实际上拷贝的是引用
        node->data = data;
        node->l = NULL;
        node->r = NULL;
        // 这是二级指针
        *root = node;
        return 0;
    }
    if(data <= (*root)->data){
       return insert(&((*root)->l),  data);
    }else {
       return insert(&((*root)->r), data);
    }

}

void draw_(struct node_st * root, int level){
    if (root ==NULL) {
        return;
    }
   draw_(root->r, level +1);
   for (int i=0; i<level; i++) {
        printf("    ");
   }
   printf("%c\n", root->data);
   draw_(root->l, level +1);

}
void draw(struct node_st * root){
    draw_(root, 0);
    printf("-------------------------------\n");
}
struct node_st *tree =NULL;
int main(){
    // 存放原则，小数往左，大数往右
    
    char arr[] ="cefadjbh";
    int i;
    struct score_st  tmp;
    // 这里减1是为了去掉尾0.
    for (i =0; i<sizeof(arr)/sizeof(*arr) -1; i++) {

        insert(&tree, arr[i]);
    }
   
    draw(tree);
    int res= save(tree,FNAME);
    printf("save result:%d\n", res);
    exit(0);
}