//functions to scroll text on LED matrix
/*
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
    
    Serial.print("lC");
    for (int h = 0; h < height; h++) {
        lastCol[h] = LEDs[width-1+h*24];
        Serial.print(lastCol[h]);
    
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
        LEDs[h*24] = lastCol[h];
    }
}
    
void stepLeft() {
    //store the first column 
    
    for (int h = 0; h < height; h++) {
        firstCol[h] = LEDs[h*24];
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
        LEDs[width-1+h*24] = firstCol[h];
    }
}
    
void stepUp() {
    //store the first row 
    
    for (int w = 0; w < width; w++) {
        firstRow[w] = LEDs[w];
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
        LEDs[w+24*(height-1)]= firstRow[w];
    } 
}
    
void stepDown() {
    //store the last row 
    
    for (int w = 0; w < width; w++) {
        lastRow[w] = LEDs[w+(height-1)*24];
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
        LEDs[w]= lastRow[w];
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

*/

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
    int lastCol[height];
    for (int h = 0; h < height; h++) {
        lastCol[h] = LEDs[width - 1][h];
    }
    
    //move pixels to the right one column at a time
    //by setting each column equal to the column on the left
    for (int w = width; w > 0; w--) {
        for (int h = 0; h < height; h++) {
            LEDs[w][h] = LEDs[w-1][h];
        }
    }
    //set the first column = to last column of array
    for (int h = 0; h < height; h++) {
        LEDs[0][h] = lastCol[h];
    }
}
    
void stepLeft() {
    //store the first column 
    int firstCol[height];
    for (int h = 0; h < height; h++) {
        firstCol[h] = LEDs[0][h];
    }
    
    //move pixels to the left one column at a time
    //by setting each column equal to the column on the right
    for (int w = 0; w < width-1; w++) {
        for (int h = 0; h < height; h++) {
            LEDs[w][h] = LEDs[w+1][h];
        }
    }
    
    //set the last column = to first column of the matrix
    for (int h = 0; h < height; h++) {
        LEDs[width-1][h] = firstCol[h];
    }
}
    
void stepUp() {
    //store the first row 
    int firstRow[width];
    for (int w = 0; w < width; w++) {
        firstRow[w] = LEDs[w][0];
    }
    
    //move pixels up one row at a time
    //by setting each row = to row below it
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++) {
            LEDs[w][h]=LEDs[w][h+1];
        }
    }
    
    //set the last row equal to the first row
    for (int w = 0; w < width; w++) {
        LEDs[w][height-1]= firstRow[w];
    } 
}
    
void stepDown() {
    //store the last row 
    int lastRow[width];
    for (int w = 0; w < width; w++) {
        lastRow[w] = LEDs[w][height-1];
    }
    
    //move pixels down one row at a time
    //by setting each row = to row above it
    for (int h = height-1; h > 0; h++){
        for (int w = 0; w < width; w++) {
            LEDs[w][h]=LEDs[w][h-1];
        }
    }

    //set the first row equal to the last row
    for (int w = 0; w < width; w++) {
        LEDs[w][0]= lastRow[w];
    } 
}    

void clearLEDs() {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            LEDs[w][h] = 0;
        }
    }
}

    
void setLEDs() {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            matrix.drawPixel(w, h, LEDs[w][h]-'0');
        }
    }
    matrix.writeScreen();
}  

