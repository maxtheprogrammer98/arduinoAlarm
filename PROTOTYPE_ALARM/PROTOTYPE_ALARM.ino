// VARIABLES
const int PHOTORESISTOR = A0;
const int MIC = A1;
const int BUZZER = 2;
const int BUTTON = 3;
const int LED_ON = 4;
const int LED_DANGER = 5;

// VALUES FROM SENSORS
int PHOTORESISTOR_VALUE; 
int MIC_VALUE;

// FLAGS
bool danger = false;
bool alarmOn = false;

void setup() {
  // INPUT
  pinMode(PHOTORESISTOR, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(MIC, INPUT);
  // OUTPUTS
  pinMode(LED_ON, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  // CONSOLE
  Serial.begin(9600);
}

void loop() {

  // READING VALUES FROM ANALOGIC SENSORS
  PHOTORESISTOR_VALUE = analogRead(PHOTORESISTOR);
  MIC_VALUE = analogRead(MIC);

  // READING VALUES FROM DIGITAL SENSORS
  int buttonState = digitalRead(BUTTON);

  // UPDATING STATE WHEN BUTTON IS PRESSED
  if(buttonState == HIGH){
    alarmOn = updateFlagActivate();
  }

  // TURNING ON LED ON
  activateLedOn();

  // DETECTING DANGER AND UPDATING FLAG STATES IF NEEDED
  detectDanger();
  
  // ACTIVATING SPEAKER VIA PHOTORESISTOR
  activateBuzzer();

  // DISPLAYING VALUES ON CONSOLE
  displayStatesOnConsole();
}


// FUNCTION UPDATING STATE FLAG (ACTIVATE)
bool updateFlagActivate(){
   Serial.println("TOGGLE!!!!!!!!! ");
   alarmOn = !alarmOn;
   return alarmOn;
}

// DETECTS IF THE LASER CONTACT WAS INTERCEPTED ALSO IF THE MIC DETECTED ANY NOISE
void detectDanger(){
  // UPDATING STATE FLAG (DANGER)
  if(alarmOn){
    if( PHOTORESISTOR_VALUE < 920 || MIC_VALUE > 550){
      danger = true;
    } else {
      danger = false;
    }
  }
}

// IF THE DANGER STATE IS TRUE, THEN THE BUZZER IS ACTIVATED
void activateBuzzer(){
  if(danger == true){
    // buzzer activated
    tone(BUZZER, 330);
    // led activated
    digitalWrite(LED_DANGER, HIGH);
    // displaying message on console
    Serial.println("hay intrusos!");
  } else {
    // deactivating buzzer
    noTone(BUZZER);
    // TURNING LED OFF
    digitalWrite(LED_DANGER, LOW);
  }
}

// TURNS ON A LED WHEN THE DEVICE IS ACTIVATED
void activateLedOn(){
  if(alarmOn == true){
    digitalWrite(LED_ON,HIGH);
  } else {
    danger = false;
    digitalWrite(LED_ON, LOW);
    digitalWrite(LED_DANGER, LOW);
  }
}

// DISPLAYS STATES VALUE ON CONSOLE
void displayStatesOnConsole(){
  Serial.println("photoresistor value: ");
  Serial.println(PHOTORESISTOR_VALUE);
  Serial.println("MIC value: ");
  Serial.println(MIC_VALUE);
  delay(500);
}


