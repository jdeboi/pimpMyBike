//functions to scroll text on LED matrix

void translate(int x, int y) {
    //x and y are # of steps in each dimension
    if (x > 0) {
        for (int i = 0; i < x; i++) {
            stepRight();
        }
    }
    else if (x < 0){  
        for (int i = 0; i > x; i--) {
            stepLeft();
        }
    }
    if (y > 0){
        for (int i = 0; i < y; i++) {
            stepUp();
        }
    }
    else if (y < 0){
        for (int i = 0; i > y; i--) {
            stepDown();
        }
    }
    setLEDs();
}
    
void stepRight() {
    //store the last column 
    for (int h = 0; h < height; h++) {
        storeLEDs[h] = LEDs[width-1+h*24];
    
    }
    Serial.println();
    //move pixels to the right one column at a time
    //by setting each column equal to the column on the left
    for (int w = width-1; w > 0; w--) {
        for (int h = 0; h < height; h++) {
            LEDs[w+h*24] = LEDs[w-1+h*24];
        }
    }
  
    //set the first column = to last column of array
    for (int h = 0; h < height; h++) {
        LEDs[h*24] = storeLEDs[h];
    }
}
    
void stepLeft() {
    for (int h = 0; h < height; h++) {
        storeLEDs[h] = LEDs[h*24];
    }
    
    //move pixels to the left one column at a time
    //by setting each column equal to the column on the right
    for (int w = 0; w < width-1; w++) {
        for (int h = 0; h < height; h++) {
            LEDs[w+h*24] = LEDs[w+1+h*24];
        }
    }
    
    //set the last column = to first column of the matrix
    for (int h = 0; h < height; h++) {
        LEDs[width-1+h*24] = storeLEDs[h];
    }
}
    
void stepUp() {
    //store the first row 
    
    for (int w = 0; w < width; w++) {
        storeLEDs[w] = LEDs[w];
    }
    
    //move pixels up one row at a time
    //by setting each row = to row below it
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++) {
            LEDs[w+h*24]=LEDs[w+(h+1)*24];
        }
    }
    
    //set the last row equal to the first row
    for (int w = 0; w < width; w++) {
        LEDs[w+24*(height-1)]= storeLEDs[w];
    } 
}
    
void stepDown() {
    for (int w = 0; w < width; w++) {
        storeLEDs[w] = LEDs[w+(height-1)*24];
    }
    
    //move pixels down one row at a time
    //by setting each row = to row above it
    for (int h = height-1; h > 0; h++){
        for (int w = 0; w < width; w++) {
            LEDs[w+h*24]=LEDs[w+(h-1)*24];
        }
    }

    //set the first row equal to the last row
    for (int w = 0; w < width; w++) {
        LEDs[w]= storeLEDs[w];
    } 
}   

void setLEDs() {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            matrix.drawPixel(w, h, (LEDs[w+h*24]-'0'));
        }
    }
    matrix.writeScreen();
} 




