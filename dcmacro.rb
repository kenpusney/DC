#!/usr/bin/env ruby

=begin

=Structure:

	Code
	-> Instruction
	-> InstructionSequence
	-> Conditional
		-> Repeated
	-> Iterating
	-> Callable

=Syntax:

	i("move 2,&1")
	
	cond(i("cmp &1,&2")) { |args|
		<...>
	} .or_else { |args|
		<...>
	}
	
	repeat { |args|
		<...>
	} .to {
		<...>
	} 
=end


class Code
	attr_reader :code
	attr_reader :count
	def initialize()
		@code = []
	end
	def append(c)
		code << c
	end
	def unshift(c)
		code.unshift c
		@count += c.count
	end
end

class Instruction < Code
	attr_reader :ins
	def initialize(ins)
		super()
		@ins = ins
		@code << ins
	end
	undef count
	def count
		return ins.split(',').length + 1
	end
end

class InstructionSequence < Code

end

class Condition < Code
	def cond(iset)

	end
	def or_else(&block)
		yield
	end
end

class Loop < Code

end


def s2n(sym)
	if sym =~ /^_(0[bxo]?)?[a-fA-F0-9]+$/
		eval sym.to_s.sub(/_/,"")
	else
		nil
	end
end