#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    struct int_list_t* list1 = int_list_construct (10, '22', __LINE__);
    struct int_list_elem_t* temp_elem_pointer = int_list_incert_last(list1, 11, '22', __LINE__);
    int_list_incert_last(list1, 12, '22', __LINE__);
    int_list_incert_last(list1, 13, '22', __LINE__);
    int_list_incert_last(list1, 14, '22', __LINE__);
    int_list_incert_last(list1, 15, '22', __LINE__);

    DUMP_LIST (list1, int);

    int_list_elem_incert_next (temp_elem_pointer, int_list_elem_construct(110, '65', __LINE__), __LINE__);

    DUMP_LIST (list1, int);
    return 0;
}
