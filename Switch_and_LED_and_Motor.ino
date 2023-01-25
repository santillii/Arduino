int ledPin = 3;
int pushButton = 4;
int buttonState = 0;
int ledState = 0;
int currentState = 0;
int TIP120pin = 7;
int motstate = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(pushButton, INPUT);
  pinMode(TIP120pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(pushButton);
  if(buttonState == 1 && currentState != buttonState){
    ledState = !ledState;
    motstate = !motstate;
     
  }
  currentState = buttonState;
  digitalWrite(ledPin, ledState);
  digitalWrite(TIP120pin, motstate);
  delay(100);
}
