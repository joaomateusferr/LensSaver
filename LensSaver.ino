//Created by Techno John

#include <DHT.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//todas as bibliotecas estão na pasta lib com suas respectivas documentações

#define DHTPIN A0	//defini o pino A0 do controlador para a leitura do sensor de temperatura e humidade
#define DHTTYPE DHT22	//defini o tipo do densor de temperatura e humidade DHT11 futuramente sera o DHT22

LiquidCrystal_I2C lcd(0x3F, 16, 2);	//inicializa o display lcd i2c baseado no endereço obtido com o I2C_Scaner que pode ser encontrado na pasta res

const int ledVerde = 13;	//led que indica um nivel alarmante de humidae definido na porta 13 do controlador
const int ledVermelho = 12;		//led que indica um nivel alarmante de humidae definido na porta 12 do controlador
 
DHT dht(DHTPIN, DHTTYPE);	//istancia o sensor DTH

float h = 0;	//inicializa a humidade com 0
float t = 0;	//inicializa a temperatura com 0

void setup(void)	//rotina chamada toda vez que o microcontrolador é ligado
{
  lcd.begin(16,2);	//define o tamanho display lcd
  lcd.init();	//liga o display lcd
  lcd.backlight();	//liga a luz de fundo do display lcd
}  
void loop(void)	//é executado em loop enqinto o controlador estiver ligado
{
  //capta os dados dos sensores e os escreve na serial e no display lcd
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  lcd.init();
  lcd.backlight();
  
  if (isnan(t) || isnan(h)) //valida se os sensores estão conectados
  {
    Serial.println("Error de leitura\n");
    
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Error");
    
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, LOW);
  } 
  else	//printa os dados lidos dos sensor na serial e no display LCD
  {
    Serial.print(h);
    Serial.print(" ");
    Serial.print(t);
    Serial.print(" ");

    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("H ");
    lcd.print(h,1);
    lcd.print("% ");
    lcd.setCursor(0, 1);
    lcd.print("T ");
    lcd.print(t,1);
    lcd.print("C");
	
    if(h>55)	//liga o led relacionado ao estado da humidade
    {
      digitalWrite(ledVermelho, HIGH);
      digitalWrite(ledVerde, LOW);
    }
    else
    {
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledVermelho, LOW);
    }
    
  }
}
