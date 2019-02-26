//#define USE_MATH_DEFINES

#include <math.h>

#ifndef DIFFERENTIAL_H_INCLUDED
#define DIFFERENTIAL_H_INCLUDED


char* Math_Phrase    = NULL;
int   Phrase_Pointer = 0;
int   ARF            = 0;

#define NOW( ch )           (Math_Phrase[Phrase_Pointer] == ch)
#define CH                  Math_Phrase[Phrase_Pointer]
#define MOVE()              Phrase_Pointer ++;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define VAR_MAX_LEN     10
#define VAR_MAX_COUNT   10
#define EQUAL_DOUBLE( d1, d2 )  ( -0.000001 <= d1-d2 && d1-d2 <= 0.000001 )

struct Variable
{
    char _Name [VAR_MAX_LEN];
    double _Value;
};

struct Variable Var_Array [VAR_MAX_COUNT] = {};


int add_var (char* var_name)
{
    int i = 0;

    for (i = 0; i<VAR_MAX_COUNT; i++)
    {
        if (Var_Array[i]._Name[0] == '\0')
        {
            strcat (Var_Array[i]._Name, var_name);
            return i;
        }
        if (strcmp (Var_Array[i]._Name, var_name) == 0 )
            return i;
    }

    fprintf (stderr, "ERROR: overflow in number of variables:\n"
                     "Tried to make \"%s\" the No%d variable.\n", var_name, i);
    PAUSE;

    ARF = 1;
    return -1;
}

int get_var_number (char* var_name, int line)
{
    if (var_name == NULL)
    {
        fprintf (stderr, "ERROR: Function get_var_number received 'nullptr' instead of\n"
                         "pointer to a name. (Line %d)\n", line);
        PAUSE;
    }

    int i = 0;

    for (i = 0; i < VAR_MAX_COUNT; i++)
    {
        if (strcmp(Var_Array[i]._Name, var_name) == 0)
        {
            return i;
        }
    }

    fprintf (stderr, "ERROR: On line %d function get_var_number received as an argument\n"
                     "a variable name, not present in a function. (name = %s)\n\nFunction has such variables:\n\n", line, var_name);

    for (i = 0; i < VAR_MAX_COUNT; i++)
    {
        if (Var_Array[i]._Name[0] == '\0')
        {
            break;
        }
        fprintf (stderr, "Var No%d: --> %s", i+1, Var_Array[i]._Name);
    }

    //PAUSE;
    return -1;
}

struct tree_node* Get_Variable (int line)
{
    char* function_name = "Get Variable";
    char var_name [VAR_MAX_LEN] = "";

    skip_frase_spaces();

    int i = 0;
    while (('a' <= CH && CH <= 'z') ||
           ('A' <= CH && CH <= 'Z') ||
           ('0' <= CH && CH <= '9'))
    {
        var_name [i] = CH;
        MOVE();
        i++;
    }

    int var_number = add_var (var_name);

    struct tree_node* var_node = node_construct("0", 'lbrv', line);
    var_node->node_type = TYPE__VARIABLE;
    var_node->data      = var_number;

