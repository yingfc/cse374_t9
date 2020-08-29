// Copyright [2020] Yingfan Chen

#ifndef T9_PRIV_H_
#define T9_PRIV_H_

typedef struct T9 {
    char *word;
    struct T9 *nodes[9];
} T9;

#endif  // T9_PRIV_H_
