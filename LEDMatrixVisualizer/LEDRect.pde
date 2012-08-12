class LEDRect {
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
  int w;
  int h;
  //"on" stores whether or not the LEDs are lit up
  boolean state;
  boolean fillR;
  //this linked list of points keeps track of all locations of
  //LEDs comprising this line
  LinkedList<LEDPoint> LEDPoints = new LinkedList<LEDPoint>();



  public LEDRect(int x, int y){
    x0 = x;
    y0 = y;
    x0P = x/space;
    y0P = y/space;
  }
  
  //xt and yt are mouseX and mouseY
  //this function determines which LEDs make up the line
  //the line begins at the starting point (defined when first clicked)
  //and ends at the values passed into the function (where the cursor is)  
  void setRectCursor(int xt, int yt, boolean f, boolean l){
    LEDPoints.clear();
    fillR = f;
    x1P = xt/ space;
    y1P = yt/ space;
    w = x1P - x0P;
    h = y1P - y0P;
    state = l;
    if(w > 0){
      for(int i = 0; i <= w; i++){
        addToShape(x0P + i, y0P);
        addToShape(x0P + i, y0P+h);
      }
    }
    else if(w < 0){
      for(int i = 0; i < abs(w)+1; i++){
        addToShape(x0P - i, y0P);
        addToShape(x0P - i, y0P+h);
      }
    }
    if(h > 0){
      for(int i = 0; i <= h; i++){
        addToShape(x0P, y0P+i);
        addToShape(x0P+w, y0P+i);
      }
    }
    else if(h < 0){
      for(int i = 0; i < abs(h); i++){
        addToShape(x0P, y0P-i);
        addToShape(x0P+w, y0P-i);
      }
    }
    if(fillR){
      setFill();
    }
  }

  void setFill(){
    if(w > 0 && h > 0){
      for (int i = x0P; i < x1P; i++) {
        for (int j = y0P; j < y1P; j++) {
          addToShape(i, j);
        }
      }
    }
    else if(w > 0 && h < 0){
      for (int i = x0P; i < x1P; i++) {
        for (int j = y1P; j < y0P; j++) {
          addToShape(i, j);
        }
      }
    }
    else if(w < 0 && h > 0){
      for (int i = x1P; i < x0P; i++) {
        for (int j = y0P; j < y1P; j++) {
          addToShape(i, j);
        }
      }
    }
    else if(w < 0 && h < 0){
      for (int i = x1P; i < x0P; i++) {
        for (int j = y1P; j < y0P; j++) {
          addToShape(i, j);
        }
      }
    }
  }
  
  void addToShape(int x, int y){
    if(x >= 0 && x < wLEDs && y >= 0 && y < hLEDs){
      LEDPoint p = new LEDPoint(x, y, state);
      LEDPoints.add(p);
    }
  }
  
  boolean inRect(int x, int y){
    if(x >= x0P && x < x0P + w && y >= y0P && y < y0P+h){
      return true;
    }
    else{
      return false;
    }
  }
  
  int [] getRect(){
    int [] rectPoints = new int [LEDPoints.size()*2];   
    for(int i = 0; i < LEDPoints.size(); i++){
      int x = LEDPoints.get(i).x;
      int y = LEDPoints.get(i).y;
      rectPoints[i*2] = x;
      rectPoints[i*2+1] = y;
    }
    return rectPoints;
  } 
  
  void drawRect(){
    for(int i = 0; i < LEDPoints.size(); i++){
      LEDPoints.get(i).drawPoint();
    }
  }
}
