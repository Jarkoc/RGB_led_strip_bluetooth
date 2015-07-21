
/*
 PROJECT: ArduDroid 
 PROGRAMMER: Hazim Bitar (techbitar at gmail dot com)
 DATE: Oct 31, 2013
 FILE: ardudroid.ino
 LICENSE: Public domain
*/

#define START_CMD_CHAR '*'
#define END_CMD_CHAR '#'
#define DIV_CMD_CHAR '|'
#define CMD_DIGITALWRITE 10
#define CMD_ANALOGWRITE 11
#define CMD_TEXT 12
#define CMD_READ_ARDUDROID 13
#define MAX_COMMAND 20  // max command number code. used for error checking.
#define MIN_COMMAND 10  // minimum command number code. used for error checking. 
#define IN_STRING_LENGHT 40
#define MAX_ANALOGWRITE 255
#define PIN_HIGH 3
#define PIN_LOW 2

String inText;

void setup() {
  Serial.begin(9600);
  Serial.println("Brian van Vlymen");
  Serial.flush();
}

void loop()
{
  Serial.flush();
  int ard_command = 0;
  int pin_num = 0;
  int pin_value = 0;

  char get_char = ' ';  //read serial

  // wait for incoming data
  if (Serial.available() < 1) return; // if serial empty, return to loop().

  // parse incoming command start flag 
  get_char = Serial.read();
  if (get_char != START_CMD_CHAR) return; // if no command start flag, return to loop().

  // parse incoming command type
  ard_command = Serial.parseInt(); // read the command
  
  // parse incoming pin# and value  
  pin_num = Serial.parseInt(); // read the pin
  pin_value = Serial.parseInt();  // read the value

  // 1) GET TEXT COMMAND FROM ARDUDROID
  if (ard_command == CMD_TEXT){   
    inText =""; //clears variable for new input   
    while (Serial.available())  {
      char c = Serial.read();  //gets one byte from serial buffer
      delay(5);
      if (c == END_CMD_CHAR) { // if we the complete string has been read
        // add your code here
        break;
      }              
      else {
        if (c !=  DIV_CMD_CHAR) {
          inText += c; 
          delay(5);
        }
      }
    }
  }

  // 2) GET digitalWrite DATA FROM ARDUDROID
  if (ard_command == CMD_DIGITALWRITE){  
    if (pin_value == PIN_LOW) pin_value = LOW;
    else if (pin_value == PIN_HIGH) pin_value = HIGH;
    else return; // error in pin value. return. 
    set_digitalwrite( pin_num,  pin_value);  // Uncomment this function if you wish to use 
    return;  // return from start of loop()
  }

  // 3) GET analogWrite DATA FROM ARDUDROID
  if (ard_command == CMD_ANALOGWRITE) {  
    analogWrite(  pin_num, pin_value ); 
    // add your code here
    return;  // Done. return to loop();
  }

  // 4) SEND DATA TO ARDUDROID
  if (ard_command == CMD_READ_ARDUDROID) { 
    // char send_to_android[] = "Place your text here." ;
    // Serial.println(send_to_android);   // Example: Sending text
    Serial.print(" Analog 0 = "); 
    Serial.println(analogRead(A0));  // Example: Read and send Analog pin value to Arduino
    return;  // Done. return to loop();
  }
}

