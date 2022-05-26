/*Programación de Arduino. Control Termostato Arduino-Google V1.1 2022-05-26
*   Copyright (C) 2022  SAUL SANTA CRUZ RODRIGUEZ | CARLOS ALBERTO BOYZO RAMIREZ|
*ALEJANDRA QUINTANA MARTINEZ | EMIR PEREZ GARCIA.
*
*
*   This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <dht.h>
dht DHT;
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
#define DHT11_PIN 8
int venti=9;
int button=A0;
int ledState=0; 
int buttonOld=1;
int buttonNew;   
int conta;
const byte ROWS=4;
const byte COLS=3;
char teclas[ROWS][COLS]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'},
};
byte rowPins[ROWS]={10,11,12,13};
byte colsPins[COLS]={A5,A4,A3};
Keypad teclado = Keypad( makeKeymap(teclas), rowPins, colsPins, ROWS, COLS );
void menu_pantalla0() {
  lcd.setCursor(0,0);
  lcd.begin(16,2);
  lcd.print("Bienvenido al");
  lcd.setCursor(0, 1);
  lcd.print("proyecto final");
  lcd.display();
  delay(5000);
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Elige una opcion");
  lcd.display();
  lcd.setCursor(0, 1);
  lcd.print("de inicio");
  lcd.display();
  delay(5000);
}
void menu_pantalla1() {
lcd.clear();
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("1)Manual");
  lcd.setCursor(0, 1);
  lcd.print("2)Automatico");
  lcd.setCursor(10, 0);
  lcd.print("3)Menu");
   delay (3000);
}

void setup() {
  Serial.begin (9600);
pinMode(A1,OUTPUT);
lcd.setCursor(0,0);
conta=0;
menu_pantalla0();
menu_pantalla1();
pinMode (venti, OUTPUT);
  pinMode (button, INPUT);
}

void loop() {
  char Key= teclado.getKey();
  buttonNew=digitalRead(button);
   if (buttonNew==1 && buttonOld==0) {
    if (ledState==1)
    {
      digitalWrite(venti,0);
      ledState=0;
    }
    else
    {
      digitalWrite (venti,9);
      ledState=1;
    }
    } 
    buttonOld=buttonNew;
  if (Key=='1' && conta==0) {    
  DHT.read11(DHT11_PIN);
  lcd.begin(16,2);
  lcd.setCursor (0,0);
  lcd.print("Temp ");
  lcd.print(DHT.temperature);
  lcd.print(" C");
lcd.setCursor (0,1);
  lcd.print("Humedad ");
  lcd.print(DHT.humidity);
  lcd.print("%");
delay(2000);
    conta=1;
  }
  
  if (Key=='2' && conta==0) {
  DHT.read11(DHT11_PIN);
  lcd.begin(16,2);
  lcd.setCursor (0,0);
  lcd.print("Temp ");
  lcd.print(DHT.temperature);
  lcd.print(" C");
  lcd.setCursor (0,1);
  lcd.print("Humedad ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  delay(2000);

  if(DHT.temperature>26){
  if (ledState==0)
    {
  digitalWrite(venti,9);
  ledState=1;
    }
    else
    {
      digitalWrite (venti,0);
      ledState=0;
    }
}
    conta=1;
  }
  if ((Key=='3') && (conta==1 || conta==2))
  {
    menu_pantalla1();
    conta=0;
    digitalWrite (venti,0);
    ledState=0;
  }
 }
