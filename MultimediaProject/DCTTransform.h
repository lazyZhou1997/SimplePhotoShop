#pragma once
#ifndef DCT_TRANSFORM
#define DCT_TRANSFORM

//����DCT�任
void DCT(double ** input, double ** output, int row, int col);

//����DCT���任
void IDCT(double ** input, double ** output, int row, int col);

#endif