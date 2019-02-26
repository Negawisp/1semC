struct return_stack
{
	size_t  Count;
	size_t  MaxCount;
	int*    data;
};


struct return_stack* stack_construct (int length)
{
    struct return_stack* temp_p = calloc (1, sizeof (struct return_stack));
    temp_p -> data = calloc (length + 1, sizeof (int));
    temp_p -> MaxCount = length;
    temp_p -> Count = 0;

    return temp_p;
}


int push (struct return_stack* stck, int wtp)
{
    if (stck->Count >= stck->MaxCount)
    {
        printf ("Stack OVERFLOW!");
        PAUSE;
    }

    stck->data[stck->Count] = wtp;
    stck->Count++;

    return 0;
}

int pop (struct return_stack* stck)
{
    stck->Count--;
    if (stck->Count < 0)
    {
        printf ("Stack OVERDOWN!");
        PAUSE;
    }

    return stck->data[stck->Count];
}

#define PLAY_GAME_CASE   'play'
#define OPEN_TREE_CASE   'tree'
#define   COMPARE_CASE   'cmpr'
#define QUIT_GAME_CASE   'quit'




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Helping functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int seek_char (char* buffer, char ch, int position)
{
    while (buffer [position] != ch && buffer [position] != '\0')
        position++;

    if (buffer [position] == '\0')
        return -1;
    else
        return position;
}


