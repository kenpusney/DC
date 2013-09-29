#ifndef DUMPER_H
#define DUMPER_H

#include "core.h"
#include <string>
namespace dc{
	namespace dump{
		class TDumper{
			public:
				TDumper()=default;
				~TDumper();
				uint32_t fetch();
				uint32_t* seek(size_t position);
				uint32_t next();
				uint32_t select(size_t position);
				void load(std::string filename);
				void move(size_t position);
				uint32_t* base();
			private:
				uint32_t* mContent = nullptr;
				uint32_t* mCurrent = nullptr;
				TDumper(const TDumper&);
				TDumper& operator=(const TDumper&);
				void release();
		};
	}
}
#endif
