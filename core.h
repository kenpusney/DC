

#ifndef __CORE_H__
#define __CORE_H__

#include <string>
#include <iostream>
#include "types.h"
namespace dc{
	class Core{
		public:
			void initialize(std::string config);
			Core():Core("boot.conf"){};
			Core(std::string config):conf(config){};
			void dump();
		private:
			std::string conf;
	};
}

#endif //__CORE_H__
