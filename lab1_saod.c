#include <stdio.h>
#include <stdlib.h>
#include "lab1_saod.h"

rbtree *create_node(int key, int value)
{
    rbtree *node = malloc(sizeof(rbtree));
    node->color = RED;
    node->key = key;
    node->value = value;
    return node;
}

rbtree *rbtree_add(rbtree *t_root, int key, int value)
{
    rbtree *tree = t_root;
    while (tree != t_root->null)
    {
        if (key < tree->key)
        {
            tree = tree->left;
        }
        else if (key > tree->key)
        {
            tree = tree->right;
        }
        else
        {
            return;
        }
    }

    rbtree *node = create_node(key, value);
    if (t_root->root == NULL)
    {
        t_root->null = malloc(sizeof(rbtree));
        t_root->null->color = BLACK;
        t_root->root = node;
        t_root->parent = t_root->null;
    }
    else
    {
        if (key < t_root->parent->key)
        {
            t_root->parent->left = node;
        }
        else
        {
            t_root->parent->right = node;
        }
    }

    node->color = RED;
    node->left = t_root->null;
    node->right = t_root->null;
    rbtree_add_fixup(t_root, node);
    return tree;
}

void left_rotate(rbtree *t_root, rbtree *parent)
{
    rbtree *child = parent->right;
    parent->right = child->left;
    if (child->left != t_root->null)
    {
        child->left->parent = parent;
    }
    child->parent = parent->parent;
    if (parent->parent == t_root->null)
    {
        t_root->root = child;
    }
    else
    {

        if (parent == parent->parent->left)
        {
            parent->parent->left = child;
        }
        else
        {
            parent->parent->right = child;
        }
    }
    child->left = parent;
    parent->parent = child;
}

void right_rotate(rbtree *t_root, rbtree *parent)
{
    rbtree *child = parent->left;
    parent->left = child->right;
    if (child->right != t_root->null)
    {
        child->right->parent = parent;
    }
    child->parent = parent->parent;
    if (parent->parent == t_root->null)
    {
        t_root->root = child;
    }
    else
    {

        if (parent == parent->parent->left)
        {
            parent->parent->left = child;
        }
        else
        {
            parent->parent->right = child;
        }
    }
    child->right = parent;
    parent->parent = child;
}

void rbtree_add_fixup(rbtree *t_root, rbtree *child)
{
    while (child->parent->color == RED)
    {
        if (child->parent == child->parent->parent->left)
        {
            rbtree *uncle = child->parent->parent->right;
            if (uncle->color == RED)
            //case 1
            {
                child->parent->color = BLACK;
                uncle->color = BLACK;
                child->parent->parent->color = RED;
                child = child->parent->parent;
            }
            else
            {
                if (child == child->parent->right)
                {
                    //case 2
                    child = child->parent;
                    left_rotate(t_root, child);
                }
                //case 3
                child->parent->color = BLACK;
                child->parent->parent->color = RED;
                right_rotate(t_root, child->parent->parent);
            }
        }
        else
        {
            rbtree *uncle = child->parent->parent->left;
            if (uncle->color == RED)
            {
                //case 4
                child->parent->color = BLACK;
                uncle->color = BLACK;
                child->parent->parent->color = RED;
                child = child->parent->parent;
            }
            else
            {
                if (child == child->parent->left)
                {
                    //case 5
                    child = child->parent;
                    right_rotate(t_root, child);
                }
                //case 6
                child->parent->color = BLACK;
                child->parent->parent->color = RED;
                left_rotate(t_root, child->parent->parent);
            }
        }
    }
    t_root->root->color = BLACK;
}

rbtree *rbtree_lookup(rbtree *t_root, int key)
{
    while (t_root != t_root->null)
    {
        if (t_root->key == key)
        {
            return t_root;
        }
        else
        {
            if (t_root->key < key)
            {
                t_root = t_root->left;
            }
            else
            {
                t_root = t_root->right;
            }
        }
    }
    return t_root;
}

rbtree *rbtree_transplant(rbtree *t_root, rbtree *u, rbtree *v)
{
    if (u->parent == t_root->null)
    {
        t_root->root = v;
    }
    else
    {
        if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
    }
    v->parent = u->parent;
    return v;
}

rbtree *rbtree_min(rbtree *t_root)
{
    while (t_root->left != t_root->null)
    {
        t_root = t_root->left;
    }
    return t_root;
}

rbtree *rbtree_max(rbtree *t_root)
{
    while (t_root->right != t_root->null)
    {
        t_root = t_root->right;
    }
    return t_root;
}

rbtree *rbtree_delete(rbtree *t_root, int key)
{
    rbtree *node = rbtree_lookup(t_root, key);
    rbtree *x;
    if (node == t_root->null)
    {
        return;
    }
    rbtree *y = node;
    int y_original_color = node->color;
    if (node->left == t_root->null)
    {
        x = node->right;
        rbtree_transplant(t_root, node, node->right);
    }
    else
    {
        if (node->right == t_root->null)
        {
            x = node->left;
            rbtree_transplant(t_root, node, node->left);
        }
        else
        {
            y = rbtree_min(node->right);
            y_original_color = y->color;
            rbtree *x = y->right;
            if (y->parent == node)
            {
                x->parent = y;
            }
            else
            {
                rbtree_transplant(t_root, y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            rbtree_transplant(t_root, node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }
    }
    if (y_original_color == BLACK)
    {
        rbtree_delete_fixup(t_root, x);
    }
    free(node);
}

void rbtree_delete_fixup(rbtree *t_root, rbtree *node)
{
    while (node != t_root->root && node->color == BLACK)
    {
        if (node == node->parent->left)
        {
            rbtree *w = node->parent->right;
            if (w->color == RED)
            {
                //case 1
                w->color = BLACK;
                node->parent->color = RED;
                left_rotate(t_root, node->parent);
                w = node->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                //case 2
                w->color = RED;
                node = node->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    //case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(t_root, w);
                    w = node->parent->right;
                }
                //case 4
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(t_root, node->parent);
                node = t_root->root;
            }
        }
        else
        {
            rbtree *w = node->parent->left;
            if (w->color == RED)
            {
                //case 5
                w->color = BLACK;
                node->parent->color = RED;
                left_rotate(t_root, node->parent);
                w = node->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                //case 6
                w->color = RED;
                node = node->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    //case 7
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(t_root, w);
                    w = node->parent->left;
                }
                //case 8
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(t_root, node->parent);
                node = t_root->root;
            }
        }
    }
    node->color = BLACK;
}

int main()
{
    printf("zaebis`\n");
    return 0;
}