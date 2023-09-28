#include <LiquidCrystal_I2C.h>       //Library LCD I2C
LiquidCrystal_I2C lcd(0x27, 20, 4);  //Alamat I2C

#define atas 43 // button atas pada pin 43
#define bawah 44 // button bawah pada pin 44
#define ok 45 // button ok pada pin 45
#define cancel 46 // button cancel pada pin 46
#define p1 40  //button player 1 pada pin 40
#define p2 42  //button player 2 pada pin 42
#define ulang 41  //button reset pada pin 41
#define play 39 //button play pada pin 39
#define DITEKAN LOW
#define BOUNCE 50

char state;
char state2;

long lastButton = 0;
long delayAntiBouncing = 50;
unsigned long TSekarang;
unsigned long TAkhir;

int setmenit1;  //Set waktu main player 1
int setmenit2;
int menitP1 = 1;
int menitP2 = 1;
int detik1 = 0;
int detik2 = 0;

bool playwaktu = true;
bool giliran1 = true;
bool done = true;



void setup() {
  Serial.begin(9600);
  lcd.init();       //Mulai LCD
  lcd.backlight();  //Nyalakan backlight
  pinMode(43, INPUT_PULLUP);
  pinMode(44, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(46, INPUT_PULLUP);
  pinMode(p1, INPUT_PULLUP);  //Setting I/O
  pinMode(p2, INPUT_PULLUP);
  pinMode(ulang, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(ok) == DITEKAN) {
    delay(BOUNCE);
    while (digitalRead(ok) == DITEKAN) {}
    lcd.clear();
    menuSetting();
  }
  lcd.setCursor(0, 0);
  lcd.print(" Selamat Datang Di  ");
  lcd.setCursor(0, 1);
  lcd.print(" Jam Catur Bicara ");
  lcd.setCursor(18, 3);
  lcd.print("Ok");
}

void menuSetting() {
  //-----------------------------------------------------------------
  // MENU
setMenu1:
  if (digitalRead(ok) == DITEKAN) {
    delay(BOUNCE);
    while (digitalRead(ok) == DITEKAN) {}
    lcd.clear();
    goto setSubMenu1;

  } else if (digitalRead(atas) == DITEKAN) {
    delay(BOUNCE);
    while (digitalRead(atas) == DITEKAN) {}
    lcd.clear();
    goto setMenu2;  //pilih paling akhir

  } else if (digitalRead(bawah) == DITEKAN) {
    delay(BOUNCE);
    while (digitalRead(bawah) == DITEKAN) {}
    lcd.clear();
    goto setMenu2;
  }



  lcd.setCursor(0, 0);
  lcd.print(">Setting Timer");
  lcd.setCursor(0, 1);
  lcd.print(" Mulai Pertandingan");

  goto setMenu1;

  //-----------------------------------------------------------------
setMenu2:
  if (digitalRead(ok) == DITEKAN) {
    delay(BOUNCE);
    while (digitalRead(ok) == DITEKAN) {}
    lcd.clear();
    goto setSubMenu2;

  } else if (digitalRead(atas) == DITEKAN) {
    delay(BOUNCE);
    while (digitalRead(atas) == DITEKAN) {}
    lcd.clear();
    goto setMenu1;  //pilih paling akhir

  } else if (digitalRead(bawah) == DITEKAN) {
    delay(BOUNCE);
    while (digitalRead(bawah) == DITEKAN) {}
    lcd.clear();
    goto setMenu1;
  }



  lcd.setCursor(0, 0);
  lcd.print(" Setting Timer");
  lcd.setCursor(0, 1);
  lcd.print(">Mulai Pertandingan");


  goto setMenu2;

  //-----------------------------------------------------------------

// SUB MENU
setSubMenu1:
  setSub2Menu1:
  switch (state) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print(">SetTimer Putih :");
      lcd.setCursor(17, 0);
      lcd.print(setmenit1);
      lcd.setCursor(0, 1);
      lcd.print(" SetTimer Hitam :");
      lcd.setCursor(17, 1);
      lcd.print(setmenit2);

      if (digitalRead(atas) == 0) {
        state = 1;
        delay(200);
        lcd.clear();
      }

      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print(">SetTimer Putih :");
      lcd.setCursor(17, 0);
      lcd.print(setmenit1);
      lcd.setCursor(0, 1);
      lcd.print(" SetTimer Hitam :");
      lcd.setCursor(17, 1);
      lcd.print(setmenit2);

      if (digitalRead(atas) == 0) {
        setmenit1++;
        delay(200);
        lcd.clear();
      } else if (digitalRead(bawah) == 0) {
        setmenit1--;
        delay(200);
        lcd.clear();
      }

      if (digitalRead(ok) == 0) {
        state = 0;
        delay(200);
        Serial.println(setmenit1);
        goto setSub2Menu2;
        

      } else if (digitalRead(cancel) == 0) {
        state = 0;
        delay(200);
        lcd.clear();
        setmenit1 = 0;
        
      }
      break;
  }
  goto setSub2Menu1;

  setSub2Menu2:
  switch (state2) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print(" SetTimer Putih :");
      lcd.setCursor(17, 0);
      lcd.print(setmenit1);
      lcd.setCursor(0, 1);
      lcd.print(">SetTimer Hitam :");
      lcd.setCursor(17, 1);
      lcd.print(setmenit2);

      if (digitalRead(atas) == 0) {
        state2 = 1;
        delay(200);
        lcd.clear();
      }

      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print(" SetTimer Putih :");
      lcd.setCursor(17, 0);
      lcd.print(setmenit1);
      lcd.setCursor(0, 1);
      lcd.print(">SetTimer Hitam :");
      lcd.setCursor(17, 1);
      lcd.print(setmenit2);

      if (digitalRead(atas) == 0) {
        setmenit2++;
        delay(200);
        lcd.clear();
      } else if (digitalRead(bawah) == 0) {
        setmenit2--;
        delay(200);
        lcd.clear();
      }

      if (digitalRead(ok) == 0) {
        state2 = 0;
        delay(200);
        lcd.clear();
        Serial.println(setmenit2);
        goto setMenu1;
        

        

      } else if (digitalRead(cancel) == 0) {
        state2 = 0;
        delay(200);
        lcd.clear();
        setmenit1 = 0;
      }
      break;
    
  
  }
  goto setSub2Menu2;


  goto setSubMenu1;