// 2a) select the requested pin# for DigitalWrite action
void set_digitalwrite(int pin_num, int pin_value)
{
  switch (pin_num) {  
  case 13: // this is for standard light frame
  Serial.println("Standard lights frame");
  {
      int g = 6 ;
      int r = 5 ;
      int b = 3 ;
      int var = 0;
      

      while(var <= 100)
      {    
       for (r = 0; r <= 255; r++)// fade up red
        {
            analogWrite(5 , r );
            delay(30);
        } 
        
        for (r = 255; r >= 0 ; r--)// fade down red
        {
            analogWrite(5 , r );
            delay(30);
        }
      
        for (g = 0; g <= 255; g++)// fade up white
        {
        analogWrite( 3 , g);
        analogWrite( 6 , g);
        analogWrite( 5, g);
        delay(30);
        }
        
        for (g = 255; g >= 0; g--)// fade down white
        {
        analogWrite( 6 , g);
        analogWrite( 5 , g);
        analogWrite( 3, g);
        delay(30);
        }
        
        for (r = 0; r <= 85; r++) // fade up purple
        {
          //analogWrite( 10 , r);
          analogWrite( 3 , r);
          analogWrite( 5, r); 
           delay(30);
        }
     
        for (r = 85; r >= 0; r--) // fade down purple
        {
          //analogWrite( 10 , r);
          analogWrite( 5 , r);
          analogWrite( 3, r); 
           delay(30);
        }
        
        for (g = 0; g <= 255; g++)// fade up white
        {
        analogWrite( 6 , g);
        analogWrite( 3 , g);
        analogWrite( 5, g);
        delay(10);
        }
        
        for (g = 255; g >= 0; g--)// fade down white
        {
        analogWrite( 6 , g);
        analogWrite( 3 , g);
        analogWrite( 5, g);
        delay(20);
        }
        var++;
      }// while (var <= *); 
  }        
break;

  case 12: // cops siren alert! 
  Serial.println("cop siren");
  {
   int r = 5;
   int b = 3;
   int g = 6;
   int var = 0;

   while(var <= 100)
    {
      pinMode(5, OUTPUT); 
      digitalWrite(5, HIGH); // red HIGH   
      delay(50);
      digitalWrite(5, LOW);  // red low 
      delay(50);
      pinMode(3, OUTPUT);
      digitalWrite(3, HIGH); // blue high
      delay(50);
      digitalWrite(3, LOW); // blue low 
      delay(50);
      pinMode(6,OUTPUT);
      digitalWrite(6, HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(3, HIGH);
      delay(50);
      digitalWrite(6, LOW);
      digitalWrite(5,LOW);
      digitalWrite(3, LOW);
      delay(50);
      var++;    
   }
 }
break;
 

  case 11:// Happy New Year 
  Serial.println("Happy New Year");
  {
    int g = 6 ;
    int r = 5 ;
    int b = 3 ;
    int var = 0;

    while(var <= 2)
     {
       for (r = 0; r <= 255; r++)// fade up light blue
        {
            analogWrite(6 , r );
            analogWrite(3 , r );
            delay(30);
        } 
        
        for (r = 255; r >= 0 ; r--)// fade down lightblue
        {
            analogWrite(6 , r );
            analogWrite(3 , r );
            delay(30);
        }
      
       for (g = 0; g <= 255; g++)// fade up blue
        {
        analogWrite( 3, g);
        delay(30);
        }
        
        for (g = 255; g >= 0; g--)// fade down blue
        {
       
        analogWrite( 3, g);
        delay(30);
        }
        
        for (r = 0; r <= 255; r++) // fade up white
        {
          analogWrite( 5 , r);
          analogWrite( 6, r);
          analogWrite( 3, r); 
           delay(30);
        }
     
       for (r = 255; r >= 0; r--) // fade down white
        {
          analogWrite( 5 , r);
          analogWrite( 6, r);
          analogWrite( 3, r); 
           delay(30);
        }
        var++;
    } // while (var < * );
  } // after the serial.println comments.  
break;


  case 10: // Happy Valentine Day
  Serial.println("Happy Valentine Day");
  {
    int g = 6 ;
    int r = 5 ;
    int b = 3 ;
    int var = 0;

    while(var <= 2)
    {
      for (r = 0; r <= 255; r++) // fade up red 
      { 
        analogWrite(5, r);
        delay(20);
      }
      for (r = 255; r >= 0; r--) // fade down red 
      { 
        analogWrite(5, r);
        delay(20);
      }
      
      for ( r = 0; r <= 255; r++) // fade up red
      {
       analogWrite(5, r);
       delay(5); 
      }
      
      for (b = 0; b <= 153; b++) // fade up pink 
      { 
        analogWrite(3, b);
        //analogWrite(5, b);
        delay(30);
      }
      
      for (b = 153; b >= 0; b--) // fade down pink
      { 
        analogWrite(3, b);
        //analogWrite(5, b);
        delay(30);
      }
      
      for ( r = 255; r >= 0; r--) // fade down red
      {
       analogWrite(5, r);
       delay(10); 
      }
      
      for (g = 0; g <= 255; g++)// fade up white
      {
      analogWrite( 6 , g);
      analogWrite( 3 , g);
      analogWrite( 5, g);
      delay(20);
      }
      
      for (g = 255; g >= 0; g--)// fade down white
      {
      analogWrite( 6 , g);
      analogWrite( 3 , g);
      analogWrite( 5, g);
      delay(20);
      }
      var++;  
    } // while (var <= *); 
  } // after the serial.println comments.
break;
    case 9: // Patrick Day
  Serial.println("Patrick Day");
  {
    int g = 6 ;
    int r = 5 ;
    int b = 3 ;
    int var = 0;

    while(var <= 2)
    {
      for (g = 0; g <= 255; g++) // fade up green 
      { 
        analogWrite(6, g);
        delay(20);
      }
      for (g = 255; g >= 153; g--) // its okay number fade down green 
      { 
        analogWrite(6, g);
        delay(20);
      }
      for (b = 0; b <= 102; b++) // fade up blue 
      { 
        analogWrite(3, b);
        delay(20);
      }
      for (b = 153; b >= 0; b--)
      {
         analogWrite(3, b);
         analogWrite(6, b);
         delay(20);  
      }
      for (r = 0; r <= 255; r++) // fade up white 
      { 
        analogWrite(5, r);
        analogWrite(6, r);
        analogWrite(3, r);
        delay(20);
      }
      for (r = 255; r >= 0; r--) // fade down white 
      { 
        analogWrite(5, r);
        analogWrite(6, r);
        analogWrite(3, r);
        delay(10);
      }
      var++;
    }
  }     
    break;
    
  case 8: // Easter
  Serial.println("Easter");
  {
    int g = 6 ;
    int r = 5 ;
    int b = 3 ;
    int var = 0;

    while(var <= 2)
    {
      for (r = 0; r <= 153; r++) // fade up green  
      { 
        analogWrite(6, r);
        delay(20);
      }
      for (r = 0; r <= 102; r++) // fade up blue
      {
        analogWrite(3,r);
        delay(20);
      }
      for (r = 102; r >= 0; r--) // fade down blue
      { 
        analogWrite(3, r);
        delay(20);
      }
      for (r = 153; r >= 0; r--) // fade down green (light green)
      { 
        analogWrite(6, r);
        delay(20);
      }
      for (r = 0; r <= 255; r++) // fade up red and green
      { 
        analogWrite(5, r);
        analogWrite(6, r);
        delay(20);
      }
      for (r = 255; r >= 0; r--) // fade down red and green  (yellow)
      { 
        analogWrite(5, r);
        analogWrite(6, r);
        delay(20);
      }
      
      for (r = 0; r <= 153; r++) // fade up blue
      { 
        analogWrite(3, r);
        delay(10);
      }
      for (r = 0; r <= 255; r++) // fade up red
      { 
        analogWrite(5, r);
        delay(10);
      }
      
      for( r = 153; r >= 0; r--) // fade down blue
        {
          analogWrite(3, r);
          delay(20);
        } 
      for( r = 255; r >= 0; r--) // fade down red
        {
          analogWrite(5, r);
          delay(20);
        } 

      for (r = 255; r >= 0; r++) // fade up light blue  
       { 
         analogWrite(6, r);
         analogWrite(3, r);
         delay(10);
       }
      for (r = 0; r >= 255; r--) // fade down light blue
       { 
         analogWrite(6, r);
         analogWrite(3, r);
         delay(10);
       }
    
      var++;
    }
  } 
  break;
  case 7:
    pinMode(7, OUTPUT);
    Serial.println("Happy of 4th July");
  {
   int r = 5;
   int b = 3;
   int g = 6;
   int var = 0;

   while(var <= 100)
    {
        for( r = 0; r <= 255; r++) // fade up white
        {
          analogWrite(3, r);
          analogWrite(5, r);
          analogWrite(6, r);
          delay(20);
        }
          digitalWrite (5, LOW); 
          digitalWrite (6, LOW); 
          digitalWrite (3, LOW); 
          delay(1000);
     
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          
        for( r = 150; r >= 0; r--) // fade down red all done!!
        {
          analogWrite(5, r);
          delay(30);
        }
        for( r = 0; r <= 255; r++) // fade up white
        {
          analogWrite(3, r);
          analogWrite(5, r);
          analogWrite(6, r);
          delay(20);
        }
          digitalWrite (5, LOW); 
          digitalWrite (6, LOW); 
          digitalWrite (3, LOW); 
          delay(1000);

          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW); // blue low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW); // blue low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW); // blue low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW); // blue low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW); // blue low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW); // blue low 
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
      for( r = 150; r >= 0; r--) // fade down blue all done!
        {
          analogWrite(3, r);
          delay(30);
        }

        for( r = 0; r <= 255; r++) // fade up white
        {
          analogWrite(3, r);
          analogWrite(5, r);
          analogWrite(6, r);
          delay(30);
        }
          digitalWrite (5, LOW); 
          digitalWrite (6, LOW); 
          digitalWrite (3, LOW); 
          delay(3000);

          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW); // blue low
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW); // blue low
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW); // blue low
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW); // red low 
          delay(50);
