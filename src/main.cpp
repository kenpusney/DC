#include "engine.h"
#include "dumper.h"
#include <iostream>

int main(int argc, char* argv[]) {

    // Or you can use your own Dumper and Execution Engine.
    dc::dump::BCDumper d;
    if (argc > 1)
        d.load(argv[1]);
    else
        d.load("a.out");
    dc::engine::DefaultExecutionEngine e{d};
    e.execute();
    return 0;
}
