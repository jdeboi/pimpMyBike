class ImageButtons
{
  int x, y;
  int wButton, hButton;
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
  int xTextPad = 3;
  int yTextPad;

  ImageButtons(int ix, int iy, int iw, int ih, PImage ibase, PImage iroll, 
     PImage idown, color icolor, color ihighlight, color ipressed, String l, boolean init) 
  {
    x = ix;
    y = iy;
    wButton = iw;
    hButton = ih;
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
    yTextPad = hButton -4;
  }
  
  ImageButtons(int ix, int iy, int iw, int ih, color icolor, color ihighlight, 
    color ipressed, String l, boolean init) 
  {
    x = ix;
    y = iy;
    wButton = iw;
    hButton = ih;
    basecolor = icolor;
    highlightcolor = ihighlight;
    pressedcolor = ipressed;
    currentcolor = basecolor;
    label = l;
    pressed = init;
    yTextPad = hButton -4;
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
  
  void reset(){
    pressed = false;
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
    if (mouseX >= x && mouseX <= x+wButton && 
      mouseY >= y && mouseY <= y+hButton) {
      text(label, x+xTextPad, y+yTextPad);
      return true;
    } 
    else {
      //text(label, x+xTextPad, y+yTextPad);
      return false;
    }
  }
  
  void display() 
  {
    noStroke();
    fill(currentcolor);
    rect(x, y, wButton, hButton);
    stroke(0);
    textSize(12);
    
    if(label == "Circle"){
      setShapeColors();
      ellipse(x+5, y+8, wButton/2, wButton/2);
      fill(0);
      //text(label, x+xTextPad, y+yTextPad);
    }
    else if(label == "Rect"){
      setShapeColors();
      rect(x+5, y+8, wButton/2, wButton/2);
      fill(0);
      //text(label, x+xTextPad, y+yTextPad);
    }
    else if(label == "Line"){
      setShapeColors();
      line(x+10, y+10, x+wButton-10, y+30);
      fill(0);
      //text(label, x+xTextPad, y+yTextPad);
    }
    else if(label == "Clear"){
      image(currentimage, x+3, y+3);
      fill(0);
      //text(label, x+xTextPad, y+yTextPad);
    }
    else{
      image(currentimage, x+3, y+3);
      fill(0);
      //text(label, x+xTextPad, y+yTextPad);
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

