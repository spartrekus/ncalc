    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ncurses.h>


#include "tinyexpr.h"
#include <stdio.h>
#include <math.h>



#ifdef _WIN32
/// WIN
#include <windows.h>
int termsize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 0;
    printf("OS: Windows \n" );
    printf("columns: %d\n", columns);
    printf("rows: %d\n", rows);
}
#else
/// LINUX
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
int termsize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("OS: Linux \n" );
    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
}
#endif





////////////////////////////////////////////////////////////////////
char *strrlf(char *str) 
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}
////////////////////////////////////////////////////////////////////
char *strcut( char *str , int myposstart, int myposend )
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}








int rows, cols;


///////////////////////////////////////////////////////////
void drawinput( char *mytext , char *myresult)
{
     getmaxyx( stdscr, rows, cols);
     int fooj; 

     color_set( 2, NULL ); attroff( A_REVERSE);

     for ( fooj = 0 ; fooj <= cols-1;  fooj++)
       mvaddch( rows-4, fooj , ACS_HLINE );

     mvprintw( 0, 0, "|NCALC|");
     mvprintw( 2, 0, "%s" , strrlf( mytext ) );
     mvprintw( 3, 0, "=%s" , myresult );

     mvprintw( rows-3, 0, "I:> %s" , strrlf( mytext ) );
     color_set( 0, NULL ); attron( A_REVERSE);
     printw( " " );
     color_set( 0, NULL ); attroff( A_REVERSE);

     
     color_set( 0, NULL ); attroff( A_REVERSE);
     mvprintw( rows-1, 0, "" ); 
     
     color_set( 0, NULL ); attroff( A_REVERSE);
     printw(  "Esc" ); 
     color_set( 4, NULL ); attron( A_REVERSE);
     printw( "Clear" ); 

     color_set( 0, NULL ); attroff( A_REVERSE);
     printw(  " " ); 
     color_set( 0, NULL ); attroff( A_REVERSE);
     printw(  "c-c" ); 
     color_set( 4, NULL ); attron( A_REVERSE);
     printw( "Quit" ); 
}





///////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{
   printf("Hello to ncalc demo !\n");
   termsize();

   char cwd[PATH_MAX];
   initscr();			
   curs_set( 0 );
   start_color();
   init_pair(1, COLOR_RED, COLOR_BLACK);
   init_pair(2, COLOR_GREEN, COLOR_BLACK);
   init_pair(3, COLOR_BLUE, COLOR_BLACK);
   init_pair(4, COLOR_CYAN, COLOR_BLACK);
   color_set( 2, NULL );

   int gameover; 
   gameover = 0;
   char ch ; 
   char charo[PATH_MAX]; int foo ; 
   char strmsg[PATH_MAX];
   char strresult[PATH_MAX];
   strncpy( strmsg, "", PATH_MAX );
   strncpy( strresult, "", PATH_MAX );

   getmaxyx( stdscr, rows, cols);
   
   while ( gameover == 0)
   {
           getmaxyx( stdscr, rows, cols);

           erase();
           drawinput( strmsg , strresult );
	   refresh(); // <- not necessary
           ch = getch();

		  if ( ch == 127  ) 
		  {
			   strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );
			   strncpy( strresult, ""  ,  PATH_MAX );
		  }

		  else if ( ch == 4  ) 
		  {
			   strncpy( strmsg, ""  ,  PATH_MAX );
			   strncpy( strresult, ""  ,  PATH_MAX );
		  }



		  else if ( ch == 27  ) 
		  {
			   strncpy( strmsg, ""  ,  PATH_MAX );
			   strncpy( strresult, ""  ,  PATH_MAX );
		  }



	          else if (
			(( ch >= 'a' ) && ( ch <= 'z' ) ) 
		        || (( ch >= 'A' ) && ( ch <= 'Z' ) ) 
		        || (( ch >= '1' ) && ( ch <= '9' ) ) 
		        || (( ch == '0' ) ) 
		        || (( ch == '~' ) ) 
		        || (( ch == '!' ) ) 
		        || (( ch == '&' ) ) 
		        || (( ch == '=' ) ) 
		        || (( ch == ':' ) ) 
		        || (( ch == ';' ) ) 
		        || (( ch == '<' ) ) 
		        || (( ch == '>' ) ) 
		        || (( ch == ' ' ) ) 
		        || (( ch == '|' ) ) 
		        || (( ch == '#' ) ) 
		        || (( ch == '?' ) ) 
		        || (( ch == '+' ) ) 
		        || (( ch == '/' ) ) 
		        || (( ch == '\\' ) ) 
		        || (( ch == '.' ) ) 
		        || (( ch == '$' ) ) 
		        || (( ch == '%' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '{' ) ) 
		        || (( ch == '}' ) ) 
		        || (( ch == '(' ) ) 
		        || (( ch == ')' ) ) 
		        || (( ch == ']' ) ) 
		        || (( ch == '[' ) ) 
		        || (( ch == '*' ) ) 
		        || (( ch == '"' ) ) 
		        || (( ch == '@' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '_' ) ) 
		        || (( ch == '^' ) ) 
		        || (( ch == '\'' ) ) 
	             ) 
		  {
                           foo = snprintf( charo, PATH_MAX , "%s%c",  strmsg, ch );
			   strncpy( strmsg,  charo ,  PATH_MAX );
			   strncpy( strresult, ""  ,  PATH_MAX );
		  }
		  
		  else if ( ch == 10 ) 
		  {
                           foo = snprintf( charo, PATH_MAX , "Result: %f\n", te_interp( strmsg , 0));
			   strncpy( strresult, charo, PATH_MAX );
                           //printf("Result: %f\n", te_interp( strmsg , 0));
		  }


   }

   curs_set( 1 );
   endwin();		

   printf( "%s\n" , strmsg );
   //printf("Result: %f\n", te_interp( strmsg , 0));

   return 0;
}



