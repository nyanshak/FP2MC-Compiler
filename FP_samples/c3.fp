
CONSTANTS 
{stra(A)} {strb(B)} {strc(C)} {strd(D)} {stre(E)} {strf(F)} {strg(G)}
{strh(H)} {stri(I)} {strj(J)} {strk(K)} {strl(L)}
{newl (\n)}
  
FUNCTIONS
{printa prvala return pranone 
  {print (value of ) stra ( is ) prvala (\n)} {=pranone1}
}
{printb prvalb return prbnone 
  {print (value of ) strb ( is ) prvalb (\n)} {=prbnone1}
}
{printc prvalc return prcnone 
  {print (value of ) strc ( is ) prvalc (\n)} {=prcnone1}
}
{printd prvald return prdnone 
  {print (value of ) strd ( is ) prvald (\n)} {=prdnone1}
}
{printe prvale return prenone 
  {print (value of ) stre ( is ) prvale (\n)} {=prenone1}
}
{printf prvalf return prfnone 
  {print (value of ) strf ( is ) prvalf (\n)} {=prfnone1}
}
{printg prvalg return prgnone 
  {print (value of ) strg ( is ) prvalg (\n)} {=prgnone1}
}
{printh prvalh return prhnone 
  {print (value of ) strh ( is ) prvalh (\n)} {=prhnone1}
}
{printi prvali return prinone 
  {print (value of ) stri ( is ) prvali (\n)} {=prinone1}
}
{printj prvalj return prjnone 
  {print (value of ) strj ( is ) prvalj (\n)} {=prjnone1}
}
{printk prvalk return prknone 
  {print (value of ) strk ( is ) prvalk (\n)} {=prknone1}
}
{printl prvall return prlnone 
  {print (value of ) strl ( is ) prvall (\n)} {=prlnone1}
}

{printall va vb vc vd ve vf vg vh vi vj vk return pall
  { print (From printall) stra va strb vb strc vc strd vd stre ve
          strf vf strg vg strh vh stri vi strj vj strk vk newl}
  {=pall {+ va vb vc vd ve vf vg vh vi vj vk}}
}

{justfortest val return retval
  {= abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz val}
  {= retval abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz }
  {= vala {** - 10}}
  {= valb {/ -  36  0.4}}
  {= valc {* -   5.0 -16}}
  {= vald {* -7 -   10.0}}
  {= temp 5}
  {= vale {+{+{+{+{+ {+{+{+{+{+ {+ temp temp}
                     temp}temp}temp}temp}temp}
                     temp}temp}temp}temp}temp} }
  {= valf {-  25 -  25.0}}
  {= valg {--  10 -50}}
  {= valh 30}
  {= temp 1}
  {= vali {+temp temp temp temp temp  temp temp temp temp temp}}
  {= valj 10}
  {= valk {* 0.0 1 2 3 4 5 6 7 8 9 -10 }}
  {      if {>= val vala} then {= retval {+ retval vala}} {= jta {printa vala}}
   else {if {>= val valb} then {= retval {+ retval valb}} {= jtb {printb valb}}
   else {if {>= val valc} then {= retval {+ retval valc}} {= jtc {printc valc}}
   else {if {>= val vald} then {= retval {+ retval vald}} {= jtd {printd vald}}
   else {if {>= val vale} then {= retval {+ retval vale}} {= jte {printe vale}}
   else {if {>= val valf} then {= retval {+ retval valf}} {= jtf {printf valf}}
   else {if {>= val valg} then {= retval {+ retval valg}} {= jtg {printg valg}}
   else {if {>= val valh} then {= retval {+ retval valh}} {= jth {printh valh}}
   else {if {>= val vali} then {= retval {+ retval vali}} {= jti {printi vali}}
   else {if {>= val valj} then {= retval {+ retval valj}} {= jtj {printj valj}}
   else {if {>= val valk} then {= retval {+ retval valk}} {= jtk {printk valk}}
   else {= retval 0} {= jtl {printl val}}
  } }}}}} }}}}}
  {= retpall {printall vala valb valc vald vale valf valg valh vali valj valk}}
  {print (Returned value from printall is ) retpall newl}
  {= retpall {+{+{+{+{+ {+{+{+{+{+ {+ retpall vala}
                        valb}valc}vald}vale}valf} valg}valh}vali}valj}valk}}
  {print (Locally computed sum of all values is ) retpall newl}
}

{justforwhile wva wvb wvc wvd wve wvf wvg wvh wvi wvj
 return wret

  {= wret 0}
  {while {> wva 0} {= wret {+ wret 1}} {= wva {- wva 1}} 
   {while {> wvb 0} {= wret {+ wret 1}} {= wvb {- wvb 1}} 
    {while {> wvc 0} {= wret {+ wret 1}} {= wvc {- wvc 1}} 
     {while {> wvd 0} {= wret {+ wret 1}} {= wvd {- wvd 1}} 
      {while {> wve 0} {= wret {+ wret 1}} {= wve {- wve 1}} 
            {while {> wvf 0} {= wret {+ wret 1}} {= wvf {- wvf 1}} 
             {while {> wvg 0} {= wret {+ wret 1}} {= wvg {- wvg 1}} 
              {while {> wvh 0} {= wret {+ wret 1}} {= wvh {- wvh 1}} 
               {while {> wvi 0} {= wret {+ wret 1}} {= wvi {- wvi 1}} 
                {while {> wvj 0} {= wret {+ wret 1}} {= wvj {- wvj 1}} 
  }}}}}     }}}}}
 
}

MAIN
{print (How many rounds do you want to try justfortest  )}
{read numrounds}
{loop numrounds
  { print (Input an integer or a float value for test )}
  { read tt }
  {= jft {justfortest tt}}
  {print (Just for test for ) tt (is ) jft newl} 
}
{print (How many rounds do you want to try justforwhile  )}
{read numrounds}
{loop numrounds
  { print (Input 10 integer or float values for test )}
  { read tta ttb ttc ttd tte ttf ttg tth tti ttj }
  {= jfw {justforwhile tta ttb ttc ttd tte ttf ttg tth tti ttj}}
  {print (Just for while has return value ) jfw newl} 
}

