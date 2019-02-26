#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED


#define DOT_DUMP_TREE_BY_ELEM( base_elem )                             \
{                                                                      \
    FILE* dmp = fopen("dmp.gv", "wb");                                 \
    fprintf (dmp, "digraph G {\n");                                    \
    dot_dump_tree (base_elem, dmp,  __LINE__);                         \
    fprintf (dmp, "\n}\n");                                            \
    fclose (dmp);                                                      \
    system ("xdot dmp.gv >> xdot.log 2>> xdot.log");                   \
}

#define CASE_OF_LEFT       'LEFT'
#define CASE_OF_RIGHT      'RGHT'
#define CASE_OF_PARENT     'prnt'

#define MAX_FUNCTION_NAME_LENGTH   10
#define MAX_VARIABLES              10

#define SINGLE_TABULATION_LENGTH   4
#define SINGLE_TABULATION          "    "
#define MAX_BRANCH_LENGTH          100


#define PAUSE {int t = 0; t = scanf("%d", &t);}


#define TYPE__FUNCTION      'cnuF'
#define TYPE__VARIABLE      'lbrV'
#define TYPE__CONSTANT      'tsnC'


#define DUMP_NODE( node )                                                               \
{                                                                                       \
    fprintf (stderr, " ~~~ Dump of node on address 0x%p ~~ \n", node);                  \
    fprintf (stderr, "  Data:             %lf\n", node -> data);                        \
    fprintf (stderr, "  Good canary:      %s\n", (char*)&node -> good_canary);          \
    fprintf (stderr, "  Canary1:          %s\n", (char*)&node -> canary1);              \
    fprintf (stderr, "  Canary2:          %s\n", (char*)&node -> canary2);              \
    fprintf (stderr, "  Node type:        %s\n", (char*)&node -> node_type);            \
    fprintf (stderr, "  Parent pointer:       0x%p\n", node -> parent);                 \
    fprintf (stderr, "  Left  branch pointer: 0x%p\n", node -> left_branch);            \
    fprintf (stderr, "  Right branch pointer: 0x%p\n", node -> right_branch);           \
    PAUSE;                                                                              \
}


#define CHECK_CANARY( node )                                                                         \
{                                                                                                    \
    if ( node -> canary1 != node -> good_canary )                                                    \
    {                                                                                                \
        fprintf (stderr, "ERROR: Detected dead canary1 at function\n"                                \
                         "%s, line %d.\n",  __PRETTY_FUNCTION__, __LINE__);                                     \
    }                                                                                                \
    if ( node -> canary2 != node -> good_canary )                                                    \
    {                                                                                                \
        fprintf (stderr, "ERROR: Detected dead canary2 at function\n"                                \
                         "%s, line %d.\n",  __PRETTY_FUNCTION__, __LINE__);                                     \
    }                                                                                                \
    if ( ( node -> canary1 != node -> good_canary ) || ( node -> canary2 != node -> good_canary ) )  \
        {DUMP_NODE (node); DOT_DUMP_TREE_BY_ELEM (node);   }                                         \
}


#define CHECK_CREATED( node )                                                 \
if (node == NULL)                                                             \
{                                                                             \
    fprintf (stderr, "ERROR: Function %s received NULL\n"                     \
                     "as a node argument on line %d.",  __PRETTY_FUNCTION__, line);  \
    PAUSE;                                                                    \
}


#define CHECK_LEFT( node )                                                             \
{                                                                                      \
    if ( node -> left_branch )                                                         \
    {                                                                                  \
        if ( node -> left_branch -> parent != node )                                   \
        {                                                                              \
            fprintf (stderr, "ERROR: Detected wrong connection with left-branch\n"     \
                             "node at function %s on line %d.\n", __PRETTY_FUNCTION__, __LINE__); \
            DOT_DUMP_TREE_BY_ELEM(node);                                               \
            DOT_DUMP_TREE_BY_ELEM(node -> left_branch->parent);                               \
        }                                                                              \
    }                                                                                  \
}