////////////////////////////////
          digitalWrite(6, LOW); // white low required
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);

          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW);
          delay(50);
          digitalWrite(3,HIGH);
          delay(50);
          digitalWrite(3,LOW);
          delay(50);
          digitalWrite(3,HIGH);
          delay(50);
          digitalWrite(3,LOW);
          delay(50);
          digitalWrite(3,HIGH);
          delay(50);
          digitalWrite(3,LOW); // blue low
          delay(50);

          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);

          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW);
          delay(50);
          digitalWrite(5,HIGH);
          delay(50);
          digitalWrite(5,LOW);
          delay(50);
          digitalWrite(5,HIGH);
          delay(50);
          digitalWrite(5,LOW);
          delay(50);
          digitalWrite(5,HIGH);
          delay(50);
          digitalWrite(5,LOW); // red low
          delay(50);
          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW);
          delay(50);
          digitalWrite(3,HIGH);
          delay(50);
          digitalWrite(3,LOW);
          delay(50);
          digitalWrite(3,HIGH);
          delay(50);
          digitalWrite(3,LOW);
          delay(50);
          digitalWrite(3,HIGH);
          delay(50);
          digitalWrite(3,LOW); // blue low
          delay(50);

          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);

          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW);
          delay(50);
          digitalWrite(5,HIGH);
          delay(50);
          digitalWrite(5,LOW);
          delay(50);
          digitalWrite(5,HIGH);
          delay(50);
          digitalWrite(5,LOW);
          delay(50);
          digitalWrite(5,HIGH);
          delay(50);
          digitalWrite(5,LOW); // red low
          delay(50);
          digitalWrite(3,HIGH); // blue high
          delay(50);
          digitalWrite(3,LOW);
          delay(50);
          digitalWrite(3,HIGH);
          delay(50);
          digitalWrite(3,LOW);
          delay(50);
          digitalWrite(3,HIGH);
          delay(50);
          digitalWrite(3,LOW);
          delay(50);
          digitalWrite(3,HIGH);
          delay(50);
          digitalWrite(3,LOW); // blue low
          delay(50);

          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);
          digitalWrite(6, HIGH); // white high
          digitalWrite(5,HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(6, LOW); // white low
          digitalWrite(5,LOW);
          digitalWrite(3, LOW);
          delay(50);

          digitalWrite(5,HIGH); // red high
          delay(50);
          digitalWrite(5,LOW);
          delay(50);
          digitalWrite(5,HIGH);
          delay(50);
          digitalWrite(5,LOW);
          delay(50);
          digitalWrite(5,HIGH);
          delay(50);
          digitalWrite(5,LOW);
          delay(50);
          digitalWrite(5,HIGH);
          delay(50);
          digitalWrite(5,LOW); // red low
          delay(50);
      for( r = 150; r >= 0; r--) // fade down white
        {
          analogWrite(3, r);
          analogWrite(5, r);
          analogWrite(6, r);
          delay(50);
        }
      var++;    
   }
 }
