////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// someone / something is trying to trick me
void s_i_t_t_m(int s_l , char * string)
{
    if(strlen(string) == s_l && string[0] != 48) {
     printf("checking . . . \n") ;
     for(int i = 0; i < strlen(string); i++) {
     // if(string[i] != ' ' && string[i] <= 57 && string[i] >= 48)
      if(string[i] <= 57 && string[i] >= 48)
       printf("ok . . . \n") ;
      else{
        printf("\nE : Sir , I will tell u a secret : something is wrong in your input ! \nSir : GO OUT.") ;
        exit(1);
      }
     }
    }else{
        printf("\nE : Sir , I will tell u a secret : someone is trying to trick me  ! \nSir : GO OUT.") ;
        exit(1);
   }
}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// commad_checker
void check_shell_rv(int which_need_check , char* statment , int exit_sir)
{
   if (which_need_check != 0)
   {
        printf("Command  applying failed :  %s .",statment);
        if (exit_sir == -1)
          exit(EXIT_FAILURE);
   }
}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void edit_file_content(const char* file_dir, char* syntax , char* mode)
{
    int i = 0  ;
    FILE * fp;
    fp = fopen(file_dir,mode);
    if(fp == NULL)
    {
        printf("Unable to open file : %s .\n", file_dir);
        exit(EXIT_FAILURE);
    }
    for (i = 0; syntax[i] !='\0'; i++)
    {
      fputc(syntax[i] , fp);
    }

   fclose(fp);
}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void work_status(int reader)
{
    switch (reader){
        case '1' :
            puts("Turning on") ;
            check_shell_rv(system("setprop cpufreq.limit.status 1"),"Turning on Failed",-1);
            break ;
        case '2' :
            puts("Turning off") ;
            check_shell_rv(system("setprop cpufreq.limit.status 0"),"Turning on Failed",-1);
            edit_file_content("/sys/power/cpufreq_max_limit","-1","w");
            break  ;
 }
}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void work_setconfig(int reader)
{
char temp[2] , freq[7] , src[50] , dest[50];
    switch (reader){
        case '1' :
            puts("Changing manually") ;
            sleep(1) ;
            puts("Setting new values") ;
            check_shell_rv(system("clear")," ",1);
/////////////////////////////////////
//TEMPERATURE
            puts("") ;
            printf("New temperature value (max 2 digits)\t : ") ;
            scanf(" %s", temp) ;
            //checking
            s_i_t_t_m(2,temp) ;
            //
            // change now
            strcpy(src,  "setprop \"cpufreq.limit.dtempa\" ");
            strcpy(dest,"\"");
            strcat(dest, temp);
            strcat(src, dest);
            strcat(src, "\"");
            check_shell_rv(system(src)," failed to change temperature value",-1);
////
            // write to config
            strcpy(src,  "cpufreq.limit.dtempa=");
            strcpy(dest, temp);
            strcat(src, dest);
            edit_file_content("/data/cfl_config.txt",src,"w");
////

/////////////////////////////////////
//FREQ
            puts("");
            printf("New freq value (max 7 digits)\t : ") ;
            //checking
            scanf(" %s", freq) ;
            s_i_t_t_m(7,freq) ;
            //
            // change now
            strcpy(src,  "setprop \"cpufreq.limit.freqv\" ");
            strcpy(dest,"\"");
            strcat(dest, freq);
            strcat(src, dest);
            strcat(src, "\"");
            check_shell_rv(system(src)," failed to change freq value",-1);
////
            // write to config
            strcpy(src,  "\ncpufreq.limit.freqv=");
            strcpy(dest, freq);
            strcat(src, dest);
            edit_file_content("/data/cfl_config.txt",src,"a");
////

/////////////////////////////////////
            break ;
        case '2' :
            puts("Reseting default") ;
            check_shell_rv(system("setprop \"cpufreq.limit.dtempa\"  \"$(getprop cpufreq.limit.dtempa.default)\"")," failed to reset temperature value",-1);
            check_shell_rv(system("setprop \"cpufreq.limit.freqv\"  \"$(getprop cpufreq.limit.freqv.default)\"") ," failed to change freq value",-1);
            check_shell_rv(system("echo \"cpufreq.limit.dtempa=$(getprop cpufreq.limit.dtempa.default)\"  >/data/cfl_config.txt"),"failed to update some stuff , please uninstall module and reinstall again",-1);
            check_shell_rv(system("echo \"cpufreq.limit.freqv=$(getprop cpufreq.limit.freqv.default)\"  >>/data/cfl_config.txt"),"failed to update some stuff , please uninstall module and reinstall again",-1);
            break  ;
 }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
