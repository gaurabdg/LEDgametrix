typedef struct Pipe {
  
  byte parts;
  byte Xcrd;
};


typedef struct Gameplay {

  Pipe pipe1;
  Pipe pipe2;

  byte framebuffer[8];
};


