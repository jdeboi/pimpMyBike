class LEDPoint {
  int x;
  int y;
  boolean on;
  
  public LEDPoint (int xt, int yt, boolean o){
    x = xt;
    y = yt;
    on = o;
  }
  
  boolean equal(int xt, int yt){
    if(xt == x && yt == y){
      return true;
    }
    else{
      return false;
    }
  }
  
  void drawPoint(){
    fill(255);
    if(on){
      fill(255, 0, 0);
    }
    ellipse(x*space+padding, y*space+padding, circleD, circleD);
  }
}
