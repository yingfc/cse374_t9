// Copyright [2020] Yingfan Chen
#include <stddef.h>
#include "t9_lib.h"
#include "t9_priv.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_WORD_LEN 50

T9* InitializeEmptyT9() {
  T9* dict = malloc(sizeof(T9));
  if (!dict) {
      fprintf(stderr, "failed allocating memory\n");
      exit(1);
  }
  dict->word = NULL;
  for (int i = 0; i < 9; i++) {
      dict->nodes[i] = NULL;
  }
  return dict;
}

T9* InitializeFromFileT9(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "file not exist\n");
    return NULL;
  }
  char* word = (char*) malloc(MAX_WORD_LEN * sizeof(char));
  T9* dict = InitializeEmptyT9();
  while (fgets(word, MAX_WORD_LEN, file)) {
    if (word[strlen(word) - 1] == '\n') {
      word[strlen(word) - 1] = '\0';
    }
    AddWordToT9(dict, word);
  }
  free(word);
  return dict;
}

int char2num(char character) {
  int charToNum[26] = {2, 2, 2, 3, 3, 3,
                       4, 4, 4, 5, 5, 5,
                       6, 6, 6, 7, 7, 7, 7,
                       8, 8, 8, 9, 9, 9, 9};
  return charToNum[character - 'a'];
}

void AddWordToT9(T9* dict, const char* word) {
  if (dict == NULL || word == NULL || !isdigit(word[0])) {
    exit(0);
  }
  T9* curr = dict;
  for (int i = 0; i < strlen(word); i++) {
    int currNum = char2num(word[i]);
    if (!curr->nodes[currNum-2]) {
        curr->nodes[currNum-2] = InitializeEmptyT9();
    }
    curr = curr->nodes[currNum-2];
  }
  bool duplicate = false;
  if (strcmp(curr->word, word) == 0) {
    duplicate = true;
  }
  if (duplicate) {
    curr->word = malloc(strlen(word) + 1);
    if (curr->word == NULL) {
      printf("failed allocating memory\n");
      exit(1);
    }
    strncpy(curr->word, word, strlen(word) + 1);
  }
}

char* PredictT9(T9* dict, const char* nums) {
  if (!nums) {
    return NULL;
  }
  T9* curr = dict;
  int currNum;
  for (int i = 0; i < strlen(nums); i++) {
    if (nums[i] == '#') {
      currNum = -1;
    } else {
      currNum = nums[i] - '0';
    }
    if (currNum < 2 || currNum > 10 || curr->nodes[currNum-2] == NULL) {
      return NULL;
    } else {
      curr = curr->nodes[currNum-2];
    }
  }
  return curr->word;
}

void DestroyT9(T9* dict) {
  free(dict);
}
