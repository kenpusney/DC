
#include "Types.hpp"
#include "Engine.hpp"
#include "Dumper.hpp"
#include <cstdio>
namespace dc {
    namespace engine {

        /// determine an instruction's param length(when pos == 0) 
        /// & info(when pos == 1 / 2 / 3).

        size_t param(const TInstruction& ins, int pos = 0) {
            return ( ins.instruct.oprand / (1 << (6 * pos))) & 0x3f;
        }


        DefaultExecutionEngine::DefaultExecutionEngine(Dumper& dmp, TRegisterFrame& registers) :
                mRegisters(&registers),
                mPool(dmp.base()),
                mPC(0),
                mSP(dmp.size()),
                mFP(dmp.size() / 4 * 3),
                mDumper(&dmp) {
        }
        void DefaultExecutionEngine::execute() {
            bool terminated = false;
            while (!terminated) {
                auto ci = TInstruction(mPool[mPC]);
                TInstruction params[4]{ci};
                uint32_t params_info[4]{param(ci)};
                for (int param_position = 1, param_count = params_info[0]; (param_position <= param_count); ++param_position) {
                    ++mPC;
                    params[param_position] = TInstruction(mPool[mPC]);
                    params_info[param_position] = param(params[0], param_position);
                }
                switch (static_cast<EInstruction> (params[0].instruct.opcode)) {
                        //@Category: Common Ops:
                    case EInstruction::move:
                        move(params, params_info);
                        break;
                    case EInstruction::test:
                        test((*mRegisters)[ERegister::R1]);
                        break;
                    case EInstruction::call:
                        call(params, params_info);
                        break;
                    case EInstruction::ret:
                        ret(params, params_info);
                        break;
                    case EInstruction::halt:
                        terminated = true;
                        break;
                        //@Category: Arithmetic Ops:
                    case EInstruction::add:
                        calc2(params, params_info, [](uint32_t x, uint32_t y)->uint32_t {
                            return x + y; });
                        break;
                    case EInstruction::sub:
                        calc2(params, params_info, [](uint32_t x, uint32_t y)->uint32_t {
                            return x - y; });
                        break;
                    case EInstruction::mul:
                        calc2(params, params_info, [](uint32_t x, uint32_t y)->uint32_t {
                            return x*y; });
                        break;
                    case EInstruction::div:
                        calc2(params, params_info, [](uint32_t x, uint32_t y)->uint32_t {
                            return x / y; });
                        break;
                    case EInstruction::inc: case EInstruction::dec:
                        break;
                        //@Category: Jump Ops:
                    case EInstruction::jmp:
                        jump(params, params_info, [](void) ->bool {
                            return true;
                        });
                        break;
                    case EInstruction::cmp:
                        calc2(params, params_info, [](uint32_t x, uint32_t y)->uint32_t {
                            return x - y; });
                        break;
                    case EInstruction::jz:
                        jump(params, params_info,
                                [&]()->bool {
                                    return mRegisters->flags[ uintval(EFlag::zero) ];
                                });
                        break;
                    case EInstruction::jnz:
                        jump(params, params_info,
                                [&]()->bool {
                                    return !mRegisters->flags[ uintval(EFlag::zero) ];
                                });
                        break;
                    case EInstruction::jc:
                        jump(params, params_info,
                                [&]()->bool {
                                    return mRegisters->flags[ uintval(EFlag::carry) ];
                                });
                        break;
                    case EInstruction::jnc:
                        jump(params, params_info,
                                [&]()->bool {
                                    return !mRegisters->flags[ uintval(EFlag::carry) ];
                                });
                        break;
                        //@Category: Bit ops:
                    case EInstruction::band:
                        calc2(params, params_info, [](uint32_t x, uint32_t y)->uint32_t {
                            return x&y; });
                        break;
                    case EInstruction::bor:
                        calc2(params, params_info, [](uint32_t x, uint32_t y)->uint32_t {
                            return x | y; });
                        break;
                    case EInstruction::bxor:
                        calc2(params, params_info, [](uint32_t x, uint32_t y)->uint32_t {
                            return x^y; });
                        break;
                    case EInstruction::bnot:
                        break;
                    case EInstruction::lshift:
                        calc2(params, params_info, [](uint32_t x, uint32_t y)->uint32_t {
                            return x << y; });
                        //@Category: IO Ops:
                    case EInstruction::in:
                        break;
                    case EInstruction::out:
                        if (!params_info[0])
                            std::printf("0x%08x(%d)\n", (*mRegisters)[ERegister::R1], (*mRegisters)[ERegister::R1]);
                        else {
                            uint32_t value = locate(params[1], params_info[1]);
                            std::printf("0x%08x(%d)\n", value, value);
                        }
                        break;
                        //@Category: Stack Ops:
                    case EInstruction::push:
                        push(params, params_info);
                        break;
                    case EInstruction::pop:
                        pop(params, params_info);
                    default:
                        break;
                }
                mPC++;
            }
        }

