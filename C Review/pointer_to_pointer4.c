#include <stdio.h>

void foo(char* const* s) {

}

int main(void) {
    char* p;
    foo(&p);

    return 0;
}
