//biblioteca
#include <Time.h>
#include <TimeLib.h>
#define DISPLAY_BRIGHTNESS  500
#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW
#define SEG 7
#define COM 4
//pinos referentes a cada segmento
const int a = 31;
const int b = 33;
const int c = 35;
const int d = 37;
const int e = 39;
const int f = 41;
const int g = 43;
const int dp = 45;
const int vetorSeg[] = {a, b, c, d, e, f, g, dp};
//pinos referentes aos comuns
const int c1 = 47;
const int c2 = 49;
const int c3 = 51;
const int c4 = 53;
const int vetorComun[] = {c1, c2, c3, c4};
//pinos referentes aos botões
const int botamMinutos = 2;
const int botamHoras = 3;
const int botamSet = 4;
//contadores internos
int segundos = 0;
int minutos = 0;
int horas = 0;

void setup() {
  for (int x = 0; x <= SEG; x++) {
    pinMode(vetorSeg[x], OUTPUT);
  }
  for (int x = 0; x <= COM; x++) {
    pinMode(vetorComun[x], OUTPUT);
  }
  //botoes
  pinMode(botamMinutos, INPUT);
  pinMode(botamHoras, INPUT);
  pinMode(botamSet, INPUT);
  //pull-ups ligado
  digitalWrite(botamMinutos, HIGH);
  digitalWrite(botamHoras, HIGH);
  digitalWrite(botamSet, HIGH);
}

void loop() {
  segundos++;
  if (segundos > 59) {
    minutos++;
    segundos = 0;
    if (minutos > 59) {
      horas++;
      minutos = 0;
      if (horas > 23) {
        horas = 0;
      }
    }
  }

  digitalWrite(dp, HIGH);
  int tempo = (horas * 100) + minutos;

  for (int i = 250; i > 0; i--) {
    if (tempo > 100) {
      displayNum01(tempo);
    } else {
      displayNum02(tempo);
    }
  }

  for (int i = 250; i > 0; i--) {
    if (tempo > 100) {
      displayNum03(tempo);
    } else {
      displayNum04(tempo);
    }
  }

  if (!(digitalRead(botamSet))) {
    set_relogio(horas, minutos);
  }

  if (!(digitalRead(botamMinutos))) {
    int horaParada = horas;
    int minutoParado = minutos;
    int segundoParado = segundos;
    set_cronometro();
    set_tempo(horaParada, minutoParado, segundoParado);
  }
}

void set_tempo(int hr, int minu, int seg) {
  horas = hr;
  minutos = minu;
  segundos = seg;
}

void set_cronometro() {
  set_tempo(0, 0, 0);
  while (digitalRead(botamHoras) != 0) {
    int tempo = segundos;
    for (int i = 250; i > 0; i--) {
      if (tempo > 100) {
        displayNum01(tempo);
      } else {
        displayNum02(tempo);
      }
    }

    for (int i = 250; i > 0; i--) {
      if (tempo > 100) {
        displayNum03(tempo);
      } else {
        displayNum04(tempo);
      }
    }
    segundos++;
  }
}

void set_relogio(int hr, int minu) {
  byte minutosB = minu;
  byte horasB = hr;

  while (!digitalRead(botamSet)) {
    while (!digitalRead(botamMinutos)) {
      minutosB++;
      if (minutosB > 59) {
        minutosB = 0;
      }
      for (int i = 20; i > 0; i--) {
        int tempo = (horasB * 100) + minutosB;
        if (tempo > 1000) {
          displayNum01(tempo);
        } else {
          displayNum02(tempo);
        }
      }
      delay(150);
    }

    while (!digitalRead(botamHoras)) {
      horasB++;
      if (horasB > 23) {
        horasB = 0;
      }
      for (int i = 20; i > 0; i--) {
        int tempo = (horasB * 100) + minutosB;
        if (tempo > 1000) {
          displayNum01(tempo);
        } else {
          displayNum02(tempo);
        }
      }
      delay(150);
    }

    for (int i = 20; i > 0; i--) {
      displayNum01((horasB * 100) + minutosB);
    }
    set_tempo(horasB, minutosB, 0);
  }
}

