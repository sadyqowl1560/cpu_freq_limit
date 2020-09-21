// Mycustom_functions.h



// Variables
char content[2000000]={0x0};
char result[2000000]={0x0};

// Light Functions

// (1) Concatenate two strings .
char* concat(const char *string1, const char *string2)
{
    char *result = malloc(strlen(string1) + strlen(string2) + 1); // +1 for the null-terminator
    // in real code you would check for Errors in malloc here
    strcpy(result, string1);
    strcat(result, string2);
    return result;
}

// Heavy Functions
// (1) Check IF command was applied or no .

int check_shell_pushlog(int which_need_check , char* statment , int exit_sir)
{
   if (which_need_check != 0)
   {
        char* concater ;
        /// printf("%s : Command  applying failed .",statment);
        concater = NULL ;
        concater = concat("log -p e ", "\"Error : ") ;
        concater = concat(concater , statment) ;
        concater = concat(concater , "\"") ;
        system(concater);
        if (exit_sir == -1)
        {
          concater = NULL ;
          concater = concat("log -p e ", "\"Error : I am out sir") ;
          concater = concat(concater , "\"") ;
          system(concater);
          exit(EXIT_FAILURE);
        }
        return 1 ;
   }else
    return 0 ;
}

//
// (2) Send output of  command .

char* get_commandr(char * command)
{
    char* concater ;
    strcpy(result, "");
    FILE *cmd= popen(command, "r");
    while (fgets(result, sizeof(result), cmd) !=NULL)
    pclose(cmd);
    concater = NULL ;
    concater = concat("log -p i ", "\"I : cfl report ") ;
    concater = concat(concater , result) ;
    concater = concat(concater , "\"") ;
    system(concater);
    return result ;
}

// (3) get info from another device

void print_file_content(const char* file_dir, char* mode)
{
    FILE * fp;
    char ch;
    fp = fopen(file_dir,mode);
    if(fp == NULL)
    {
        char* concater ;
        concater = NULL ;
        concater = concat("log -p e ", "\"Error : ") ;
        concater = concat(concater ,"Unable to open file : ") ;
        concater = concat(concater , file_dir) ;
        concater = concat(concater , "\"") ;
        system(concater);
        //printf("Unable to open file : %s .\n", file_dir);
        exit(EXIT_FAILURE);
    }
    fseek( fp, 0 , SEEK_SET );
    while(1) {
       ch = fgetc(fp);
       if( feof(fp) ) {
          break;
       }
      printf("%c", ch);
   }

   fclose(fp);
}

// (4) get info from another device and return it .

char* read_file_content(const char* file_dir, char* mode)
{
    strcpy(content, "");
    int i = 0  ;
    FILE * fp;
    char ch;
    fp = fopen(file_dir,mode);
    if(fp == NULL)
    {
        char* concater ;
        concater = NULL ;
        concater = concat("log -p e ", "\"Error : ") ;
        concater = concat(concater ,"Unable to open file : ") ;
        concater = concat(concater , file_dir) ;
        concater = concat(concater , "\"") ;
        system(concater);
        //printf("Unable to open file : %s .\n", file_dir);
        exit(EXIT_FAILURE);
    }
    fseek( fp, 0 , SEEK_SET );
    while(1) {
       ch = fgetc(fp);
       if( feof(fp) ) {
          break;
       }
     content[i] = ch ;
     i++ ;
   }
   fclose(fp);
   return content ;
}

// (5) edit file


void edit_file_content(const char* file_dir, char* syntax , char* mode)
{
    int i = 0  ;
    FILE * fp;
    fp = fopen(file_dir,mode);
    if(fp == NULL)
    {
        char* concater ;
        concater = NULL ;
        concater = concat("log -p e ", "\"Error : ") ;
        concater = concat(concater ,"Unable to open file : ") ;
        concater = concat(concater , file_dir) ;
        concater = concat(concater , "\"") ;
        system(concater);
        //printf("Unable to open file : %s .\n", file_dir);
        exit(EXIT_FAILURE);
    }
    for (i = 0; syntax[i] !='\0'; i++)
    {
      fputc(syntax[i] , fp);
    }

   fclose(fp);
}
