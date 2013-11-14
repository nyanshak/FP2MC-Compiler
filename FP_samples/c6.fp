CONSTANTS

FUNCTIONS

MAIN
{read val}
{ if {< val 0}
  then {= retval -1}
  else {= retval 1}
       { while {> val 0}
          {= retval {* retval val}}
          {= val {- val 1}}
       }
}
{print (Factorial of) val (is) retval}
