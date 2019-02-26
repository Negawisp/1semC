//
// Created by Blind on 02.11.2017.
//
int ERRno = 0;

#include <stdlib.h>
#include <stdio.h>

#define NULL_ARGUMENT_ERROR          'null'
#define NEXT_UNASSOTIATION_ERROR     'next'
#define PREV_UNASSOTIATION_ERROR     'prev'
#define CANARY_ERROR                 'cnry'


#define DUMP_INT_ELEMENT( element )            \
printf ("Address: %x\n", element);             \
printf ("Data:    %d\n", element->data);       \
printf ("Prev Address: %x\n", element->prev);  \
printf ("Next Address: %x\n\n", element->next);


#define PRINT_ERR( err_text, error_code )                                                  \
{                                                                                          \
	fprintf(stderr, "%s in function \"%s\" on line #%d.", err_text, FunctionName, Line);   \
	ERRno = error_code;                                                                    \
}

#define CHECK_PREV( base )                                                \
if ((base->prev != NULL) && (base->prev->next != base))                   \
	PRINT_ERR ("Found wrong PREV connection", PREV_UNASSOTIATION_ERROR);

#define CHECK_NEXT( base )                                                \
if ((base->prev != NULL) && (base->next->prev != base))                   \
	PRINT_ERR ("Found wrong NEXT connection", NEXT_UNASSOTIATION_ERROR);

#define CHECK_CANARY( base )                                                                  \
if ((base -> canary1 != base -> std_canary) || (base -> canary2 != base -> std_canary))       \
    PRINT_ERR ("ERROR: Detected defected data in function %s on line %d.", CANARY_ERROR);

#define CHECK_ALL( base )     \
    CHECK_PREV   ( base );    \
    CHECK_NEXT   ( base );    \
    CHECK_CANARY ( base );    \


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
struct type##_list_elem_t* type##_list_elem_construct (type Data, int canary_val, int Line)                                \
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
		         FunctionName, #type , Line);                                                                             \
		                                                                                                                  \
        char answer[10] = "";                                                                                             \
        scanf ("%s", answer);                                                                                             \
	}                                                                                                                     \
	free(elem);                                                                                                           \
	return prev;                                                                                                          \
}                                                                                                                         \
                                                                                                                          \
int type##_list_elem_incert_next (struct type##_list_elem_t* base_elem, struct type##_list_elem_t* new_elem, int Line)    \
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
    CHECK_ALL (base_elem); if (ERRno) return ERRno;                                                                       \
    CHECK_ALL (new_elem);  if (ERRno) return ERRno;                                                                       \
                                                                                                                          \
	if (base_elem -> next != NULL)                                                                                        \
		base_elem -> next -> prev = new_elem;                                                                             \
	new_elem  -> next = base_elem -> next;                                                                                \
	new_elem  -> prev = base_elem;                                                                                        \
	base_elem -> next = new_elem;                                                                                         \
                                                                                                                          \
    CHECK_ALL (base_elem); if (ERRno) return ERRno;                                                                       \
    CHECK_ALL (new_elem);  if (ERRno) return ERRno;                                                                       \
	                                                                                                                      \
	return 0;                                                                                                             \
}                                                                                                                         \
                                                                                                                          \
                                                                                                                          \
int type##_list_elem_incert_prev (struct type##_list_elem_t* base_elem, struct type##_list_elem_t* new_elem, int Line)    \
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
    CHECK_ALL (base_elem); if (ERRno) return ERRno;                                                                       \
    CHECK_ALL (new_elem);  if (ERRno) return ERRno;                                                                       \
                                                                                                                          \
	if (base_elem -> prev != NULL)                                                                                        \
		base_elem -> prev -> next = new_elem;                                                                             \
	new_elem  -> next = base_elem;                                                                                        \
	new_elem  -> prev = base_elem -> prev;                                                                                \
	base_elem -> prev = new_elem;                                                                                         \
                                                                                                                          \
    CHECK_ALL (base_elem); if (ERRno) return ERRno;                                                                       \
    CHECK_ALL (new_elem);  if (ERRno) return ERRno;                                                                       \
                                                                                                                          \
	return 0;                                                                                                             \
}


LIST_TYPE_DECLARATION (int)
LIST_TYPE_DECLARATION (double)
