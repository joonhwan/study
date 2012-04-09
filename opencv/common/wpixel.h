#pragma once

template<typename T, int C>
struct WPixelValue
{
	typedef T PixelValueArray[C];
	PixelValueArray data;
	PixelValueArray& getDataPtr() {
		return data;
	}
};

template<typename T>
struct WPixelValue<T,1>
{
	T data;
	T* getDataPtr() {
		return &data;
	}
};

template<typename T, int C>
struct WPixelPosition : public WPixelValue<T,C>
{
	typedef int PosValueArray[C];
	PosValueArray x;
	PosValueArray y;
	PosValueArray& getXPtr() {
		return x;
	}
	PosValueArray& getYPtr() {
		return y;
	}
};

template<typename T>
struct WPixelPosition<T,1> : public WPixelValue<T,1>
{
	int x;
	int y;
	int* getXPtr() {
		return &x;
	}
	int* getYPtr() {
		return &y;
	}
};
