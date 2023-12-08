#include "src/domain/motor.ino"

#define pwm1 2 // Motor Direito
#define ingA1 4 // Motor Direito
#define ingB1 3 // Motor Direito

#define pwm2 8 // Motor Esquerdo
#define ingA2 10 // Motor Esquerdo
#define ingB2 9 // Motor Esquerdo

//mpu 6050
/*
class Motor{
  private:
    int pinoPwm;
    int pinoIngA;
    int pinoIngB;

    int pwm;
  
  public:
    Motor(int pinoPwm, int pinoIngA, int pinoIngB){
      this->pinoPwm = pinoPwm;
      this->pinoIngA = pinoIngA;
      this->pinoIngB = pinoIngB;

      pinMode(this->pinoPwm, OUTPUT);
      pinMode(this->pinoIngA, OUTPUT);
      pinMode(this->pinoIngB, OUTPUT);
    }

    void setPwm(int novoPwm) {
      this->pwm = novoPwm;
    }

    void rodarHorario(){
      analogWrite(this->pinoPwm,this->pwm);
      digitalWrite(this->pinoIngA, HIGH);
      digitalWrite(this->pinoIngB, LOW);
    }

    void rodarAntiHorario(){
      analogWrite(this->pinoPwm,this->pwm);
      digitalWrite(this->pinoIngA, LOW);
      digitalWrite(this->pinoIngB, HIGH);
    }

    void parar(){
      digitalWrite(this->pinoIngA, LOW);
      digitalWrite(this->pinoIngB, LOW);
    }
};
*/

Motor motorDireito(pwm1, ingA1, ingB1);
Motor motorEsquerdo(pwm2, ingA2, ingB2);



void setup() {
  Serial.begin(9600);
}

void loop() {
  // tempo para andar uma cedula!
  int tempo = 2200;

  if (Serial.available() > 0) {
    String stringSerial = Serial.readString();
    Serial.flush(); 
    char primeiroCaracter = stringSerial.charAt(0);

    controlarMovimento(primeiroCaracter, tempo);
  }
}

void controlarMovimento(char direcao, int tempo){
  switch (direcao) {
      case 'W':
        //SEGUIR EM FRENTE
        andarFrente(tempo); 
        break;
      case 'A':
        //ESQUERDA 90º
        virarEsquerda90(); 
        break;
      case 'S':
        //SEGUIR PARA TRAS
        andarTras(tempo); 
        break;
      case 'D':
        //DIREITA 90º
        virarDireita90(); 
        break;
      case 'P':
        //PARAR
        parar(); 
        break;
    }
}

void andarFrente(int tempo){
  motorDireito.setPwm(190);
  motorEsquerdo.setPwm(190);

  motorDireito.rodarHorario();
  motorEsquerdo.rodarHorario();

  delay(tempo);  
  parar();
}

void andarTras(int tempo){
  motorDireito.setPwm(128);
  motorEsquerdo.setPwm(128);

  motorDireito.rodarAntiHorario();
  motorEsquerdo.rodarAntiHorario();

  delay(tempo);  
  parar();
}

void virarEsquerda90(){
  motorDireito.setPwm(255);
  motorEsquerdo.setPwm(255);

  motorDireito.rodarHorario();
  motorEsquerdo.rodarAntiHorario();
        
  delay(1200);  
  parar();
}

void virarDireita90(){
  motorDireito.setPwm(255);
  motorEsquerdo.setPwm(255);

  motorDireito.rodarAntiHorario();
  motorEsquerdo.rodarHorario();
      
  delay(1200);   
  parar();
}

void parar(){
  motorDireito.parar();
  motorEsquerdo.parar();
}

