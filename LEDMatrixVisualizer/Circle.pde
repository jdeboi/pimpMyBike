class Circle {
  int x0;
  int y0;
  int x1;
  int y1;
  int x0P;
  int y0P;
  int w;
  int h;
  int r;
  int rP;
  boolean fillC;
  int space;
  
  public Circle(int x, int y, boolean f, int s){
    x0 = x;
    y0 = y;
    x1 = 0;
    y1 = 0;
    x0P = x0 / s;
    y0P = y0 / s;
    w = 0;
    h = 0;
    r = 0;
    rP = 0;
    fillC = f;
    space = s;
  }
  
  //x and y are mouseX and mouseY
  void drawCircleCursor(int x, int y){
     x1 = x;
     y1 = y;
     r = int(sqrt((x0-x)*(x0-x) + (y0-y)*(y0-y)));
     rP = r/space;
  }
  
  boolean inCircle(int xP, int yP){
    int f = 1 - rP;
    int ddF_x = 1;
    int ddF_y = -2 * rP;
    int x = 0;
    int y = rP;
  
    if (xP == x0P){
     if (yP == y0P+rP || yP == y0P-rP){
       return true;
     }
    }
    else if(yP == y0P){
      if (xP == x0P+rP || xP == x0P-rP){
        return true;
      }
    }
  
    while (x<y) {
      if (f >= 0) {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;
      
      
      if (xP == x0P + x && yP == y0P + y){
        return true;
      }
      else if (xP == x0P - x && yP == y0P + y){
        return true;
      }
      else if(xP == x0P + x && yP == y0P - y){
        return true;
      }
      else if (xP == x0P - x && yP == y0P - y){
        return true;
      }
      else if (xP == x0P + y && yP == y0P + x){
        return true;
      }
      else if (xP == x0P - y && yP == y0P + x){
        return true;
      }
      else if (xP == x0P + y && yP == y0P - x){
        return true;
      }
      else if (xP == x0P - y && yP == y0P - x){
        return true;
      }
    }
    if(fillC){
        if(inFill(xP, yP)){
          return true;
        }
        else{
          return false;
        }
    }
    return false;
  }
  
  boolean inFill(int xP, int yP){
    int f = 1 - rP;
    int ddF_x = 1;
    int ddF_y = -2 * rP;
    int x = 0;
    int y = rP;
  
    if(xP == x0P && yP >= y0P-rP && yP <= y0P+rP+1){
      return true;
    }
  
    while (x<y) {
      if (f >= 0) {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;
    
      if(xP == x0P+x && yP >= y0P-y && yP <= y0P+y+1){
        return true;
      }
      else if(xP == x0P-x && yP >= y0P-y && yP <= y0P+y+1){
        return true;
      }
      else if(xP == x0P+y && yP >= y0P-x && yP <= y0P+x+1){
        return true;
      }
      else if(xP == x0P-y && yP >= y0P-x && yP <= y0P+x+1){
        return true;
      }
    }
    return false;
  }
}

