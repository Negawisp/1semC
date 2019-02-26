#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "Akinator.h"

int main()
{

    FILE* save = fopen("save.txt", "rb");
    struct tree_node* root     = load_akinator (save, __LINE__, 0);
    fclose (save);

    branch_check (root, __LINE__);
    int what_to_do = 'nthing';


    do
    {
        what_to_do = open_main_menu();
        system("clear");

        switch (what_to_do)
        {
        case PLAY_GAME_CASE:
            {
                do
                {
                    system("clear");

                    branch_check(root, __LINE__);
                    play (root, __LINE__);
                    printf("\n\nPlay again?\n");
                }while (get_yes_no());
            }break;

        case OPEN_TREE_CASE:
            {
                DOT_TREE_BY_ELEM (root);
            }break;

        case COMPARE_CASE:
            {
                do
                {
                    system("clear");

                    char character1 [50] = {};
                    char character2 [50] = {};

                    printf("Type in the first character: ");
                    fgets (character1, sizeof(character1), stdin); character1 [strlen(character1) - 1] = '\0';
                    printf("And now the second character: ");
                    fgets (character2, sizeof(character2), stdin); character2 [strlen(character2) - 1] = '\0';

                    Compare(root, character1, character2);
                    //Compare (root, "IIyTuH", "CTEIIyIIIuH");

                    printf("\n\nDo it again?)\n");
                }while (get_yes_no());
            }break;

        case QUIT_GAME_CASE:
            break;

        default:
            {
                printf ("SOMEBOY SKIPPED TWO CHECKS OF correctness of choise of user!!\n"
                        "(while showing the main menu)");
                PAUSE;
            }break;
        }

    }while (what_to_do != QUIT_GAME_CASE);

    save = fopen("save.txt", "wb");
    save_progress (save, root, 0, __LINE__);
    fclose (save);

    branch_check  (root, __LINE__);
    branch_remove (root, __LINE__);
    return 0;
}
