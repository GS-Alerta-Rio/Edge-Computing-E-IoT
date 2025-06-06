#define PIN_TRIG 3
#define PIN_ECHO 2
#define BUZZER_PIN 13


int lerDistanciaCM(){ //função para ler a distância em CM do sensor Ultrassônico
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  int duracao = pulseIn(PIN_ECHO, HIGH);
  int distanciaCM = duracao / 58;
  return distanciaCM;
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

}

void loop() {
 int distancia = lerDistanciaCM(); // Chama a função para obter a distância

  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println("cm ");

  // Lógica para acender os LEDs com base na distância
  if (distancia >= 300) { // Nível baixo: distância maior ou igual a 300 cm
    digitalWrite(7, HIGH);   // Acende o LED Verde
    digitalWrite(8, LOW);  // Apaga o LED Amarelo
    digitalWrite(9, LOW); // Apaga o LED Vermelho
    noTone(BUZZER_PIN);
    Serial.println("Nível: Baixo (LED Verde)");
  } else if (distancia >= 150 && distancia <= 299) { // Nível de alerta: distância entre 150 cm e 299 cm
    digitalWrite(7, LOW);    // Apaga o LED Verde
    digitalWrite(8, HIGH); // Acende o LED Amarelo
    digitalWrite(9, LOW); // Apaga o LED Vermelho
    noTone(BUZZER_PIN);
    Serial.println("Nível: Alerta (LED Amarelo)");
  } else if (distancia < 149) { // Nível crítico: distância menor que 149 cm
    digitalWrite(7, LOW);    // Apaga o LED Verde
    digitalWrite(8, LOW);  // Apaga o LED Amarelo
    digitalWrite(9, HIGH); // Acende o LED Vermelho
    tone(BUZZER_PIN, 262, 250);
    Serial.println("Nível: Crítico (LED Vermelho)");
  }

  delay(1000);

}