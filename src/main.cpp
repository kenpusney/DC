#include "core.h"
#include "engine.h"
#include "dumper.h"
#include <iostream>
int main(){
	dc::dump::TDumper d;
	d.load("a.out");
	dc::engine::TEngine e{d};
	e.execute();
}