setSubMenu2:
  lcd.setCursor(1, 1);  //Tampilan Awal
  lcd.print("  P1         P2  ");

    menitP1 = setmenit1;
    menitP2 = setmenit2;

  if (digitalRead(p1) == 0 || digitalRead(p2) == 0 || digitalRead(play) == 0) {  //Baca tombol
    if ((millis() - lastButton) > delayAntiBouncing) {
      if (playwaktu && digitalRead(play) == 0) {  //Jika player 1 menekan tombol, maka
        lcd.setCursor(1, 1);
        lcd.print("  P1         P2  ");
        done = false;
        giliran1 = true;  //Jalankan waktu player 2
      } else if (giliran1 && digitalRead(p1) == 0) {
        lcd.setCursor(1, 1);
        lcd.print("  P1         P2  ");
        done = false;
        giliran1 = false ;
      } else if (!giliran1 && digitalRead(p2) == 0){
        lcd.setCursor(1, 1);
        lcd.print("  P1         P2  ");
        done = false;
        giliran1 = true;
      }
    }
    lastButton = millis();

  } else if (digitalRead(ulang) == 0) {  //Ulang waktu jika reset ditekan
    menitP1 = setmenit1;
    menitP2 = setmenit2;
    detik1 = 0;
    detik2 = 0;
    done = true;
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("  P1         P2  ");
  }

  TSekarang = millis();
  if (TSekarang - TAkhir > 1000) {  //Kurangi waktu 1 detik pada
    if (giliran1 && !done) {        //player 1 jika giliran 1
      detik1--;
    } else if (!giliran1 && !done) {  //player 2 jika giliran 2
      detik2--;
    }
    TAkhir = TSekarang;
  }

  if (detik1 < 0) {
    detik1 = 59;
    menitP1--;  //Kurangi menit setiap 60 detik
  }
  if (detik2 < 0) {
    detik2 = 59;
    menitP2--;
  }

  if (menitP1 == 0 && detik1 == 0) {  //Jika player 1 kehabisan waktu
    lcd.setCursor(1, 1);
    lcd.print("  Waktu Habis   ");
    lcd.setCursor(1, 2);
    lcd.print("--Player 2 Win--");
    done = true;
  } else if (menitP1 == 0 && detik2 == 0) {  //Jika player 2 kehabisan waktu
    lcd.setCursor(1, 1);
    lcd.print("  Waktu Habis   ");
    lcd.setCursor(1, 2);
    lcd.print("--Player 1 Win--");
    done = true;
  } else {  //Tampilkan waktu
    lcd.setCursor(2, 2);
    lcd.print(menitP1);
    lcd.print(":");
    lcd.print(detik1);
    lcd.print("  ");
    lcd.setCursor(13, 2);
    lcd.print(menitP2);
    lcd.print(":");
    lcd.print(detik2);
    lcd.print("  ");
  }
  goto setSubMenu2;
}