DumpCore Virtual Machine Specification (version 0.0)
===========

  * author: Kim Leo <kenpusney@outlook.com>

## Why DumpCore?

DumpCore是一个基于x86架构模型设计的寄存器虚拟机。所有基础思想都来源于
Intel(R) x86的相应内容。目前的设计目的是为了模拟计算机的基本原理和实
现一个简易的操作系统。

DumpCore使用C++等编程语言实现，组件化，可配置，并有不错的跨平台可移
植性。

## Structure

     ========== 
    |          |   ----> dcasm, the assembly language.
    |          |   ----> dctrans, the assembler(written in Ruby).
    | DumpCore |   ----> the DC::Engine.
    |          |   ----| the DC::Lib.
    |          |   ----| the DC::InterCom.
     ==========

### Components

#### dcasm

`dcasm`是一个基于

#### dctrans

`dctrans`是一个使用Ruby实现的dcasm-instruction -> dc-bytecode的翻译
程序。指令集等各个组件可以通过`constant.yml`文件来进行配置。

使用方法：
    dctrans <asm-file> [<target-file>]

#### DC::Engine

  * General Registers * 16;
  * Arithmetic Logic Unit(the Engine);

#### DC::Lib

  * Libraries for modern programming language.

#### DC::InterCom

### Bits
  
  * See doc/instructions.md