break;
  case 6: // Halloween
    Serial.println("Halloween");
  {
    int g = 6 ;
    int r = 5 ;
    int b = 3 ;
    int var = 0;

    while(var <= 10)
    {
      for (r = 0; r <= 255; r++) // fade up red 
      { 
        analogWrite(5, r);
        delay(20);
      }
      for (r = 0; r <= 153; r++) // fade up green
      {
        analogWrite(6,r);
        delay(20);
      }
      for (r = 153; r >= 0; r--) // fade down green
      {
        analogWrite(6,r);
        delay(20);
      }
      for (r = 255; r >= 0; r--) // fade down red
      {
        analogWrite(5,r);
        delay(20);
      }
      for (r = 0; r <= 85; r++) // fade up red
      {
        analogWrite(5,r);
        delay(5);
      }
      for (r = 0; r <= 85; r++) // fade up blue
      {
        analogWrite(3,r);
        delay(20);
      }
      for (r = 85; r >= 0; r--) // fade down blue
      {
        analogWrite(3,r);
        delay(20);
      }
      for (r = 85; r >= 0; r--) // fade down red
      {
        analogWrite(5,r);
        delay(20);
      }
      for (r = 0; r <= 187; r++) // fade up red
      {
        analogWrite(5,r);
        delay(20);
      }
      for (r = 187; r >= 0; r--) // fade down red
      {
        analogWrite(5,r);
        delay(20);
      }
      var++;
    }
  }
break;
  case 5: // XMAS
    Serial.println("XMAS");
  {
    int g = 6 ;
    int r = 5 ;
    int b = 3 ;
    int var = 0;

    while(var <= 10)
    {
      for (r = 0; r <= 255; r++) // fade up red 
      { 
        analogWrite(5, r);
        delay(20);
      }
      for (r = 255; r >= 0; r--) // fade down red
      {
        analogWrite(5,r);
        delay(20);
      }
      for (r = 0; r <= 255; r++) // fade up green 
      { 
        analogWrite(6, r);
        delay(20);
      }
      for (r = 255; r >= 0; r--) // fade down green
      {
        analogWrite(6,r);
        delay(20);
      }

      var++;
    }
  }
break;
  case 4:
    pinMode(4, OUTPUT);
    digitalWrite(4, pin_value);         
    // add your code here 
    break;
  case 3:
    pinMode(3, OUTPUT);
    digitalWrite(3, pin_value);         
    // add your code here 
    break;
  case 2:
    pinMode(2, OUTPUT);
    digitalWrite(2, pin_value);         
    // add your code here 
    break;
    
    // default: 
    // if nothing else matches, do the default
    // default is optional
    
  } 
}

