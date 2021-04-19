int A = 7;//IN1 is connected to 10 
int A_bar = 6;//IN2 is connected to 11  
int B = 5;//IN3 is connected to 12  
int B_bar = 4;//IN4 is connected to 13 

int Pole1[] = {1, 0, 0, 1};
int Pole2[] = {0, 1, 1, 0};
int Pole3[] = {1, 1, 0, 0};
int Pole4[] = {0, 0, 1, 1};

const int x = 5000;

const int trigger = 8;
const int echo = 9;
const int maxDistance = 60;

void setup() {
  // Stepper motor things
  pinMode(A, OUTPUT);
  pinMode(A_bar, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(B_bar, OUTPUT);

  // distance sensor
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);

  // alarm
  pinMode(10, OUTPUT);
}

void alarm() {
  analogWrite(10, 128);
  while (true) {
  }
}

int getDistance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  int duration = pulseIn(echo, HIGH);
  return (duration * 0.0343)/2;
}

void forward(unsigned int steps) {
  for (int i = 0; i < (steps/4) ; i++) {
    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_bar, LOW);
    delayMicroseconds (x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(B_bar, LOW);
    delayMicroseconds (x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, HIGH);
    delayMicroseconds (x);

    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, HIGH);
    delayMicroseconds (x);
  }
}

void backward(unsigned int steps) {
  for (int i = 0; i < (steps/4); i++) {
    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, HIGH);
    delayMicroseconds (x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, HIGH);
    delayMicroseconds (x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(B_bar, LOW);
    delayMicroseconds (x);

    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_bar, LOW);
    delayMicroseconds (x);
  }
}

void loop() {
  while (getDistance() > maxDistance) {}

  forward(300);
  backward(300);
  alarm();
}