    CHECK_CREATED (var_node);
    CHECK_NODE    (var_node);
    return var_node;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Helping functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/




int get_yes_no ()
{
    char* answer = calloc (10, sizeof (char));
    do
    {
        printf ("yes/no: ");
        fgets  (answer, MAX_FUNCTION_NAME_LENGTH-1, stdin); answer [strlen (answer) - 1] = '\0';
    }while (strcasecmp (answer, "yes") && strcasecmp (answer, "no") && strcasecmp (answer, "y") && strcasecmp (answer, "n") && strcasecmp (answer, "da"));

    printf("\n");
    if (strcasecmp (answer, "yes") == 0 || strcasecmp (answer, "da") == 0 || strcasecmp (answer, "y") == 0)
    {
        free(answer);
        return 1;
    }
    if (strcasecmp (answer, "no")  == 0 || strcasecmp (answer, "n") == 0)
    {
        free(answer);
        return 0;
    }

    fprintf (stderr, "HOW DID WE GET HERE?? (In get_yes_no)\n");
    PAUSE;
    return -1;
}



char* get_tabulation (int indention, int line)
{
    char* function_name = "get_tabulation";

    int   current_tabulation_length  = indention * SINGLE_TABULATION_LENGTH;
    char* tabulation                 = calloc ( current_tabulation_length+1, sizeof (char));
    CHECK_CREATED (tabulation);

    int i = 0;
    for (i = 0; i < indention; i++)
        if (strcat (tabulation, SINGLE_TABULATION) == NULL)
        {
            fprintf (stderr, "Somehow skipped the MAX_BRANCH_LENGTH check\n"
                             "(At function %s on line %d.)\n"
                             "Last node:\n", function_name, line);
            PAUSE;
        }

    return tabulation;
}



char* rng_quote (int switcher)
{
    int q_number = rand() % 3;
    switch (switcher)
    {
    case '+':
        {
            switch (q_number)
            {
            case 0:
                return "Let's add";
            case 1:
                return "Sample text";
            case 2:
                return "EZ";
            }
        }
    case '-':
        {
            switch (q_number)
            {
            case 0:
                return "Let's make a take off";
            case 1:
                return "Subtracting";
            case 2:
                return "Like this here:";
            }
        }
    case '*':
        {
            switch (q_number)
            {
            case 0:
                return "Let's multiply";
            case 1:
                return "Mult it boyyyy!";
            case 2:
                return "Can multiply here:";
            }
        }
    case '/':
        {
            switch (q_number)
            {
            case 0:
                return "Can divide here:";
            case 1:
                return "Dividing";
            case 2:
                return "SAMPLE TEXT";
            }
        }
    case 'log':
        {
            switch (q_number)
            {
            case 0:
                return "This log is const:";
            case 1:
                return "Taking logarithm";
            case 2:
                return "Let's take logarithm";
            }
        }
    case '^':
        {
            switch (q_number)
            {
            case 0:
                return "This power is constant:";
            case 1:
                return "Powering";
            case 2:
                return "Let's make it to a better look:";
            }
        }
    case 'sin':
        {
            switch (q_number)
            {
            case 0:
                return "Sine can be simplified:";
            case 1:
                return "This sine is a constant:";
            case 2:
                return "Taking sine:";
            }
        }
    case 'cos':
        {
            switch (q_number)
            {
            case 0:
                return "Taking cosine";
            case 1:
                return "Constant cosine";
            case 2:
                return "Dat COS";
            }
        }
    case 'tg':
        {
            switch (q_number)
            {
            case 0:
                return "TG can be simplified";
            case 1:
                return "Let's count this tangent";
            case 2:
                return "EZ to count:";
            }
        }
    case 'ctg':
        {
            switch (q_number)
            {
            case 0:
                return "Constant cotangent";
            case 1:
                return "Cotaaaangetnf";
            case 2:
                return "Counting cotangent";
            }
        }
    case 'asin':
        {
            switch (q_number)
            {
            case 0:
                return "Arcsine here";
            case 1:
                return "Do ypu think i can't count this Asine?? Who do you think I am!?";
            case 2:
                return "Let's find an angle which will give this sine:";
            }
        }
    case 'acos':
        {
            switch (q_number)
            {
            case 0:
                return "WHO DO YOU THINK I AM?! I will SMASH this cosine!";
            case 1:
                return "Cosine is EZ";
            case 2:
                return "This cosine is const, don't you see?";
            }
        }
    case 'atg':
        {
            switch (q_number)
            {
            case 0:
                return "Yep, an arctangent";
            case 1:
                return "This is also a constant asked to be simplified";
            case 2:
                return "This is actually that";
            }
        }
    case 'actg':
        {
            switch (q_number)
            {
            case 0:
                return "Arccotangent <- this is long word tho";
            case 1:
                return "Simmmplifing";
            case 2:
                return "Constant arccotangent:";
            }
        }
    case 'sh':
        {
            switch (q_number)
            {
            case 0:
                return "Sinh AKA shine ~~";
            case 1:
                return "Shinus, as Russians call it.";
            case 2:
                return "Constant hyperbolic sine:";
            }
        }
    case 'ch':
        {
            switch (q_number)
            {
            case 0:
                return "CH is for \"cho za HHHyperbolic cosine?\"";
            case 1:
                return "Constant chosinus";
            case 2:
                return "Look, hyperbolic cosine here:";
            }
        }
    case 'th':
        {
            switch (q_number)
            {
            case 0:
                return "Hyperbolic tangent constant:";
            case 1:
                return "tHangent?";
            case 2:
                return "(Achievement get: use of TH)";
            }
        }
    case 'cth':
        {
            switch (q_number)
            {
            case 0:
                return "Oh, my lovely hyperbolic cotangent!";
            case 1:
                return "Sample text";
            case 2:
                return "Sample text";
            }
        }

    case '=':
        {
            switch (q_number)
            {
            case 0:
                return "Should be no trouble to see";
            case 1:
                return "But look at that!";
            case 2:
                return "Simplifies a lot:";
            }
        }

    }
    assert (0);
    return "Undefined error";
}


/*         ~~~~~~~~~~~~~~~~    Differential functions    ~~~~~~~~~~~~~~~~~~        */

int save_as_tree (FILE* output, struct tree_node* base, int indention, int line)
{
    char* function_name = "save_as_tree";

    if (indention >= MAX_BRANCH_LENGTH)
    {
        fprintf(stderr, "Too long branch :(\n"
                        "(In function %s, line %d.)\n"
                        "Last node:\n", function_name, line);
        DUMP_NODE (base);
    }

    CHECK_CREATED (base);
    CHECK_NODE    (base);

    char* tabulation = get_tabulation(indention, line);
    fprintf (output, "%s(",     tabulation);

    switch (base->node_type)
    {
    case TYPE__FUNCTION:
        {
#define DEF_FUNC( name, num, diff_code )                     \
if ( 0.001 > base->data - num && base->data - num > -0.001)  \
{                                                            \
    fprintf (output, "'%s'\n", name);                        \
} else

#include "functions_list.h"

#undef DEF_FUNC
        {
            fprintf (stderr, "ERROR: Node of \"Function\" type contained \"%lf\" as data.\n\n", base->data);
            DUMP_NODE( base );

            PAUSE;
        }

        }break;

    case TYPE__VARIABLE:
        {
            fprintf (output, "'%c'\n", *(char*)&base->data);
        }break;

    case TYPE__CONSTANT:
        {
            fprintf (output, "'%lf'\n", base -> data);
        }
    }


    if (base -> left_branch )
        save_as_tree (output, base -> left_branch,  indention+1, line);
    if (base -> right_branch)
        save_as_tree (output, base -> right_branch, indention+1, line);


    fprintf (output, "%s)\n",       tabulation);
    free (tabulation);
    return 0;
}



int skip_separators (FILE* file)
{
    char c = 0;

    do
    {
        c = fgetc (file);
    }
    while (isspace(c) || c == '(');

    if (c == EOF)
        return 1;

    return 0;
}

#define LOAD_ERROR_FOUND( text )                                                   \
{                                                                                  \
    fprintf (stderr, "%s \n"                                                       \
                    "(Function %s, line %d)", text, function_name, line);          \
    fclose(input);                                                                 \
    PAUSE;                                                                         \
}

struct tree_node* load_from_tree (FILE* input, int line)
{
    char* function_name = "load_equation";
    CHECK_CREATED (input);


    if (skip_separators (input))
    {
        LOAD_ERROR_FOUND ("ERROR: Dismatching numbers of functions and arguments.");
        PAUSE;
    }


    char this_data [MAX_FUNCTION_NAME_LENGTH] = "";
    //fscanf (input, "%[\"']\"", this_data);
    fscanf (input, "%[^'\"]", this_data);
    fscanf (input, "%*c");

    struct tree_node* this_node = node_construct(this_data, 'usrD', line);
    CHECK_CREATED(this_node);

    if (this_node->node_type == TYPE__FUNCTION)
    {
        node_add (this_node, CASE_OF_LEFT, load_from_tree (input, line), line);
        if (this_node -> left_branch == NULL)
        {
            fprintf (stderr, "ERROR: Function \"%s\" on in input file\n"
                             "had not got LEFT(first) argument.\n", this_data);
            PAUSE;
        }

        node_add(this_node, CASE_OF_RIGHT, load_from_tree (input, line), line);
        if (this_node -> right_branch == NULL)
        {
            fprintf (stderr, "ERROR: Function \"%s\" on in input file\n"
                             "had not got RIGHT(second) argument.\n", this_data);
            PAUSE;
        }
    }

    else
    {
        this_node -> left_branch  = NULL;
        this_node -> right_branch = NULL;
    }


    CHECK_NODE(this_node);
    return this_node;
}
#undef LOAD_ERROR_FOUND




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                           Operators: +, -, *, /, sin, ...                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct tree_node* OpPlus (struct tree_node* node1, struct tree_node* node2)
{
    char* function_name = "operator plus";
    int line = 71105;

    CHECK_CREATED( node1 );
    CHECK_NODE   ( node1 );

    CHECK_CREATED( node2 );
    CHECK_NODE   ( node2 );

    struct tree_node* PLUS = node_construct("+", 'sulp', line);

    node_add (PLUS, CASE_OF_LEFT,  node1->adress, line);
    node_add (PLUS, CASE_OF_RIGHT, node2->adress, line);

    CHECK_NODE (PLUS);

    return PLUS;
};


struct tree_node* OpMinus (struct tree_node* node1, struct tree_node* node2)
{
    char* function_name = "operator minus";
    int line = 77717105;

    CHECK_CREATED( node1 );
    CHECK_NODE   ( node1 );

    CHECK_CREATED( node2 );
    CHECK_NODE   ( node2 );

    struct tree_node* MINUS = node_construct("-", 'snim', line);

    node_add (MINUS, CASE_OF_LEFT,  node1->adress, line);
    node_add (MINUS, CASE_OF_RIGHT, node2->adress, line);

    CHECK_NODE (MINUS);

    return MINUS;
};


struct tree_node* OpMult (struct tree_node* node1, struct tree_node* node2)
{
    char* function_name = "operator mult";
    int line = 7771017;

    CHECK_CREATED( node1 );
    CHECK_NODE   ( node1 );
    CHECK_CREATED( node2 );
    CHECK_NODE   ( node2 );

