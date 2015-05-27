Jenna deBoisblanc
July, 2012
Shout out to Adafruit Industries

This LED Visualizer makes it easy to design patterns for use with the 16x24 Red LED Matrix Panel - Chainable HT1632C Driver, which is produced by Adafruit Industries and is available here: 
https://www.adafruit.com/products/555.

Download the entire LEDMatrixVisualizer folder and open LEDMatrixVisualizer in Processing.

Once your design is complete, you can export the pixel values to a text file, or you can import previous designs (edit the file paths at the top of the sketch). The print button allows you to generate a bitmap of the LED values (either 1 or 
0). If you're using the Arduino bike circuit code, you can copy/paste the LED values into the brake light or turning indicator LED pixel arrays.

All of the shapes are stored in linked lists.  At some point, it'd be nice to write functions to animate individual shape objects.