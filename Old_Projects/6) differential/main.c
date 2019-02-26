#pragma GCC diagnostic ignored "-Wmultichar"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "differential.h"

#define STR_MAX_LENGTH 50
/*
void save_var_value (int* var_number, double* value)
{
    char str[STR_MAX_LENGTH] = "";
    fgets (str, STR_MAX_LENGTH-1, stdin);
    char var_name[STR_MAX_LENGTH] = "";
    sscanf(str, "%[^ =]%*[ ]%*[=]%d", &var_name, value);
    *var_number = get_var_number(var_name, __LINE__);
}
*/

struct tree_node* simplify_repetedly (struct tree_node* root, char* pre_f, FILE* out)
{
    int changed_const_flag    = 1;
    int changed_zero_one_flag = 1;
    while (changed_const_flag == 1 || changed_zero_one_flag == 1)
    {
        //fprintf (out, "The equation now:\n");
        tex_tree (root, pre_f, out, __LINE__);
        changed_const_flag    = 0;
        changed_zero_one_flag = 0;
        //root = simplify_const   (root, &changed_const_flag,    out, __LINE__);
        root = simplify_zero_one(root, &changed_zero_one_flag, out, __LINE__);
    }
    fprintf (out, "After all the simplifications it looks like this:\n");
    tex_tree (root, pre_f, out, __LINE__);

    fprintf (stderr, "---> %d\n", __LINE__);
    DUMP_NODE(root);
    return root;
}

int main()
{
    system("say \"Zdrastvui, dorogoy!\"");

    FILE* out = fopen("output.tex", "wb");
    char  str [200] = {};
    fgets (str, sizeof(str)-1, stdin);
    double x_val = 0;
    printf ("x="); scanf ("%lg", &x_val);
    double y_val = 'lul';

    struct tree_node* root = load_from_phrase(str, __LINE__);
    DOT_DUMP_TREE_BY_ELEM(root);
    if (runner(root, get_var_number("y", __LINE__), __LINE__, 0, is_var))
    {
        printf ("y="); scanf ("%lg", &y_val);
    }

    fprintf (out, "\\documentclass[12pt]{article}\n"
                  "\\begin{document}\n");

    fprintf (stderr, "---> %d\n", __LINE__);
    DUMP_NODE(root);
    root = simplify_repetedly (root, "f(x)=", out);
    fprintf (stderr, "---> %d\n", __LINE__);
    DUMP_NODE(root);

    fprintf(out, "\\begin{equation}\n\\end{equation}\nLet's find f'(x). ");

    struct tree_node* diff_root = differential(root, get_var_number("x", __LINE__), out, __LINE__);
    diff_root = simplify_repetedly (diff_root, "f'(x)=", out);
    if (!EQUAL_DOUBLE('lul', y_val))
    {
        runner(root,      get_var_number("y", __LINE__), __LINE__, y_val, change_var_to_const );
        runner(diff_root, get_var_number("y", __LINE__), __LINE__, y_val, change_var_to_const );
    }
    runner(root,      get_var_number("x", __LINE__), __LINE__, x_val, change_var_to_const );
    runner(diff_root, get_var_number("x", __LINE__), __LINE__, x_val, change_var_to_const );

    fprintf(out, "Let's count f(%lg). ", x_val);
    root = simplify_repetedly (     root, "f=", out);

    fprintf (out, "Let's count f'(%lg). ", x_val);
    diff_root = simplify_repetedly (diff_root, "f'(x)=", out);

    branch_remove(root, __LINE__);
    branch_remove(diff_root, __LINE__);
    fprintf (out, "\\end{document}\n");
    fclose  (out);
    system("latex output.tex >> tex.log 2>> tex.log");
    return 0;
}