void displayNum01(int digito) {
  for (int i = 4 ; i > 0 ; i--) {
    switch (i) {
      case 1:
        digitalWrite(c4, DIGIT_ON);
        digitalWrite(dp, LOW);
        break;
      case 2:
        digitalWrite(c3, DIGIT_ON);
        digitalWrite(dp, LOW);
        break;
      case 3:
        digitalWrite(c2, DIGIT_ON);
        digitalWrite(dp, LOW);
        break;
      case 4:
        digitalWrite(c1, DIGIT_ON);
        digitalWrite(dp, LOW);
        break;
    }

    LigaSegmentos(digito % 10);
    digito /= 10;
    delayMicroseconds(DISPLAY_BRIGHTNESS);

    LigaSegmentos(10);

    digitalWrite(c4, DIGIT_OFF);
    digitalWrite(c3, DIGIT_OFF);
    digitalWrite(c2, DIGIT_OFF);
    digitalWrite(c1, DIGIT_OFF);
  }
}

void displayNum02(int digito) {
  for (int i = 4 ; i > 0 ; i--) {
    switch (i) {
      case 1:
        digitalWrite(c4, DIGIT_ON);
        digitalWrite(dp, LOW);
        break;
      case 2:
        digitalWrite(c3, DIGIT_ON);
        digitalWrite(dp, LOW);
        break;
      case 3:
        digitalWrite(c2, DIGIT_ON);
        digitalWrite(dp, LOW);
        break;
      case 4:
        digitalWrite(c1, DIGIT_ON);
        digitalWrite(dp, LOW);
        break;
    }

    LigaSegmentos(digito % 10);
    digito /= 10;
    delayMicroseconds(DISPLAY_BRIGHTNESS);

    LigaSegmentos(10);

    digitalWrite(c4, DIGIT_OFF);
    digitalWrite(c3, DIGIT_OFF);
    digitalWrite(c2, DIGIT_OFF);
    digitalWrite(c1, DIGIT_OFF);
  }
}

void displayNum03(int digito) {
  for (int i = 4 ; i > 0 ; i--) {
    switch (i) {
      case 1:
        digitalWrite(c4, DIGIT_ON);
        digitalWrite(dp, HIGH);
        break;
      case 2:
        digitalWrite(c3, DIGIT_ON);
        digitalWrite(dp, HIGH);
        break;
      case 3:
        digitalWrite(c2, DIGIT_ON);
        digitalWrite(dp, HIGH);
        break;
      case 4:
        digitalWrite(c1, DIGIT_ON);
        digitalWrite(dp, HIGH);
        break;
    }

    LigaSegmentos(digito % 10);
    digito /= 10;
    delayMicroseconds(DISPLAY_BRIGHTNESS);

    LigaSegmentos(10);

    digitalWrite(c4, DIGIT_OFF);
    digitalWrite(c3, DIGIT_OFF);
    digitalWrite(c2, DIGIT_OFF);
    digitalWrite(c1, DIGIT_OFF);
  }
}

void displayNum04(int digito) {
  for (int i = 4 ; i > 0 ; i--) {
    switch (i) {
      case 1:
        digitalWrite(c4, DIGIT_ON);
        digitalWrite(dp, HIGH);
        break;
      case 2:
        digitalWrite(c3, DIGIT_ON);
        digitalWrite(dp, HIGH);
        break;
      case 3:
        digitalWrite(c2, DIGIT_ON);
        digitalWrite(dp, HIGH);
        break;
      case 4:
        digitalWrite(c1, DIGIT_ON);
        digitalWrite(dp, HIGH);
        break;
    }

    LigaSegmentos(digito % 10);
    digito /= 10;
    delayMicroseconds(DISPLAY_BRIGHTNESS);

    LigaSegmentos(10);

    digitalWrite(c4, DIGIT_OFF);
    digitalWrite(c3, DIGIT_OFF);
    digitalWrite(c2, DIGIT_OFF);
    digitalWrite(c1, DIGIT_OFF);
  }
}

