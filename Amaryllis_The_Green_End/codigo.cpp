#include <DHT.h> // Incluir DHT
#include <LiquidCrystal_I2C.h> // Incluir LCD
#include <Servo.h> // Incluir Servo Motor

// Definir Entradas
#define ledG 13
#define ledY 12
#define ledR 8

#define buzzer 4

#define dhtpin 7
#define dhttype DHT22

Servo servo; // Declarar o servo motor

////////////////////////////////////////////////////////

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(dhtpin, dhttype);

//////////////////////////////////////////////////////

void setup() {
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  servo.attach(3); // Configurar o pino do servo
  servo.write(0);  // Inicializar o servo na posição 0 graus

  dht.begin();
  
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("--------------------");
  lcd.setCursor(5,1);
  lcd.print("Dados da");
  lcd.setCursor(7,2);
  lcd.print("Horta"); 
  lcd.setCursor(0,3);
  lcd.print("--------------------");
  delay(4000);
  lcd.clear();
}

void loop() {
    int temp = dht.readTemperature();
    int umi = dht.readHumidity();
    Serial.println("Temperatura: " + String(temp));
    Serial.println("Umidade: " + String(umi));
   
    // Perda dos alimentos
    if((umi < 30 || umi > 90) || (temp > 35 || temp < 15)){
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, LOW);
      digitalWrite(ledR, HIGH);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("--------------------"); 
      lcd.setCursor(7,1);
      lcd.print("Perda do");
      lcd.setCursor(5,2);
      lcd.print("Alimento");
      lcd.setCursor(0,3);
      lcd.print("--------------------");
      delay(2000);  

      tone(buzzer, 700, 2000);
    }

    ////////////////////////////////////////////////////////
    
    // Condições de Plantio Específico
    // Hortaliças e Frutas
    else if((temp >= 15 && temp <= 20) || (umi >= 60 && umi <= 80)){
      digitalWrite(ledG, HIGH);
      digitalWrite(ledY, LOW);
      digitalWrite(ledR, LOW);
     
      // Movimento do servo para indicar condições favoráveis
      servo.write(90); // Mover o servo para 90 graus
      delay(1000); // Manter posição por 1 segundo
      servo.write(0);  // Retornar o servo para 0 graus

      lcd.setCursor(0,0);
      lcd.print("--------------------");
      lcd.setCursor(3,1);
      lcd.print("Perfeito para:");
      lcd.setCursor(0,2);
      lcd.print("Hortalicas e Frutas");
      lcd.setCursor(0,3);
      lcd.print("--------------------");
      delay(2000);
      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("--------------------");
      lcd.setCursor(3,1);
      lcd.print("Perfeito para:");
      lcd.setCursor(7,2);
      lcd.print("Graos");
      lcd.setCursor(0,3);
      lcd.print("--------------------");
      delay(2000);
      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("--------------------");
      lcd.setCursor(3,1);
      lcd.print("Perfeito para:");
      lcd.setCursor(8,2);
      lcd.print("Cafe");
      lcd.setCursor(0,3);
      lcd.print("--------------------");
      delay(2000);
      lcd.clear();

    ////////////////////////////////////////////////////////

    // Plantas Tropicais
    } else if((umi >= 70 && umi <= 90) || (temp > 20 && temp <= 30)){
      digitalWrite(ledG, HIGH);
      digitalWrite(ledY, LOW);
      digitalWrite(ledR, LOW);
      
      lcd.setCursor(0,0);
      lcd.print("--------------------"); 
      lcd.setCursor(3,1);
      lcd.print("Perfeito para:");
      lcd.setCursor(2,2);
      lcd.print("Plantas Tropicais");
      lcd.setCursor(0,3);
      lcd.print("--------------------");
      delay(2000);
      lcd.clear();

    ///////////////////////////////////////////////////////      
    
    // Alerta de Possível Perda
    } else {
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, HIGH);
      digitalWrite(ledR, LOW);
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("--------------------");
      lcd.setCursor(5,1);
      lcd.print("Possivel");
      lcd.setCursor(7,2);
      lcd.print("Perda");
      lcd.setCursor(0,3);
      lcd.print("--------------------");
      delay(2000);
    }
}