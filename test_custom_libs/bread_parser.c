#define CROI_LIB_BREAD_PARSER_IMPL_H
#include "../custom_libs/bread_parser.h"

int main(void)
{
    bread_parser_add_option('o', "optional", 0, 0);
    bread_parser_add_option('v', "verbose", 0, 0);

    bread_print_arg();
    return 0;
}
