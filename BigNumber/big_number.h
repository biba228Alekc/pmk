#pragma once
#include <stdbool.h>

typedef unsigned char digit;

// ��� �������� ����� (>10 ������)
typedef struct BigNumber
{
	size_t size;		// ������ �����
	digit* digits;  	// ������ �� ���� �����
	bool is_negative;	// ���� �����
}BigNumber;
/*
* @brief �������� �������� �����
* @param number_ : ������ � ������� ������
* @return ��������� �� ���������� ������ � ������� ������
*/
BigNumber* CreateBN(char* number_);

/*
* @brief ������� ��������� ������� �����
* @param bn_ : ��������� �� ������� �����
*/
void DeleteBN(BigNumber** bn_);

/*
* @brief ������ �������� �����
* @param bn_ : ��������� �� ������� �����
*/
void PrintBN(BigNumber* bn_);

/*
* @brief ����� ���� ������� �����
* @param bn1_, bn2_ : ������� �����
* @return ������� ����� �� ����� ���� �������
*/
BigNumber* SumBN(BigNumber* bn1_, BigNumber* bn2_);

/*
* @brief ��������� ������ �������� ����� �� �������
* @param bn1_, bn2_ : ������� ����� 
* @param result : ��������� ���������
* @return  ��������� ���������
*/
BigNumber* Minus(BigNumber* bn1_, BigNumber* bn2_, BigNumber* result);

/*
* @brief ��������� ���� ������� �����
* @param bn1, bn2 : ������� �����
* @return ��������� ���������
*/
BigNumber* MultiplyBN(BigNumber* bn1, BigNumber* bn2);

/*
* @brief �������� ����� �������� �����
* @param bn : ������� ����� ��� �����������
* @return ����� �������� �����
*/
BigNumber* CopyBN(BigNumber* bn);

/*
* @brief ��������� �������� ����� �� ����� �����
* @param bn : ������� �����
* @param num : ����� �����
* @return ��������� ��������� �������� ����� �� ����� �����
*/
BigNumber* MultiplyBNOnli(BigNumber* bn, int num);

/*
* @brief ��������� ������ �������� ����� �� ������� 
* @param bn1_, bn2_ : ������� �����
* @return ��������� ��������� � ��������������� ������
*/
BigNumber* MinusreversBN(BigNumber* bn1, BigNumber* bn2);

/*
* @brief ��������� ���� ������� �����
* @param bn1, bn2 : ������� ����� ��� ���������
* @return ����� �����: -1 ���� bn1 ������ bn2, 0 ���� ��� �����, 1 ���� bn1 ������ bn2
*/
int CompareBN(BigNumber* bn1, BigNumber* bn2);

/*
* @brief ������� ������ �������� ����� �� ������
* @param dividend : �������
* @param divisor : ��������
* @return ������� �� �������
*/
BigNumber* DivideBN(BigNumber* dividend, BigNumber* divisor);
