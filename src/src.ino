#include "numbers.h"
#include "presets.h"

#include <LedControl.h>
#include <Timer.h>

#define LED_PIN 13
#define BUTTON_PIN 2

#define DIN 8
#define CS 9
#define CLK 10

LedControl MX = LedControl(DIN, CLK, CS, 1);
Gameplay game;
Timer timer;

boolean running = true;

int Update;
int Pipe1MoveTimer;
int Pipe2MoveTimer;

void setup()
{
  MX.shutdown(0, false);
  MX.setIntensity(0, 8);
  MX.clearDisplay(0);
  pinMode (BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  randomSeed(analogRead(0));
  running = false
  timer.every(30, ButtonPressScan);
  GameStart(true);
}

void GameStart(boolean ask)
{
  if (ask) 
  {
    running = true;
    game.pipe1.Xcrd = 7;
    game.pipe1.parts = PipeGen();
    game.pipe2.Xcrd = 7;
    game.pipe2.parts = PipeGen();
	imer.after(2500, Pipe1Start);
    timer.after(4500, Pipe2Start);
  } 
  else 
  {
    running = false;
    timer.stop(Update);
    timer.stop(Pipe1MoveTimer);
    timer.stop(Pipe2MoveTimer);
  }
}

void Pipe1Start()
{
  Pipe1MoveTimer = timer.every(200, Pipe1Move);
}

void Pipe2Start()
{
  Pipe2MoveTimer = timer.every(200, Pipe2Move);
}

void Pipe1Move()
{
  PipeMove(&game.pipe1);
}

void Pipe2Move()
{
  PipeMove(&game.pipe2);
}

void PipeMove(Pipe *pipe)
{
  if (pipe->Xcrd == 255) 
  {
    PipeDelete(pipe, 0);
    pipe->parts = PipeGen();
    pipe->Xcrd = 7;
  }
  else if (pipe->Xcrd < 7) 
  {
    PipeDelete(pipe, pipe->Xcrd + 1);    
  }

  PipeDraw(pipe, pipe->Xcrd);

  pipe->Xcrd = pipe->Xcrd - 1;
}

void PipeDraw(Pipe *pipe, byte x) 
{
  for (byte row = 0; row < 8; row++) 
  {
    if (pipe->parts & (0x80 >> row)) 
    {
      MX.setLed(0, row, x, HIGH);
    }
  }
}

void PipeDelete(Pipe *pipe, byte x) 
{
  for (byte row = 0; row < 8; row++) 
  {
    if (pipe->parts & (0x80 >> row)) 
    {
      MX.setLed(0, row, x, LOW);
    }
  }
}

byte PipeGen()
{
  byte hole = random(4, 7);
  byte holeBits = (1 << hole) - 1;
  byte offset = random(1, 8 - hole);
  return 0xff & ~(holeBits << offset);
}

void ButtonPressScan()
{
  static boolean init = false;
  boolean ButtonPress = digitalRead(BUTTON_PIN);

  if (ButtonPress) 
  {
    if (running = true) 
    {
      
      if (!init) 
      {
     	//change bird pos      
      }      
    }
    else 
    {
      transition();
      startGame(true); 
    }
  }
  init = ButtonPress;
  digitalWrite(LED_PIN, ButtonPress);
}


void screenburst()
{
  for (int i = 0; i < 15; ++i) 
  {
    allOn(true);
    delay(20);
    allOn(false);
    delay(20);
  }
}

void gameOver()
{
  GameStart(false);
}

void allOn(boolean on) 
{
  byte val = on ? 0xff : 0;
  for (byte n = 0; n < 8; ++n) 
  {
    MX.setRow(0, n, val);
  }
}

void loop() 
{
  timer.update();
}

void bufferMove()
{
  for(int step = 0;step < 8;step++)
  {
    for (int row = 0; row < 8; row++) 
    {
      byte pixels = game.framebuffer[row];
      if (row % 2) 
      {
        pixels = pixels >> 1;        
      }
      else 
      {
        pixels = pixels << 1;      
      }
      updateFrameRow(row, pixels);
    }
    
    delay(50);
  }  
}

void updateFrameRow(byte row, byte pixels) 
{
  MX.setRow(0, row, pixels);
  game.framebuffer[row] = pixels;
}

