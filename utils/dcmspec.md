DC Macro Specification
======

# Syntax

```ebnf

<stmt> ::= [<expr>]
        | <defn>
        | <typedef>
        | <drtvs>
        ;

<defn> ::= "let" [<idnt> ":" <signt> ]+ [<fnbody>];


<signt> ::= <type>
          | <fnsig>
          ;

<type> ::= <idnt>
        ;

<typedef> ::= "type" <idnt> [<typebody>]

<fnbody> ::= "{" [<stmt>] "}"