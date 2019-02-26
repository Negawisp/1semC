#include <string.h>
#include <stdlib.h>

#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#endif //TREE_H_INCLUDED

#define CASE_OF_NO         'NUOU'
#define CASE_OF_YES        'YYAS'
#define CASE_OF_PARENT     'prnt'

#define MAX_DATA_LENGTH    256

#define SINGLE_TABULATION_LENGTH   4
#define SINGLE_TABULATION          "    "
#define MAX_BRANCH_LENGTH          100


#define PAUSE {int t = 0; scanf("%d", &t);}


#define DUMP_NODE( node )                                              \
{                                                                      \
    fprintf (stderr, " ~~~ Dump of node on address %x ~~ \n", node);   \
    fprintf (stderr, "  Data:             %s", node -> data);          \
    fprintf (stderr, "  Good canary:      %d", node -> good_canary);   \
    fprintf (stderr, "  Canary1:          %d", node -> canary1);       \
    fprintf (stderr, "  Canary2:          %d", node -> canary2);       \
    fprintf (stderr, "  Parent pointer:   %x", node -> parent);        \
    fprintf (stderr, "  No case pointer:  %x", node -> no_case);       \
    fprintf (stderr, "  Yes case pointer: %x", node -> yes_case);      \
    PAUSE;                                                             \
}


#define CHECK_CANARY( node )                                                                         \
{                                                                                                    \
    if ( node -> canary1 != node -> good_canary )                                                    \
    {                                                                                                \
        fprintf (stderr, "ERROR: Detected dead canary1 at function\n"                                \
                         "%s, line %d.", function_name, line);                                       \
    }                                                                                                \
    if ( node -> canary2 != node -> good_canary )                                                    \
    {                                                                                                \
        fprintf (stderr, "ERROR: Detected dead canary2 at function\n"                                \
                         "%s, line %d.", function_name, line);                                       \
    }                                                                                                \
    if ( ( node -> canary1 != node -> good_canary ) || ( node -> canary2 != node -> good_canary ) )  \
        DUMP_NODE ( node );                                                                          \
}


#define CHECK_CREATED( node )                                                 \
if (node == NULL)                                                             \
{                                                                             \
    fprintf (stderr, "ERROR: Function %s received NULL\n"                     \
                     "as a node argument on line %d.", function_name, line);  \
    PAUSE;                                                                    \
}


#define CHECK_NO_CASE( node )                                                          \
{                                                                                      \
    if ( node -> no_case )                                                             \
    {                                                                                  \
        if ( node -> no_case -> parent != node )                                       \
        {                                                                              \
            fprintf (stderr, "ERROR: Detected wrong connection with no_case\n"         \
                             "node at function %s on line %d.", function_name, line);  \
            DUMP_NODE ( node );                                                        \
        }                                                                              \
    }                                                                                  \
}


#define CHECK_YES_CASE( node )                                                         \
{                                                                                      \
    if ( node -> yes_case )                                                            \
    {                                                                                  \
        if ( node -> yes_case -> parent != node )                                      \
        {                                                                              \
            fprintf (stderr, "ERROR: Detected wrong connection with yes_case\n"        \
                             "node at function %s on line %d.", function_name, line);  \
            DUMP_NODE ( node );                                                        \
        }                                                                              \
    }                                                                                  \
}


#define CHECK_NODE( node )   \
CHECK_CANARY   (node);       \
CHECK_NO_CASE  (node);       \
CHECK_YES_CASE (node);



