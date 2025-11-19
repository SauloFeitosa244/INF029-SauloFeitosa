// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br
//
//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho
//
//  ----- Dados do Aluno -----
//  Nome:Saulo Teixeira Cardoso Feitosa
//  email:saulotcfeitosa@gmail.com
//  Matrícula:20242160012
//  Semestre:2025.2
//
//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025
//
// #################################################

#include <stdio.h>
#include "SauloFeitosa-20242160012-T1.h" 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    DataQuebrada dq = quebraData(data);

   if(dq.valido == 0) return 0;

   if(dq.iAno < 0) return 0;
   if(dq.iMes < 1 || dq.iMes > 12) return 0;
   if(dq.iDia < 1 || dq.iDia > 31) return 0;

   if(dq.iMes == 4 || dq.iMes == 6 || dq.iMes == 9 || dq.iMes == 11) {
      if(dq.iDia > 30) return 0;
   }

   if(dq.iMes == 2) {
      int bissexto = 0;
      if((dq.iAno % 4 == 0 && dq.iAno % 100 != 0) || (dq.iAno % 400 == 0)) bissexto = 1;
      if(bissexto) {
         if(dq.iDia > 29) return 0;
      } else {
         if(dq.iDia > 28) return 0;
      }
   }

   return 1;
}

/* ajuda para q2 */
static int diasNoMes(int mes, int ano) {
    if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) return 31;
    if(mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
    if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) return 29;
    return 28;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

   DiasMesesAnos dma;
   DataQuebrada dStart = quebraData(datainicial);
   DataQuebrada dEnd = quebraData(datafinal);

   if(q1(datainicial) == 0) {
      dma.retorno = 2;
      return dma;
   }
   if(q1(datafinal) == 0) {
      dma.retorno = 3;
      return dma;
   }

   if (dStart.iAno > dEnd.iAno ||
      (dStart.iAno == dEnd.iAno && dStart.iMes > dEnd.iMes) ||
      (dStart.iAno == dEnd.iAno && dStart.iMes == dEnd.iMes && dStart.iDia > dEnd.iDia)) {
      dma.retorno = 4;
      return dma;
   }

   int a1 = dStart.iAno;
   int m1 = dStart.iMes;
   int d1 = dStart.iDia;

   int a2 = dEnd.iAno;
   int m2 = dEnd.iMes;
   int d2 = dEnd.iDia;

   if (d2 < d1) {
      m2 = m2 - 1;
      if (m2 == 0) {
         m2 = 12;
         a2 = a2 - 1;
      }
      d2 = d2 + diasNoMes(m2, a2);
   }

   if (m2 < m1) {
      m2 = m2 + 12;
      a2 = a2 - 1;
   }

   dma.qtdDias = d2 - d1;
   dma.qtdMeses = m2 - m1;
   dma.qtdAnos = a2 - a1;
   dma.retorno = 1;
   return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
   if(texto == NULL) return 0;
   int qtdOcorrencias = 0;
   if(isCaseSensitive == 1) {
      for (int i = 0; texto[i] != '\0'; i++) {
         if(texto[i] == c) qtdOcorrencias++;
      }
   } else {
      char target = (char) tolower((unsigned char)c);
      for (int i = 0; texto[i] != '\0'; i++) {
         if(tolower((unsigned char)texto[i]) == target) qtdOcorrencias++;
      }
   }
   return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
   if(strTexto == NULL || strBusca == NULL) return 0;
      int lenT = (int) strlen(strTexto);
      int lenB = (int) strlen(strBusca);
      if(lenB == 0 || lenT == 0 || lenB > lenT) return 0;

      char *textoLower = (char *) malloc(lenT + 1);
      char *buscaLower = (char *) malloc(lenB + 1);
      if(!textoLower || !buscaLower) {
         if(textoLower) free(textoLower);
         if(buscaLower) free(buscaLower);
         return 0;
      }

      for(int i = 0; i < lenT; i++) textoLower[i] = (char) tolower((unsigned char) strTexto[i]);
      textoLower[lenT] = '\0';
      for(int i = 0; i < lenB; i++) buscaLower[i] = (char) tolower((unsigned char) strBusca[i]);
      buscaLower[lenB] = '\0';

      int count = 0;
      int maxPairs = 15;
      for(int i = 0; i <= lenT - lenB && count < maxPairs; i++){
         int match = 1;
         for(int j = 0; j < lenB; j++){
            if(textoLower[i + j] != buscaLower[j]){
                  match = 0;
                  break;
            }
         }
         if(match){
            posicoes[2*count] = i + 1;
            posicoes[2*count + 1] = i + lenB;
            count++;
         }
      }

      free(textoLower);
      free(buscaLower);
      return count;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{

   int negativo = 0;
   if(num < 0){
      negativo = 1;
      num = -num;
   }
   int rev = 0;
   while(num > 0){
      rev = rev * 10 + (num % 10);
      num /= 10;
   }
   if(negativo) rev = -rev;
   return rev;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
   if (numerobusca < 0 || numerobase < 0) return 0;

    int baseDigits[20], buscaDigits[20];
    int lenBase = 0, lenBusca = 0;

    int temp = numerobase;
    if (temp == 0) { baseDigits[lenBase++] = 0; }
    while (temp > 0) {
        baseDigits[lenBase++] = temp % 10;
        temp /= 10;
    }
    for (int i = 0; i < lenBase/2; i++) {
        int t = baseDigits[i];
        baseDigits[i] = baseDigits[lenBase-1-i];
        baseDigits[lenBase-1-i] = t;
    }

    temp = numerobusca;
    if (temp == 0) { buscaDigits[lenBusca++] = 0; }
    while (temp > 0) {
        buscaDigits[lenBusca++] = temp % 10;
        temp /= 10;
    }
    for (int i = 0; i < lenBusca/2; i++) {
        int t = buscaDigits[i];
        buscaDigits[i] = buscaDigits[lenBusca-1-i];
        buscaDigits[lenBusca-1-i] = t;
    }

    if (lenBusca > lenBase) return 0;

    int qtd = 0;
    for (int i = 0; i <= lenBase - lenBusca; i++) {
        int ok = 1;
        for (int j = 0; j < lenBusca; j++) {
            if (baseDigits[i + j] != buscaDigits[j]) {
                ok = 0;
                break;
            }
        }
        if (ok) qtd++;
    }
    return qtd;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {
   int rows = 8;
    int cols = 10;
    int len = (int) strlen(palavra);
    if(len == 0) return 0;

    int dx[8] = {-1,-1, 0, 1, 1, 1, 0, -1};
    int dy[8] = { 0, 1, 1, 1, 0,-1,-1, -1};

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            for(int dir = 0; dir < 8; dir++){
                int rr = r;
                int cc = c;
                int k;
                for(k = 0; k < len; k++){
                    if(rr < 0 || rr >= rows || cc < 0 || cc >= cols) break;
                    if(matriz[rr][cc] != palavra[k]) break;
                    rr += dx[dir];
                    cc += dy[dir];
                }
                if(k == len) return 1;
            }
        }
    }
    return 0;
 }



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
