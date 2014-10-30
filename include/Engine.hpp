
#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <functional>

namespace dc {
    namespace dump{
        struct IDumper;
    }

    namespace type{
        union TInstruction;
        struct TRegisterFrame;
    }

    namespace engine {
        using namespace dc::type;
        using Dumper = dc::dump::IDumper;

        size_t param(const TInstruction& ins, int pos);

        class IExecutionEngine{
            virtual void execute() = 0;
        };
        class DefaultExecutionEngine: IExecutionEngine {
        public:
            void execute();
            DefaultExecutionEngine() = default;
            DefaultExecutionEngine(Dumper& dmp, TRegisterFrame& registers);
        private:
            TRegisterFrame *mRegisters;
            uint32_t *mPool; // 512KB(2<<16) is enough for everyone.
            uint32_t mPC; // Program Counter
            uint32_t mSP; // Stack Pointer
            const uint32_t mFP; // Function Pointer
            uint32_t mFC = 0; // Function Counter
            uint32_t EYE = 1; // IDENTIFICATION NUMBER
            Dumper* mDumper;

            // Binary calculation
            void calc2(TInstruction* params, uint32_t* params_info,
                    std::function<uint32_t(uint32_t, uint32_t) > fun);
            void test(uint32_t value);
            void jump(TInstruction* params, uint32_t* params_info,
                    std::function<bool()>);
            void move(TInstruction* params, uint32_t* params_info);

            void call(TInstruction* params, uint32_t* params_info);
            void ret(TInstruction* params, uint32_t* params_info);
            void push(TInstruction* params, uint32_t* params_info);
            void pop(TInstruction* params, uint32_t* params_info);

            // Locations
            uint32_t& locate(TInstruction& param, uint32_t& info);
        };
    }
}

#endif // __EIGINE_H__