#define NULL_CHECK( node, case_ )                                                   \
switch (case_)                                                                      \
{                                                                                   \
case CASE_OF_NO:                                                                    \
    {                                                                               \
        if (node -> no_case != NULL)                                                   \
        {                                                                                \
            fprintf (stderr, "ERROR: Wrong interaction with \"no\" answer pointer\n"      \
                             "of node at function %s on line %d.", function_name, line);  \
            DUMP_NODE (node);                                                             \
        }                                                                                \
    } break;                                                                           \
                                                                                    \
case CASE_OF_YES:                                                                  \
    {                                                                               \
        if (node -> yes_case != NULL)                                                  \
        {                                                                                \
            fprintf (stderr, "ERROR: Wrong interaction with \"yes\" answer pointer\n"     \
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
    char*              data;

    struct tree_node*  parent;
    struct tree_node*  no_case;
    struct tree_node*  yes_case;

    int canary2;
};


struct tree_node* node_construct (char* data, int canary, int line)
{
    char* function_name = "node_construct";

    CHECK_CREATED(data);
    struct tree_node* node = calloc (1, sizeof (struct tree_node));
    CHECK_CREATED (node);

    node -> data        = data;
    node -> canary1     = canary;
    node -> canary2     = canary;
    node -> good_canary = canary;

    CHECK_CREATED (node);
    CHECK_NODE    (node);
    CHECK_CREATED (node -> data);
    return node;
};


struct tree_node* node_add (struct tree_node* base, const int answer_case,
                            struct tree_node* answer, int line)
{
    char* function_name = "node_add";

    CHECK_CREATED (base);
    NULL_CHECK    (base,   answer_case);
    if (answer == NULL)
        return NULL;

    CHECK_NODE    (base);
    CHECK_NODE    (answer);
    NULL_CHECK    (answer, CASE_OF_PARENT);


    switch (answer_case)
    {
    case CASE_OF_NO:
        {
            base   -> no_case = answer;
            answer -> parent  = base;
        }break;

    case CASE_OF_YES:
        {
            base   -> yes_case = answer;
            answer -> parent   = base;
        }break;

    case CASE_OF_PARENT:
        {
            fprintf(stderr, "ERROR: No, you cannot add a parent. Kids don't make their\n"
                            "parents, live with it. (line %d)", line);
            PAUSE;
        }break;
    }

    CHECK_NODE (base);
    CHECK_NODE (answer);

    return answer;
}


int node_remove (struct tree_node* node, int line)
{
    char* function_name = "node_remove";

    CHECK_CREATED (node);
    CHECK_NODE    (node);
    NULL_CHECK    (node, CASE_OF_NO);
    NULL_CHECK    (node, CASE_OF_YES);

    CHECK_CREATED (node -> data);
    free (node -> data);
    free (node);
    return 0;
}


int branch_check (struct tree_node* base, int line)
{
    char* function_name = "branch_check";

    CHECK_NODE (base);

    if (base -> no_case )
        branch_check (base -> no_case,  line);
    if (base -> yes_case)
        branch_check (base -> yes_case, line);

    return 0;
}


int branch_remove (struct tree_node* base, int line)
{
    char* function_name = "branch_remove";

    if (base -> no_case )
        branch_remove (base -> no_case,  line);
    if (base -> yes_case)
        branch_remove (base -> yes_case, line);

    free (base);
    return 0;
}


int dot_dump_tree (struct tree_node* node, FILE* outF, int line)
{
    char* function_name = "dot_dump_node";

    CHECK_CREATED (node);

    int canary_error = 0;
    if (node->canary1 != node->good_canary || node->canary2 != node->good_canary)
        canary_error = 1;

    int yes_error    = 0;
    if (node->yes_case)
        if (node->yes_case->parent != node)
            yes_error = 1;

    int no_error     = 0;
    if (node-> no_case)
        if (node-> no_case->parent != node)
            no_error = 1;


    fprintf (outF, "Node%x\n[shape = record, ", node);
    if (canary_error)
        fprintf (outF, "color = red, ");
    else
    {
        if (node->no_case == NULL)
            fprintf (outF, "color = green, ");
        else
            fprintf (outF, "color = black, ");
    }

    fprintf     (outF, " label = \"{");
    fprintf     (outF, " <adr> %x | DATA: %s | ", node, node->data);
    fprintf     (outF, " Canary1:   %d \\l",      node->canary1);
    fprintf     (outF, " Canary2:   %d \\l",      node->canary2);
    fprintf     (outF, " Should be: %d |",        node->good_canary);
    fprintf     (outF, " <yes> YES:  %x | <no> NO:  %x",   node->yes_case, node->no_case);
    fprintf     (outF, " | <prnt> Parent:  %x",            node->parent);
    fprintf     (outF, "}\"];\n");

    if (node->yes_case)
    {
        fprintf (outF, "Node%x : <yes> -> Node%x : <adr> ", node, node->yes_case);
    if (yes_error)
        fprintf (outF, "[color = red];\n");
    else
        fprintf (outF, "[color = green];\n");
    }

    if (node->no_case)
    {
        fprintf (outF, "Node%x : <no> -> Node%x : <adr> ", node, node->no_case);
    if (yes_error)
        fprintf (outF, "[color = red];\n");
    else
        fprintf (outF, "[color = blue];\n");
    }

    if (node->parent)
    {
        fprintf (outF, "Node%x : <prnt> -> Node%x : <adr> ", node, node->parent);
        fprintf (outF, "[color = gray];\n");
    }

    if (node->no_case)
        dot_dump_tree (node->no_case,  outF, line);
    if (node->yes_case)
        dot_dump_tree (node->yes_case, outF, line);

    return 0;
}


int dot_tree (struct tree_node* node, FILE* outF, int line)
{
    char* function_name = "dot_node";

    CHECK_CREATED (node);

    fprintf (outF, "Node%x\n[shape = record, ", node);
    if (node->no_case == NULL)
        fprintf (outF, "color = green, ");
    else
        fprintf (outF, "color = black, ");

    fprintf     (outF, " label = \"{");
    fprintf     (outF, " <adr> %s  | ",        node->data);

    fprintf     (outF, " <yes> YES | <no> NO",   node->yes_case, node->no_case);
    fprintf     (outF, "}\"];\n");

    if (node->yes_case)
    {
        fprintf (outF, "Node%x : <yes> -> Node%x : <adr> ", node, node->yes_case);
        fprintf (outF, "[color = green];\n");
    }

    if (node->no_case)
    {
        fprintf (outF, "Node%x : <no> -> Node%x : <adr> ", node, node->no_case);
        fprintf (outF, "[color = blue];\n");
    }


    if (node->no_case)
        dot_tree (node->no_case,  outF, line);
    if (node->yes_case)
        dot_tree (node->yes_case, outF, line);

    return 0;
}


#define DOT_DUMP_TREE_BY_ELEM( base_elem )                             \
{                                                                      \
    FILE* dmp = fopen("dmp.gv", "wb");                                 \
    fprintf (dmp, "digraph G {\n");                                    \
    dot_dump_tree (base_elem, dmp,  __LINE__);                         \
    fprintf (dmp, "\n}\n");                                            \
    fclose (dmp);                                                      \
    system ("xdot dmp.gv");                                            \
}

#define DOT_TREE_BY_ELEM( base_elem )                                  \
{                                                                      \
    FILE* dmp = fopen("dmp.gv", "wb");                                 \
    fprintf (dmp, "digraph G {\n");                                    \
    dot_tree (base_elem, dmp,  __LINE__);                              \
    fprintf (dmp, "\n}\n");                                            \
    fclose (dmp);                                                      \
    system ("xdot dmp.gv");                                            \
}


