//#include <iostream>
//#include <wiringPi.h>
//#include <mcp3004.h>

using namespace std ;

#define BASE 200
#define SPI_CHAN 0

const int channel = 0 ;

int main() {
  if ( wiringPiSetup() == -1 )
    return 0 ;
    
  mcp3004Setup( BASE, SPI_CHAN ) ; // check mcp3008 setup or not
  
  while ( 1 ) {
    int x = analogRead( BASE + channel ) ; // read Analog input
    cout << x << endl ;
    delay( 500 ) ;
  
  } // while

} // main
