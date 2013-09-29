
#include "engine.h"
#include <cstdio>
namespace dc{
	namespace engine{
		
		using TI=TInstruction;
		using EI=EInstruction;
		using ER=ERegister;
		using EUT=EUnitType;
		using uint=uint32_t;

	    size_t param(TI ins,int pos=0){
			return  ( ins.common.oprand / (1<<(6*pos)) ) & 0x3f;  
		}

		void TEngine::execute(){
			bool iterminate = false;
			while(!iterminate){
				auto cinstr = TI(mPool[mPC]);
				TI params[4]{ cinstr };
				uint params_info[4]{ param(cinstr) };
				for( int ppos = 1, pcount = params_info[0]; (ppos <= pcount);++ppos) {
					++mPC;
					params[ppos] = TI(mPool[mPC]);
					params_info[ppos] = param( params[0], ppos );
				}
				switch(static_cast<EI>(params[0].common.opcode)){
				//@Category: Common Ops:
					case EI::move:
						move( params, params_info );
						break;
					case EI::test:
						test(mRegisters[ER::data1]);
						break;
					case EI::call:
						break;
					case EI::ret:
						break;
					case EI::term:
						iterminate = true;
						break;
				//@Category: Arithmetic Ops:
					case EI::add:
						calc2(params, params_info, [](uint x, uint y)->uint{ return x+y; }) ;
						break;
					case EI::sub:
						calc2(params, params_info, [](uint x, uint y)->uint{ return x-y; }) ;
						break;
					case EI::mul:
						calc2(params, params_info, [](uint x, uint y)->uint{ return x*y; }) ;
						break;
					case EI::div:
						calc2(params, params_info, [](uint x, uint y)->uint{ return x/y; }) ;
						break;
					case EI::inc: case EI::dec:
						break;
				//@Category: Jump Ops:
					case EI::jmp:
						jump(params, params_info, [](void)->bool{ return true;} );
						break;
					case EI::cmp:
						calc2(params, params_info, [](uint x, uint y)->uint{ return x-y; });
						break;
					case EI::jz: 
						jump(params, params_info, 
								[&]()->bool{ 
									return mRegisters.flags[ code(EFlag::zero) ];
								} );
						break;
					case EI::jnz: 
						jump(params, params_info, 
								[&]()->bool{ 
									return !mRegisters.flags[ code(EFlag::zero) ];
								} );
						break;
					case EI::jc: 
						jump(params, params_info,
								[&]()->bool{ 
									return mRegisters.flags[ code(EFlag::carry) ];
								} );
						break;
					case EI::jnc:
						jump(params, params_info, 
								[&]()->bool{ 
									return !mRegisters.flags[ code(EFlag::carry) ];
								} );
						break;
				//@Category: Bit ops:
					case EI::band:
						calc2(params, params_info, [](uint x, uint y)->uint{ return x&y; });
						break;
					case EI::bor:
						calc2(params, params_info, [](uint x, uint y)->uint{ return x|y; });
						break;
					case EI::bxor:
						calc2(params, params_info, [](uint x, uint y)->uint{ return x^y; });
						break;
					case EI::bnot:
						break;
					case EI::lshift:
						calc2(params, params_info, [](uint x, uint y)->uint{ return x<<y; });
				//@Category: IO Ops:
					case EI::in:
						break;
					case EI::out:
						if( ! params_info[0] )
							std::printf("0x%08x(%d)\n", mRegisters[ER::data1], mRegisters[ER::data1]);
						else{
							uint value;
							switch ( static_cast<EUT>(params_info[1])){
								case EUT::identi:
									value = params[1].code;
									break;
								case EUT::addr:
									value = mPool[ params[1].code];
									break;
								default:
									value = 0;
							}
							std::printf("0x%08x(%d)\n", value, value);
						}
						break;
					default:
						break;
				}
				mPC++;
			}
		}
		
		void TEngine::calc2(TI* params,uint* params_info, std::function<uint(uint,uint)> fun){
			auto pcount = param( TI(params[0]) );
			if( pcount >= 2 ){
				uint v[3] {0};
				for(int pos=1;pos<=3;++pos){
					switch( static_cast<EUT>(params_info[pos]) ){
						case EUT::identi:
							v[pos] = params[pos].code;
							break;
						case EUT::addr:
							v[pos] = mPool[ params[pos].code ];
							break;
						case EUT::reg:
							v[pos] = mRegisters [ params[pos].code ];
							break;
						default:
							v[pos] = 1;
					}
				}
				v[0] = fun(v[1],v[2]);
				test(v[0]);
				if( static_cast<EUT>(params_info[3]) == EUT::addr && params[3].code != 0 ){
					mPool[ params[3].code ] = v[0];
				}else{
					mRegisters[ ER::data1 ] = v[0];
				}
			}
			return;
		}
		
		void TEngine::jump(TI* params, uint* params_info, std::function<bool()> condition){
			if( condition() ){
				mPC += static_cast<int>(params[1].code);
			}
		}
		
		void TEngine::move(TI* params, uint* params_info){
			
		}
		
		void TEngine::test(uint v){
			if ( v == 0 )
				mRegisters.flags[ code(EFlag::zero) ] = 1;
			else
				mRegisters.flags[ code(EFlag::zero) ] = 0;
			if ( int(v) < 0)
				mRegisters.flags[ code(EFlag::sign) ] = 1;
			else
				mRegisters.flags[ code(EFlag::sign) ] = 0;
		}
	}
}
