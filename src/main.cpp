#include "Engine.hpp"
#include "Dumper.hpp"
#include "Types.hpp"

int main(int argc, char* argv[]) {

    // Or you can use your own Dumper and Execution Engine.
    dc::dump::BCDumper d;
    dc::type::TRegisterFrame frame;
    if (argc > 1)
        d.load(argv[1]);
    else
        d.load("C:\\a.out");
    dc::engine::DefaultExecutionEngine e{d, frame};
    e.execute();
    return 0;
}
