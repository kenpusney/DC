#include "dumper.h"
#include <fstream>


using TI = dc::type::TInstruction;
namespace dc{
	namespace dump{
		TDumper::~TDumper(){
			this -> release();
		}

		uint32_t* TDumper::base(){
			return mContent;
		}

		uint32_t TDumper::fetch(){
			return *mCurrent;
		}

		uint32_t TDumper::next(){
			return *(++mCurrent);
		}

		uint32_t TDumper::select(size_t pos){
			return mContent[pos];
		}
		
		uint32_t* TDumper::seek(size_t pos){
			return mContent+pos;
		}

		void TDumper::move(size_t position){
			mCurrent = mContent+position;
		}
		
		void TDumper::load(std::string filename){
			try{
				if(!mContent)
					mContent = new uint32_t[ 2 << 16 ];
				else
					return;
			}catch(...){
				this -> release();
				return;
			}
			mCurrent = mContent;
			std::fstream inf( filename, std::ios::binary | std::ios::in );
			while( !inf.eof() ){
				unsigned int ib[4] {0};
				for(int ibsize = 0; ibsize < 4 && !inf.eof();++ibsize){
					ib[ibsize] = inf.get();
				}
				//Treat as big-endian
				*(mCurrent++) = TI(ib[0],ib[1],ib[2],ib[3]).code;
			}
			mCurrent = mContent;
		}
		
		void TDumper::release(){
			if ( mContent != nullptr )
				return;
			try{
				delete [] mContent;
				mContent = nullptr;
			}catch(...){
				mContent = nullptr;
				return;
			}
		}
	}
}