int get_yes_no ()
{
    char* answer = calloc (10, sizeof (char));
    char t = 0;
    do
    {
        printf ("yes/no: ");
        fgets  (answer, MAX_DATA_LENGTH-1, stdin); answer [strlen (answer) - 1] = '\0';
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
}


int print_guess (char* data)
{
    int cs = rand() % 7;

    switch (cs)
    {
    case 0:
        {
            printf ("9 gyMA|0, 3T0 %s.\n", data);
        }break;
    case 1:
        {
            printf ("MHE KA}|{ETC9, 3T0 %s.\n", data);
        }break;
    case 2:
        {
            printf ("3T0 %s, 9 IIPAB?\n", data);
        }break;
    case 3:
        {
            printf ("Obviously, it is %s.\n", data);
        }break;
    case 4:
        {
            printf ("Is it %s?\n", data);
        }break;
    case 5:
        {
            printf ("9 3HA|0!! 3T0 %s!\n", data);
        }break;
    case 6:
        {
            printf ("100 percent it is %s!\n", data);
        }break;
    }

    return 0;
}


int print_question (char* data)
{
    int cs = rand() % 7;

    switch (cs)
    {
    case 0:
        {
            printf ("Is your character %s?\n", data);
        }break;
    case 1:
        {
            printf ("Can your character be described as %s?\n", data);
        }break;
    case 2:
        {
            printf ("0H0 %s, ga?\n", data);
        }break;
    case 3:
        {
            printf ("MHE II0M0}|{ET 3HATb, IIEPCOHaZH %s?\n", data);
        }break;
    case 4:
        {
            printf ("BAIII IIEPC0HA}|{ %s?\n", data);
        }break;
    case 5:
        {
            printf ("uHTEPECH0, IIEPCOHA}|{ %s?\n", data);
        }break;
    case 6:
        {
            printf ("I wonder if they %s?\n", data);
        }break;
    }

    return 0;
}


int print_end_guessed ()
{
    int cs = rand() % 7;

    switch (cs)
    {
    case 0:
        {
            printf ("Just as I thought)\n");
        }break;
    case 1:
        {
            printf ("TAK 9 u gyMAL!\n");
        }break;
    case 2:
        {
            printf ("9 }|{E r0B0PuJl ;)\n");
        }break;
    case 3:
        {
            printf ("TAK 9 u gyMAJl ;)\n");
        }break;
    case 4:
        {
            printf ("Hy B0T u g0r0B0PuJluCb ))\n");
        }break;
    case 5:
        {
            printf ("IIpu9TH0 3HaTb, 4T0 9 TAK0u yMHbIu )\n");
        }break;
    case 6:
        {
            printf ("YYes! I knew it!\n");
        }break;
    }

    return 0;
}


int print_end_not_guessed ()
{
    int cs = rand() % 7;

    switch (cs)
    {
    case 0:
        {
            printf ("Noooo! I lost :(\n");
        }break;
    case 1:
        {
            printf ("EJlKu - IIaJlKu!\n");
        }break;
    case 2:
        {
            printf ("Nu 9 }|{E HE 3HaJl!\n");
        }break;
    case 3:
        {
            printf ("6ygy 3HATb...\n");
        }break;
    case 4:
        {
            printf ("KAK 9 MOr IIPOurPATb!?\n");
        }break;
    case 5:
        {
            printf ("Live and learn, live and learn...\n");
        }break;
    case 6:
        {
            printf ("ga JlAgH0! TbI BCE BbIgyMAJl!\n");
        }break;
    }

    return 0;
}






/*         ~~~~~~~~~~~~~~~~    Akinator functions    ~~~~~~~~~~~~~~~~~~        */

int node_insert_question (struct tree_node* base, int canary, int line)
{
    char* function_name = "node_insert_question";

    CHECK_CREATED (base);
    CHECK_NODE    (base);
    NULL_CHECK    (base, CASE_OF_NO );
    NULL_CHECK    (base, CASE_OF_YES);


    char* quality       = calloc (MAX_DATA_LENGTH, sizeof (char));
    char* yes_character = calloc (MAX_DATA_LENGTH, sizeof (char));
    int str_length = 0;

    CHECK_CREATED (quality);
    CHECK_CREATED (yes_character);

    printf("KTO }|{E 3TO, ECJlu HE %s?\nEnter the new character's name: \n", base -> data);
    //scanf ("%s", yes_character);

    fgets (yes_character, MAX_DATA_LENGTH-1, stdin); yes_character [strlen (yes_character) - 1] = '\0';
    //sprintf (yes_character, "Let's play!");

    printf("\nNu khorosho, i chem zhe vash \"%s\"\n"
           "otlichaetsya ot \"%s\"?\nEnter the quality that the new character has: \n", yes_character, base->data);
    //scanf ("%s", quality);
    fgets (quality,       MAX_DATA_LENGTH-1, stdin); quality       [strlen (quality) - 1      ] = '\0';
    //sprintf (quality, "Was it a joke");

    struct tree_node* yes_case = node_construct (yes_character, canary, line);
    CHECK_CREATED (yes_case);
    CHECK_CREATED (yes_case -> data);
    CHECK_NODE    (yes_case);

    struct tree_node* no_case  = node_construct (base -> data,  canary, line);
    CHECK_CREATED (no_case );
    CHECK_CREATED (no_case -> data );
    CHECK_NODE    (no_case );

    base -> data = quality;
    CHECK_CREATED (base -> data);

    node_add (base, CASE_OF_NO,  no_case,  line);
    node_add (base, CASE_OF_YES, yes_case, line);

    branch_check(base, line);
    return 0;
}


int save_progress (FILE* output, struct tree_node* base, int indention, int line)
{
    char* function_name = "save_progress";

    if (indention >= MAX_BRANCH_LENGTH)
    {
        fprintf(stderr, "Too long branch :(\n"
                        "(In function %s, line %d.)\n"
                        "Last node:\n", function_name, line);
        DUMP_NODE (base);
    }

    CHECK_CREATED (base);
    CHECK_NODE    (base);

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
            DUMP_NODE(base);
        }


    fprintf (output, "%s( '%s'\n", tabulation, base -> data);

    if (base -> no_case )
        save_progress (output, base -> no_case,  indention+1, line);
    if (base -> yes_case)
        save_progress (output, base -> yes_case, indention+1, line);


    fprintf (output, "%s)\n",      tabulation);

    free (tabulation);
    return 0;
}


#define LOAD_AKINATOR_ERROR_FOUND( text )                                                             \
{                                                                                                     \
    fprintf(stderr, "%s \n"                                                                           \
                    "(Function %s, line %d, file_line %d)", text, function_name, line, file_line);    \
    fclose(input);                                                                                    \
    PAUSE;                                                                                            \
}

struct tree_node* load_akinator (FILE* input, int line, int file_line)
{
    char* function_name = "load_akinator";
    CHECK_CREATED (input);


    char* buffer = calloc (MAX_BRANCH_LENGTH * SINGLE_TABULATION_LENGTH + MAX_DATA_LENGTH * 2, sizeof (char));
    CHECK_CREATED (buffer);

    fgets (buffer,         MAX_BRANCH_LENGTH * SINGLE_TABULATION_LENGTH + MAX_DATA_LENGTH * 2, input);


    int char_position = 0;
    int end_position  = 0;
    file_line++;


