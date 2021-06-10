#include <Servo.h>

Servo myservo;
const int stepPin = 10;
const int dirPin = 9;

int pos = 0;

int positions[] = { 160, 143, 123, 103, 82, 62, 42 };
int nr_of_positions = 7;

int current_pos = 4;

void setup() {
  Serial.begin(115200);
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object
  myservo.write(positions[current_pos]);
  randomSeed(analogRead(0));

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  int randNumber = random(0, nr_of_positions);
  Serial.print("Going to:");
  Serial.println(randNumber);

  move_to_pos(randNumber);
  Serial.println("Done!");
  next_marble();

  delay(2000); // One second delay
}


void next_marble()
{
  digitalWrite(dirPin, LOW);
  for (int x = 0; x < 27; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(3000);

    digitalWrite(stepPin, LOW);
    delayMicroseconds(3000);
  }
}

int move_to_pos(int pos)
{
  if (pos == current_pos)
  {
    return 0;
  }
  else if (pos < current_pos)
  {
    for (int posi = positions[current_pos]; posi <= positions[pos]; posi += 1)
    {
      myservo.write(posi);
      delay(20);
    }
  }
  else // if (pos < current_pos)
  {
    for (int posi = positions[current_pos]; posi >= positions[pos]; posi -= 1)
    {
      myservo.write(posi);
      delay(20);
    }
  }

  current_pos = pos;
  return 1;

}
