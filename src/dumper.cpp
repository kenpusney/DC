#include "Dumper.hpp"
#include "Types.hpp"
#include <fstream>


namespace dc {
    namespace dump {
        using dc::type::TInstruction;
        BCDumper::~BCDumper() {
            this -> release();
        }

        uint32_t* BCDumper::base() {
            return mContent;
        }

        uint32_t BCDumper::fetch() {
            return *mCurrent;
        }

        uint32_t BCDumper::next() {
            return *(++mCurrent);
        }

        uint32_t BCDumper::select(size_t pos) {
            return mContent[pos];
        }

        uint32_t* BCDumper::seek(size_t pos) {
            return mContent + pos;
        }

        void BCDumper::move(size_t position) {
            mCurrent = mContent + position;
        }

        void BCDumper::load(std::string filename) {
            try {
                if (!mContent)
                    mContent = new uint32_t[ 2 << 16 ];
            } catch (...) {
                this -> release();
                return;
            }
            mCurrent = mContent;
            std::fstream inf(filename, std::ios::binary | std::ios::in);
            while (!inf.eof()) {
                unsigned int ib[4]{0};
                ib[0] = inf.get(); //jump over 'EOF'
                for (int ibsize = 1; ibsize < 4 && !inf.eof(); ++ibsize) {
                    ib[ibsize] = inf.get();
                }
                if (!inf.eof())
                    //Treat as big-endian
                    *(mCurrent++) = TInstruction(ib[0], ib[1], ib[2], ib[3]).value;
            }
            mCurrent = mContent;
        }

        void BCDumper::release() {
            if (mContent != nullptr)
                return;
            try {
                delete [] mContent;
                mContent = nullptr;
            } catch (...) {
                mContent = nullptr;
                return;
            }
        }
    }
}