#define CHECK_RIGHT( node )                                                            \
{                                                                                      \
    if ( node -> right_branch )                                                        \
    {                                                                                  \
        if ( node -> right_branch -> parent != node )                                  \
        {                                                                              \
            fprintf (stderr, "ERROR: Detected wrong connection with right-branch\n"    \
                             "node at function %s on line %d.\n", __PRETTY_FUNCTION__, __LINE__);  \
            DOT_DUMP_TREE_BY_ELEM(node);                                               \
            DOT_DUMP_TREE_BY_ELEM(node -> right_branch->parent);                               \
        }                                                                              \
    }                                                                                  \
}


#define CHECK_NODE( node )   \
CHECK_CANARY   (node);       \
CHECK_LEFT     (node);       \
CHECK_RIGHT    (node);



#define NULL_CHECK( node, case_ )                                                   \
switch (case_)                                                                      \
{                                                                                   \
case CASE_OF_LEFT:                                                                  \
    {                                                                               \
        if (node -> left_branch != NULL)                                               \
        {                                                                                \
            fprintf (stderr, "ERROR: Wrong interaction with LEFT-branch pointer\n"        \
                             "of node at function %s on line %d.", function_name, line);  \
            DUMP_NODE (node);                                                             \
        }                                                                                \
    } break;                                                                           \
                                                                                    \
case CASE_OF_RIGHT:                                                                \
    {                                                                               \
        if (node -> right_branch != NULL)                                              \
        {                                                                                \
            fprintf (stderr, "ERROR: Wrong interaction with RIGHT-branch pointer\n"       \
                             "of node at function %s on line %d.", function_name, line);  \
            DUMP_NODE (node);                                                             \
        }                                                                                \
    } break;                                                                           \
                                                                                    \
case CASE_OF_PARENT:                                                               \
    {                                                                               \
        if (node -> parent != NULL)                                                    \
        {                                                                                \
            fprintf (stderr, "ERROR: Wrong interaction with a parent pointer\n"           \
                             "of node at function %s on line %d.", function_name, line);  \
            DUMP_NODE (node);                                                             \
        }                                                                                \
    } break;                                                                           \
                                                                                     \
default:                                                                            \
    {                                                                               \
        fprintf (stderr, "ERROR: Macro \"NULL_WARNING\" received\n"                 \
                         "wrong \"case_\" argument on line %d.", line);             \
        PAUSE;                                                                      \
    }                                                                               \
}

struct tree_node
{
    int canary1;

    int                good_canary;
    double             data;
    int                node_type;

    struct tree_node*  adress;
    struct tree_node*  parent;
    struct tree_node*  left_branch;
    struct tree_node*  right_branch;

    int canary2;
};


int dot_dump_tree (struct tree_node* node, FILE* outF, int line);
int tex_tree   (struct tree_node* base, char* pre_f, FILE* out, int line);
int tex_branch (struct tree_node* node, FILE* file,  int line);
int skip_frase_spaces ();

int transport_data (struct tree_node* node, char* data)
{
#define DEF_FUNC( name, number, dif_code )  \
    if (strcmp (data, name) == 0)           \
    {                                       \
        node->node_type = TYPE__FUNCTION;   \
        node->data      = number;           \
    }                                       \
    else

#include "functions_list.h"

#undef DEF_FUNC

    if (strlen (data) == 1 && isalpha (data[0]))
    {
        node->node_type = TYPE__VARIABLE;
        *(char*)&node->data = data[0];
    }else
    if (isdigit (data[0]) || data[0] == '-' || data[0] == '+')
    {
        printf ("---> %d\n", __LINE__);
        node->node_type = TYPE__CONSTANT;
        node->data      = atof (data);
    }else
    if (data[0] == '\0')
        {}
    else
    {
        fprintf (stderr, "ERROR: Detected some strange function \"%s\".", data);
        PAUSE;
        return 1;
    }

    CHECK_NODE (node);
    return 0;
}