    struct tree_node* MULT = node_construct("*", 'tlum', line);
    node_add (MULT, CASE_OF_LEFT,  node1->adress, line);
    node_add (MULT, CASE_OF_RIGHT, node2->adress, line);
    CHECK_NODE (MULT);
    return MULT;
};


struct tree_node* OpDiv (struct tree_node* node1, struct tree_node* node2)
{
    char* function_name = "operator div";
    int line = 917193;

    CHECK_CREATED( node1 );
    CHECK_NODE   ( node1 );

    CHECK_CREATED( node2 );
    CHECK_NODE   ( node2 );

    struct tree_node* DIV = node_construct("/", 'dvid', line);

    node_add (DIV, CASE_OF_LEFT,  node1->adress, line);
    node_add (DIV, CASE_OF_RIGHT, node2->adress, line);

    CHECK_NODE (DIV);

    return DIV;
};



struct tree_node* OpDeg (struct tree_node* node1, struct tree_node* node2)
{
    char* function_name = "operator deg";
    int line = 939733;

    CHECK_CREATED (node1);
    CHECK_NODE    (node1);

    CHECK_CREATED (node2);
    CHECK_NODE    (node2);

    struct tree_node* DEG = node_construct("^", 'rged', line);

    node_add (DEG, CASE_OF_LEFT,  node1->adress, line);
    node_add (DEG, CASE_OF_RIGHT, node2->adress, line);

    CHECK_NODE (DEG);

    return DEG;
};

struct tree_node* OpLog (struct tree_node* node1, struct tree_node* node2)
{
    char* function_name = "operator log";
    int line = 109;

    CHECK_CREATED (node1);
    CHECK_NODE    (node1);

    CHECK_CREATED (node2);
    CHECK_NODE    (node2);

    struct tree_node* LOG = node_construct("log", 'gol', line);

    node_add (LOG, CASE_OF_LEFT,  node1->adress, line);
    node_add (LOG, CASE_OF_RIGHT, node2->adress, line);

    CHECK_NODE (LOG);

    return LOG;
};



struct tree_node* OpSin (struct tree_node* node)
{
    char* function_name = "operator sin";
    int line = 517;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* SIN = node_construct("sin", 'nis', line);

    node_add (SIN, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (SIN);

    return SIN;
};

struct tree_node* OpCos (struct tree_node* node)
{
    char* function_name = "operator cos";
    int line = 605;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* COS = node_construct("cos", 'soc', line);

    node_add (COS, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (COS);

    return COS;
};


struct tree_node* OpTg (struct tree_node* node)
{
    char* function_name = "operator tg";
    int line = 79;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* TG = node_construct("tg", 'gt', line);

    node_add (TG, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (TG);

    return TG;
};


struct tree_node* OpCtg (struct tree_node* node)
{
    char* function_name = "operator ctg";
    int line = 679;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* CTG = node_construct("ctg", 'gtc', line);

    node_add (CTG, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (CTG);

    return CTG;
};

struct tree_node* OpArcsin (struct tree_node* node)
{
    char* function_name = "operator arcsin";
    int line = 476517;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* ARCSIN = node_construct("arcsin", 'nisa', line);

    node_add (ARCSIN, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (ARCSIN);

    return ARCSIN;
};

struct tree_node* OpArccos (struct tree_node* node)
{
    char* function_name = "operator arccos";
    int line = 476605;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* ARCCOS = node_construct("arccos", 'soca', line);

    node_add (ARCCOS, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (ARCCOS);

    return ARCCOS;
};

struct tree_node* OpArctg (struct tree_node* node)
{
    char* function_name = "operator arctg";
    int line = 47679;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* ARCTG = node_construct("arctg", 'gta', line);

    node_add (ARCTG, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (ARCTG);

    return ARCTG;
};

struct tree_node* OpArcctg (struct tree_node* node)
{
    char* function_name = "operator arcctg";
    int line = 476679;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* ARCCTG = node_construct("arcctg", 'gtca', line);

    node_add (ARCCTG, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (ARCCTG);

    return ARCCTG;
};

struct tree_node* OpSh (struct tree_node* node)
{
    char* function_name = "operator sh";
    int line = 5417;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* SH = node_construct("sh", 'hs', line);

    node_add (SH, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (SH);

    return SH;
};

struct tree_node* OpCh (struct tree_node* node)
{
    char* function_name = "operator ch";
    int line = 6405;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* Ch = node_construct("ch", 'hc', line);

    node_add (Ch, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (Ch);

    return Ch;
};

struct tree_node* OpTh (struct tree_node* node)
{
    char* function_name = "operator th";
    int line = 7447;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* Th = node_construct("th", 'ht', line);

    node_add (Th, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (Th);

    return Th;
};

struct tree_node* OpCth (struct tree_node* node)
{
    char* function_name = "operator cth";
    int line = 67447;

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    struct tree_node* Cth = node_construct("cth", 'htc', line);

    node_add (Cth, CASE_OF_LEFT, node->adress, line);

    CHECK_NODE (Cth);

    return Cth;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int skip (char* str_to_cmp)
{
    int str_length = strlen(str_to_cmp);
    int i = 0;

    for (i = 0; i < str_length; i++)
        if (CH == str_to_cmp[i])
        {
            MOVE();
        }
        else
        {
            return i;
        }

    return -1;
}

int skip_frase_spaces ()
{
    while (NOW (' ') || NOW ('\n') || NOW ('\t') || NOW ('\r') )
        MOVE ();

    if (NOW (EOF))
        return 1;
    return 0;
}




struct tree_node* Get_Polynom (int line);

struct tree_node* Get_Atom (int line)
{
    char* function_name = "Get atom";

    skip_frase_spaces();

    struct tree_node* ret_node = NULL;

    if (NOW('('))
    {
        MOVE();
        ret_node = Get_Polynom(line);

        CHECK_CREATED(ret_node);
        CHECK_NODE   (ret_node);

        skip_frase_spaces();

        if (!NOW(')'))
        {
            fprintf (stderr, "ERROR!! Closing bracket required at symbol No %d.\n"
                             "Line %d\n", Phrase_Pointer, line);
            PAUSE;
        }

        MOVE();
        return ret_node;
    }

#define RETURN_OPER( oper )                 \
    skip_frase_spaces();                    \
    ret_node = Op##oper (Get_Atom(line));   \
    CHECK_CREATED(ret_node);                \
    CHECK_NODE   (ret_node);                \
    return ret_node;


