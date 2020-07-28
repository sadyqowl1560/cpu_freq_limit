//headers and global_variables
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "animation.h"
#include "output.h"
#include "work.h"
int nav_checker ;
char reader  ;
#include "nav.h"
//functions_delecrations

//main_function
int main()
{
//declerations
//
part0 :
    outputs() ;
    all_nav() ;
    if (nav_checker == 0 )
      goto part0 ;
// #1
      if (reader == '1'){
       output1() ;
       all_nav() ;
       if (nav_checker == 0 )
        goto part0 ;
       work_status(reader) ;
       sleep (1) ;
       goto part0 ;
      }
// #1
//
//#2
     else if (reader == '2'){
       output2() ;
       all_nav() ;
       if (nav_checker == 0 )
        goto part0 ;
       work_setconfig(reader) ;
       sleep (1) ;
       goto part0 ;
//#2
    }
    return 0;
}
