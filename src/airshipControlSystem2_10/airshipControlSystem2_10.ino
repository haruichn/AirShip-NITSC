/*
2014.10.10
Airship Controling System (ACS)
ver2.10
Haru

adjust output voltage 5V to 3V
adjust play 10 to 20
adjust pulseNum3 
*/


//set pin num (3ch)
//--------------------------------------------
// to input
const int rcv1 = 4; // up/down
const int rcv2 = 7; // go/back
const int rcv3 = 8; // left/right

// to output
const int outPin1_pwm = 3;
const int outPin1_1 = 2;
const int outPin1_2 = 5;
const int outPin2_pwm = 6;
const int outPin2_1 = 9;
const int outPin2_2 = 11;
const int outPin3_pwm = 10;
const int outPin3_1 = 12;
const int outPin3_2 = 13;
//--------------------------------------------

// init
//--------------------------------------------
int pulseNum1 = 0;
int pulseNum2 = 0;
int pulseNum3 = 0;

int speedVal1 = 0;
int speedVal2 = 0;
int speedVal3 = 0;

int play = 20;
int pwm = 135;
//--------------------------------------------


void setup(){
  
	//setup pin mode
	//--------------------------------------------
	pinMode(rcv1, INPUT);
	pinMode(rcv2, INPUT);
	pinMode(rcv3, INPUT);

	pinMode(outPin1_pwm, OUTPUT); // outPin1: under motor
	pinMode(outPin1_1, OUTPUT);
    pinMode(outPin1_2, OUTPUT);
	pinMode(outPin2_pwm, OUTPUT); // outPin2: left motor
	pinMode(outPin2_1, OUTPUT);
	pinMode(outPin2_2, OUTPUT);
	pinMode(outPin3_pwm, OUTPUT); // outPin3: right morot
	pinMode(outPin3_1, OUTPUT);
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

	// convert pulseNum(1100~1900) to speedVal(-pwm~pwm)
	int speedVal1 = map(pulseNum1, 1900, 1100, -pwm, pwm); // up/down
	int speedVal2 = map(pulseNum2, 1900, 1100, -pwm, pwm); // go/back
	int speedVal3 = map(pulseNum3, 1850, 1100, -pwm, pwm); // left/right

	// constrain speedVal
	speedVal1 = constrain(speedVal1, -pwm, pwm);
	speedVal2 = constrain(speedVal2, -pwm, pwm);
	speedVal3 = constrain(speedVal3, -pwm, pwm);


	//control
	//--------------------------------------------
	// up/down
	//--------------------------------------------
	if( speedVal1 > play){
		analogWrite(outPin1_pwm, speedVal1);
		digitalWrite(outPin1_1, HIGH);
		digitalWrite(outPin1_2, LOW);
	}

	else if( speedVal1 < -play){
		analogWrite(outPin1_pwm, -speedVal1);
		digitalWrite(outPin1_1, LOW);
		digitalWrite(outPin1_2, HIGH);
	} else {
		digitalWrite(outPin1_1, LOW);
		digitalWrite(outPin1_2, LOW);
	}
	//--------------------------------------------

	// go/back
	//--------------------------------------------
	// go
	if( speedVal2 > play){
		analogWrite(outPin2_pwm, speedVal2);
		digitalWrite(outPin2_1, HIGH);
		digitalWrite(outPin2_2, LOW);

		analogWrite(outPin3_pwm, speedVal2);
		digitalWrite(outPin3_1, HIGH);
		digitalWrite(outPin3_2, LOW);

	}
	// back
	else if( speedVal2 < -play){
		analogWrite(outPin2_pwm, -speedVal2);
		digitalWrite(outPin2_1, LOW);
		digitalWrite(outPin2_2, HIGH);

		analogWrite(outPin3_pwm, -speedVal2);
		digitalWrite(outPin3_1, LOW);	
		digitalWrite(outPin3_2, HIGH);	
	}
	// stop
	//--------------------------------------------

	// left/right
	//--------------------------------------------
	// left
	else if( speedVal3 > play){
		analogWrite(outPin2_pwm, speedVal3);
		digitalWrite(outPin2_1, LOW);
		digitalWrite(outPin2_2, HIGH);

		analogWrite(outPin3_pwm, speedVal3);
		digitalWrite(outPin3_1, HIGH);
		digitalWrite(outPin3_2, LOW);
	}

	// right
	else if( speedVal3 < -play){
		analogWrite(outPin2_pwm, -speedVal3);
		digitalWrite(outPin2_1, HIGH);
		digitalWrite(outPin2_2, LOW);

		analogWrite(outPin3_pwm, -speedVal3);
		digitalWrite(outPin3_1, LOW);
		digitalWrite(outPin3_2, HIGH);
	// stop
	} else {
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