    switch (CH)
    {
    case 's':
        {
            MOVE();
            if (NOW ('i'))
            {
                int moved = skip("in");
                if (moved != -1)
                {
                    Phrase_Pointer -= moved + 1;
                    break;
                }
                RETURN_OPER (Sin);
            }

            if (NOW ('h'))
            {
                MOVE();
                if (isalpha (CH))
                {
                    Phrase_Pointer -= 2;
                    break;
                }
                RETURN_OPER (Sh);
            }

            fprintf(stderr, "ERROR: Function started with 's', but continued with '%c'\n"
                            "(Char number %d)\n", CH, Phrase_Pointer);
            PAUSE;
        }

    case 'c':
        {
            MOVE();

            switch (CH)
            {
            case 'o':
                {
                    skip ("os");
                    RETURN_OPER (Cos);
                } break;

            case 't':
                {
                    MOVE();

                    if (NOW('g'))
                    {
                        MOVE();
                        RETURN_OPER (Ctg);
                    }

                    if (NOW('h'))
                    {
                        MOVE();
                        RETURN_OPER (Cth);
                    }

                    fprintf(stderr, "ERROR: Function started with 'ct', but continued with '%c'\n"
                                    "(Char number %d)\n", CH, Phrase_Pointer);
                    PAUSE;
                } break;

            case 'h':
                {
                    MOVE();
                    RETURN_OPER (Ch);
                } break;

            default:
                {
                    fprintf(stderr, "ERROR: Function started with 'c', but continued with '%c'\n"
                                    "(Char number %d)\n", CH, Phrase_Pointer);
                    PAUSE;
                }
            }
        } break;

    case 't':
        {
            MOVE();

            if (NOW ('g'))
            {
                MOVE();
                RETURN_OPER (Tg);
            }

            if (NOW ('h'))
            {
                MOVE();
                RETURN_OPER (Th);
            }

            fprintf(stderr, "ERROR: Function started with 't', but continued with '%c'\n"
                            "(Char number %d)\n", CH, Phrase_Pointer);
            PAUSE;
        } break;

    case 'a':
        {
            skip ("arc");

            switch (CH)
            {
            case 's':
                {
                    skip ("sin");
                    RETURN_OPER (Arcsin);
                } break;

            case 'c':
                {
                    MOVE();

                    if (NOW ('o'))
                    {
                        skip ("os");

                        skip_frase_spaces();
                        RETURN_OPER (Arccos);
                    }

                    if (NOW ('t'))
                    {
                        skip ("tg");
                        RETURN_OPER (Arcctg);
                    }


                    fprintf(stderr, "ERROR: Function started with 'arcc', but continued with '%c'\n"
                                    "(Char number %d)\n", CH, Phrase_Pointer);
                    PAUSE;
                } break;

            case 't':
                {
                    skip ("tg");
                    RETURN_OPER (Arctg);
                } break;

            default:
                {
                    fprintf(stderr, "ERROR: Function started with 'arc', but continued with '%c'\n"
                                    "(Char number %d)\n", CH, Phrase_Pointer);
                    PAUSE;
                }
            }
        }
        break;

    case 'l':
        {
            skip("log");
            skip_frase_spaces();

            if (!NOW('('))
            {
                fprintf(stderr, "ERROR: Function \"log\" required '(' but met '%c'\n"
                                "(Char number %d)\n", CH, Phrase_Pointer);
                PAUSE;
            }
            MOVE();

            struct tree_node* log_arg  = Get_Polynom(line);
            CHECK_CREATED (log_arg);
            CHECK_NODE    (log_arg);

            skip_frase_spaces();
            if (!NOW(','))
            {
                fprintf(stderr, "ERROR: Function \"log\" required ',' but met '%c'\n"
                                "(Char number %d)\n", CH, Phrase_Pointer);
                PAUSE;
            }
            MOVE();

            struct tree_node* log_base = Get_Polynom(line);
            CHECK_CREATED (log_base);
            CHECK_NODE    (log_base);

            skip_frase_spaces();

            if (!NOW(')'))
            {
                fprintf(stderr, "ERROR: Function \"log\" required ')' but met '%c'\n"
                                "(Char number %d)\n", CH, Phrase_Pointer);
                PAUSE;
            }
            MOVE();

            skip_frase_spaces();
            struct tree_node* log_itself = OpLog(log_arg, log_base);
            CHECK_CREATED (log_itself);
            CHECK_NODE    (log_itself);
            return log_itself;
        } break;


    case 'p':
        {
            skip("pow");
            skip_frase_spaces();

            if (!NOW('('))
            {
                fprintf(stderr, "ERROR: Function \"pow\" required '(' but met '%c'\n"
                                "(Char number %d)\n", CH, Phrase_Pointer);
                PAUSE;
            }
            MOVE();

            struct tree_node* pow_base  = Get_Polynom(line);
            CHECK_CREATED (pow_base);
            CHECK_NODE    (pow_base);

            skip_frase_spaces();
            if (!NOW(','))
            {
                fprintf(stderr, "ERROR: Function \"pow\" required ',' but met '%c'\n"
                                "(Char number %d)\n", CH, Phrase_Pointer);
                PAUSE;
            }
            MOVE();

            struct tree_node* power = Get_Polynom(line);
            CHECK_CREATED (power);
            CHECK_NODE    (power);

            skip_frase_spaces();

            if (!NOW(')'))
            {
                fprintf(stderr, "ERROR: Function \"log\" required ')' but met '%c'\n"
                                "(Char number %d)\n", CH, Phrase_Pointer);
                PAUSE;
            }
            MOVE();

            skip_frase_spaces();
            struct tree_node* pow_itself = OpDeg(pow_base, power);
            CHECK_CREATED (pow_itself);
            CHECK_NODE    (pow_itself);
            return pow_itself;
        } break;

    case 'P':
        {
            skip ("Pi");
            skip_frase_spaces();
            return node_construct("3.1415926536", 'IP', line);
        }

    case 'e':
        {
            MOVE();
            skip_frase_spaces();
            return node_construct("2.7182818285", 'e', line);
        }

    default:
        {
        }

#undef RETURN_OPER

    }


    double numeric = 0;

    if (CH < '0' || '9' < CH)
    {
        return Get_Variable(line);
    }

    do
    {
        numeric = numeric * 10 + CH - '0';
        MOVE();
    }
    while ('0' <= CH && CH <= '9');

    if (!NOW('.'))
    {
        ret_node = node_construct("0", 'mun', line);
        ret_node -> data = numeric;
        return ret_node;
    }


    MOVE();
    int signs_aft_pnt = 1;

    if (CH < '0' || '9' < CH)
    {
        fprintf (stderr, "ERROR: Numbers after point required.\n"
                         "   (Line %d, char No%d in phrase: %c, Function %s.)", line, Phrase_Pointer, CH, function_name);
        PAUSE;
    }

    do
    {
        numeric = numeric + (CH - '0')/exp(signs_aft_pnt*log(10));
        MOVE();
    }
    while ('0' <= CH && CH <= '9');


    ret_node = node_construct("0", 'mun', line);
    ret_node -> data = numeric;
    return ret_node;
};


struct tree_node* Get_Deg (int line)
{
    char* function_name = "Get degree";

    if (skip_frase_spaces())
    {
        fprintf (stderr, "ERROR: The phrase ended where a monomial was awaited.\n"
                         "   (Line %d)", line);
        PAUSE;
    }

    struct tree_node* ret_node = Get_Atom (line);

    if (NOW ('^'))
    {
        MOVE();
        if (skip_frase_spaces())
        {
            fprintf (stderr, "ERROR: The phrase ended where a POWER was awaited.\n"
                             "   (Line %d)", line);
            PAUSE;
        }

        ret_node = OpDeg(ret_node, Get_Deg (line));
    }

    skip_frase_spaces();
    CHECK_NODE(ret_node);
    return ret_node;
}



struct tree_node* Get_Monom (int line)
{
    char* function_name = "Get monomial";

