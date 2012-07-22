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
  boolean on;
  boolean fillR;
  //this linked list of points keeps track of all locations of
  //LEDs comprising this line
  LinkedList<LEDPoint> LEDPoints = new LinkedList<LEDPoint>();



  public LEDRect(int x, int y, boolean f, boolean o){
    x0 = x;
    y0 = y;
    x0P = x/space;
    y0P = y/space;
    fillR = f;
    on = o;
  }
  
  //xt and yt are mouseX and mouseY
  //this function determines which LEDs make up the line
  //the line begins at the starting point (defined when first clicked)
  //and ends at the values passed into the function (where the cursor is)  
  void setRectCursor(int xt, int yt){
    LEDPoints.clear();
    x1P = xt/ space;
    y1P = yt/ space;
    w = x1P - x0P;
    h = y1P - y0P;
    for(int i = 0; i < w; i++){
      addToShape(x0P + i, y0P);
      addToShape(x0P + i, y0P+h-1);
    }
    for(int i = 0; i < h; i++){
      addToShape(x0P, y0P+i);
      addToShape(x0P+w-1, y0P+i);
    }
    if(fillR){
      setFill();
    }
  }

  void setFill(){
    for (int i = x0P; i < x0P+w; i++) {
      for (int j = y0P; j < y0P+h; j++) {
        addToShape(i, j);
      }
    }
  }
  
  void addToShape(int x, int y){
    LEDPoint p = new LEDPoint(x, y, on);
    LEDPoints.add(p);
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
    for(int i = 0; i < rectPoints.length; i = i+2){
      int x = LEDPoints.get(i/2).x;
      int y = LEDPoints.get(i/2).y;
      rectPoints[i] = x;
      rectPoints[i+1] = y;
    }
    return rectPoints;
  }
  
  void drawRect(){
    for(int i = 0; i < LEDPoints.size(); i++){
      LEDPoints.get(i).drawPoint();
    }
  }
}
