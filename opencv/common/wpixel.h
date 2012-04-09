#pragma once

#include <opencv2/opencv.hpp>

template<typename T, int C>
struct WPixelValue
{
	typedef T PixelValueArray[C];
	PixelValueArray data;
	PixelValueArray& getDataPtr() {
		return data;
	}
	const T& getDataRef() const {
		return data;
	}
	T& getDataRef() {
		return data;
	}
};

template<typename T>
struct WPixelValue<T,1>
{
	WPixelValue(T _data)
		: data(_data)
	{
	}
	T data;
	T* getDataPtr() {
		return &data;
	}
	T getDataRef() const {
		return data;
	}
	T& getDataRef() {
		return data;
	}
};

template<typename T>
struct WPixelValue<T,3>
{
	WPixelValue(T d0)
	{
		data[0] = data[1] = data[2] = d0;
	}
	WPixelValue(T d0, T d1, T d2)
	{
		data[0] = d0;
		data[1] = d1;
		data[2] = d2;
	}
	typedef T PixelValueArray[3];
	PixelValueArray data;
	PixelValueArray& getDataPtr() {
		return data;
	}
	PixelValueArray& getDataRef() {
		return data;
	}
	const PixelValueArray& getDataRef() const {
		return data;
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
	WPixelPosition(T d0, int _x, int _y)
		: WPixelValue<T,1>(d0)
		, x(_x)
		, y(_y)
	{
	}
	int x;
	int y;
	int* getXPtr() {
		return &x;
	}
	int* getYPtr() {
		return &y;
	}
};

template<typename T>
struct WPixelPosition<T,3> : public WPixelValue<T,3>
{
	WPixelPosition(T d0, T d1, T d2, int _x, int _y)
		: WPixelValue<T,1>(d0, d1, d2)
		, x(_x)
		, y(_y)
	{
	}
	typedef int PosValueArray[3];
	PosValueArray x;
	PosValueArray y;
	PosValueArray& getXPtr() {
		return x;
	}
	PosValueArray& getYPtr() {
		return y;
	}
};
