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
  int space;
  int on;
  //this linked list of points keeps track of all locations of
  //LEDs comprising this line
  LinkedList<LEDPoint> LEDPoints = new LinkedList<LEDPoint>();



  public LEDLine(int x, int y, int o){
    x0 = x;
    y0 = y;
    space = s;
    x0P = x/space;
    y0P = y/space;
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
    boolean steep = abs(y1P - y0P) > abs(x1P - x0P);
    if (steep) {
      int xtemp0 = y0P;
      int xtemp1 = y1P;
      y0P = x0P;
      y1P = x1P;
      x0P = xtemp0;
      x1P = xtemp1;
    }

    if (x0P > x1P) {
      int xtemp0 = x0P;
      int ytemp0 = y0P;
      x0P = x1P;
      y0P = y1P;
      x1P = xtemp0;
      y1P = ytemp0;
    }
  
    int dx, dy;
    dx = x1P - x0P;
    dy = abs(y1P - y0P);
  
    int err = dx / 2;
    int ystep;
  
    if (y0P < y1P) {
      ystep = 1;
    } 
    else {
      ystep = -1;
    }
    for (; x0P<=x1P; x0P++) {
      if (steep) {
        addToShape(y0P, x0P);
      } 
      else {
        addToShape(x0P, y0P);
      }
      err -= dy;
      if (err < 0) {
        y0P += ystep;
        err += dx;
      }
    }
  }
  
  void addToShape(int x, int y){
    LEDPoint p = new LEDPoint(x, y);
    LEDPoints.add(p);
  }
  
  boolean inLine(int x, int y){
    for(int i = 0; i < LEDPoints.size(); i++){
      if(LEDPoints.get(i).equal(x, y)){
        return true;
      }
      else{
        return false;
      }
    }
  }
  
  //this function takes 
  //void translateShape(int x, int y){
  //}
  
}