    char_position = seek_char (buffer, '(', 0);
    if (char_position == -1)
    {
        if (seek_char(buffer, ')', 0) == - 1)
        {
            LOAD_AKINATOR_ERROR_FOUND("ERROR: Save-file had an opening line without a \"(\" symbol.");
        }
        else
        {
            free (buffer);
            return NULL;
        }
    }


    char_position = seek_char (buffer, '\'', char_position);
    if (char_position == -1)
    {
        LOAD_AKINATOR_ERROR_FOUND("ERROR: Save-file had no opening \" ' \" symbol after the \"(\" symbol.");
    }

    char_position++;

    end_position  = seek_char (buffer, '\'', char_position);
    if (end_position  == -1)
    {
        LOAD_AKINATOR_ERROR_FOUND("ERROR: Save-file had no closing \" ' \" symbol after the \"(\" symbol.");
    }
    buffer[end_position] = '\0';


    char*             this_data = calloc(MAX_DATA_LENGTH+1, sizeof (char)); CHECK_CREATED(this_data);
              strcat (this_data, buffer + char_position);


    struct tree_node* this_node = node_construct(this_data, 'usrD', line);
    CHECK_CREATED(this_node); CHECK_CREATED(this_node->data);


        node_add(this_node, CASE_OF_NO,  load_akinator (input, line, file_line), line);
    if (this_node -> no_case == NULL)
        this_node -> yes_case = NULL;
    else
    {
        node_add(this_node, CASE_OF_YES, load_akinator (input, line, file_line), line);
        if (this_node -> yes_case == NULL)
        {
            fprintf (stderr, "ERROR: Question \"%s\" on line in input file\n"
                             "had not got \"yes\" case.\n", this_data, file_line);
            free (buffer);
            PAUSE;
        }
        fgets(buffer, 100, input);
        end_position = 0;
    }


    CHECK_NODE(this_node);
    free (buffer);
    return this_node;
}


int play (struct tree_node* node, int line)
{
    if (node -> yes_case == NULL || node -> no_case == NULL)
    {
        print_guess (node -> data);
        printf ("Did Akinator guess your character?\n");
        if (get_yes_no ())
        {
            print_end_guessed ();
            return 0;
        }
        else
        {
            node_insert_question (node, 'usrD', line);
            printf("\n%s... %s...\n", node->yes_case->data, node->data);
            print_end_not_guessed ();
            return 0;
        }
    }
    else
    {
        print_question (node -> data);
        if (get_yes_no ())
        {
            play (node -> yes_case, line);
            return 0;
        }
        else
        {
            play (node -> no_case,  line);
            return 0;
        }
    }
}


int open_main_menu()
{
    system ("clear");

    printf (
"   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _      \n"
" /                                                                           \\   \n"
"         __   _  __   _    _   _    _       __  _______   _____    _____          \n"
"|       /  | | |/ /  | |  / | | |  | |     /  ||__   __| / ___ \\  |  __ \\     | \n"
"       /   | | | /   | | /  | | |__| |    /   |   | |   | /   \\ | | |__| |       \n"
"|     / /| | |   \\   | |/   | |  __  |   / /| |   | |   | |   | | |  ___/     |  \n"
"     / __  | | |\\ \\  |   /| | | |  | |  / __  |   | |   | \\___/ | | |          \n"
"|   /_/  |_| |_| \\_\\ |__/ |_| |_|  |_| /_/  |_|   |_|    \\_____/  |_|         |\n"
"                                                                                  \n"
" \\                                                                           /   \n"
"    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _       \n"
"                                                                                  \n"
"                                CHOSE THE NUMBER:                                 \n"
"                          1. PLAY AKINATOR                                        \n"
"                          2. WATCH THE MAP OF AKINATOR                            \n"
"                          3. COMPARE TWO CHARACTERS                               \n"
"                          4. QUIT                                                 \n"
"                                                                                  \n"
    );

    char answer [10] = "lel";

    while (strcmp (answer, "1") && strcmp (answer, "2") && strcmp (answer, "3") && strcmp (answer, "4"))
    {
        printf ("Enter 1,2,3 or 4: ");
        fgets  (answer, MAX_DATA_LENGTH-1, stdin); answer [strlen (answer) - 1] = '\0';
    }

    if (strcmp(answer, "1") == 0)
    {
        printf("HERE1\n");
        return PLAY_GAME_CASE;
    }
    if (strcmp(answer, "2") == 0)
    {
        return OPEN_TREE_CASE;
    }
    if (strcmp(answer, "3") == 0)
    {
        return COMPARE_CASE;
    }
    if (strcmp(answer, "4") == 0)
    {
        return QUIT_GAME_CASE;
    }

    printf ("ERROR! SKIPPED THE CHECK OF CORRECT ANSWER IN FUNCTION OPEN_MAIN_MENU!\n");
    PAUSE;
}


