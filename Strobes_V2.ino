#define SWITCH_MODE 6
#define TOGGLE 5
#define BUZZER 4
#define SEQ1 8
#define SEQ2 9

int currentMode = 0; //Modes equate to Patterns. 0 = Pattern 1. 1 = Pattern 2. 2 = Pattern 3.
bool lastSwitchState = false;

void setup() {
  pinMode(SWITCH_MODE, INPUT);
  pinMode(TOGGLE, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(SEQ1, OUTPUT);
  pinMode(SEQ2, OUTPUT);
}

void loop() {
  // Check if the switch is currently toggled on. 
  if(checkInput(TOGGLE) == true)
  {
    switch(currentMode)
    {
      case 0:
        pattern1();
        break;

      case 1:
        pattern2();
        break;

      case 2:
        pattern3();
        break;

      default:
        break;
    }
  }

  //Check if we have pressed our mode switch since last cycle
  if(lastSwitchState == false && checkInput(SWITCH_MODE))
  {
    currentMode = selectMode();
  }
  lastSwitchState = checkInput(SWITCH_MODE);

}

//Blink 8 times each side 4 blinks. 2 times together (2 blink, pause, 2 blink).  
void pattern1()
{
  for(int i=0; i<4; i++)
  {
    blink(SEQ1, 50, 50);
    blink(SEQ1, 50, 50);
    blink(SEQ1, 50, 50);
    blink(SEQ1, 50, 50);
    
    //If our switch is no longer on, panic and break.
    if(!checkInput(TOGGLE))
    {
      return;
    }
    
    blink(SEQ2, 50, 50);
    blink(SEQ2, 50, 50);
    blink(SEQ2, 50, 50);
    blink(SEQ2, 50, 50);
  }

  //If our switch is no longer on, panic and break.
    if(!checkInput(TOGGLE))
    {
      return;
    }

  flash(50, 100);
  flash(50, 100);
  delay(100);

  //If our switch is no longer on, panic and break.
    if(!checkInput(TOGGLE))
    {
      return;
    }

  flash(50, 100);
  flash(50, 100);
  delay(900);
}

//Blink alternating
void pattern2()
{
    blink(SEQ1, 50, 50);
    blink(SEQ1, 50, 50);
    blink(SEQ1, 50, 50);
    blink(SEQ1, 50, 50);

    //If our switch is no longer on, panic and break.
    if(!checkInput(TOGGLE))
    {
      return;
    }

    blink(SEQ2, 50, 50);
    blink(SEQ2, 50, 50);
    blink(SEQ2, 50, 50);
    blink(SEQ2, 50, 50);
}

//Blink together
void pattern3()
{
  flash(50, 100);
  flash(50, 100);
  delay(100);

  //If our switch is no longer on, panic and break.
    if(!checkInput(TOGGLE))
    {
      return;
    }

  flash(50, 100);
  flash(50, 100);
  delay(100);
}

void flash(int flashduration, int pauseduration)
{
  digitalWrite(SEQ1, HIGH);
  digitalWrite(SEQ2, HIGH);
  delay(flashduration);
  digitalWrite(SEQ1, LOW);
  digitalWrite(SEQ2, LOW);
  delay(pauseduration);
}

void blink(int target, int blinkduration, int pauseduration)
{
  digitalWrite(target, HIGH);
  delay(blinkduration);
  digitalWrite(target, LOW);
  delay(pauseduration);
}

void beep(int duration)
{
  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER, LOW);
  delay(duration);
}

//Check our input state. This will be polled occasionally to shut down before a sequence ends, as a panic prevention around police.
bool checkInput(int pin)
{
  if(digitalRead(pin) == HIGH)
  {
    return true;
  }
  else return false;
}

int selectMode()
{
  int nextMode = currentMode + 1;
  if(nextMode > 2)
  {
    beep(100);
    return 0;
  }
  else
  {
    for(int i=-1; i<nextMode; i++)
    {
      beep(100);
    }
    return nextMode;
  }
}