    if (skip_frase_spaces())
    {
        fprintf (stderr, "ERROR: The phrase ended where a monomial was awaited.\n"
                         "   (Line %d)", line);
        PAUSE;
    }

    struct tree_node* ret_node = Get_Deg (line);

    while (NOW ('*') || NOW ('/'))
    {
        if (NOW ('*'))
        {
            MOVE();
            skip_frase_spaces();

            ret_node = OpMult (ret_node, Get_Monom (line));
        }
        else
        {
            MOVE();
            skip_frase_spaces();

            ret_node = OpDiv (ret_node, Get_Monom (line));
        }
        skip_frase_spaces();
    }

    CHECK_NODE(ret_node);
    return ret_node;
}

struct tree_node* Get_Polynom (int line)
{
    char* function_name = "Get polynomial";

    if (skip_frase_spaces())
    {
        fprintf (stderr, "ERROR: The phrase ended where a polynomial was awaited.\n"
                         "   (Line %d)", line);
        PAUSE;
    }

    struct tree_node* ret_node = Get_Monom (line);
    skip_frase_spaces();

    while (NOW ('+') || NOW ('-'))
    {
        if (NOW ('+'))
        {
            MOVE();
            skip_frase_spaces();

            ret_node = OpPlus(ret_node, Get_Polynom (line));
        }
        else
        {
            MOVE();
            skip_frase_spaces();

            ret_node = OpMinus(ret_node, Get_Polynom (line));
        }
        skip_frase_spaces();
    }

    CHECK_NODE (ret_node);
    return ret_node;
}


struct tree_node* load_from_phrase (char* phrase, int line)
{
    if (Math_Phrase != NULL)
        free (Math_Phrase);
    Math_Phrase = phrase;
    Phrase_Pointer = 0;

    return Get_Polynom (line);
}




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                         /*   ~~~      THE SIMPLIFIER    ~~~  */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int branches_equal (struct tree_node* node1, struct tree_node* node2)
{
    char* function_name = "branches_equal";
    int line = 3941;

    if (node1 == NULL)
        if (node2 == NULL)
            return 1;
        else return 0;
    else
        if (node2 == NULL)
            return 0;

    CHECK_NODE(node1);
    CHECK_NODE(node2);

    if (!(node1->data == node2->data && node1->node_type == node2->node_type))
        return 0;

    else
    {
        int result1 = branches_equal(node1->left_branch, node2->left_branch);
        int result2 = branches_equal(node1->right_branch, node2->right_branch);

        return result1 && result2;
    }
}


int change_var_to_const (struct tree_node* node, int var_num, double value)
{
    char* function_name = "change_var_to_const";
    int line = 101010;
    CHECK_CREATED(node);
    CHECK_NODE(node);

    //fprintf(stderr, "\n\nThis node entered function:");
    //DUMP_NODE(node);
    if (node->node_type == TYPE__VARIABLE && EQUAL_DOUBLE(node->data, var_num))
    {
        node->node_type = TYPE__CONSTANT;
        node->data = value;
        //fprintf (stderr, "\n\nGIVING VALUE %lf", value);
        //fprintf (stderr, "Now node has value of %lf", node->data);
        CHECK_NODE(node);
        return 0;
    }
    CHECK_NODE(node);
    return 0;
}

int is_var (struct tree_node* node, int var_num, double not_used_value)
{
    if (node->node_type == TYPE__VARIABLE && EQUAL_DOUBLE(node->data, var_num))
        return 1;
    else
        return 0;
}


int runner (struct tree_node* node, int var_num, int line, double d_value, int ( * func ) (struct tree_node*, int var_num, double value))
{
    char* function_name = "runner";

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    int func_ret = func (node, var_num, d_value);
    if (func_ret)
        return func_ret;

    if (node->left_branch)
    {
        func_ret = runner (node->left_branch,  var_num, line, d_value, func);
        if (func_ret)
            return func_ret;
    }

    if (node->right_branch)
    {
        func_ret = runner (node->right_branch, var_num, line, d_value, func);
        if (func_ret)
            return func_ret;
    }

    CHECK_NODE (node);
    return 0;
}

#define IS_NODE( noda, numb )   (noda->node_type == TYPE__CONSTANT && EQUAL_DOUBLE (noda->data, numb))
#define CHECK_ARF()             if (ARF != 0) return node;

#define MIN_ONE_NODE node_construct("-1", 'mun', line )

struct tree_node* simplify_const (struct tree_node* node, int* changed_flag, FILE* tex, int line)
{
    char* function_name = "simplify const";

    CHECK_CREATED (node);
    CHECK_NODE    (node);

    if (node->node_type != TYPE__FUNCTION)
        return node;

    node_add (node, CASE_OF_LEFT,  simplify_const (node-> left_branch,  changed_flag, tex, line), line);
        CHECK_ARF();

    if (node->right_branch != NULL)
    {
        node_add (node, CASE_OF_RIGHT, simplify_const (node-> right_branch, changed_flag, tex, line), line);
            CHECK_ARF();
    }

