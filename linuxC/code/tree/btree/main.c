#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX(i, j) (((i) > (j)) ? (i) : (j))
#define NAMESIZE 32
struct score_st{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};
struct node_st{
    struct score_st data;
    struct node_st *l, *r;
};
void print_s(struct score_st *d){
    printf("%d %s %d %d \n", d->id, d->name,d->math, d->chinese);
}
void print_s_id(struct score_st *d){
    printf("%d\n", d->id);
}
int insert(struct node_st ** root,struct score_st* data){
    struct node_st *node;
    if (*root == NULL) {
        node= malloc(sizeof(*node));
        if(node == NULL){
            return -1;
        }
        // 这里这样写，没有问题，是因为结构体复制的是，会直接生成一个全新的副本，但是也有一个前提
        // 结构体里面定义的是字符数组，如果定义的是字符指针就会有问题，定义成字符指针实际上拷贝的是引用
        node->data = *data;
        node->l = NULL;
        node->r = NULL;
        // 这是二级指针
        *root = node;
        return 0;
    }
    if(data->id <= (*root)->data.id){
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
   print_s_id(&root->data);
   draw_(root->l, level +1);

}
void draw(struct node_st * root){
    draw_(root, 0);
    printf("-------------------------------\n");
}
struct score_st * find(struct node_st *root, int id){
    if (root == NULL) {
        return NULL;
    }
    if (id== root->data.id) {
        return &root->data;
    }
    if (id< root->data.id) {
       return find(root->l, id);
    }else {
       return find(root->r, id);
    }
}
void travel(struct node_st *root){
    if (root == NULL) {
        return;
    }
    //printf("%d", root ->data.id);
    print_s(&(root ->data));
    travel(root->l);
    travel(root->r);
}
struct node_st *tree =NULL;
int get_num(struct node_st *root){
    if (root == NULL) {
        return 0;
    }
    int l= get_num(root->l) ;
    int r = get_num(root->r);
    //return MAX(l, r) +1;
    return l + 1 +r;

}
struct node_st * find_min(struct node_st * root){
    if (root ->l == NULL) {
        return root;
    }
    return find_min(root->l);

}
struct node_st * find_max(struct node_st * root){
    if (root ->r == NULL) {
        return root;
    }
    return find_max(root->r);

}
static void turn_left(struct node_st **root){
    // 左旋就是把原来根的右子节点当作根节点，把根挂在新的根节点的左子树上
    //但是新的根节点左子树不一定为空，所以，要顺着左子树一直找，找到某个节点
    // 的左子树为空，
    // 然后旧的根节点的右子树就变成了空
    struct node_st * cur = *root;
    *root = cur->r;
    cur->r = NULL;
    find_min(*root) ->l =cur;
    //draw(tree);
}
static void turn_right(struct node_st **root){
    // 左旋就是把原来根的左子节点当作根节点，把根挂在新的根节点的右子树上
    //但是新的根节点右子树不一定为空，所以，要顺着右子树一直找，找到某个节点
    // 的右子树为空，
    // 然后旧的根节点的右子树就变成了空
    struct node_st * cur = *root;
    *root = cur->l;
    cur->l = NULL;
    find_max(*root) ->r =cur;
    //draw(tree);

}
static void balance(struct node_st ** root){
    if (*root == NULL) {
        return;
    }
    while(1){
        int  sub =get_num((*root)->l)  - get_num((*root)->r);

        if (sub >= -1 && sub <=1) {
            // 这时候说明平衡了，可以结束了
            break;
        }
        if (sub < -1) {
         turn_left(root);
        }else {
            turn_right(root);
        }
    }
    balance(&(*root)->l);
    balance(&(*root)->r);
}
static void delete(struct node_st ** root, int id){
    struct node_st **node = root;
    struct node_st *cur = NULL;

    while (*node!=NULL && (*node)->data.id !=id) {
        if (id < (*node)->data.id) {
            node = &(*node)->l;
        }else {
            node = &(*node)->r;
        }
    }
    if (*node==NULL) {
        return;
    }
    cur =*node;
    if (cur->l==NULL) {
        *node = cur->r;
    }else {
        *node = cur->l;
        find_max(cur->l)->r= cur->r;
    }
    free(cur);

    
}
int main(){
    // 存放原则，小数往左，大数往右
    
    int arr[] ={1,2,3,7,6,5,9,8,4};
    int i;
    struct score_st  tmp;
    for (i =0; i<sizeof(arr)/sizeof(*arr); i++) {

        snprintf(tmp.name, NAMESIZE, "stu%d", arr[i]);
        tmp.id = arr[i];
        tmp.math = rand()%100;
        tmp.chinese = rand()%100;
        insert(&tree, &tmp);
    }
    #if 0
    int tmpid = 2;
    struct score_st *datap = NULL;
    datap =  find(tree, tmpid);
    if (datap == NULL) {
        printf("Can not find the id %d\n", tmpid);
    }else {
        print_s( datap);
    }
    #endif 
    //travel(tree);
    draw(tree);
    balance(&tree);
    draw(tree);
    int tmpid  =5;
    delete(&tree, tmpid);
    draw(tree);


    exit(0);
}