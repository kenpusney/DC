
## 2013-09-24

  + 加入 intr(中断) 指令，未实现。
  + 实现 dctrans 功能及 constant.yml 可配置
  + 实现 dc::dump::Dumper 模块，用来提供可随机访问的存储器接口。


## 2013-09-29

  + 实现 Jump Category 系列指令(jmp, jz, jnz, jc, jnc)
  + FIX: 非二进制模式打开文件，dctrans会在写入\x0a( "\n" )的时候
  	同时写入为\x0d\x0a( "\r\n" )

## 2013-11-18

  + 实现 symbol_mark, Jump Category 系列指令可以直接通过相应的 mark
    来跳转到对应位置

## 2013-11-19

  + 实现 `call` 和 `ret` 指令。同时对递归和嵌套调用提供支持。

