//
// Created by Blind on 02.11.2017.
//
#include <stdlib.h>
#include <stdio.h>


#define NULL_ARGUMENT_ERROR          'null'
#define NEXT_UNASSOTIATION_ERROR     'next'
#define PREV_UNASSOTIATION_ERROR     'prev'
#define CANARY_ERROR                 'cnry'
#define BAD_LIST_ERROR               'list'

#define FORWARD                      'frwd'
#define BACKWARD                     'bcwd'

int ERRno = 0;

#define DUMP_int_ELEMENT( element )                 \
if (element)                                        \
{                                                   \
    printf ("Address: %x\n", element);              \
    printf ("Data:    %d\n", element->data);        \
    printf ("Prev Address: %x\n", element->prev);   \
    printf ("Next Address: %x\n\n", element->next); \
}                                                   \
else                                                \
    printf ("(Can't dump NULL)");


#define DUMP_double_ELEMENT( element )              \
if (element)                                        \
{                                                   \
    printf ("Address: %x\n", element);              \
    printf ("Data:    %lf\n", element->data);       \
    printf ("Prev Address: %x\n", element->prev);   \
    printf ("Next Address: %x\n\n", element->next); \
}                                                   \
else                                                \
    printf ("(Can't dump NULL)");



#define PRINT_ERR( err_text, error_code )                                                       \
{                                                                                               \
	fprintf(stderr, "%s\nin function \"%s\" on line N%d.\n\n", err_text, FunctionName, Line);   \
	ERRno = error_code;                                                                         \
}

#define CHECK_PREV( base )                                                                      \
if ((base->prev != NULL) && (base->prev->next != base))                                         \
	PRINT_ERR ("Found wrong PREV connection", PREV_UNASSOTIATION_ERROR);

#define CHECK_NEXT( base )                                                                      \
if ((base->next != NULL) && (base->next->prev != base))                                         \
	PRINT_ERR ("Found wrong NEXT connection", NEXT_UNASSOTIATION_ERROR);

#define CHECK_CANARY( base )                                                                    \
if ((base -> canary1 != base -> std_canary) || (base -> canary2 != base -> std_canary))         \
    PRINT_ERR ("ERROR: Detected defected data (dead canary)", CANARY_ERROR);

#define CHECK_ALL( base )                                                                       \
    CHECK_PREV   ( base );                                                                      \
    CHECK_NEXT   ( base );                                                                      \
    CHECK_CANARY ( base );