    int node_data = node->data;
    switch (node_data)
    {

#define RET_OPER_BRANCH( OPERATOR, op_cnst )                                                                     \
    {                                                                                                            \
        if (node->left_branch->node_type == TYPE__CONSTANT && node->right_branch->node_type == TYPE__CONSTANT)   \
        {                                                                                                        \
        fprintf  (tex, "%s\n", rng_quote (op_cnst));                                                             \
        fprintf (tex, "\\begin{equation}\n");                                                                    \
        tex_branch(node, tex, line);                                                                             \
            node->node_type = TYPE__CONSTANT;                                                                    \
            node->data = node->left_branch->data OPERATOR node->right_branch->data;                              \
            branch_remove (node-> left_branch, line);                                                            \
            branch_remove (node->right_branch, line);                                                            \
                                                                                                                 \
            node-> left_branch = NULL;                                                                           \
            node->right_branch = NULL;                                                                           \
            *changed_flag = 1;                                                                                   \
        fprintf (tex, "=");                                                                                      \
        tex_branch(node, tex, line);                                                                             \
        fprintf (tex, "\n\\end{equation}\n");                                                                    \
            return node;                                                                                         \
        }                                                                                                        \
    } break;
    case 1:   //PLUS
        RET_OPER_BRANCH (+, '+');
    case 2:   //MINUS
        RET_OPER_BRANCH (-, '-');
    case 3:   //DIVIDE
        {
            if (IS_NODE (node->right_branch, 0))
            {
                ARF = 1;
                fprintf  (tex,  "Can't divide by zero!\n");
                return node;
            }
            RET_OPER_BRANCH (/, '/');
        }
    case 4:   //MULTIPLY
        {
            if (node->left_branch->node_type == TYPE__CONSTANT && node->right_branch->node_type == TYPE__CONSTANT)
            {
            fprintf  (tex, "%s\n", rng_quote ('*'));
            fprintf (tex, "\\begin{equation}\n");
            tex_branch(node, tex, line);
                node->node_type = TYPE__CONSTANT;
                node->data = node->left_branch->data * node->right_branch->data;
                branch_remove (node-> left_branch, line);
                branch_remove (node->right_branch, line);

                node-> left_branch = NULL;
                node->right_branch = NULL;
                *changed_flag = 1;
            fprintf (tex, "=");
            tex_branch(node, tex, line);
            fprintf (tex, "\n\\end{equation}\n");
                return node;
            }
        } break;
    case 5:  //power
        {
            if (IS_NODE (node->left_branch, 0) && IS_NODE (node->right_branch, 0))
            {
                ARF = 1;
                fprintf  (tex,  "Expression has no sense:\n"
                                "\\begin{equation}\n0^{0}\n\\end{equation}\n");
                return node;
            }

            if (node->left_branch->node_type == TYPE__CONSTANT && node->right_branch->node_type == TYPE__CONSTANT)
            {
        fprintf  (tex, "%s\n", rng_quote ('^'));
        fprintf (tex, "\\begin{equation}\n");
        tex_branch(node, tex, line);
                node->node_type = TYPE__CONSTANT;
                node->data = exp (node->right_branch->data * log(node->left_branch->data));
                branch_remove (node-> left_branch, line);
                branch_remove (node->right_branch, line);

                node-> left_branch = NULL;
                node->right_branch = NULL;
                *changed_flag = 1;
        fprintf (tex, "=");
        tex_branch(node, tex, line);
        fprintf (tex, "\n\\end{equation}\n");
                return node;
            }
        }
    case 18:  //log
        {
            if (node->left_branch->node_type == TYPE__CONSTANT && node->right_branch->node_type == TYPE__CONSTANT)
            {
        fprintf  (tex, "%s\n", rng_quote ('log'));
        fprintf (tex, "\\begin{equation}\n");
        tex_branch(node, tex, line);
                node->node_type = TYPE__CONSTANT;
                node->data = log (node->left_branch->data) / log (node->right_branch->data);
                branch_remove (node-> left_branch, line);
                branch_remove (node->right_branch, line);

                node-> left_branch = NULL;
                node->right_branch = NULL;
                *changed_flag = 1;
        fprintf (tex, "=");
        tex_branch(node, tex, line);
        fprintf (tex, "\n\\end{equation}\n");
                return node;
            }
        }break;
#undef RET_OPER_BRANCH

#define RET_COUNTED_CONST( func, op_cnst )               \
    if (node->left_branch->node_type == TYPE__CONSTANT)  \
    {                                                    \
    fprintf (tex, "%s\n", rng_quote (op_cnst));          \
    fprintf (tex, "\\begin{equation}\n");                \
    tex_branch(node, tex, line);                         \
        node->node_type = TYPE__CONSTANT;                \
        node->data = func (node->left_branch->data);     \
        branch_remove (node-> left_branch, line);        \
                                                         \
        node-> left_branch = NULL;                       \
        node->right_branch = NULL;                       \
        *changed_flag = 1;                               \
    fprintf (tex, "=");                                  \
    tex_branch(node, tex, line);                         \
    fprintf (tex, "\n\\end{equation}\n");                \
    return node;                                         \
    } break;
    case 6:  //sin
        RET_COUNTED_CONST (sin, 'sin');
    case 7:  //cos
        RET_COUNTED_CONST (cos, 'cos');
    case 8:  //tan
        RET_COUNTED_CONST (tan, 'tg');
    case 9:  //cotan
        RET_COUNTED_CONST (1 / tan, 'ctg');
    case 10:  //asin
        RET_COUNTED_CONST (asin, 'asin');
    case 11:  //acos
        RET_COUNTED_CONST (acos, 'acos');
    case 12:  //atan
        RET_COUNTED_CONST (atan, 'atg');
    case 13:  //acotan
        RET_COUNTED_CONST (3.141593 / 2 - atan, 'actg');
    case 14:  //sinh
        RET_COUNTED_CONST (sinh, 'sh');
    case 15:  //cosh
        RET_COUNTED_CONST (cosh, 'ch');
    case 16:  //tanh
        RET_COUNTED_CONST (tanh, 'th');
    case 17:  //cosh
        RET_COUNTED_CONST (1 / tanh, 'cth');
#undef RET_COUNTED_CONST
    }

    return node;
}

#define RET_ONLY( branch )                           \
    fprintf (tex, "%s\n", rng_quote ('='));          \
    fprintf (tex, "\\begin{equation}\n");            \
    tex_branch(node, tex, line);                     \
        struct tree_node* ret_node = node-> branch;  \
        node-> branch = NULL;                        \
        branch_remove (node, line);                  \
    fprintf (tex, "=");                              \
    tex_branch(ret_node, tex, line);                 \
    fprintf (tex, "\n\\end{equation}\n");            \
        ret_node -> parent = NULL;                   \
        *changed_flag = 1;                           \
        CHECK_NODE (ret_node);                       \
        return ret_node;

#define RET_ZERO                                  \
    fprintf (tex, "%s\n", rng_quote ('='));       \
    fprintf (tex, "\\begin{equation}\n");         \
    tex_branch(node, tex, line);                  \
        branch_remove (node, line);               \
        *changed_flag = 1;                        \
    fprintf (tex, "=0");                          \
    fprintf (tex, "\n\\end{equation}\n");         \
        return node_construct("0", 'OREZ', line);

#define RET_ONE                                   \
    fprintf (tex, "%s\n", rng_quote ('='));       \
    fprintf (tex, "\\begin{equation}\n");         \
    tex_branch(node, tex, line);                  \
        branch_remove (node, line);               \
        *changed_flag = 1;                        \
    fprintf (tex, "=1");                          \
    fprintf (tex, "\n\\end{equation}\n");         \
        return node_construct("1", 'ENO', line);

struct tree_node* simplify_zero_one (struct tree_node* node, int* changed_flag, FILE* tex, int line)
{
    char* function_name = "simplify zero/one";

    CHECK_CREATED (node);
    CHECK_NODE    (node);
    if (node->node_type != TYPE__FUNCTION)
        return node;

    node_add (node, CASE_OF_LEFT,  simplify_zero_one (node-> left_branch,  changed_flag, tex, line), line);
        CHECK_ARF();
    if (node->right_branch != NULL)
    {
        node_add (node, CASE_OF_RIGHT, simplify_zero_one (node-> right_branch, changed_flag, tex, line), line);
            CHECK_ARF();
    }