int seek_character (struct tree_node* root, char* Name, struct return_stack* Answers_stack)
{
    if (root -> no_case != NULL)
    {
        if (seek_character(root -> no_case, Name, Answers_stack))
        {
            push (Answers_stack, 0);
            return 1;
        }

        if (root->yes_case == NULL)
        {
            printf ("Somehow didn't see the wrong structure of a tree!\n");
            DOT_DUMP_TREE_BY_ELEM(root);
            PAUSE;
        }

        if (seek_character(root -> yes_case, Name, Answers_stack))
        {
            push (Answers_stack, 1);
            return 1;
        }

        return 0;
    }
    else
    {
        if (strcasecmp(Name, root->data) == NULL)
            return 1;
        else
            return 0;
    }

    printf ("Somehow didn't see the wrong structure of a tree!\n");
            DOT_DUMP_TREE_BY_ELEM(root);
            PAUSE;
}


#define NEXT_ANSWER( answer_type )                                              \
{                                                                               \
    switch ( answer_type##_answer )                                             \
        {                                                                       \
        case 0:                                                                 \
            {                                                                   \
                answer_type##_cur_node = answer_type##_cur_node->no_case;       \
            }break;                                                             \
        case 1:                                                                 \
            {                                                                   \
                answer_type##_cur_node = answer_type##_cur_node->yes_case;      \
            }break;                                                             \
        default:                                                                \
            {                                                                   \
                printf ("ERROR! Somehow written not 0 or 1 to stack!wqGWer");   \
                PAUSE;                                                          \
            }                                                                   \
        }                                                                       \
}
int Compare (struct tree_node* root, char* first, char* second)
{
    struct return_stack*  FirstGuyAnswers = stack_construct(MAX_BRANCH_LENGTH);
    struct return_stack* SecondGuyAnswers = stack_construct(MAX_BRANCH_LENGTH);

    int not_found_flag = 0;
    if (!seek_character(root, first, FirstGuyAnswers))
    {
        printf ("Sorry, but there was no such character as \"%s\".\n", first);
        not_found_flag++;
    }
    if (!seek_character(root, second, SecondGuyAnswers))
    {
        printf ("Sorry, but there was no such character as \"%s\".\n", second);
        not_found_flag++;
    }
    if (not_found_flag)
        return 0;

    int first_answer  = pop(FirstGuyAnswers);
    struct tree_node* first_cur_node  = root;

    int second_answer = pop(SecondGuyAnswers);
    struct tree_node* second_cur_node = root;

    int eq_flag = 0;
    while (first_answer == second_answer && first_cur_node -> no_case)
    {
        if (!eq_flag)
        {
            eq_flag++;
            if (first_answer)
                printf ("\nBoth %s and %s are %s", first, second, first_cur_node->data);
            else
                printf ("\nBoth %s and %s are not %s", first, second, first_cur_node->data);
        }
        else
        {
            if (first_answer)
                printf (", %s", first_cur_node->data);
            else
                printf (", not %s", first_cur_node->data);
        }

        NEXT_ANSWER (first);
        first_answer = pop(FirstGuyAnswers);

        NEXT_ANSWER (second);
        second_answer = pop(SecondGuyAnswers);
    }


    if (first_cur_node->no_case == NULL)
    {
        printf(".");
        return 0;
    }

    if (eq_flag == 0)
        printf ("%s and %s have nothing in common,\n", first, second);
    else
        printf (",\n");

    printf ("\nbut %s is ", first);
    while (first_cur_node->no_case != NULL)
    {
        if (!first_answer)
            printf ("not ");
        printf("%s, ", first_cur_node->data);

        NEXT_ANSWER (first);
        first_answer = pop(FirstGuyAnswers);
    }

    eq_flag = 0;
    printf ("\naand, %s is", second);
    while (second_cur_node->no_case != NULL)
    {
        if (!second_answer)
            printf (" not");
        printf(" %s,", second_cur_node->data);
        eq_flag = 1;

        NEXT_ANSWER (second);
        second_answer = pop(SecondGuyAnswers);
    }

    if (!eq_flag)
        printf(",");
    printf(" and that's basically it))\n");
    return 0;
}
