

#include "core.h"
#include "except.h"

namespace dc{
	void Core::initialize(std::string config){
		this->conf = config;
	}
	void Core::dump(){
		std::cout<< conf << std::endl;
	}
}
