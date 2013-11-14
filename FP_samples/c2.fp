 CONSTANTS {errorval -  1} {minval 0} {unit 1}
           { msgfac (Factorial of) }  { msgis (is) } {newl (\n)}

 FUNCTIONS

 { factorial val return retval
   { if {< val minval}
     then {= retval errorval}
     else {= retval 1}
          { while {> val minval}
             {= retval {* retval val}}
             {= val {- val unit}}
          }
   }
 }

 { printfac inval facval return pfnone
   {print msgfac inval msgis facval newl}
   {= pfnone 1}
 }

 MAIN
 {print (Enter the number of rounds you want to run this program )}
 {read numround}
 {= numrnd numround}
 {loop numrnd
     {read x continue}
     {= f {factorial x}}
     {= pfac {printfac x f}}
 }
