#define BTN 4
#define LED 3
#define Potenciometro1 A0
#define FotoResistor A1
#define btnModo 2

byte estadoLed = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT);
  pinMode(btnModo, INPUT);
  pinMode(FotoResistor, INPUT);
  Serial.begin(9600);
}

void Manual(int intensidadeLed);
void Automatico(int intensidadeLed);
bool VerificarBtn(byte botao);

void loop() {
  static byte modo = 1;
  int intensidadeLed = analogRead(Potenciometro1);
  int intensidadePWM = map(intensidadeLed, 0, 1023, 0, 255);

  if (VerificarBtn(btnModo)) {
    modo = !modo;  // alterna entre 0 (automático) e 1 (manual)
  }

  if (modo == 1) {
    Manual(intensidadePWM);
  } else {
    Automatico(intensidadePWM);
  }
  delay(50);
}

bool VerificarBtn(byte botao) {
  static byte lastRead[10] = {0}; // guarda estado anterior de vários botões
  byte leitura = digitalRead(botao);

  if (leitura == HIGH && lastRead[botao] == LOW) {
    lastRead[botao] = leitura;
    return true;
  }

  lastRead[botao] = leitura;
  return false;
}

void Manual(int intensidadeLed) {
  if (VerificarBtn(BTN)) {
    estadoLed = !estadoLed;
  }

  if (estadoLed == 1) {
    analogWrite(LED, intensidadeLed);
  } else {
    analogWrite(LED, 0);
  }
}

void Automatico(int intensidadeLed) {
  int luz = analogRead(FotoResistor);
  Serial.println(luz);

  if (luz < 500) { // acende quando está escuro
    analogWrite(LED, intensidadeLed);
  } else {
    analogWrite(LED, 0);
  }
}
