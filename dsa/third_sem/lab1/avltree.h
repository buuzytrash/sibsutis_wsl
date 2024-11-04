#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>

#ifndef __avltree__
#define __avltree__

struct avltree
{
    int key;
    char *value;

    int height;
    struct avltree *left;
    struct avltree *right;
};

struct avltree *avltree_create(int key, char *value);                    // создание авл-дерева done
struct avltree *avltree_lookup(struct avltree *tree, int key);           // поиск узла по ключу done
void avltree_free(struct avltree *tree);                                 // удаление авл-дерева (обход в обратном порядке) done
struct avltree *avltree_add(struct avltree *tree, int key, char *value); // добавление элемента done
struct avltree *avltree_delete(struct avltree *tree, int key);           // удаление элемента done
struct avltree *avltree_min(struct avltree *tree);                       // поиск минимального элемента
struct avltree *avltree_max(struct avltree *tree);                       // поиск максимального элемента
int avltree_height(struct avltree *tree);                                // высота дерева done
int avltree_balance(struct avltree *tree);                               // баланс дерева done
struct avltree *avltree_right_rotate(struct avltree *tree);              // правый поворот done
struct avltree *avltree_left_rotate(struct avltree *tree);               // левый поворот done
struct avltree *avltree_leftright_rotate(struct avltree *tree);          // лево правый поворот done
struct avltree *avltree_rightleft_rotate(struct avltree *tree);          // право левый поворот done
void avltree_print_dfs(struct avltree *root, int level);                 // вывод до опред уровня
int imax2(int height_left, int height_right);                            // максимум высот между 2 поддеревьями
struct avltree *balance_delete(struct avltree *tree);
struct avltree *delete_min(struct avltree *tree);
double wtime();

#endif