#define CHECK_LIST(list, type)                                                                             \
{                                                                                                          \
    CHECK_CANARY ( list );                                                                                 \
    if (type##_list_check_forward (list->head, Line) == NULL)                                              \
    {                                                                                                      \
        struct type##_list_elem_t* current = list->head;                                                   \
        int elem_number = 0;                                                                               \
        while (current != NULL)                                                                            \
        {                                                                                                  \
            current = current->next;                                                                       \
            elem_number++;                                                                                 \
        }                                                                                                  \
        if (elem_number != list->elems_count)                                                                \
        {                                                                                                       \
            fprintf (stderr,                                                                                     \
                     "ERROR: Real and recorded number of elements in list do not match (on line N%d).", Line);   \
            ERRno = BAD_LIST_ERROR;                                                                              \
        }                                                                                                       \
        if (current != list->tail)                                                                           \
        {                                                                                                  \
            fprintf (stderr, "ERROR: Can't access tail from head (on line N%d).", Line);                   \
            ERRno - BAD_LIST_ERROR;                                                                        \
        }                                                                                                  \
    } else ERRno = BAD_LIST_ERROR;                                                                         \
}



#define LIST_TYPE_DECLARATION( type )          \
struct type##_list_elem_t                      \
{                                              \
	int canary1;                               \
	int std_canary;                            \
	type data;                                 \
	struct type##_list_elem_t* prev;           \
	struct type##_list_elem_t* next;           \
	int canary2;                               \
};                                             \
                                               \
                                               \
struct type##_list_t                           \
{                                              \
	int canary1;                               \
	                                           \
	int std_canary;                            \
	struct type##_list_elem_t* head;           \
	struct type##_list_elem_t* tail;           \
	int elems_count;                           \
	                                           \
	int canary2;                               \
};                                             \
                                               \
                                               \
struct type##_list_elem_t* type##_list_elem_construct (type Data, int canary_val, int Line)                               \
{                                                                                                                         \
    char* FunctionName = "type##_list_elem_construct";                                                                    \
                                                                                                                          \
	struct type##_list_elem_t* elem = (struct type##_list_elem_t*)calloc (1, sizeof (struct type##_list_elem_t));         \
	if (elem == NULL)                                                                                                     \
    {                                                                                                                     \
		fprintf(stderr, "Could not allocate memory for \"%s_list_elem_t* elem\" on line %d.", #type, Line);               \
		perror("");                                                                                                       \
	}                                                                                                                     \
	elem -> canary1    = canary_val;                                                                                      \
	elem -> canary2    = canary_val;                                                                                      \
	elem -> std_canary = canary_val;                                                                                      \
	elem -> data = Data;                                                                                                  \
	elem -> prev = NULL;                                                                                                  \
	elem -> next = NULL;                                                                                                  \
	return elem;                                                                                                          \
}                                                                                                                         \
                                                                                                                          \
                                                                                                                          \
struct type##_list_elem_t*type##_list_elem_remove (struct type##_list_elem_t* elem, int Line)                             \
{                                                                                                                         \
    char* FunctionName = "type##_list_elem_remove";                                                                       \
                                                                                                                          \
	if (elem == NULL)                                                                                                     \
	{                                                                                                                     \
		fprintf (stderr, "ERROR: %s_list_elem_remove got NULL as an argument on line %d", #type , Line);                  \
		perror("");                                                                                                       \
	}                                                                                                                     \
                                                                                                                          \
    CHECK_ALL (elem); if (ERRno) return NULL;                                                                             \
                                                                                                                          \
	struct type##_list_elem_t* prev = elem->prev;                                                                         \
	struct type##_list_elem_t* next = elem->next;                                                                         \
    CHECK_ALL (next); if (ERRno) return NULL;                                                                             \
    CHECK_ALL (prev); if (ERRno) return NULL;                                                                             \
	int empty_prev_flag = 0;                                                                                              \
                                                                                                                          \
	if (prev != NULL)                                                                                                     \
	{                                                                                                                     \
		empty_prev_flag++;                                                                                                \
		prev -> next = next;                                                                                              \
	}                                                                                                                     \
	                                                                                                                      \
	if (next != NULL)                                                                                                     \
	{                                                                                                                     \
		next -> prev = prev;                                                                                              \
    CHECK_ALL (next); if (ERRno) return NULL;                                                                             \
    CHECK_ALL (prev); if (ERRno) return NULL;                                                                             \
		free (elem);                                                                                                      \
		return next;                                                                                                      \
	}                                                                                                                     \
	                                                                                                                      \
	if (empty_prev_flag == 1)                                                                                             \
	{                                                                                                                     \
		fprintf (stderr,                                                                                                  \
           "WARNING: Function %s_list_elem_remove on line %d\n"                                                           \
           "removed %s_list_elem_t without both prev and next elements!\n"                                                \
           "I, programmer, aknowledged the threat and accepted it:  ",                                                    \
		         #type , Line, #type );                                                                             \
		                                                                                                                  \
        char answer[10] = "";                                                                                             \
        scanf ("%s", answer);                                                                                             \
	}                                                                                                                     \
	free(elem);                                                                                                           \
	return prev;                                                                                                          \
}                                                                                                                         \
                                                                                                                          \
struct type##_list_elem_t* type##_list_elem_incert_next                                                                   \
                                 (struct type##_list_elem_t* base_elem, struct type##_list_elem_t* new_elem, int Line)    \
{                                                                                                                         \
    char* FunctionName = "type##_list_elem_incert_next";                                                                  \
                                                                                                                          \
	if (base_elem == NULL)                                                                                                \
	{                                                                                                                     \
		fprintf (stderr,                                                                                                  \
	             "ERROR: %s_list_elem_incert_next got NULL as base_elem pointer on line %d", #type , Line);               \
		perror("");                                                                                                       \
	}                                                                                                                     \
	if (new_elem  == NULL)                                                                                                \
	{                                                                                                                     \
		fprintf (stderr,                                                                                                  \
	             "ERROR: %s_list_elem_incert_next got NULL as new_elem pointer on line %d", #type , Line);                \
		perror("");                                                                                                       \
	}                                                                                                                     \
                                                                                                                          \
    CHECK_ALL (base_elem); if (ERRno) return NULL;                                                                        \
    CHECK_ALL (new_elem);  if (ERRno) return NULL;                                                                        \
                                                                                                                          \
	if (base_elem -> next != NULL)                                                                                        \
		base_elem -> next -> prev = new_elem;                                                                             \
	new_elem  -> next = base_elem -> next;                                                                                \
	new_elem  -> prev = base_elem;                                                                                        \
	base_elem -> next = new_elem;                                                                                         \
                                                                                                                          \
    CHECK_ALL (base_elem); if (ERRno) return NULL;                                                                        \
    CHECK_ALL (new_elem);  if (ERRno) return NULL;                                                                        \
	                                                                                                                      \
	return new_elem;                                                                                                      \
}                                                                                                                         \
                                                                                                                          \
                                                                                                                          \
struct type##_list_elem_t* type##_list_elem_incert_prev                                                                   \
                                 (struct type##_list_elem_t* base_elem, struct type##_list_elem_t* new_elem, int Line)    \
{                                                                                                                         \
    char* FunctionName = "type##_list_elem_incert_prev";                                                                  \
                                                                                                                          \
	if (base_elem == NULL)                                                                                                \
	{                                                                                                                     \
		fprintf (stderr,                                                                                                  \
	             "ERROR: %s_list_elem_incert_next got NULL as base_elem pointer on line %d", #type , Line);               \
		perror("");                                                                                                       \
	}                                                                                                                     \
	if (new_elem  == NULL)                                                                                                \
	{                                                                                                                     \
		fprintf (stderr,                                                                                                  \
	             "ERROR: %s_list_elem_incert_next got NULL as new_elem pointer on line %d", #type , Line);                \
		perror("");                                                                                                       \
	}                                                                                                                     \
                                                                                                                          \
    CHECK_ALL (base_elem); if (ERRno) return NULL;                                                                        \
    CHECK_ALL (new_elem);  if (ERRno) return NULL;                                                                        \
                                                                                                                          \
	if (base_elem -> prev != NULL)                                                                                        \
		base_elem -> prev -> next = new_elem;                                                                             \
	new_elem  -> next = base_elem;                                                                                        \
	new_elem  -> prev = base_elem -> prev;                                                                                \
	base_elem -> prev = new_elem;                                                                                         \
                                                                                                                          \
    CHECK_ALL (base_elem); if (ERRno) return NULL;                                                                        \
    CHECK_ALL (new_elem);  if (ERRno) return NULL;                                                                        \
                                                                                                                          \
	return new_elem;                                                                                                      \
}                                                                                                                         \
                                                                                                                          \
struct type##_list_elem_t* type##_list_check_forward (struct type##_list_elem_t* base_elem, int Line)                     \
{                                                                                                                         \
    char* FunctionName = "type##_list_check_forward";                                                                     \
                                                                                                                          \
    if (base_elem == NULL)                                                                                                \
    {                                                                                                                     \
        fprintf (stderr,                                                                                                  \
                 "ERROR: %s_list_check_forward received NULL as base_elem pointer on line %d", #type , Line);             \
        perror("");                                                                                                       \
    }                                                                                                                     \
    ERRno = 0;                                                                                                            \
    CHECK_ALL(base_elem);                                                                                                 \
    if (ERRno) { printf("Problem is encountered with base_element."); return base_elem; }                                 \
                                                                                                                          \
                                                                                                                          \
    struct type##_list_elem_t* current = base_elem;                                                                       \
    int elem_number = 0;                                                                                                  \
                                                                                                                          \
    while (current->next)                                                                                                 \
    {                                                                                                                     \
        current = current->next;                                                                                          \
        CHECK_ALL(current);                                                                                               \
        if (ERRno)                                                                                                        \
        {                                                                                                                 \
            printf ("Problem is encountered with element N%d:\n", elem_number);                                           \
            printf("~~ Previous element(%d): ~~\n", elem_number-1);                                                       \
            DUMP_##type##_ELEMENT(current->prev);                                                                         \
            printf("~~ Current element(%d):  ~~\n", elem_number);                                                         \
            DUMP_##type##_ELEMENT(current);                                                                               \
            printf("~~   Next element:   ~~\n");                                                                          \
            DUMP_##type##_ELEMENT(current->next);                                                                         \
            return current;                                                                                               \
        }                                                                                                                 \
        elem_number++;                                                                                                    \
    }                                                                                                                     \
                                                                                                                          \
                                                                                                                          \
    printf ("No problems encountered during the check.\n"                                                                 \
            "%d elements are following after the base.", elem_number);                                                    \
    return NULL;                                                                                                          \
}                                                                                                                         \
                                                                                                                          \
                                                                                                                          \
int dump_##type##_list (struct type##_list_elem_t* elem, FILE* outF, const int direction, int Line)                       \
{                                                                                                                         \
    if (elem == NULL)                                                                                                     \
    {                                                                                                                     \
        fprintf (stderr, "ERROR: dump_%s_list received NULL as elem pointer on line %d.", #type , Line);                  \
        perror("");                                                                                                       \
    }                                                                                                                     \
                                                                                                                          \
    char* FunctionName = "dump_##type##_list";                                                                            \
                                                                                                                          \
    int this_error = 0;                                                                                                   \
                                                                                                                          \
    ERRno = 0;                                                                                                            \
    int canary_ok = 1;                                                                                                    \
    CHECK_CANARY (elem);                                                                                                  \
    if (ERRno)                                                                                                            \
        { canary_ok = 0; this_error = 1; }                                                                                \
                                                                                                                          \
    ERRno = 0;                                                                                                            \
    int prev_ok = 1;                                                                                                      \
    CHECK_PREV (elem);                                                                                                    \
    if (ERRno)                                                                                                            \
        { prev_ok = 0; this_error = 1; }                                                                                  \
                                                                                                                          \
    ERRno = 0;                                                                                                            \
    int next_ok = 1;                                                                                                      \
    CHECK_NEXT (elem);                                                                                                    \
    if (ERRno)                                                                                                            \
        { next_ok = 0; this_error = 1; }                                                                                  \
                                                                                                                          \
                                                                                                                          \
    if (this_error)                                                                                                       \
    {                                                                                                                     \
        printf ("~~Defected node found during the dump of list: ~~\n");                                                   \
        printf ("-> Prev elem:\n");                                                                                       \
        DUMP_int_ELEMENT (elem->prev);                                                                                    \
                                                                                                                          \
        printf ("-> This elem:\n");                                                                                       \
        DUMP_int_ELEMENT (elem);                                                                                          \
                                                                                                                          \
        printf ("-> Next elem:\n");                                                                                       \
        DUMP_int_ELEMENT (elem->next);                                                                                    \
    }                                                                                                                     \
                                                                                                                          \
                                                                                                                          \
    fprintf     (outF, "Node%x\n[shape = record, ",   elem              );                                                \
    if (!canary_ok)                                                                                                       \
        fprintf (outF, "color = red, "                                  );                                                \
    else                                                                                                                  \
        fprintf (outF, "color = black, "                                );                                                \
    fprintf     (outF, " label = \""                                    );                                                \
    fprintf     (outF, " <adr> %x | DATA: %d | ", elem, elem->data      );                                                \
    fprintf     (outF, " Canary1:   %d \\l",      elem->canary1         );                                                \
    fprintf     (outF, " Canary2:   %d \\l",      elem->canary2         );                                                \
    fprintf     (outF, " Should be: %d |",        elem->std_canary      );                                                \
    fprintf     (outF, " <pr>  %x | <nx> %x",     elem->prev, elem->next);                                                \
    fprintf     (outF, "\"];\n"                                         );                                                \
    if (elem->prev != NULL)                                                                                               \
    {                                                                                                                     \
        fprintf (outF, "Node%x : <pr> -> Node%x : <adr> ", elem, elem->prev );                                            \
    if (!prev_ok)                                                                                                         \
        fprintf (outF, "[color = red];\n"                               );                                                \
    else                                                                                                                  \
        fprintf (outF, "[color = green];\n"                             );                                                \
    }                                                                                                                     \
    if (elem->next != NULL)                                                                                               \
    {                                                                                                                     \
        fprintf (outF, "Node%x : <nx> -> Node%x : <adr> ", elem, elem->next );                                            \
    if (!next_ok)                                                                                                         \
        fprintf (outF, "[color = red]\n"                                );                                                \
    else                                                                                                                  \
        fprintf (outF, "[color = blue];\n"                              );                                                \
    }                                                                                                                     \
                                                                                                                          \
                                                                                                                          \
    switch (direction)                                                                                                    \
    {                                                                                                                     \
    case FORWARD:                                                                                                         \
        {                                                                                                                 \
            if (elem->next)                                                                                               \
                dump_##type##_list (elem->next, outF, FORWARD,  Line);                                                    \
        } break;                                                                                                          \
                                                                                                                          \
    case BACKWARD:                                                                                                        \
        {                                                                                                                 \
            if (elem->prev)                                                                                               \
                dump_##type##_list (elem->prev, outF, BACKWARD, Line);                                                    \
        } break;                                                                                                          \
    }                                                                                                                     \
                                                                                                                          \
    return this_error;                                                                                                    \
}                                                                                                                         \
                                                                                                                          \
                                                                                                                          \
struct type##_list_t* type##_list_construct (type first_elem_data, int canary_val, int Line)                              \
{                                                                                                                         \
    char* FunctionName = "type##_list_construct";                                                                         \
                                                                                                                          \
	struct type##_list_t* list_adress = (struct type##_list_t*)calloc (1, sizeof (struct type##_list_t));                 \
	list_adress -> canary1     = canary_val;                                                                              \
	list_adress -> canary2     = canary_val;                                                                              \
	list_adress -> std_canary  = canary_val;                                                                              \
	list_adress -> head        = type##_list_elem_construct (first_elem_data, canary_val, Line);                          \
	list_adress -> tail        = list_adress -> head;                                                                     \
	list_adress -> elems_count = 1;                                                                                       \
	return list_adress;                                                                                                   \
}                                                                                                                         \
                                                                                                                          \
struct type##_list_elem_t* type##_list_incert_first (struct type##_list_t* lst, type data, int canary_val, int Line)                             \
{                                                                                                                         \
    char* FunctionName = "type##_list_incert_first";                                                                      \
    if (lst == NULL)                                                                                                      \
        { fprintf (stderr, "ERROR: %s received NULL as list argument on line %d.", FunctionName, Line); return 1; }       \
                                                                                                                          \
    struct type##_list_elem_t* elem = type##_list_elem_construct (data, canary_val, Line);                                \
    type##_list_elem_incert_prev (lst->head, elem, Line);                                                                 \
    lst->head = elem;                                                                                                     \
    lst->elems_count ++;                                                                                                  \
    return elem;                                                                                                             \
}                                                                                                                         \
                                                                                                                          \
struct type##_list_elem_t* type##_list_incert_last (struct type##_list_t* lst, type data, int canary_val, int Line)                               \
{                                                                                                                             \
    char* FunctionName = "type##_list_incert_last";                                                                              \
    if (lst == NULL)                                                                                                              \
        { fprintf (stderr, "ERROR: %s_list_incert_last received NULL as list argument on line %d.", #type , Line); perror(""); }  \
                                                                                                                                  \
    struct type##_list_elem_t* elem = type##_list_elem_construct (data, canary_val, Line);                                       \
    type##_list_elem_incert_next (lst->tail, elem, Line);                                                                     \
    lst->tail = elem;                                                                                                      \
    lst->elems_count ++;                                                                                                  \
    return elem;                                                                                                             \
}                                                                                                                         \
                                                                                                                          \
                                                                                                                          \
int type##_list_remove (struct type##_list_t* lst, int Line)                                                               \
{                                                                                                                         \
    char* FunctionName = "type##_list_remove";                                                                             \
    if (lst == NULL)                                                                                                        \
        { fprintf (stderr, "ERROR: %s_list_remove received NULL as list argument on line %d.", #type , Line); perror(""); }  \
                                                                                                                             \
    ERRno = 0;                                                                                                              \
    CHECK_LIST (lst, type );                                                                                              \
    if (ERRno)                                                                                                            \
        return 1;                                                                                                         \
                                                                                                                          \
    struct type##_list_elem_t* current = lst -> head;                                                                    \
    struct type##_list_elem_t* next    = NULL;                                                                            \
                                                                                                                          \
    while (current != NULL)                                                                                               \
    {                                                                                                                     \
        next = current -> next;                                                                                           \
        free (current);                                                                                                   \
        current = next;                                                                                                   \
    }                                                                                                                     \
                                                                                                                          \
    free (lst);                                                                                                           \
                                                                                                                          \
    return 0;                                                                                                             \
}






#define DUMP_LIST_BY_ELEM( base_elem, type )                           \
{                                                                      \
    FILE* dmp = fopen("dmp.gv", "wb");                                 \
    fprintf (dmp, "digraph G {\n");                                    \
    dump_##type##_list (base_elem, dmp, FORWARD,  __LINE__);           \
if (base_elem->prev != NULL)                                           \
    dump_##type##_list (base_elem->prev, dmp, BACKWARD,  __LINE__);    \
    fprintf (dmp, "\n}\n");                                            \
    fclose (dmp);                                                      \
    system ("xdot dmp.gv");                                            \
}


#define DUMP_LIST( list, type )                                        \
{                                                                      \
    DUMP_LIST_BY_ELEM ( list->head, type );                            \
}

LIST_TYPE_DECLARATION (int)
LIST_TYPE_DECLARATION (double)
