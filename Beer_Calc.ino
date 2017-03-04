    #include <SPI.h>
    #include <Gamebuino.h>
    Gamebuino gb;

    int postionTriangle;
    int valeurDI1 = 10;   // 1rst part of the Density 1
    int valeurDI2 = 70;     // 2nd part of the Density 1
    int valeurDF1 = 10;   // 1rst part of the Density 2
    int valeurDF2 = 20;   // 2nd part of the Density 2
    int valeurDI=1070;      // density 1
    int valeurDF=1020;;       // density 2
    float valeurDIcor=0;      // corrected init density
    int temperature=65;
    int choix = 1;          // used to choose the modification
    float resultat=0;
    
const byte logo[] PROGMEM = {64,36,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111110,
B10000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000010,
B10001111,B10011110,B01111001,B11110000,B00000000,B00000000,B00000000,B00000010,
B10001100,B11011011,B01101101,B10011000,B00000011,B11001100,B10001111,B00000010,
B10001100,B11011011,B01101101,B10011000,B00000010,B00011110,B10001000,B00000010,
B10001111,B10011110,B01111001,B11110001,B11100010,B00010010,B10001000,B00000010,
B10001100,B11011000,B01100001,B10110000,B00000010,B00011110,B10001000,B00000010,
B10001111,B11001110,B00111001,B10111000,B00000011,B11010010,B11101111,B01000010,
B10000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000010,
B10000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000010,
B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111110,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000001,B10011001,B00110000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000010,B01100110,B11001100,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000100,B00000000,B00000110,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000100,B10000000,B01000010,
B00000000,B00000000,B00000000,B00000000,B00000000,B00001110,B00001000,B00000001,
B00000000,B00000000,B00000000,B01111000,B00000000,B00011111,B11111111,B11110001,
B00000000,B00000000,B00000001,B10000110,B00000000,B11111111,B11111111,B11111001,
B00011101,B10011101,B10110001,B00110010,B00000001,B11111101,B11011101,B11011001,
B00010101,B01011001,B00100010,B01001001,B00000011,B11111101,B11011101,B11011110,
B00011101,B10010000,B10010010,B01111001,B00000011,B10011101,B11011101,B11011100,
B00010001,B01011101,B10110001,B01001010,B00000011,B10011101,B11011101,B11011100,
B00000000,B00000000,B00000001,B10000110,B00000011,B10011101,B11011101,B11011100,
B00000000,B00000000,B00000000,B01111000,B00000011,B10011101,B11011101,B11011100,
B00000000,B00000000,B00000000,B00000000,B00000011,B10011101,B11011101,B11011100,
B00000000,B00000000,B00000000,B00000000,B00000011,B10011101,B11011101,B11011100,
B00000000,B00000000,B00000000,B00000000,B00000011,B11111101,B11011101,B11011100,
B00000000,B00000000,B00000000,B00000000,B00000001,B11111101,B11011101,B11011100,
B00000000,B00000000,B00000000,B00000000,B00000000,B11111101,B11011101,B11011100,
B00000000,B00000000,B00000000,B00000000,B00000000,B00011111,B11111111,B11111100,
B00000000,B00000000,B00000000,B00010000,B00000101,B11011110,B01100110,B10011100,
B00000000,B00000000,B00000000,B00101010,B10101010,B10011111,B01011010,B11011100,
B00000000,B00000000,B00000000,B00101001,B11000100,B10011111,B00100110,B11011100,
B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,B11111111,B11111000,
};

    void setup() {
      gb.begin();
      gb.titleScreen(F(""),logo);
    }

    void loop() {
      while (1) {
        if (gb.update()) {

  // exit game
      if (gb.buttons.pressed(BTN_C)) {
        setup();
      }
    //----choix de la ligne----------

          if (gb.buttons.released(BTN_A)) {  // released is better than repeat here to choose a menu, avoid rolling menu = changing menu only when released,
            choix = choix + 1;
            if (choix == 4) {
              choix = 1;
            }
           }

    //---------results frame----------
    gb.display.drawRect(37, 3, 45, 21);  // Result rect Alcool
    gb.display.cursorX = 40;
    gb.display.cursorY = 5;
    gb.display.print(F("Alcohol"));
    resultat=valeurDIcor-valeurDF;
    gb.display.cursorX = 40;
    gb.display.cursorY = 15;
    gb.display.println(resultat/7.6);   // formula : (DI-DF)/7.6  and il replaced DI by DI corrected by temperature

    gb.display.drawRect(37, 25, 45, 21);  // Result rect DI corr
    valeurDIcor=((0.1963596*temperature)+(0.002661056*temperature*temperature))-5.431719;   // Formula for DI corrected temperature
    valeurDIcor=valeurDIcor+valeurDI;

    gb.display.cursorX = 40;
    gb.display.cursorY = 27;
    gb.display.print(F("Corr DI"));
    gb.display.cursorX = 40;
    gb.display.cursorY = 37;
    gb.display.println(valeurDIcor);

    // Temperature--------------------------------------------------------------------------------------------------------------------------
              gb.display.cursorX = 0;
              gb.display.cursorY = 35;
              gb.display.print(F("TP:"));
              gb.display.drawRect(15, 33, 12, 10) ;
             
              gb.display.cursorX = 17;
              gb.display.cursorY = 35; 
              gb.display.print(temperature);
          if (choix == 3) {
                gb.display.drawTriangle(17, 33, 20, 30, 23, 33);
                gb.display.drawTriangle(17, 43, 20, 46, 23, 43);
       
           // ------- Controls temperature  -----------------------
       
                if (gb.buttons.repeat(BTN_UP, 1)) {
                  gb.display.fillTriangle(17, 33, 20, 30, 23, 33);    //  fill triangle : black triangle when pressed, empty triangle when not pressed
                  temperature++;
                }
                if (gb.buttons.repeat(BTN_DOWN, 1)) {
                  gb.display.fillTriangle(17, 43, 20, 46, 23, 43);
                  temperature--;
                }
       
              }

     //Densité Finale -----------------------------------------------------------------------------------------------------------------
     
          gb.display.cursorX = 0;
          gb.display.cursorY = 20;
          gb.display.print(F("DF:"));
          gb.display.drawRect(15, 18, 20, 10) ;

          gb.display.cursorX = 17;
          gb.display.cursorY = 20;
          gb.display.print(valeurDF);

          gb.display.cursorX = 17;
          gb.display.cursorY = 5;
          gb.display.println(valeurDF1);

          gb.display.cursorX = 26;
          gb.display.cursorY = 5;
          gb.display.println(valeurDF2);


          if (choix == 2) { 
            // ------- Controls  ----------------
            if (gb.buttons.repeat(BTN_RIGHT, 1)) {
              if (postionTriangle == 0) {
                postionTriangle = 10;
              }
            }

            if (gb.buttons.repeat(BTN_LEFT, 1)) {
              if (postionTriangle == 10) {
                postionTriangle = 0;
              }
            }
            if (gb.buttons.repeat(BTN_UP, 1)) {
              gb.display.fillTriangle(17 + postionTriangle, 18, 20 + postionTriangle, 15, 23 + postionTriangle, 18);
              if (postionTriangle == 10) {
                valeurDF2++;
              }
              if (postionTriangle == 0) {
                valeurDF1++;
              }
            }
            if (gb.buttons.repeat(BTN_DOWN, 1)) {
              gb.display.fillTriangle(17 + postionTriangle, 28, 20 + postionTriangle, 31, 23 + postionTriangle, 28);
              if (postionTriangle == 10) {
                valeurDF2--;
              }
              if (postionTriangle == 0) {
                valeurDF1--;
              }
            }
            gb.display.drawTriangle(17 + postionTriangle, 18, 20 + postionTriangle, 15, 23 + postionTriangle, 18);
            gb.display.drawTriangle(17 + postionTriangle, 28, 20 + postionTriangle, 31, 23 + postionTriangle, 28);
            valeurDF = valeurDF1 * 100 + valeurDF2;

            if (valeurDF1 < 0) {
              valeurDF1 = 0;
            }
            if (valeurDF2 < 0) {
              valeurDF2 = 0;
            }

            if (valeurDF1 > 99) {
              valeurDF1 = 99;
            }
            if (valeurDF2 > 99) {
              valeurDF2 = 99;
            }
          } // end if choix ==2




    //Densité Initiale  ---------------------------------------------------------------------------------------

          gb.display.cursorX = 0;
          gb.display.cursorY = 5;
          gb.display.print(F("DI:"));


          gb.display.cursorX = 17;
          gb.display.cursorY = 5;
          gb.display.println(valeurDI1);

          gb.display.cursorX = 26;
          gb.display.cursorY = 5;
          gb.display.println(valeurDI2);

          gb.display.drawRect(15, 3, 20, 10) ;
          if (choix == 1) {
            if (gb.buttons.repeat(BTN_RIGHT, 1)) {
              if (postionTriangle == 0) {
                postionTriangle = 10;
              };
            }

            if (gb.buttons.repeat(BTN_LEFT, 1)) {
              if (postionTriangle == 10) {
                postionTriangle = 0;
              };
            }
            if (gb.buttons.repeat(BTN_UP, 1)) {
              gb.display.fillTriangle(17 + postionTriangle, 3, 20 + postionTriangle, 0, 23 + postionTriangle, 3);
              if (postionTriangle == 10) {
                valeurDI2++;
              }
              if (postionTriangle == 0) {
                valeurDI1++;
              }
            }
            if (gb.buttons.repeat(BTN_DOWN, 1)) {
              gb.display.fillTriangle(17 + postionTriangle, 13, 20 + postionTriangle, 16, 23 + postionTriangle, 13);
              if (postionTriangle == 10) {
                valeurDI2--;
              }
              if (postionTriangle == 0) {
                valeurDI1--;
              }
            }

            gb.display.drawTriangle(17 + postionTriangle, 3, 20 + postionTriangle, 0, 23 + postionTriangle, 3);
            gb.display.drawTriangle(17 + postionTriangle, 13, 20 + postionTriangle, 16, 23 + postionTriangle, 13);

            valeurDI = valeurDI1 * 100 + valeurDI2;

            if (valeurDI1 < 0) {
              valeurDI1 = 0;
            }
            if (valeurDI2 < 0) {
              valeurDI2 = 0;
            }

            if (valeurDI1 > 99) {
              valeurDI1 = 99;
            }
            if (valeurDI2 > 99) {
              valeurDI2 = 99;
            }
          }
          }
        }
      }
