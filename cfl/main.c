#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "mycustom_functions.h"
int main()
{
    ///////////////////////////// constant /////////////////////////////////////////////
    const char thermal_dir[] ="/sys/devices/virtual/thermal/thermal_zone11/temp" ;
    const char freq_limit_dir[] ="/sys/power/cpufreq_max_limit" ;
    const char data_file[] ="/data/cfl_config.txt" ;
    const char temp_prop[] ="cpufreq.limit.dtempa" ;
    const char freq_prop[] ="cpufreq.limit.freqv" ;
    const char temp_default_prop[] ="cpufreq.limit.dtempa.default" ;
    const char freq_default_prop[] ="getprop cpufreq.limit.freqv.default" ;
    ///////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////// variables //////////////////////////////////////////////
    char* concater ,* temp_avg ,*temp_reader , * freq_limit;
    int  avg ,total ,counter,temp[5],determined_avg_number ;
    char nochain[] = "-1" ;
    ///////////////////////////////////////////////////////////////////////////////////
    temp_avg = (char*)malloc(2*sizeof(char));
    freq_limit = (char*)malloc(7*sizeof(char));
    //
    temp_reader = (char*)malloc(2*sizeof(char));


   // char tempv[2] , freqv[7] , chain[7] , determined_avg[2] , nochain[] = "-1" , temp_c[2] ;
    ////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// setup_cfl 0 //////////////////////////////////////////////
    //
    check_shell_pushlog(system("setprop cpufreq.limit.status 1"),"E0",-1)  ;
    read_file_content(freq_limit_dir,"r") ;
    ////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////// setup_cfl 1 //////////////////////////////////////////////
    //////////cfl_temp_fix///////////////
    concater = NULL ;
    concater = concat("cat ", data_file) ;
    concater = concat(concater , " |grep \"") ;
    concater = concat(concater , temp_prop) ;
    concater = concat(concater , "\" |grep -o [0-9][0-9]") ;
    //
    strcpy(temp_avg , get_commandr(concater)) ;
    //
    concater = NULL ;
    concater = concat("setprop ",temp_prop) ;
    concater = concat(concater , " ") ;
    concater = concat(concater , temp_avg) ;
    check_shell_pushlog(system(concater),"E1",-1) ;
    //////////cfl_freq_fix///////////////
    concater = NULL ;
    concater = concat("cat ", data_file) ;
    concater = concat(concater , " |grep \"") ;
    concater = concat(concater , freq_prop) ;
    concater = concat(concater , "\" |grep -o [0-9][0-9][0-9][0-9][0-9][0-9][0-9]") ;
    //
    strcpy(freq_limit, get_commandr(concater)) ;
    //
    concater = NULL ;
    concater = concat("setprop ", freq_prop) ;
    concater = concat(concater , " ") ;
    concater = concat(concater , freq_limit) ;
    check_shell_pushlog(system(concater),"E2",-1) ;
    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////

    while(1) {
      /////////////////////////////////////////////
      // (2) setup_cfl 2
      /////////////// (1) TEMP/////////////////////
      concater = NULL ;
      concater = concat("getprop ", temp_prop) ;
      if (check_shell_pushlog(system(concater),"E3",0) != 0)
      {
      concater = NULL ;
      concater = concat("getprop ", temp_default_prop) ;
      strcpy(temp_avg , get_commandr(concater)) ;
      }else{
      strcpy(temp_avg , get_commandr(concater)) ;
      }
      //
        determined_avg_number = atoi(temp_avg) ;
      //
      ///////////////(2) CREQ/////////////////////
      concater = NULL ;
      concater = concat("getprop ", freq_prop) ;
      if (check_shell_pushlog(system(concater),"E4",0) != 0)
      {
      concater = NULL ;
      concater = concat("getprop ", freq_default_prop) ;
      strcpy(freq_limit , get_commandr(concater)) ;
      }else{
      strcpy(freq_limit , get_commandr(concater)) ;
      }
      //
      // (end of 2)
        /////////////////////////////////////////////
      if (strcmp(get_commandr("getprop cpufreq.limit.status"),"1"))
       {
        /////////////////////////////////////////////
        // (3) get temp avg during  5s
        /////////////////////////////////////////////

        for (counter = 0 ; counter < 5 ; counter++)
        {
          strcpy(temp_reader,read_file_content(thermal_dir,"r"));
          temp[counter] = atoi(temp_reader) ;
          sleep(1) ;
        }

       total = 0 ;
       for (counter = 0 ; counter < 5 ; counter++)
       {
         total = total + temp[counter]  ;
       }
       avg = total / 5 ;
        /////////////////////////////////////////////
        // (5) cfl is here
        /////////////////////////////////////////////

        if ( avg >= determined_avg_number )
        {
         concater = NULL ;
         concater = concat("chmod 755 ", freq_limit_dir) ;
         check_shell_pushlog(system(concater),"E5",-1) ;
         edit_file_content(freq_limit_dir,freq_limit,"r+") ;
         sleep (60) ;
        }else{
         concater = NULL ;
         concater = concat("chmod 755 ", freq_limit_dir) ;
         check_shell_pushlog(system(concater),"E6",-1) ;
         edit_file_content(freq_limit_dir,nochain,"r+") ;
         sleep (10) ;
        }

    }else
      sleep (10) ;
  }
    return 0;
}