    int node_data = node->data;
    switch (node_data)
    {
    case 1:   //PLUS
        {
            if (IS_NODE (node->right_branch, 0))
            {
                RET_ONLY (left_branch);
            }

            if (IS_NODE (node-> left_branch, 0))
            {
                RET_ONLY (right_branch);
            }
        } break;

    case 2:   //MINUS
        {
            if (IS_NODE (node->right_branch, 0))
            {
                RET_ONLY (left_branch)
            }

            if (node->right_branch->node_type != TYPE__CONSTANT && IS_NODE (node->left_branch, 0))
            {
            fprintf (tex, "%s\n", rng_quote ('='));
            fprintf (tex, "\\begin{equation}\n");
            tex_branch(node, tex, line);
                struct tree_node* ret_node = node->right_branch;
            fprintf (tex, "=-");
            tex_branch(node->right_branch, tex, line);
            fprintf (tex, "\n\\end{equation}\n");
                node-> right_branch = NULL;
                branch_remove (node, line);
                *changed_flag = 1;
                return OpMult(MIN_ONE_NODE, ret_node);
            }
        } break;

    case 3:   //DIVIDE
        {
            if (IS_NODE (node->right_branch, 0))
            {
                ARF = 1;
                fprintf (tex, "Can't divide by zero!\n");
                return node;
            }

            if (IS_NODE (node->right_branch, 1))
            {
                RET_ONLY (left_branch)
            }

            if (IS_NODE (node->right_branch, -1))
            {
            fprintf (tex, "%s\n", rng_quote ('='));
            fprintf (tex, "\\begin{equation}\n");
            tex_branch(node, tex, line);
                struct tree_node* ret_node = node->left_branch;
            fprintf (tex, "=-");
            tex_branch(node->left_branch, tex, line);
            fprintf (tex, "\n\\end{equation}\n");
                node-> left_branch = NULL;
                branch_remove (node, line);
                *changed_flag = 1;
                return OpMult(MIN_ONE_NODE, ret_node);
            }

            if (IS_NODE (node->left_branch, 0))
            {
                RET_ZERO;
            }


            if (IS_NODE (node->left_branch, 1))
            {
            fprintf (tex, "%s\n", rng_quote ('='));
            fprintf (tex, "\\begin{equation}\n");
            tex_branch(node, tex, line);
                struct tree_node* ret_node = node->right_branch;
                node-> right_branch = NULL;
                branch_remove (node, line);
                *changed_flag = 1;
                ret_node = OpDeg(ret_node, MIN_ONE_NODE);
            fprintf (tex, "=");
            tex_branch(ret_node, tex, line);
            fprintf (tex, "\n\\end{equation}\n");
                return ret_node;
            }


            if (IS_NODE (node->left_branch, -1))
            {
            fprintf (tex, "%s\n", rng_quote ('='));
            fprintf (tex, "\\begin{equation}\n");
            tex_branch(node, tex, line);
                struct tree_node* ret_node = node->right_branch;
                ret_node = OpDeg(ret_node, MIN_ONE_NODE);
            fprintf (tex, "=-");
            tex_branch(ret_node, tex, line);
            fprintf (tex, "\n\\end{equation}\n");
                node-> right_branch = NULL;
                branch_remove (node, line);
                *changed_flag = 1;
                return OpMult(MIN_ONE_NODE, ret_node);
            }
        } break;


    case 4:   //MULTIPLY
        {
            if (IS_NODE (node->right_branch, 1))
            {
                RET_ONLY (left_branch);
            }

            if (IS_NODE (node->left_branch, 1))
            {
                RET_ONLY (right_branch);
            }

            if (IS_NODE (node->left_branch, 0) || IS_NODE (node->right_branch, 0))
            {
                RET_ZERO;
            }
        } break;

    case 5:  //power
        {
            if (IS_NODE (node->right_branch, 0))
            {
                RET_ONE;
            }

            if (IS_NODE (node->right_branch, 0))
            {
                RET_ONE;
            }

            if (IS_NODE (node->right_branch, 1))
            {
                RET_ONLY (left_branch);
            }

            if (IS_NODE (node-> left_branch, 1))
            {
                RET_ONE;
            }

        }break;


    case 18:  //log
        {
            if (node->left_branch-> node_type == TYPE__CONSTANT && node->left_branch-> data <= 0)
            {
                fprintf (tex, "Log can't have an argument <= 0.\n");
                ARF = 1;
                return node;
            }

            if (node->right_branch->node_type == TYPE__CONSTANT && node->right_branch->data <= 0)
            {
                fprintf (tex, "Log can't have a base <= 0.\n");
                ARF = 1;
                return node;
            }

            if (IS_NODE (node->right_branch, 1))
            {
                fprintf (tex, "Log can't have '1' as a base.\n");
                ARF = 1;
                return node;
            }

            if (IS_NODE (node->left_branch, 1) )
            {
                RET_ZERO;
            }

            if (branches_equal(node->left_branch, node->right_branch))
            {
                RET_ONE;
            }
        }break;
    }

    return node;
}

#undef RET_ZERO
#undef RET_ONE
#undef RET_ONLY

#undef MIN_ONE_NODE


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                         /*   ~~~   THE DIFFERENTIATOR   ~~~  */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


struct tree_node* differential (struct tree_node* node, int diff_var_number, FILE* tex, int line)
{
    switch (node->node_type)
    {
    case TYPE__FUNCTION:
        {
#define DEF_FUNC( name, num, diff_code )                     \
if ( 0.001 > node->data - num && node->data - num > -0.001)  \
{                                                            \
    diff_code;                                               \
} else

#include "functions_list.h"

#undef DEF_FUNC

            {
                fprintf(stderr, "No such function <<number %lf>> to differentiate)", node->data);
                PAUSE;
            }
        }break;

    case TYPE__VARIABLE:
        {
            int cur_var_number = node->data;
            if (cur_var_number == diff_var_number)
                return node_construct("1", 'ENO', line);
            else
                return node_construct("0", 'OREZ', line);
        }break;

    case TYPE__CONSTANT:
        return node_construct("0", 'OREZ', line);
    }

    return 0;
}



