// nav stuff
void nav()
{
 puts("") ;
 printf("NAV : (b) : back , (e) : exit \n");
 puts("") ;
}

int determined_nav(char nav_value)
{
 switch (nav_value) {
    case 'b' :
      return 0 ;
      break ;
    case 'e' :
      system("clear") ;
      puts("OK SIR , I am out . ") ;
      exit (0) ;
      break ;
    case '1' :
      return 1 ;
      break ;
    case '2' :
      return 1 ;
      break ;
    default :
     system("clear") ;
     puts("U R JOKING WITH ME , I am out . ") ;
     exit(1) ;
 }
}

void all_nav() {
    nav() ;
    printf("YOUR_CHOICE : \t") ;
    scanf(" %c", &reader ) ;
    nav_checker = determined_nav(reader) ;
}
