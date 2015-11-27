import processing.serial.*; // Needed for Serial comm
import java.io.*; // Needed for file I/O

String inString;  // String to store input from Serial
Serial myPort;    // Serial port object

// Graphing variables
int xPos = 1;     // horizontal position of the graph
// Continuity variables:
// (i.e. connect each point to the next point with a straight line)
int lastxPos=1;
int lastheight=0;

PrintWriter out; // File output stream object

// Setup(): performs initialization
void setup () {
  size(1300, 600); // Set the window size

  // Init Serial port
  myPort = new Serial(this, "/dev/ttyACM0", 115200);

  // serialEvent() is called when a newline character is received via Serial:
  myPort.bufferUntil('\n');
  
  resetScrn(); // Initialize the graph
  
  // Setup output stream to write logs to file out.dat
  out = createWriter("out.dat");
  frameRate(50); // Set rate for output stream
}

// draw(): called several times per second to update the GUI
void draw () {
  // Check for serial input
  if (inString != null) {
    out.print(inString); // Log data
    updateLn(inString);  // Update graph with data
  }
}

// keyPressed(): called when a key is pressed while the window is in focus
void keyPressed(){
  out.flush(); // Flush output buffer to ensure all contents are written to file
  out.close(); // Close the output buffer
  exit();      // Exit the program
}

// serialEvent(): called automatically whenever a newline character is received
// in the Serial data buffer
void serialEvent (Serial myPort) {
  inString = myPort.readStringUntil('\n'); // Read serial input as string
}

/* resetScrn():
   (Re-)Initializes the graph window by clearing the window and
   redrawing the scale markings for a new plot.
   
   @params
   void
   
   @return
   void
*/
void resetScrn(){
  //Clear screen
  background(254, 254, 254);
  
  float h = height/25; // Determine the number of pixels per Newton
  //Create scale markings:
  fill(0, 0, 0); // Text color: black
  textSize(10);
  stroke(0, 0, 0); // Scale line color: black
  strokeWeight(1); // Line weight: 1
  for(int i = 1; i <= 25; ++i){ // Add scale marker for each Newton
     text(str(25 - i), 5, i*h);
     line(0, i*h, width, i*h);
  }
}

/* resetGraph():
   Resets the graph to allow for continuous plotting of data, starting
   from the left side again.
   
   @params
   void
   
   @return
   void
*/
void resetGraph(){
  xPos = 0;
  lastxPos = 0;
  resetScrn();
}

/* updateLn():
   Updates the graph of the data currently being plotted with
   a new data point.
   
   @params
   String val           The new data point, in string form
   
   @return
   void
*/
void updateLn(String val){
  val = trim(val);                        // trim off whitespaces
  float inByte = float(val);              // convert to float
  inByte = map(inByte, 0, 25, 0, height); //map to the screen height

  //Drawing a line from last data point to the new one.
  stroke(0,0,255);                        //stroke color
  strokeWeight(2);                        //stroke wider
  line(lastxPos, lastheight, xPos, height - inByte); 
  lastxPos= xPos;
  lastheight= int(height-inByte);

  if (xPos >= width) { // Graph has reached right edge of window
    resetGraph(); // Continue from left edge
  }else{
    xPos++; // increment the horizontal position counter
  }
}