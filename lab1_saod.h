#ifndef LAB1_SAOD_H
#define LAB1_SAOD_H

#define RED 1
#define BLACK 0

typedef struct{
    int key;
    int value;
    int color;
    rbtree* root;
    rbtree* right;
    rbtree* left;
    rbtree* parent;
}rbtree;

void left_rotate(rbtree* parent);

void rbtree_add_fixup(rbtree* t_root, rbtree* child);
rbtree* rbtree_add(rbtree* t_root, int key, int value);
rbtree* rbtree_lookup(rbtree* t_root, int key);
rbtree* rbtree_delete(rbtree* t_root, int key);
rbtree* rbtree_min(rbtree* t_root);
rbtree* rbtree_max(rbtree* t_root);
void rbtree_free(rbtree* t_root);
void rbtree_print_dfs(rbtree* t_root, int level);
rbtree* create_node(int key, int value);

#endif