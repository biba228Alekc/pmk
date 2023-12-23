#pragma once


void writeStringToFile(const char* str, const char* filename);



double** createMatrix(int n);



void write2MATRIXXToFile(double** matrix, int n, const char* filename);



void freeMatrix(double** matrix, int n);


void getMinor(double** src, double** dest, int row, int col, int n);


double calcDeterminant(double** matrix, int n);


double** getInverseMatrix(double** matrix, int n);


void printMatrix(double** matrix, int n);


void Fstring(const char* str, const char* fileoname);


void GGG(int n, double** matrix);


void jjj(double** inverseMatrix, int n);

