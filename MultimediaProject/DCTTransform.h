#pragma once
#ifndef DCT_TRANSFORM
#define DCT_TRANSFORM

//进行DCT变换
void DCT(double ** input, double ** output, int row, int col);

//进行DCT反变换
void IDCT(double ** input, double ** output, int row, int col);

#endif