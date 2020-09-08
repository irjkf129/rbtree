#ifndef LAB1_SAOD_H
#define LAB1_SAOD_H

#define RED 1
#define BLACK 0

typedef struct rbt{
    int key;
    int value;
    int color;
    struct rbt* null;
    struct rbt* root;
    struct rbt* right;
    struct rbt* left;
    struct rbt* parent;
}rbtree;

void left_rotate(rbtree *t_root, rbtree *parent);//+
void right_rotate(rbtree *t_root, rbtree *parent);//+
void rbtree_transplant(rbtree* t_root, rbtree* u, rbtree* v);//+
rbtree* create_node(int key, int value);//+
void rbtree_add_fixup(rbtree* t_root, rbtree* child);//+
void rbtree_delete_fixup(rbtree* t_root, rbtree* node);//+

rbtree* rbtree_add(rbtree* t_root, int key, int value);//+
rbtree* rbtree_lookup(rbtree* t_root, int key);//+
rbtree* rbtree_delete(rbtree* t_root, int key);//+
rbtree* rbtree_min(rbtree* t_root);//+
rbtree* rbtree_max(rbtree* t_root);//+
void rbtree_free(rbtree* t_root);//+
void rbtree_print_dfs(rbtree* t_root);

#endif