
#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "core.h"
#include "dumper.h"
#include <functional>

using TDumper=dc::dump::TDumper;
namespace dc{
	namespace engine{
		using namespace dc::type;

		size_t param(TInstruction ins, int pos);

		class TEngine{
			public:
				void execute();
				TEngine() = default;
				TEngine(TDumper& dmp):mPool(dmp.base()),mDumpSpace(&dmp),mPC(0){};
			private:
				TRegisterFrame mRegisters;
				uint32_t *mPool;	// 64KB(2<<16) is enough for everyone.
				uint32_t mPC;
				TDumper* mDumpSpace;
				void calc2(TInstruction* params,uint32_t* params_info, 
						std::function<uint32_t(uint32_t,uint32_t)> fun);
				void test(uint32_t value);
				void jump(TInstruction* params,uint32_t* params_info,
						std::function<bool()>);
				void move(TInstruction* params,uint32_t* params_info);
		};
	}
}

#endif
