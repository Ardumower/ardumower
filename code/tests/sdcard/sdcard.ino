
#include <SD.h>

#define pinUserSwitch1 46          // user-defined switch 1

const int chipSelect = pinUserSwitch1;
File myFile;

#define CONSOLE Serial



void setup(){
  CONSOLE.begin(115200);
  delay(2000);
  CONSOLE.println("START");
  
  
  if (!SD.begin(chipSelect)) {
    CONSOLE.println("initialization failed. Things to check:");
    CONSOLE.println("1. is a card inserted?");
    CONSOLE.println("2. is your wiring correct?");
    CONSOLE.println("3. did you change the chipSelect pin to match your shield or module?");
    CONSOLE.println("Note: press reset or reopen this serial monitor after fixing your issue!");
    while (true);
  }
 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.  
  myFile = SD.open("test.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    CONSOLE.print("Writing to test.txt...");
    myFile.println("This is a test file :)");
    myFile.println("testing 1, 2, 3.");
    for (int i = 0; i < 20; i++) {
      myFile.println(i);
    }
    // close the file:
    myFile.close();
    CONSOLE.println("done.");
  } else {
    // if the file didn't open, print an error:
    CONSOLE.println("error opening test.txt");
  }  
  
  myFile = SD.open("test.txt");
  if (myFile) {
    CONSOLE.println("test.txt:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      CONSOLE.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    CONSOLE.println("error opening test.txt");
  }
}

void loop(){
  
}

