/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _CRONOMETER_H_
#define _CRONOMETER_H_

#include <stdint.h>

// Classe que marca o tempo de execucao do algoritmo.
class Chronometer {
 private:
  // Retorna o instante de tempo em que se encontra o sistema operacional
  
	int SysTime();

  int begin_;
  int time_;


 uint64_t time;
 public:
  // Executa a funcao Zerar()
  Chronometer();

  // Reinicia a contagem de tempo
  void Reset();

  // Interrompe a contagem de tempo.
  void Stop();

  // Continua a contagem de tempo do ponto em que foi
  // interrompida pela funcao stop().
  void Start();

  // Retorna o valor do cronometro em segundos.
 // double Time();
  int Time();
  
  // Retorna o valor do cronometro em segundos.
  uint64_t Value();

  // Retorna o valor do cronometro em segundos, com uma precisao maior que a
  // funcao Valor.
  double dValue();
};

#endif  // _CRONOMETER_H_