void LigaSegmentos(int numeroDisplay) {
#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (numeroDisplay) {
    case 0:
      digitalWrite(a, SEGMENT_ON);
      digitalWrite(b, SEGMENT_ON);
      digitalWrite(c, SEGMENT_ON);
      digitalWrite(d, SEGMENT_ON);
      digitalWrite(e, SEGMENT_ON);
      digitalWrite(f, SEGMENT_ON);
      digitalWrite(g, SEGMENT_OFF);
      break;
    case 1:
      digitalWrite(a, SEGMENT_OFF);
      digitalWrite(b, SEGMENT_ON);
      digitalWrite(c, SEGMENT_ON);
      digitalWrite(d, SEGMENT_OFF);
      digitalWrite(e, SEGMENT_OFF);
      digitalWrite(f, SEGMENT_OFF);
      digitalWrite(g, SEGMENT_OFF);
      break;
    case 2:
      digitalWrite(a, SEGMENT_ON);
      digitalWrite(b, SEGMENT_ON);
      digitalWrite(c, SEGMENT_OFF);
      digitalWrite(d, SEGMENT_ON);
      digitalWrite(e, SEGMENT_ON);
      digitalWrite(f, SEGMENT_OFF);
      digitalWrite(g, SEGMENT_ON);
      break;
    case 3:
      digitalWrite(a, SEGMENT_ON);
      digitalWrite(b, SEGMENT_ON);
      digitalWrite(c, SEGMENT_ON);
      digitalWrite(d, SEGMENT_ON);
      digitalWrite(e, SEGMENT_OFF);
      digitalWrite(f, SEGMENT_OFF);
      digitalWrite(g, SEGMENT_ON);
      break;
    case 4:
      digitalWrite(a, SEGMENT_OFF);
      digitalWrite(b, SEGMENT_ON);
      digitalWrite(c, SEGMENT_ON);
      digitalWrite(d, SEGMENT_OFF);
      digitalWrite(e, SEGMENT_OFF);
      digitalWrite(f, SEGMENT_ON);
      digitalWrite(g, SEGMENT_ON);
      break;
    case 5:
      digitalWrite(a, SEGMENT_ON);
      digitalWrite(b, SEGMENT_OFF);
      digitalWrite(c, SEGMENT_ON);
      digitalWrite(d, SEGMENT_ON);
      digitalWrite(e, SEGMENT_OFF);
      digitalWrite(f, SEGMENT_ON);
      digitalWrite(g, SEGMENT_ON);
      break;
    case 6:
      digitalWrite(a, SEGMENT_ON);
      digitalWrite(b, SEGMENT_OFF);
      digitalWrite(c, SEGMENT_ON);
      digitalWrite(d, SEGMENT_ON);
      digitalWrite(e, SEGMENT_ON);
      digitalWrite(f, SEGMENT_ON);
      digitalWrite(g, SEGMENT_ON);
      break;
    case 7:
      digitalWrite(a, SEGMENT_ON);
      digitalWrite(b, SEGMENT_ON);
      digitalWrite(c, SEGMENT_ON);
      digitalWrite(d, SEGMENT_OFF);
      digitalWrite(e, SEGMENT_OFF);
      digitalWrite(f, SEGMENT_OFF);
      digitalWrite(g, SEGMENT_OFF);
      break;
    case 8:
      digitalWrite(a, SEGMENT_ON);
      digitalWrite(b, SEGMENT_ON);
      digitalWrite(c, SEGMENT_ON);
      digitalWrite(d, SEGMENT_ON);
      digitalWrite(e, SEGMENT_ON);
      digitalWrite(f, SEGMENT_ON);
      digitalWrite(g, SEGMENT_ON);
      break;
    case 9:
      digitalWrite(a, SEGMENT_ON);
      digitalWrite(b, SEGMENT_ON);
      digitalWrite(c, SEGMENT_ON);
      digitalWrite(d, SEGMENT_ON);
      digitalWrite(e, SEGMENT_OFF);
      digitalWrite(f, SEGMENT_ON);
      digitalWrite(g, SEGMENT_ON);
      break;
    // Desliga todos os segmentos
    case 10:
      digitalWrite(a, SEGMENT_OFF);
      digitalWrite(b, SEGMENT_OFF);
      digitalWrite(c, SEGMENT_OFF);
      digitalWrite(d, SEGMENT_OFF);
      digitalWrite(e, SEGMENT_OFF);
      digitalWrite(f, SEGMENT_OFF);
      digitalWrite(g, SEGMENT_OFF);
      break;
  }
}
