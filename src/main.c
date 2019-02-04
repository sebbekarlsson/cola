#include <stdio.h>
#include <stdlib.h>
#include "includes/eval.h"


scope* global_scope;

int main(int argc, char* argv[]) { 
    return eval_file_contents(argv[1], &global_scope);
};
