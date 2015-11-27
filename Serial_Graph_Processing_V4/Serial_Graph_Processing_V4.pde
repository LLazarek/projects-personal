import processing.serial.*;
import java.io.*; // Needing for file I/O

String inString;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph 
int xPos2 = 1;

//Variables to draw a continuous line.
int lastxPos=1;
int lastheight=0;
int lastxPos2 = 1;
int lastheight2 = 0;

float kp = 0, ki = 0, kd = 0;

PrintWriter out;

void setup () {
  // set the window size:
  size(1300, 600);

  myPort = new Serial(this, "/dev/ttyACM0", 115200);

  // A serialEvent() is generated when a newline character is received :
  myPort.bufferUntil('\n');
  resetScrn();
  
  // Setup output stream to write logs to file-----------------------------------
  out = createWriter("out.dat");
  frameRate(50);
}

public void input(String theText) {
  // automatically receives results from controller input
  interpret(theText);
}

void interpret(String str){
  myPort.write(str);
  updateK(str);
}

void draw () {
  if (inString != null) {
    out.print(inString);
    updateLn1(inString);
  }
}

void keyPressed(){
  out.flush();
  out.close();
  exit();
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  inString = myPort.readStringUntil('\n');
}

float getNum(String str){
  int c, l = str.length();
  for(int i = 0; i < l; i++){
      c = str.charAt(i);
      if((c <= 57 && c >= 48) || c == 46){
        return float(str.substring(i, l));
      }
  }
  return -1;
}

void updateK(String str){
  String parts[] = str.split(",");
  for(int i = 0; i < parts.length; i++){
    if(parts[i].contains("p")){
      kp = getNum(parts[i]);
    }else if(parts[i].contains("i")){
      ki = getNum(parts[i]);
    }else if(parts[i].contains("d")){
      kd = getNum(parts[i]);
    }
  }
  println("K vals: kp = " + kp + ", ki = " + ki + ", kd = " + kd);
}

void resetScrn(){
  //Clear screen
  background(254, 254, 254);
  
  float h = height/25; // Determine the number of pixels per Newton
  //Create scale markings:
  fill(0, 0, 0); // Text color: black
  textSize(10);
  stroke(0, 0, 0); // Scale line color: black
  strokeWeight(1); // Line weight: 1
  for(int i = 1; i <= 25; ++i){
     text(str(25 - i), 5, i*h);
     line(0, i*h, width, i*h);
  }
}

void resetGraph(){
  xPos = 0;
  lastxPos = 0;
  xPos2 = 0;
  lastxPos2 = 0;
  resetScrn();
}

void updateLn1(String val){
  val = trim(val);                // trim off whitespaces.
  float inByte = float(val);           // convert to a number.
  inByte = map(inByte, 0, 25, 0, height); //map to the screen height.

  //Drawing a line from Last inByte to the new one.
  stroke(0,0,255);     //stroke color
  strokeWeight(2);        //stroke wider
  line(lastxPos, lastheight, xPos, height - inByte); 
  lastxPos= xPos;
  lastheight= int(height-inByte);

  // at the edge of the window, go back to the beginning:
  if (xPos >= width) {
    resetGraph();
  } 
  else {
    // increment the horizontal position:
    xPos++;
  }
}