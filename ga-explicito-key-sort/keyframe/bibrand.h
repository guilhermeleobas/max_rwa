/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _BIBRAND_H_
#define _BIBRAND_H_

// Classe responsavel pela geracao de numeros aleatorios.
class Bibrand {
 private:
  // Construtor
  explicit Bibrand(int s);

  // Valor da semente.
  int *seed_;

  // Ponteiro para o sigleton.
  static Bibrand *bibrand_ptr_;

  // Atualiza o valor da semente.
  float UpdateSeed(int *ix);

 public:

  // Retorna um numero pseudo-aleatorio no intervalo [i, j].
  int IntRand(int i, int j);

  // Retorna um numero pseudo-aleatorio no intervalo [0.0, 1.0].
  double DoubleRand();

  // Inicializa o singleton.
  static void Initialize(int seed);

  // Retorna um ponteiro para a instancia.
  static Bibrand* GetInstance();

  // Libera memoria.
  ~Bibrand();

void SetValue(int  s){ 
 seed_ = new int();  
  *seed_ = s;
 UpdateSeed(seed_);
}

};

#endif  // _BIBRAND_H_

