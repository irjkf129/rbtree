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
    while (tree != NULL)
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
        t_root->root = node;
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
    rbtree_add_fixup(t_root, node);
    return tree;
}

void left_rotate(rbtree *parent)
{
    rbtree *child = parent->right;
    parent->right = child->left;
    if (child->left != NULL)
    {
        child->left->parent = parent;
    }
    child->parent = parent->parent;
    if (parent == parent->parent->left)
    {
        parent->parent->left = child;
    }
    else
    {
        parent->parent->right = child;
    }
    child->left = parent;
    parent->parent = child;
}

void right_rotate(rbtree *parent)
{
    rbtree *child = parent->left;
    parent->left = child->right;
    if (child->right != NULL)
    {
        child->right->parent = parent;
    }
    child->parent = parent->parent;
    if (parent == parent->parent->left)
    {
        parent->parent->left = child;
    }
    else
    {
        parent->parent->right = child;
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
                    left_rotate(child);
                }
                //case 3
                child->parent->color = BLACK;
                child->parent->parent->color = RED;
                right_rotate(child->parent->parent);
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
                child->parent->parent = RED;
                child = child->parent->parent;
            }
            else
            {
                if (child->parent->left == child->parent->left)
                {
                    //case 5
                    child = child->parent;
                    right_rotate(child);
                }
                //case 6
                child->parent->color = BLACK;
                child->parent->parent->color = RED;
                left_rotate(child->parent->parent);
            }
        }
    }
    t_root->root->color = BLACK;
}

rbtree *rbtree_lookup(rbtree *t_root, int key)
{
    while (t_root != NULL)
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