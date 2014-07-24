#include <DueTimer.h>
#include <MuxShield.h>

MuxShield muxShield;
volatile boolean state = 0;
int current_layer = 0;
int x = 0;
int y = 0;

volatile int row[8][8] =	{
	{21, 23, 25, 27, 29, 31, 33, 35},
	{20, 22, 24, 26, 28, 30, 32, 34},
	{1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 },
	{9 , 10, 11, 12, 13, 14, 15, 16},  //index 1
	{1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 },
	{16, 15, 14, 13, 12, 11, 10, 9 },  //index 2
	{1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 },
	{9 , 10, 11, 12, 13, 14, 15, 16},  //index 3
	};
	
	
volatile int lay[8] =
{38, 40, 43, 44, 46, 49, 50, 52};

inline void digitalWriteDirect ( int pin, boolean val ){
  if(val) g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
  else    g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
}


/*void latch_cube( int x, int y, boolean state){

	//sensorValue = analogRead (analogInPin);
	
	int q = 0 ;
	
	if (x >= 0 && x <= 1) { 
		digitalWriteDirect (row[x][y], state);
		q = 0 ;
	}
	else if(x >= 2 && x <= 3) {
	 q = 1 ;
	 muxShield.digitalWriteMS(q,row[x][y], state); // x*y'e kolom, q'de poort				
	}
	else if(x >= 4 && x <= 5) {
	 q = 2 ;
	 muxShield.digitalWriteMS(q,row[x][y], state); // x*y'e kolom, q'de poort				
	}
	else if(x >= 6 && x <= 7) {
	 q = 3 ;
	 muxShield.digitalWriteMS(q,row[x][y], state); // x*y'e kolom, q'de poort				
	}
	
}    */



void iProcess(){
  //last layer store
  int oldLayerBit = current_layer;
  int q = 0 ;
  //increment layer count
  current_layer++;
  if(current_layer >= 8){
    current_layer = 0;
  }
	Timer4.stop();
    for ( int i = 0; i<8; i++) { //iterate through bit mask
    	if (x >= 0 && x <= 1) { 
		digitalWriteDirect (row[x][y], state);
		q = 0 ;
	}
	else if(x >= 2 && x <= 3) {
	 q = 1 ;
	 muxShield.digitalWriteMS(q,row[x][y], state); // x*y'e kolom, q'de poort				
	}
	else if(x >= 4 && x <= 5) {
	 q = 2 ;
	 muxShield.digitalWriteMS(q,row[x][y], state); // x*y'e kolom, q'de poort				
	}
	else if(x >= 6 && x <= 7) {
	 q = 3 ;
	 muxShield.digitalWriteMS(q,row[x][y], state); // x*y'e kolom, q'de poort				
	}
  }
  //Hide the old layer
  digitalWriteDirect (lay[oldLayerBit], LOW);
  //New data on the pins
  Timer4.start();
  
  //new layer high
  digitalWriteDirect (lay[current_layer], HIGH);
}

void setup(){
	//pinMode (buttonPin, INPUT);

for (int i = 1 ; i <= 3 ; i++){		//i=1 column 17-32
		muxShield.setMode(i,DIGITAL_OUT);	//i=2 column 33-48 = als output ;   i=3 column 49-64
		}
			
	for (int i= 20 ; i <= 35 ; i++){
		pinMode(i, OUTPUT);					// column 1-16 = als output
		delay( 10);
		digitalWrite(i, LOW);				// set low
		}  
			
	for (int i= 38 ; i <= 52 ; i++){
	
		if(i==43){
			pinMode(i, OUTPUT);					//pin specifieke schakeling
			delay( 10);							//om kapotte pinnen op te vangen
			digitalWrite(i, LOW);};				//alleen vor pinnen binnen bereik ''for loop''.
		
		if(i==49){
			pinMode(i, OUTPUT);					//pin specifieke schakeling
			delay( 10);							//om kapotte pinnen op te vangen
			digitalWrite(i, LOW);};				//alleen vor pinnen binnen bereik ''for loop''.
			
		if(i % 3==0) continue;				// selecteert enkel even getallen
			pinMode(i, OUTPUT);					// alle grondlagen als output 
			delay( 10);
			digitalWrite(i, LOW);				// set low
		}
	for ( int i=0; i<8; i++){
	digitalWrite(lay[i], LOW);
	}

	//Timer3.attachInterrupt(firstHandler);
	//Timer3.start( 140); // Calls every 1.4ms
	Timer4.attachInterrupt(iProcess).setFrequency(1000).start();
	
}

void loop (){

randomfill(80);
delay (10000);
flip(3000);
delay(30000);
sine(3000);

}

void randomfill(int vertraging) {
	int r1, r2, r3;
	for(int i=0; i<200; i++)
    randomSeed (analogRead(9));
	for (int i=0; i<2000; i++){
	r1= random(8);
	r2= random(8);
	r3= random(8);
	x=r1;
	y=r2;
	delay (vertraging);
	state = !state;
	x=((r3+r1)/r2);
	y=((r3*r2)/r1);
	delay (vertraging);
	state = !state;
	}
}


void flip ( int iterations){
	for ( int i= 0 ; i < iterations ; i++){
		for ( int j= 0 ; j < 8 ; j++){ // Iterate through x and y. 
			for ( int k= 0 ; k< 8 ; k++) {
				y=j;
				x=k;
				state = !state;
				
}
}
}
}


void sine( int iterations){
// Remember, it takes 300+ for just a couple seconds of animation... 

for ( int i= 0 ; i < iterations ; i++){ // Iterate through x and y. 
	for ( int j= 0 ; j< 8 ; j++) {
		for(int k=0 ; k<8 ; k++){
			x=(int)((4+sin(sqrt((3.5-j)*(3.5-j)+(3.5-k)*(3.5-k)) / 1.3 + (float)i/50) * 4));
			y=k;
			//Serial.println(sensorValue);
			}
 state = !state;
 delay (20);
		}

	}	
}


void clear_cube () {

	for (int i = 1; i <= 3; i++){
		for (int j = 1; j <= 16; j++){//i=1 column 17-32
		muxShield.digitalWriteMS(i,j,LOW );	//i=2 column 33-48 = als output ;   i=3 column 49-64
		}}
			
	for ( int i=20; i <= 35; i++){
		digitalWriteDirect (i, LOW );				// set low
		}  
			
	for ( int i=38; i <= 52; i++){
	
		if (i==43){
			digitalWriteDirect (i, LOW );};
		
		if (i==49){
			digitalWriteDirect (i, LOW );};
			
		if (i % 3==0) continue;				// selecteert enkel even getallen
			digitalWriteDirect (i, LOW );				// set low
		}
	for ( int i=0; i<8; i++){
	digitalWriteDirect (lay[i], LOW );
	}
}
