

#ifndef _TYPES_H_
#define _TYPES_H_

#include <bitset>

namespace dc{
	namespace type{
		enum class EInstruction: uint8_t{
			nil				= 0x00,
			//@Category: Common Ops
				move		= 0x01,
				test		= 0x02,
				call		= 0x03,
				ret			= 0x04,
				term		= 0x05,
				intr        = 0x06,
			
			//@Category: Arithmetic Ops
				//basic aritmetic ops
				add			= 0x11, sub, mul, div,
				//increase and decrease
				inc			= 0x15, dec,
			//@Category: Jump Ops
				//No-condition Jump
				jmp			= 0x21,
				cmp			= 0x22,
				//Jump by ZF:
				jz			= 0x23, jnz,
				//Jump by CF:
				jc			= 0x25, jnc,
			//@Category: Bit Ops
				band		= 0x31, bor, bnot, bnor, bnand, bxor, //0x36
				lshift		= 0x37, rshift,
			//@Category: Stack Ops
				push		= 0x41, pop,
				
			//@Category: I/O Ops
				in			= 0x51, out,
			//@Category: String Ops
		};
		
		template<typename Enum>
		inline constexpr uint32_t code(Enum evalue){
			return static_cast<uint32_t>(evalue);
		}
		
		enum class ERegister : uint8_t{
			nil=0,	//0x00
			data0 = 0,
			data1,
			result = 0x01,
			data2,	data3,	data4,	data5,
			data6,	data7,	data8,	data9,	data10,
			data11,	data12,	data13,	data14,	data15,	//0x0F
			//flag = 0x0F,
			instruction = 0x10, //0x10
			op1,
			op2,
			op3,
			op4,
			total = 0x20
		};
		
		enum class EUnitType : uint8_t{
			nil = 0,		//0x00
			identi = 0,
			var,			//0x01
			addr,			//0x02
			str,			//0x03
			reg,			//0x04
			relpos,			//0x05
			abspos,			//0x06
		};
		
		enum class EFlag: uint32_t{
			nil = 0,	
			flag = 1,	//0x0001
			zero,		//0x0002
			carry,		//0x0003
			sign,		//0x0004
			direct,		//0x0005
			overflow,	//0x0006
			total
		};
		
		struct TRegisterFrame {
			uint32_t registers[ static_cast<size_t>(ERegister::total) ];
			std::bitset<code(EFlag::total)> flags;
			TRegisterFrame()=default;
			uint32_t& operator[](ERegister reg){ return registers[ static_cast<size_t>(reg) ]; };
			uint32_t& operator[](int pos){ return registers[pos]; };
		};
		
		
		///@Description:
		///>   [          oprand_info          ][ opcode ] 
		///>  31                               8 7        0
		///>   [ op3 ][ op2 ][ op1 ][ op_count ]
		///>  31   26 25  20 19  14 13         8
		///   
		union TInstruction{
			uint32_t code;
			struct  {
				uint32_t opcode: 8;
				uint32_t oprand: 24;
			} common;
			TInstruction()=default;
			
			explicit operator EInstruction(){ return static_cast<EInstruction>(this->common.opcode); };
			
			TInstruction(unsigned int v):code(static_cast<uint32_t>(v)){};
			TInstruction(EInstruction ins, uint32_t op_count = 0, uint32_t op1=0, uint32_t op2=0, uint32_t op3=0){
				code = (op3*(1<<26)+op2*(1<<20)+op1*(1<<14)+
								op_count*(1<<8)+dc::type::code(ins));
			}
			TInstruction(unsigned int b1,unsigned int b2,unsigned b3,unsigned b4){
				code = b1*(1<<24) + b2*(1<<16) + b3*(1<<8) + b4*(1<<0); 
			}
		};
	}
}
#endif  // __TYPES_H_
