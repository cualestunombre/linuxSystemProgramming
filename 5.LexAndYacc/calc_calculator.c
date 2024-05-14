#include <stdio.h>
#include "calc_yacc.tab.h"

int main() {
    while (1) {
        yyparse();
    }
    return 0;
}
