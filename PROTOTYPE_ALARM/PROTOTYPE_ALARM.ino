// VARIABLES
const int PHOTORESISTOR = A0;
const int MIC = A1;
const int BUZZER = 2;
const int BUTTON = 3;
const int LED_ON = 4;
const int LED_DANGER = 7;

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

  // TURNING ON LED
  if(alarmOn == true){
    digitalWrite(LED_ON,HIGH);
  } else {
    digitalWrite(LED_ON, LOW);
    danger = false;
  }

  // UPDATING STATE FLAG (DANGER)
  if(alarmOn){
    if( PHOTORESISTOR_VALUE < 945 || MIC_VALUE > 550){
      danger = true;
    } else {
      danger = false;
    }
  }
  
  // ACTIVATING SPEAKER VIA PHOTORESISTOR
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
  }

  // DISPLAYING VALUES ON CONSOLE
  Serial.println("photoresistor value: ");
  Serial.println(PHOTORESISTOR_VALUE);
  Serial.println("MIC value: ");
  Serial.println(MIC_VALUE);
  delay(500);
}

// FUNCTION UPDATING STATE FLAG (ACTIVATE)
bool updateFlagActivate(){
   Serial.println("TOGGLE!!!!!!!!! ");
   alarmOn = !alarmOn;
   return alarmOn;
}