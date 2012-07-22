class LEDPoint {
  int x;
  int y;
  
  public LEDPoint (int xt, int yt){
    x = xt;
    y = yt;
  }
  
  boolean equal(int xt, int yt){
    if(xt == x && yt == y){
      return true;
    }
    else{
      return false;
    }
  }
}