struct tree_node* node_construct (char* data, int canary, int line)
{
    char* function_name = "node_construct";

    struct tree_node* node = calloc (1, sizeof (struct tree_node));
    CHECK_CREATED (node);

    if (transport_data (node, data))
        assert (!"Transport data continued anyway.");

    node -> adress = node;

    node -> canary1     = canary;
    node -> canary2     = canary;
    node -> good_canary = canary;

    CHECK_CREATED (node);
    CHECK_NODE    (node);
    return node;
}

struct tree_node* node_add (struct tree_node* base, const int connection_case,
                            struct tree_node* new_, int line);
struct tree_node* branch_copy (struct tree_node* original, int line)
{
    char* function_name = "branch copy";

    CHECK_CREATED(original);
    CHECK_NODE   (original);

    struct tree_node* a_copy = NULL;

    int orig_node_type = original->node_type;
    switch (orig_node_type)
    {
    case TYPE__CONSTANT:
        {
            a_copy = node_construct("0", 'tsnc', line);
            a_copy->data = original->data;
        } break;

    case TYPE__FUNCTION:
        {
            CHECK_LEFT (original);

            a_copy = node_construct("+", 'cnuf', line);
            a_copy->data = original->data;

                node_add (a_copy, CASE_OF_LEFT,  branch_copy(original->left_branch,  line), line);
            if (original->right_branch!=NULL)
                node_add (a_copy, CASE_OF_RIGHT, branch_copy(original->right_branch, line), line);
        } break;

    case TYPE__VARIABLE:
        {
            a_copy = node_construct("0", 'lbrv', line);
            a_copy->node_type = TYPE__VARIABLE;
            a_copy->data = original->data;
        } break;

    default:
        {
            fprintf(stderr, "Original node was of corrupted TYPE!\n");
            DOT_DUMP_TREE_BY_ELEM(original);
            PAUSE;
        }
    }

    return a_copy;
}


struct tree_node* node_add (struct tree_node* base, const int connection_case,
                            struct tree_node* new_, int line)
{
    char* function_name = "node_add";

    CHECK_CREATED (base);
    CHECK_CREATED (new_);

    //CHECK_NODE    (base);
    //CHECK_NODE    (new_);


    switch (connection_case)
    {
    case CASE_OF_LEFT:
        {
            base   -> left_branch = new_;
            new_   -> parent      = base;
        }break;

    case CASE_OF_RIGHT:
        {
            base   -> right_branch = new_;
            new_   -> parent       = base;
        }break;

    case CASE_OF_PARENT:
        {
            fprintf(stderr, "ERROR: No, you cannot add a parent. Kids don't make their\n"
                            "parents, live with it. (line %d)", line);
            PAUSE;
        }break;
    }

    CHECK_NODE (base);
    CHECK_NODE (new_);

    return new_;
}


struct tree_node* node_remove (struct tree_node* node, int line)
{
    char* function_name = "node_remove";

    CHECK_CREATED (node);
    CHECK_NODE    (node);
    NULL_CHECK    (node, CASE_OF_LEFT);
    NULL_CHECK    (node, CASE_OF_RIGHT);

    struct tree_node* parent = node -> parent;
    free (node);
    return parent;
}


int branch_check (struct tree_node* base, int line)
{
    char* function_name = "branch_check";

    CHECK_NODE (base);

    if (base -> left_branch )
        branch_check (base -> left_branch,  line);
    if (base -> right_branch )
        branch_check (base -> right_branch, line);

    return 0;
}


int branch_remove (struct tree_node* base, int line)
{
    char* function_name = "branch_remove";

    CHECK_NODE(base);
    CHECK_CREATED(base);
    if (base -> left_branch )
        branch_remove (base -> left_branch,  line);
    if (base -> right_branch )
        branch_remove (base -> right_branch, line);

    free (base);
    return 0;
}


#endif //TREE_H_INCLUDED
