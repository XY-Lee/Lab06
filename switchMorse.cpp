#include <iostream>
#include <wiringPi.h>
#include <mcp3004.h>
#include <time.h>
#include <stdio.h>
#include <string>

using namespace std ;

#define BASE 200
#define SPI_CHAN 0

/* status */
#define S0 0 // first status
#define S1 1 // when user press enter and now is dark
#define S2 2 // when you light it
#define S3 3 // when dark time is more than 10 second

const int channel = 0 ;

char signalToChar( string str ) {

  if ( str.compare( ".-" ) == 0 )
    return 'A' ;
  else if ( str.compare( "-..." ) == 0 )
    return 'B' ;
  else if ( str.compare( "-.-." ) == 0 )
    return 'C' ;
  else if ( str.compare( "-.." ) == 0 )
    return 'D' ;
  else if ( str.compare( "." ) == 0 )
    return 'E' ;
  else if ( str.compare( "..-." ) == 0 )
    return 'F' ;
  else if ( str.compare( "--." ) == 0 )
    return 'G' ;
  else if ( str.compare( "...." ) == 0 )
    return 'H' ;
  else if ( str.compare( ".." ) == 0 )
    return 'I' ;
  else if ( str.compare( ".---" ) == 0 )
    return 'J' ;
  else if ( str.compare( "-.-" ) == 0 )
    return 'K' ;
  else if ( str.compare( ".-.." ) == 0 )
    return 'L' ;
  else if ( str.compare( "--" ) == 0 )
    return 'M' ;
  else if ( str.compare( "-." ) == 0 )
    return 'N' ;
  else if ( str.compare( "---" ) == 0 )
    return 'O' ;
  else if ( str.compare( ".--." ) == 0 )
    return 'P' ;
  else if ( str.compare( "--.-" ) == 0 )
    return 'Q' ;
  else if ( str.compare( ".-." ) == 0 )
    return 'R' ;
  else if ( str.compare( "..." ) == 0 )
    return 'S' ;
  else if ( str.compare( "-" ) == 0 )
    return 'T' ;
  else if ( str.compare( "..-" ) == 0 )
    return 'U' ;
  else if ( str.compare( "...-" ) == 0 )
    return 'V' ;
  else if ( str.compare( ".--" ) == 0 )
    return 'W' ;
  else if ( str.compare( "-..-" ) == 0 )
    return 'X' ;
  else if ( str.compare( "-.--" ) == 0 )
    return 'Y' ;
  else if ( str.compare( "--.." ) == 0 )
    return 'Z' ;
  else
    return '-' ;
  
} // signalToChar()

int main() {
  if ( wiringPiSetup() == -1 )
    return 0 ;
    
  mcp3004Setup( BASE, SPI_CHAN ) ; // check mcp3008 setup or not
  
  /* init */
  int nowStat = S0 ;  // now status
  bool lighted = false ; // is light flag 
  time_t  light_start_t = time(NULL) ; // light start time
  time_t  light_end_t = time(NULL) ;   // light end time
  
  time_t  dark_start_t = time(NULL) ;  // dark start time
  time_t  dark_end_t = 0 ; // dark end time
  
  bool getChared = true ;  // when light start, it will be set to false so that it show my signal is not changed to char 
  
  string temp = "" ; // signal temp, when dark is more than 3 seconds, it will be added to out and initial
  string out = "" ; // output word temp, when dark is more than 10 seconds, it will be printed to screen and initial
  
  
  while ( 1 ) {
    int darkValue = analogRead( BASE + channel ) ; // the dark value, more dark more high, it is common higher than 500
    // cout << darkValue << endl ; // you can use this to find your value
    switch ( nowStat ) {
      case S0 : // first status
        cout << "press enter to morse..." << endl ;
        getchar() ; // in stdio.h, when you press enter, it will get a char 
        dark_start_t = time(NULL) ; // initial dark start time
        nowStat = S1 ; // change status to S1
        break ;
        
      case S1 : // when user press enter and now is dark
        dark_end_t = time(NULL) ;
        if ( darkValue < 500 ) { // if you light it
          if ( !lighted ) { // when you don't light it, it should be false, then you light it in first time, it will enter if  
            // keep light start time
            // you say " I light it ", so make lighted be true
            // you light it in first time, so you need make getChared be false
            // change status to S2
          } // if
        } // if
        else if ( dark_end_t - dark_start_t > 3 && !getChared ) { // when dark is coming and dark time is more than 3 second and the signal have not changed to char
          // call signalToChar and add to out
          // initial temp
          // initial getChared
        } // else if
        else if ( dark_end_t - dark_start_t > 10 ) { // when dark is coming and dark time is more than 10 second
          // change status to S3
        } // else if
        break ;
        
      case S2 : // when you light it
        if ( darkValue > 500 ) { // when now is dark
          // keep light end time
          // initial lighted
          // keep dark start time
          if ( light_end_t - light_start_t > 1 ) // if light time is more than 1 second, make signal "-" into temp 
            temp += "-" ;
          else // otherwise, make "." into temp
            temp += "." ;
          // change status to S1
        } // if
        break ;
        
      case S3 : // when dark time is more than 10 second
        // print out
        // initial out
        // change status to S1
        // initial dark start time
        // initial dark end time
        break ;
        
      default :
        break ;
    } // switch()
  } // while

} // main