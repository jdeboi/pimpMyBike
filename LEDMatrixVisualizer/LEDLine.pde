class LEDLine {
  //these are the x and y coordinates in pixels
  //x0,y0 are the beginning of the line and x1,y1 are the endpoint
  int x0;
  int y0;
  int x1;
  int y1;
  //these variables store the matrix LED coordinates  
  int x0P;
  int y0P;
  int x1P;
  int y1P;
  //space is the space between LEDs on the visualizer
  //"on" stores whether or not the LEDs are lit up
  boolean on;
  //this linked list of points keeps track of all locations of
  //LEDs comprising this line
  LinkedList<LEDPoint> LEDPoints = new LinkedList<LEDPoint>();



  public LEDLine(int x, int y, boolean o){
    x0 = x;
    y0 = y;
    x0P = x/space;
    y0P = y/space;
    x1P = x/space;
    y1P = y/space;
    on = o;
  }
  
  //xt and yt are mouseX and mouseY
  //this function determines which LEDs make up the line
  //the line begins at the starting point (defined when first clicked)
  //and ends at the values passed into the function (where the cursor is)  
  void setLineCursor(int xt, int yt){
    LEDPoints.clear();
    x1P = xt/ space;
    y1P = yt/ space;
    int x0T = x0P;
    int y0T = y0P;
    int x1T = x1P;
    int y1T = y1P;
    boolean steep = abs(y1T - y0T) > abs(x1T - x0T);
    if (steep) {
      int xtemp0 = y0T;
      int xtemp1 = y1T;
      y0T = x0T;
      y1T = x1T;
      x0T = xtemp0;
      x1T = xtemp1;
    }

    if (x0T > x1T) {
      int xtemp0 = x0T;
      int ytemp0 = y0T;
      x0T = x1T;
      y0T = y1T;
      x1T = xtemp0;
      y1T = ytemp0;
    }
  
    int dx, dy;
    dx = x1T - x0T;
    dy = abs(y1T - y0T);
  
    int err = dx / 2;
    int ystep;
  
    if (y0T < y1T) {
      ystep = 1;
    } 
    else {
      ystep = -1;
    }
    for (; x0T<=x1T; x0T++) {
      if (steep) {
        addToShape(y0T, x0T);
      } 
      else {
        addToShape(x0T, y0T);
      }
      err -= dy;
      if (err < 0) {
        y0T += ystep;
        err += dx;
      }
    }
  }
  
  void addToShape(int x, int y){
    if(x >= 0 && x < wLEDs && y >= 0 && y < hLEDs){
      LEDPoint p = new LEDPoint(x, y, on);
      LEDPoints.add(p);
    }
  }
  
  boolean inLine(int x, int y){
    for(int i = 0; i < LEDPoints.size(); i++){
      if(LEDPoints.get(i).equal(x, y)){
        return true;
      }
    }
    return false;
  }
  
  void drawLine(){
    for(int i = 0; i < LEDPoints.size(); i++){
      LEDPoints.get(i).drawPoint();
    }
  }

  int [] getLine(){
    int [] linePoints = new int [LEDPoints.size()*2];   
    for(int i = 0; i < LEDPoints.size(); i++){
      int x = LEDPoints.get(i).x;
      int y = LEDPoints.get(i).y;
      linePoints[i*2] = x;
      linePoints[i*2+1] = y;
    }
    return linePoints;
  } 
}
