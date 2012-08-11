class ImageButtons
{
  int x, y;
  int w, h;
  color basecolor, highlightcolor, pressedcolor;
  color currentcolor;
  boolean over = false;
  boolean pressed = false;
  PImage base;
  PImage roll;
  PImage down;
  PImage currentimage;
  String label;
  boolean filled = false;
  boolean LEDState = true;

  ImageButtons(int ix, int iy, int iw, int ih, PImage ibase, PImage iroll, 
     PImage idown, color icolor, color ihighlight, color ipressed, String l, boolean init) 
  {
    x = ix;
    y = iy;
    w = iw;
    h = ih;
    base = ibase;
    roll = iroll;
    down = idown;
    currentimage = base;
    basecolor = icolor;
    highlightcolor = ihighlight;
    pressedcolor = ipressed;
    currentcolor = basecolor;
    label = l;
    //init determines whether the button is initially pressed or not
    pressed = init;
  }
  
  ImageButtons(int ix, int iy, int iw, int ih, color icolor, color ihighlight, 
    color ipressed, String l, boolean init) 
  {
    x = ix;
    y = iy;
    w = iw;
    h = ih;
    basecolor = icolor;
    highlightcolor = ihighlight;
    pressedcolor = ipressed;
    currentcolor = basecolor;
    label = l;
    pressed = init;
  }
  
  void update() 
  {
    over();
    if(pressed) {
      currentcolor = pressedcolor;
    } else if (over){
      currentcolor = highlightcolor;
    } else {
      currentimage = base;
      currentcolor = basecolor;
    }
  }
  
  void pressed(){
    pressed =! pressed;
  }
  
  void over() 
  {
    if( overRect() ) {
      over = true;
    } else {
      over = false;
    }
  }
  
  boolean overRect() {
    if (mouseX >= x && mouseX <= x+w && 
      mouseY >= y && mouseY <= y+h) {
      return true;
    } 
    else {
      return false;
    }
  }
  
  void display() 
  {
    noStroke();
    fill(currentcolor);
    rect(x, y, w, h);
    stroke(0);
    
    
    if(label == "Circle"){
      setShapeColors();
      ellipse(x+5, y+5, w/2, w/2);
      fill(0);
      text(label, x+4, y+buttonWidth*.92);
    }
    else if(label == "Rect"){
      setShapeColors();
      rect(x+5, y+5, w/2, w/2);
      fill(0);
      text(label, x+4, y+buttonWidth*.92);
    }
    else if(label == "Line"){
      setShapeColors();
      line(x+10, y+10, x+w-10, y+30);
      fill(0);
      text(label, x+4, y+buttonWidth*.92);
    }
    else{
      image(currentimage, x+3, y+3);
      fill(0);
      text(label, x+4, y+buttonWidth*.92);
    }
  }
  
  void switchFilled(){
    filled =! filled;
  }
  
  void switchOn(){
    LEDState =! LEDState;
  }
  
  void setShapeColors(){
    if(filled && LEDState){
      stroke(255, 0, 0);
      fill(255, 0, 0);
    }
    else if(filled && LEDState == false){
      stroke(0);
      fill(0);
    }
    else if(LEDState && filled == false){
      noFill();
      stroke(255, 0, 0);
    }
    else{
      noFill();
      stroke(0);
    }
  }
}

