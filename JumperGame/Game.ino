#include <LiquidCrystal.h>

/// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char a[2][16];

int isJumped = 0;

int buttonState = 0;

int buttonPin = 13;

int untilSpawn = 1;

int untilUpdate = 0;

bool gameOver = false;

bool gameOverStart = true;

bool isPlayerUsed = false;

bool Enemy = false;

int spawner = 1;

int score = 0;

void render()
{

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 16; j++)
    {
      lcd.setCursor(j, i);
      lcd.print(a[i][j]);

    }
  }
}

void nextStep()
{
  untilUpdate++;
  Enemy = false;
  isPlayerUsed = false;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 16; j++)
    {
      if (a[i][j] == 'O'&&isPlayerUsed == false)
      {
        isPlayerUsed = true;
        if (buttonState == 1 && i == 1)
        {
          a[i - 1][j] = 'O';
          a[i][j] = ' ';
          isJumped == 1;
        }
        else if (i == 0)
        {
          if(a[i + 1][j] == 'X')
          {
              score++;
          }
          a[i + 1][j] = 'O';
          a[i][j] = ' ';
        }
      }
      if (a[i][j] == 'X'&&untilUpdate >= 2)
      {
        if (j == 0)
        {
          a[i][j] = ' ';
        }
        else if (a[i][j - 1] == 'O')
        {
          gameOver = true;
          a[i][j] = ' ';
          a[i][j - 1] = 'X';
        }
        else
        {
          a[i][j] = ' ';
          a[i][j - 1] = 'X';
        }
        Enemy = 1;
      }
    }
  }
  if(Enemy)
  {
    untilUpdate = 0;
  }
}



void setup() {
  Serial.begin(9600);
  /// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(buttonPin, INPUT);

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 16; j++)
    {
      a[i][j] = ' ';
    }
  }

  a[1][1] = 'O';

  /// Print a message to the LCD.
}

void loop() {

  if (gameOver == false)
  {
    if (untilSpawn >= spawner)
    {
      a[1][14] = 'X';
      untilSpawn = 0;
      spawner = random(5, 10);
    }
    int score2 = score;
    a[0][12] = score2 / 1000 + '0';
    score2 %= 1000;
    a[0][13] = score2 / 100 + '0';
    score2 %= 100;
    a[0][14] = score2 / 10 + '0';
    score2 %= 10;
    a[0][15] = score2 / 1 + '0';
    
    buttonState = digitalRead(buttonPin);
    //Serial.println(buttonState);
    //lcd.setCursor(0, 1);
      nextStep();
    render();
    untilSpawn++;
    untilUpdate++;
  }
  else
  {
    if(gameOverStart)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game over");
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      lcd.setCursor(7, 1);
      lcd.print(score);
      gameOverStart = false;
    }
  }
  delay(10);
}

