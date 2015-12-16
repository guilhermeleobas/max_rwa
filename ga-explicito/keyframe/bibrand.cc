/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./bibrand.h"

#include <stdlib.h>
#include <assert.h>
using namespace std;
/**********************************************************/
/* Construtor                                             */
/**********************************************************/

Bibrand::Bibrand(int s) {
  seed_ = new int();  // Aloca memoria para armazenar o valor da semente
  *seed_ = s;
  UpdateSeed(seed_);
}

/**********************************************************/
/* Atualiza o gerador de numeros aleatorios               */
/**********************************************************/

float Bibrand::UpdateSeed(int *ix) {
  int xhi, xalo, leftlo, fhi, k;

  const int A = 16807;  // 7**5
  const int P = 2147483647;  // Mersenne prime (2**31) - 1
  const int b15 = 32768;  // 2**15
  const int b16 = 65536;  // 2**16

  /* Calculoa um numero pseudo-aleatorio */
  xhi = *ix/b16;
  xalo = (*ix-xhi*b16)*A;
  leftlo = xalo/b16;
  fhi = xhi*A+leftlo;
  k = fhi/b15;
  *ix = (((xalo-leftlo*b16)-P)+(fhi-k*b15)*b16)+k;
  if (*ix < 0) *ix = *ix + P;
  return static_cast<float>(*ix*4.656612875e-10);
}

/***********************************************************/
/* Gera um numero aleatorio no intervalo [i, j]            */
/***********************************************************/

int Bibrand::IntRand(int i, int j ) {
  UpdateSeed(seed_);
  return static_cast<int>(*seed_ / (2147483647.0 / (j - i + 1.0))) + i;
}

/**********************************************************/
/* Gera um numero aleatorio no intervalo [0.0, 1.0]       */
/**********************************************************/

double Bibrand::DoubleRand() {
  return static_cast<double>(IntRand(0, 1000000)) / 1000000.0;
}

/**********************************************************/
/*Inicializa o singleton                                  */
/**********************************************************/

Bibrand* Bibrand::bibrand_ptr_ = NULL;
void Bibrand::Initialize(int seed) {
  assert(bibrand_ptr_ == NULL);
  bibrand_ptr_ = new Bibrand(seed);
}

/**********************************************************/
/* Retorna um ponteiro para o Objeto                      */
/**********************************************************/

Bibrand* Bibrand::GetInstance() {
  assert(bibrand_ptr_ != NULL);
  return bibrand_ptr_;
}

/**********************************************************/
/* Destrutor                                              */
/**********************************************************/

Bibrand::~Bibrand() {
  delete(seed_);
}

