#include <stdio.h>
#include <stdlib.h>

int get_chars_quantity (FILE* file)
{
    int cur_pos = ftell (file);
    fseek (file, 0, SEEK_END);
    int Chars_Quantity = ftell (file);
    fseek (file, cur_pos, SEEK_SET);
    return Chars_Quantity;
}

int main()
{
    FILE* input = fopen ("in.txt", "rb");
    int chars_quantity = get_chars_quantity(input);

    char* buffer = calloc (chars_quantity + 1, sizeof(char));
    fread (buffer, sizeof(char), chars_quantity, input);
    return 0;
}
