#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include <iostream>
#include "long_int.h"
LONG_INT::LONG_INT(const char *str) : len_(strlen(str)), container_(new int[len_])
{
	size_t len = strlen(str);
	for (size_t i = 0, j = len - 1; i < len; ++i, --j)
	{
		if (isdigit(str[i]))
			container_[j] = str[i] - 48;
		else
		{
			len_ = 1;
			delete[] container_;
			container_ = new int[len_];
			container_[0] = 0;
			break;
		}
	}
}
LONG_INT::LONG_INT(const int *str, int size) : len_(size), container_(new int[len_])
{
	for (int i = 0; i < len_; ++i)
		container_[i] = str[i];
}
//LONG_INT::LONG_INT(const LONG_INT &right) : len_(right.len_)
//{
//	if (right.container_ != nullptr)
//	{
//		container_ = new int[len_];
//		memcpy(container_, right.container_, sizeof(int)* len_);
//	}
//}
LONG_INT::~LONG_INT(){ delete[] container_; }
std::ostream &operator<<(std::ostream &os, const LONG_INT &thisObject)
{
	for (int i = thisObject.len_ - 1; i >= 0; --i)
		os << thisObject.container_[i];
	return os;
}
LONG_INT &LONG_INT::operator=(const LONG_INT &right)
{
	if (this == &right)
		return *this;
	delete[] container_;
	container_ = new int[right.len_];
	len_ = right.len_;
	memcpy(container_, right.container_, sizeof(int)* len_);
	return *this;
}
LONG_INT &LONG_INT::operator=(const char *str)
{
	*this = LONG_INT(str);
	return *this;
}
LONG_INT &LONG_INT::operator*=(const LONG_INT &right)
{
	const LONG_INT *up = this, *down = &right;
	if (this->len_ < right.len_)
		up = &right, down = this;
	int totalLen = up->len_ + down->len_, tempLen = up->len_ + 1;
	int *total = new int[totalLen];
	int *temp = new int[tempLen];
	int bias = 0;
	for (int i = 0; i < totalLen; ++i)
		total[i] = 0;
	for (int j = 0; j < tempLen; ++j)
		temp[j] = 0;
	for (int i = 0; i < down->len_; ++i)
	{
		for (int j = 0; j < up->len_; ++j)
		{
			bias = up->container_[j] * down->container_[i] / 10;
			temp[j + 1] = bias;
			temp[j] += (up->container_[j] * down->container_[i] % 10);
			temp[j] = (temp[j] < 10) ? temp[j] : temp[j] % 10;
		}
		bias = 0;
		for (int k = 0; k < tempLen; ++k)
		{
			total[k + i] += (bias + temp[k]);
			bias = total[k + i] / 10;
			total[k + i] = (total[k + i] < 10) ? total[k + i] : total[k + i] % 10;
			temp[k] = 0;
		}
	}
	delete[] temp;
	for (int i = totalLen - 1; i >= 0; --i)
	{
		if (total[i] == 0)
			continue;
		else
		{
			tempLen = i + 1;
			temp = new int[tempLen];
			memcpy(temp, total, sizeof(int)* tempLen);
			break;
		}
	}
	delete[] total;
	this->len_ = tempLen;
	delete[] this->container_;
	this->container_ = new int[len_];
	memcpy(this->container_, temp, sizeof(int)* len_);
	delete[] temp;
	return *this;
}
//const LONG_INT LONG_INT::operator*(const LONG_INT &right) const
//{
//	LONG_INT res = *this;
//	res *= right;
//	return res;
//}




const LONG_INT LONG_INT::operator*(const LONG_INT &right) const
{
	const LONG_INT *up = this, *down = &right;
	if (this->len_ < right.len_)
		up = &right, down = this;
	int totalLen = up->len_ + down->len_, tempLen = up->len_ + 1;
	int *total = new int[totalLen];
	int *temp = new int[tempLen];
	int bias = 0;
	for (int i = 0; i < totalLen; ++i)
		total[i] = 0;
	for (int j = 0; j < tempLen; ++j)
		temp[j] = 0;
	for (int i = 0; i < down->len_; ++i)
	{
		for (int j = 0; j < up->len_; ++j)
		{
			bias = up->container_[j] * down->container_[i] / 10;
			temp[j + 1] = bias;
			temp[j] += (up->container_[j] * down->container_[i] % 10);
			temp[j] = (temp[j] < 10) ? temp[j] : temp[j] % 10;
		}
		bias = 0;
		for (int k = 0; k < tempLen; ++k)
		{
			total[k + i] += (bias + temp[k]);
			bias = total[k + i] / 10;
			total[k + i] = (total[k + i] < 10) ? total[k + i] : total[k + i] % 10;
			temp[k] = 0;
		}
	}
	LONG_INT res;
	delete[] res.container_;
	res.len_ = totalLen;
	res.container_ = new int[len_];
	memcpy(res.container_, total, len_);
	delete[] temp;
	delete[] total;
	return res;
}