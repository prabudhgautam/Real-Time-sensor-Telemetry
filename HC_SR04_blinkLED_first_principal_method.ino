int led=5;
int trig=6;
int echo=7;
float distance;
long time;

void setup() {
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,INPUT);
  
  Serial.begin(9600);}


void loop() {
  //clear trig
  digitalWrite(trig,LOW);
  delayMicroseconds(2);

  //initiate trig,sending 10us pulse
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  //duration of echo high
  time = pulseIn(echo,HIGH); //pulseIn() measures HIGH time:microseconds as whole numbers

  distance = time*0.034 / 2;
  Serial.println(distance);

  if(distance<=25)
  {
    digitalWrite(led,HIGH);
    }
  else
  {
    digitalWrite(led,LOW);
    }

  delay(100);
}