    /*~~*//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
    /*~*//**//**//**//**//**//*      X-DOT DUMPING         *//**//**//**//**//**//**//*~*/
    /**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//*~~*/


int dot_dump_tree (struct tree_node* node, FILE* outF, int line)
{
    char* function_name = "dot_dump_node";

    CHECK_CREATED (node);

    int canary_error = 0;
    if (node->canary1 != node->good_canary || node->canary2 != node->good_canary)
        canary_error = 1;

    int right_error    = 0;
    if (node->right_branch)
        if (node->right_branch->parent != node)
            right_error = 1;

    int left_error     = 0;
    if (node-> left_branch)
        if (node-> left_branch->parent != node)
            left_error = 1;


    fprintf (outF, "Node%p\n[shape = record, ", node);
    if (canary_error)
        fprintf (outF, "color = red, ");
    else
    {
        if (node->left_branch == NULL)
            fprintf (outF, "color = green, ");
        else
            fprintf (outF, "color = black, ");
    }

    fprintf     (outF, " label = \"{");
    fprintf     (outF, " <adr> %p | DATA: %lf ",node, node->data);

    switch (node->node_type)
    {
    case TYPE__FUNCTION:
        {
#define DEF_FUNC( name, num, diff_code )                     \
if ( 0.001 > node->data - num && node->data - num > -0.001)  \
{                                                            \
    fprintf (outF, " (%s)", name);                        \
} else

#include "functions_list.h"

#undef DEF_FUNC

            {
                fprintf(stderr, "?????");
                PAUSE;
            }
        }break;

    case TYPE__VARIABLE:
        {
            int var_num = node->data;
            fprintf (outF, "\\l (%s)", Var_Array[var_num]._Name);
        }break;
    }

    fprintf     (outF, " | Node_type: %s | ",     (char*)&node->node_type);
    fprintf     (outF, " Canary1:   %s \\l",      (char*)&node->canary1);
    fprintf     (outF, " Canary2:   %s \\l",      (char*)&node->canary2);
    fprintf     (outF, " Should be: %s |",        (char*)&node->good_canary);
    fprintf     (outF, " <left> LEFT:  %p | <rght> RIGHT:  %p", node->left_branch, node->right_branch);
    fprintf     (outF, " | <prnt> Parent:  %p",            node->parent);
    fprintf     (outF, "}\"];\n");

    if (node->left_branch)
    {
        fprintf (outF, "Node%p : <left> -> Node%p : <adr> ", node, node->left_branch);
    if ( left_error)
        fprintf (outF, "[color = red];\n");
    else
        fprintf (outF, "[color = blue];\n");
    }

    if (node->right_branch)
    {
        fprintf (outF, "Node%p : <rght> -> Node%p : <adr> ", node, node->right_branch);
    if (right_error)
        fprintf (outF, "[color = red];\n");
    else
        fprintf (outF, "[color = green];\n");
    }


    if (node->parent)
    {
        fprintf (outF, "Node%p : <prnt> -> Node%p : <adr> ", node, node->parent);
        fprintf (outF, "[color = gray];\n");
    }

    if (node->right_branch)
        dot_dump_tree (node->right_branch, outF, line);
    if (node->left_branch)
        dot_dump_tree (node->left_branch,  outF, line);

    return 0;
}


int dot_tree (struct tree_node* node, FILE* outF, int line)
{
    char* function_name = "dot_node";

    CHECK_CREATED (node);

    fprintf (outF, "Node%p\n[shape = record, ", node);
    if (node->left_branch == NULL)
        fprintf (outF, "color = green, ");
    else
        fprintf (outF, "color = black, ");

    fprintf     (outF, " label = \"{");
    fprintf     (outF, " <adr> ");

    switch (node->node_type)
    {
    case TYPE__FUNCTION:
        {
#define DEF_FUNC( name, num, diff_code )                     \
if ( 0.001 > node->data - num && node->data - num > -0.001)  \
{                                                            \
    fprintf (outF, " %s", name);                        \
} else

#include "functions_list.h"

#undef DEF_FUNC

            {
                fprintf(stderr, "?????");
                PAUSE;
            }
        }break;

    case TYPE__VARIABLE:
        {
            int var_num = node->data;
            fprintf (outF, " %s", Var_Array[var_num]._Name);
        }break;

    case TYPE__CONSTANT:
        {
            fprintf (outF, " %lf", node->data);
        }break;
    }


    fprintf     (outF, "| <left> LEFT | <rght> RIGHT");
    fprintf     (outF, "}\"];\n");


    if (node->left_branch)
    {
        fprintf (outF, "Node%p : <left> -> Node%p : <adr> ", node, node->left_branch);
        fprintf (outF, "[color = blue];\n");
    }

    if (node->right_branch)
    {
        fprintf (outF, "Node%p : <rght> -> Node%p : <adr> ", node, node->right_branch);
        fprintf (outF, "[color = green];\n");
    }



    if (node->left_branch)
        dot_tree (node->left_branch,  outF, line);
    if (node->right_branch)
        dot_tree (node->right_branch, outF, line);

    return 0;
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



int tex_branch (struct tree_node* node, FILE* file, int line)
{
    char* function_name = "tex_tree";
    CHECK_CREATED(node);
    CHECK_NODE   (node);

    if (node->node_type == TYPE__CONSTANT)
    {
        fprintf    (file, "{");
        if (EQUAL_DOUBLE(node->data, 2.718281828))
            fprintf(file, "e");
        else
        if (EQUAL_DOUBLE(node->data, 3.141592654))
            fprintf(file, "\\pi");
        else
            fprintf(file, "%lg", node->data);
        fprintf    (file, "}");
        return 0;
    }
    if (node->node_type == TYPE__VARIABLE)
    {
        int var_num = node->data;
        fprintf    (file, "{");
        fprintf (file, "%s", Var_Array[var_num]._Name);
        fprintf    (file, "}");
        return 0;
    }
    if (node->node_type != TYPE__FUNCTION)
    {
        fprintf (stderr, "ERROR!: tex_branch received a node with wrong type!\n(on line %d)\n\n", line);
        PAUSE;
        return -1;
    }

    int f_number = node->data;
#define TEX( side )                                \
    tex_branch (node->side##_branch, file, line);
    fprintf    (file, "{");
    switch (f_number)
    {
    case 1: //PLUS
        {
            TEX (left);
            fprintf(file, "+");
            TEX (right);
        } break;
    case 2: //MINUS
        {
            TEX (left);
            fprintf(file, "-");
            TEX (right);
        } break;
    case 3: //DIVIDE
        {
            TEX (left);
            fprintf(file, "\\over");
            TEX (right);
        } break;
    case 4: //MULT
        {
            int bracket_flag = (node->left_branch->node_type == TYPE__FUNCTION &&
                (EQUAL_DOUBLE(node->left_branch->data, 1) || EQUAL_DOUBLE(node->left_branch->data, 2)));
            if (bracket_flag)
                fprintf(file, "(");
            TEX (left);
            if (bracket_flag)
                fprintf(file, ")");
        fprintf(file, "*");
            bracket_flag = (node->right_branch->node_type == TYPE__FUNCTION &&
                (EQUAL_DOUBLE(node->right_branch->data, 1) || EQUAL_DOUBLE(node->right_branch->data, 2)));
            if (bracket_flag)
                fprintf(file, "(");
            TEX (right);
            if (bracket_flag)
                fprintf(file, ")");
        } break;
    case 5: //POWER
        {
            int bracket_flag = (node->left_branch->node_type == TYPE__FUNCTION);
            if (bracket_flag)
                fprintf(file, "(");
            TEX (left);
            if (bracket_flag)
                fprintf(file, ")");
            fprintf(file, "^");
            TEX (right);
        } break;
    case 18: //LOG
        {
        if (IS_NODE (node->right_branch, 2.718281828 ))
            fprintf (file, "ln");
        else
        {
            fprintf (file, "log_");
            TEX (right);
        }
            fprintf (file, "(");
            TEX (left);
            fprintf (file, ")");
        } break;

#define TEX_MONO(func)             \
        {                          \
            fprintf (file, func);  \
            fprintf (file, "(");   \
            TEX (left);            \
            fprintf (file, ")");   \
        } break;
    case 6: //SIN
        TEX_MONO ("sin");
    case 7: //COS
        TEX_MONO ("cos");
    case 8: //TG
        TEX_MONO ("tg");
    case 9: //CTG
        TEX_MONO ("ctg");
    case 10: //ARCSIN
        TEX_MONO ("arcsin");
    case 11: //ARCCOS
        TEX_MONO ("arccos");
    case 12: //ARCTG
        TEX_MONO ("arctg");
    case 13: //ARCCTG
        TEX_MONO ("arcctg");
    case 14: //SH
        TEX_MONO ("sh");
    case 15: //CH
        TEX_MONO ("ch");
    case 16: //TH
        TEX_MONO ("th");
    case 17: //CTH
        TEX_MONO ("cth");

#undef TEX_MONO
    }
    fprintf    (file, "}");
    return 0;
#undef TEX
}

int tex_tree (struct tree_node* base, char* pre_f, FILE* out, int line)
{

    fprintf (out, "\\begin{equation}\n"
                  "\\large %s", pre_f);
    tex_branch(base, out, line);
    fprintf (out, ";\n\\end{equation}\n");
    return 0;
}


#endif //DIFFERENTIAL_H_INCLUDED
