/* 24.12.2008 last modification: 26.06.2013
Copyright (c) 2008-2013 by Siegfried Koepf

This file is distributed under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.
For information on usage and redistribution and for a disclaimer of all
warranties, see the file COPYING in this distribution.

testing
gen_comb_norep_lex_init() and gen_comb_norep_lex_next()

compile
gcc -o comb_norep_lex_example comb_norep_lex_example.c comb_norep_lex.c
*/

#include "string.h"
#include "stdio.h"
#include <algorithm>
#include <vector>
#include <stack>

#include <stdlib.h>
using namespace std;
//include "_generate.h"

/*
Combinatorial generation functions public interfaces
*/

#ifndef _GENERATE_H
#define _GENERATE_H

//return values of generation functions
#define GEN_NEXT  0 //ok, print and continue
#define GEN_TERM  1 //ok, terminate
#define GEN_EMPTY 2 //ok, print EMPTY SET and continue
#define GEN_ERROR 3 //an error occured, print an error message and terminate

//combinatorial generation functions
int gen_comb_norep_init(unsigned char *vector, const unsigned char n, const unsigned char k);
int gen_comb_norep_next(unsigned char *vector, const unsigned char n, const unsigned char k);

int gen_comb_rep_init(unsigned char *vector, const unsigned char n, const unsigned char k);
int gen_comb_rep_next(unsigned char *vector, const unsigned char n, const unsigned char k);

int gen_perm_rep_init(const unsigned char n);
int gen_perm_rep_next(unsigned char *vector, const unsigned char n);

int gen_vari_rep_init(unsigned char *vector, const unsigned char m, const unsigned char n);
int gen_vari_rep_next(unsigned char *vector, const unsigned char m, const unsigned char n);

int gen_neck_init(unsigned char *vector, const unsigned char m, const unsigned char n);
int gen_neck_next(unsigned char *vector, const unsigned char m, const unsigned char n);

int gen_part_init(unsigned char *vector, const unsigned char n, unsigned char *k);
int gen_part_next(unsigned char *vector, unsigned char *k);

int gen_k_part_init(unsigned char *vector, const unsigned char n, const unsigned char k);
int gen_k_part_next(unsigned char *vector, const unsigned char k);

int gen_k_comp_init(unsigned char *vector, const unsigned char n, const unsigned char k);
int gen_k_comp_next(unsigned char *vector, const unsigned char k);

#endif


int gen_comb_norep_lex_init(unsigned char *vector, const unsigned char n, const unsigned char k)
{
int j; //index

//test for special cases
if(k > n)
 return(GEN_ERROR);

if(k == 0)
 return(GEN_EMPTY);

//initialize: vector[0, ..., k - 1] are 0, ..., k - 1
for(j = 0; j < k; j++)
 vector[j] = j;

return(GEN_NEXT);
}

int gen_comb_norep_lex_next(unsigned char *vector, const unsigned char n, const unsigned char k)
{
int j; //index

//easy case, increase rightmost element
if(vector[k - 1] < n - 1)
 {
 vector[k - 1]++;
 return(GEN_NEXT);
 }

//find rightmost element to increase
for(j = k - 2; j >= 0; j--)
 if(vector[j] < n - k + j)
  break;

//terminate if vector[0] == n - k
if(j < 0)
 return(GEN_TERM);

//increase
vector[j]++;

//set right-hand elements
while(j < k - 1)
 {
 vector[j + 1] = vector[j] + 1;
 j++;
 }

return(GEN_NEXT);
}

int main(void)
{
unsigned char n           = 5;    //length of alphabet
unsigned char k           = 3;    //length of figures
unsigned char *vector     = NULL; //where the current figure is stored
int           gen_result;         //return value of generation functions
unsigned int  set_counter;        //counting generated sequences
int           x;                  //iterator

//alloc memory for vector
vector = (unsigned char *)malloc(sizeof(unsigned char) * k);
if(vector == NULL)
 {
 fprintf(stderr, "error: insufficient memory\n");
 exit(EXIT_FAILURE);
 }

set_counter = 0;
printf("comb_norep_lex(%u, %u)\n", n, k);

//initialize
gen_result = gen_comb_norep_lex_init(vector, n, k);

if(gen_result == GEN_ERROR)
 {
 fprintf(stderr, "error: couldn't initialize\n");
 return(EXIT_FAILURE);
 }

if(gen_result == GEN_EMPTY)
 {
 set_counter++;
 printf("{} (%u)\n", set_counter);
 }

//generate all successors
while(gen_result == GEN_NEXT)
 {
 set_counter++;

 for(x = 0; x < k; x++)
  printf("%u ", vector[x]);

 printf("(%u)\n", set_counter);

 gen_result = gen_comb_norep_lex_next(vector, n, k);
 }

return(EXIT_SUCCESS);
}