void work_status(int reader)
{
    switch (reader){
        case '1' :
            puts("Turning on") ;
            system("setprop cpufreq.limit.status 1") ;
            break ;
        case '2' :
            puts("Turning off") ;
            system("setprop cpufreq.limit.status 0") ;
            break  ;
 }
}

void work_setconfig(int reader)
{
    switch (reader){
        case '1' :
            puts("Changing manually") ;
            sleep(1) ;
            char temp[2] , freq[7] , src[50] , dest[50];
            FILE *f_temp_time , *f_freq_time;
            puts("Setting new values") ;
            system("clear");
//TEMPERATURE
            puts("") ;
            printf("New temperature value (max 2 digits)\t : ") ;
            scanf(" %s", temp) ;
            // change now
            strcpy(src,  "setprop cpufreq.limit.dtempa ");
            strcpy(dest, temp);
            strcat(src, dest);
            system(src);
            // write to config
            strcpy(src,  "cpufreq.limit.dtempa=");
            strcpy(dest, temp);
            strcat(src, dest);
            f_temp_time = fopen("/data/cfl_config.txt","w");
            if(f_temp_time == NULL)
            {
              printf("Error, check root access !");
              exit(1);
            }
            fprintf(f_temp_time,"%s",src);
            fclose(f_temp_time);
//FREQ           
            puts("");
            printf("New freq value (max 7 digits)\t : ") ;
            // change now
            scanf(" %s", freq) ;
            strcpy(src,  "setprop cpufreq.limit.freqv ");
            strcpy(dest, freq);
            strcat(src, dest);
            system(src);
            // write to config
            strcpy(src,  "cpufreq.limit.freqv=");
            strcpy(dest, freq);
            strcat(src, dest);
            f_freq_time = fopen("/data/cfl_config.txt","a");
            // write to config
            if(f_freq_time == NULL)
            {
              printf("Error, check root access !");
              exit(1);
            }
            fprintf(f_freq_time,"\n%s",src);
            fclose(f_freq_time);
            break ;
        case '2' :
            puts("Reseting default") ;
            system("setprop cpufreq.limit.dtempa  $(getprop cpufreq.limit.dtempa.default)") ;
            system("echo cpufreq.limit.dtempa=$(getprop cpufreq.limit.dtempa.default)  >/data/cfl_config.txt ");
            system("setprop cpufreq.limit.freqv  $(getprop cpufreq.limit.freqv.default)") ;
            system("echo cpufreq.limit.freqv=$(getprop cpufreq.limit.freqv.default)  >>/data/cfl_config.txt");
            break  ;
 }
}
