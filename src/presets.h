typedef struct Pipe {
  
  byte parts;
  byte Xcrd;
};

typedef enum Dir {
  DOWN = -1,
  STRAIGHT,
  UP
};

typedef struct Gameplay {

  float BirdVel;
  float BirdCrd;

  Pipe pipe1;
  Pipe pipe2;

  byte framebuffer[8];
};


