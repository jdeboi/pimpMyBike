class LEDLine {
  int x0;
  int y0;
  int x1;
  int y1;
  int x0P;
  int y0P;
  int space;

  public LEDLine(int x, int y, int s){
    x0 = x;
    y0 = y;
    space = s;
    x0P = x/space;
    y0P = y/space;
  }
  
  //void inLine(int xP, int yP){}
    

  void setLines(int x0, int y0, int x1, int y1, int on){
   boolean steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
      int xtemp0 = y0;
      int xtemp1 = y1;
      y0 = x0;
      y1 = x1;
      x0 = xtemp0;
      x1 = xtemp1;
    }

    if (x0 > x1) {
      int xtemp0 = x0;
      int ytemp0 = y0;
      x0 = x1;
      y0 = y1;
      x1 = xtemp0;
      y1 = ytemp0;
    }
  
    int dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);
  
    int err = dx / 2;
    int ystep;
  
    if (y0 < y1) {
      ystep = 1;
    } 
    else {
      ystep = -1;
    }
    for (; x0<=x1; x0++) {
      if (steep) {
        setPixel(y0, x0, on);
      } else {
        setPixel(x0, y0, on);
      }
      err -= dy;
      if (err < 0) {
        y0 += ystep;
        err += dx;
      }
    }
  }
}
