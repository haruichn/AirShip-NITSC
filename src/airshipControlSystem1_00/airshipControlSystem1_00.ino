/*
2014.06.03
Airship Controling System (ACS)
ver1.00
Haru
*/


//set pin num (3ch)
//--------------------------------------------
// to input
const int rcv1 = 4; // up/down
const int rcv2 = 7; // go/back
const int rcv3 = 8; // left/right

// to output
const int outPin1_1 = 3;
const int outPin1_2 = 5;
const int outPin2_1 = 6;
const int outPin2_2 = 9;
const int outPin3_1 = 10;
const int outPin3_2 = 11;
//--------------------------------------------

// init
//--------------------------------------------
int pulseNum1 = 0;
int pulseNum2 = 0;
int pulseNum3 = 0;

int speedVal1 = 0;
int speedVal2 = 0;
int speedVal3 = 0;
//--------------------------------------------


void setup(){
  
	//setup pin mode
	//--------------------------------------------
	pinMode(rcv1, INPUT);
	pinMode(rcv2, INPUT);
	pinMode(rcv3, INPUT);

	pinMode(outPin1_1, OUTPUT); // outPin1: back motor
	pinMode(outPin1_2, OUTPUT);
	pinMode(outPin2_1, OUTPUT); // outPin2: left motor
	pinMode(outPin2_2, OUTPUT);
	pinMode(outPin3_1, OUTPUT); // outPin3: right morot
	pinMode(outPin3_2, OUTPUT);
	//--------------------------------------------

	// test pulse
	Serial.begin(9600);
}


void loop(){

	//recieve pulse
	pulseNum1 = pulseIn(rcv1, HIGH);
	pulseNum2 = pulseIn(rcv2, HIGH);
	pulseNum3 = pulseIn(rcv3, HIGH);

	// convert pulseNum(1100~1900) to speedVal(-255~255)
	int speedVal1 = map(pulseNum1, 2000, 1000, -255, 255); // up/down
	int speedVal2 = map(pulseNum2, 2000, 1000, -255, 255); // go/back
	int speedVal3 = map(pulseNum3, 2000, 1000, -255, 255); // left/right

	// constrain speedVal
	speedVal1 = constrain(speedVal1, -255, 255);
	speedVal2 = constrain(speedVal2, -255, 255);
	speedVal3 = constrain(speedVal3, -255, 255);


	//control
	//--------------------------------------------
	// up/down
	//--------------------------------------------
	if( speedVal1 > 20){
		analogWrite(outPin1_1, speedVal1);
		digitalWrite(outPin1_2, LOW);
	}

	else if( speedVal1 < -20){
		digitalWrite(outPin1_1, LOW);
		analogWrite(outPin1_2, -speedVal1);
	} else {
		digitalWrite(outPin1_1, LOW);
		digitalWrite(outPin1_2, LOW);
	}
	//--------------------------------------------

	// go/back
	//--------------------------------------------
	// go
	if( speedVal2 > 20){
		digitalWrite(outPin2_1, LOW);
		analogWrite(outPin2_2, speedVal2);

		digitalWrite(outPin3_1, LOW);
		analogWrite(outPin3_2, speedVal2);

			}
	// back
	else if( speedVal2 < -20){
		analogWrite(outPin2_1, -speedVal2);
		digitalWrite(outPin2_2, LOW);

		analogWrite(outPin3_1, -speedVal2);
		digitalWrite(outPin3_2, LOW);
	
	// stop
	}
	//--------------------------------------------

	// left/right
	//--------------------------------------------
	// left
	else if( speedVal3 > 20){
		analogWrite(outPin2_1, speedVal3);
		digitalWrite(outPin2_2, LOW);

		digitalWrite(outPin3_1, LOW);
		analogWrite(outPin3_2, speedVal3);
	}

	// right
	else if( speedVal3 < -20){
		digitalWrite(outPin2_1, LOW);
		analogWrite(outPin2_2, -speedVal3);

		analogWrite(outPin3_1, -speedVal3);
		digitalWrite(outPin3_2, LOW);
	// stop
	} else {
		digitalWrite(outPin2_1, LOW);
		digitalWrite(outPin2_2, LOW);

		digitalWrite(outPin3_1, LOW);
		digitalWrite(outPin3_2, LOW);

		digitalWrite(outPin2_1, LOW);
		digitalWrite(outPin2_2, LOW);

		digitalWrite(outPin3_1, LOW);
		digitalWrite(outPin3_2, LOW);
	
	}
	//--------------------------------------------
	//--------------------------------------------


	// sirial monitor
	Serial.print("pulseNum1: ");
	Serial.print(pulseNum1);

	Serial.print(", pulseNum2: ");
	Serial.print(pulseNum2);   

	Serial.print(", pulseNum3: ");
	Serial.print(pulseNum3);

	Serial.print(" | speedVal1: ");
	Serial.print(speedVal1);

	Serial.print(", speedVal2: ");
	Serial.print(speedVal2);

	Serial.print(", speedVal3: ");
	Serial.println(speedVal3);

} 
