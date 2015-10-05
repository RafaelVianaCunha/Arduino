// Do not remove the include below
#include "ContadorBinario.h"

char buffer[9];
int latchPin = 8; // Pino conectado ao pino 12 do 74HC595 (Latch)
int clockPin = 12; // Pino conectado ao pino 11 do 74HC595 (Clock)
int dataPin = 11; // Pino conectado ao pino 14 do 74HC595 (Data)
void shiftOut(byte dataOut);
void limparBuffer();

void setup() {
	//Comunicação serial
	Serial.begin(9600);
	Serial.flush();
	// define os pinos como saída
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	shiftOut(0); //Apaga todos os leds
}
void loop() {
	if (Serial.available() > 0) {
		//limpa o texto e os buffers
		void limparBuffer();
		int index = 0;
		int numChar = 8;
		delay(100); // deixe o buffer encher


		Serial.print("Digite o numero: ");
		while (numChar--) {
			buffer[index++] = Serial.read();
		}

		int num = strtol(buffer, NULL, 10); // Converte de char para int
		Serial.println(num);
		// define latchPin como LOW, para permitir o fluxo de dados
		digitalWrite(latchPin, LOW);
		shiftOut(num);
		// define latchPin como HIGH, para fechar e enviar os dados
		digitalWrite(latchPin, HIGH);

	}
}
void shiftOut(byte dataOut) {
	// Desloca 8 bits, com o bit menos significativo (LSB) sendo deslocado primeiro, no extremo
	// ascendente do clock
	boolean pinState;
	digitalWrite(dataPin, LOW); // deixa o registrador de deslocamento pronto para enviar dados
	digitalWrite(clockPin, LOW);
	for (int i = 0; i <= 7; i++) { // para cada bit em dataOut, envie um bit
		digitalWrite(clockPin, LOW); // define clockPin como LOW antes de enviar o bit
		// se o valor de DataOut e (E lógico) de uma máscara de bits
		// forem verdadeiros, defina pinState como 1 (HIGH)
		if (dataOut & (1 << i)) {
			pinState = HIGH;
		} else {
			pinState = LOW;
		}
		// define dataPin como HIGH ou LOW, dependendo de pinState
		digitalWrite(dataPin, pinState); // envia o bit no extremo ascendente do clock
		digitalWrite(clockPin, HIGH);
	}
	digitalWrite(clockPin, LOW); // interrompa o deslocamento de dados
}

void limparBuffer() {
	// Limpa o texto e os buffers seriais
	for (int x = 0; x < 10; x++) {
		buffer[x] = '\0';
	}
	Serial.flush();
}

