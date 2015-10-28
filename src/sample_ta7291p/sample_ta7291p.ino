/*
2014.10.07
Check ta7201p(motor driver)
ver0.7
Haru
*/

// to input
const int rcv1 = 4;
// to output
const int outPin1_1 = 3;
const int outPin1_2 = 5;
const int outPin1_3 = 2;

// init
//--------------------------------------------
int pulseNum1 = 0;
int speedVal1 = 0;
int play = 10; //about 5~30
//--------------------------------------------

void setup(){
  
	//setup pin mode
	//--------------------------------------------
	pinMode(rcv1, INPUT);
	
	pinMode(outPin1_1, OUTPUT);
	pinMode(outPin1_2, OUTPUT);
	pinMode(outPin1_3, OUTPUT);
    //--------------------------------------------

    // test pulse
	Serial.begin(9600);
}

void loop(){

    //recieve pulse
    pulseNum1 = pulseIn(rcv1, HIGH);
    // convert pulseNum(1100~1900) to speedVal(-255~255)
    speedVal1 = map(pulseNum1, 1900, 1100, -255, 255);
    // constrain speedVal
    speedVal1 = constrain(speedVal1, -255, 255);

    if(pulseNum1 < 500) speedVal1 = 0; //初期暴走対策

    //control
    if( speedVal1 > play){
		analogWrite(outPin1_1, speedVal1);
		digitalWrite(outPin1_2, HIGH);
		digitalWrite(outPin1_3, LOW);
	}
	else if( speedVal1 < -play){
		analogWrite(outPin1_1, -speedVal1);
		digitalWrite(outPin1_2, LOW);
		digitalWrite(outPin1_3, HIGH);
	} else {
		digitalWrite(outPin1_2, LOW);
		digitalWrite(outPin1_3, LOW);
	}

    
    // sirial monitor
	Serial.print("pulseNum1: ");
	Serial.print(pulseNum1);

	Serial.print(" | speedVal1: ");
	Serial.println(speedVal1);
} 