        void DefaultExecutionEngine::calc2(TInstruction* params, uint32_t* params_info, std::function<uint32_t(uint32_t, uint32_t) > fun) {
            auto pcount = param(TInstruction(params[0]));
            auto ploc = static_cast<EUnitType> (params_info[1]);
            if (pcount >= 2) {
                uint32_t v[3]{0};
                for (int pos = 1; pos <= 3; ++pos) {
                    v[pos] = locate(params[pos], params_info[pos]);
                }
                v[0] = fun(v[1], v[2]);
                test(v[0]);
                // Where to put result?
                if (params_info[3]) {
                    locate(params[3], params_info[3]) = v[0];
                } else if (ploc == EUnitType::identi ||
                        ploc == EUnitType::abspos ||
                        ploc == EUnitType::relpos) {
                    (*mRegisters)[ ERegister::R1 ] = v[0];
                } else {
                    locate(params[1], params_info[1]) = v[0];
                }
            }
            return;
        }

        void DefaultExecutionEngine::jump(TInstruction* params, uint32_t* params_info, std::function<bool() > condition) {
            if (condition()) {
                if (static_cast<EUnitType> (params_info[1]) == EUnitType::relpos)
                    mPC += static_cast<int> (params[1].value);
                else {
                    mPC = locate(params[1], params_info[1]);
                }
            }
        }

        void DefaultExecutionEngine::move(TInstruction* params, uint32_t* params_info) {
            auto pcount = param(TInstruction(params[0]));
            if (pcount == 2) {
                uint32_t v[3]{0};
                for (int pos = 1; pos <= 3; ++pos) {
                    v[pos] = locate(params[pos], params_info[pos]);
                }
                if (params_info[2]) {
                    locate(params[2], params_info[2]) = v[1];
                } else {
                    (*mRegisters)[ ERegister::R1 ] = v[1];
                }
            }
        }

        void DefaultExecutionEngine::call(TInstruction* params, uint32_t* params_info) {
            mPool[mFP + mFC] = mPC;
            ++mFC;
            if (static_cast<EUnitType> (params_info[1]) == EUnitType::relpos)
                mPC += static_cast<int> (params[1].value);
            else {
                mPC = locate(params[1], params_info[1]);
            }
        }

        void DefaultExecutionEngine::ret(TInstruction* params, uint32_t* params_info) {
            if (mFC > 0) {
                mPC = mPool[mFP + mFC - 1];
                mFC--;
            }
        }

        void DefaultExecutionEngine::push(TInstruction* params, uint32_t* params_info) {
            auto pcount = param(TInstruction(params[0]));
            if (pcount == 1) {
                mPool[mSP--] = locate(params[1], params_info[1]);
            }
        }

        void DefaultExecutionEngine::pop(TInstruction* params, uint32_t* params_info) {
            auto pcount = param(TInstruction(params[0]));
            if (pcount == 1) {
                locate(params[1], params_info[1]) = mPool[++mSP];
            }
        }

        void DefaultExecutionEngine::test(uint32_t v) {
            if (v == 0)
                mRegisters->flags[ uintval(EFlag::zero) ] = 1;
            else
                mRegisters->flags[ uintval(EFlag::zero) ] = 0;
            if (static_cast<int>(v) < 0)
                mRegisters->flags[ uintval(EFlag::carry) ] = 1;
            else
                mRegisters->flags[ uintval(EFlag::carry) ] = 0;
        }

        uint32_t& DefaultExecutionEngine::locate(TInstruction& param, uint32_t& info) {
            switch (static_cast<EUnitType> (info)) {
                case EUnitType::identi: // an identified number (e.g. 123)
                case EUnitType::abspos: // a symbol position (e.g. @fun)
                    return param.value;
                    //case EUnitType::relpos:	// a relative address given by symbol or number(e.g \02 \05)
                    //	return 	mPC+=static_cast<int>(param.code);
                case EUnitType::addr: // an address given by symbol or number (e.g. &fun &123)
                    return mPool[ param.value ];
                case EUnitType::reg: // a register name  (e.g. R1)
                    return (*mRegisters) [ param.value ];
                case EUnitType::var: // a var location using registers (e.g. $R1)
                    return mPool[ (*mRegisters)[ param.value] ];
                default:
                    return this->EYE;
            }
        }

    }
}
