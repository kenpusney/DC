#ifndef DUMPER_H
#define DUMPER_H


#include <string>
namespace dc {
    namespace dump {
        
        // Dumper Interface
        class IDumper{
        public:
            virtual ~IDumper(){};
            virtual uint32_t  fetch() = 0;
            virtual uint32_t* seek(size_t position) = 0;
            virtual uint32_t  next() = 0;
            virtual uint32_t  select(size_t position) = 0;
            virtual void      move(size_t position) = 0;
            virtual uint32_t  size() = 0;
            virtual uint32_t* base() = 0;
        };

        // Byte-Code dumper
        class BCDumper : public IDumper{
        public:
            BCDumper() = default;
            ~BCDumper();
            uint32_t fetch() override;
            uint32_t* seek(size_t position) override;
            uint32_t next() override;
            uint32_t select(size_t position) override;
            void load(std::string filename);
            void move(size_t position) override;
            uint32_t* base() override;

            size_t size() override {
                return (2 << 16);
            }
        private:
            uint32_t* mContent = nullptr;
            uint32_t* mCurrent = nullptr;
            BCDumper(const BCDumper&);
            BCDumper& operator=(const BCDumper&);
            void release();
        };
    }
}
#endif
