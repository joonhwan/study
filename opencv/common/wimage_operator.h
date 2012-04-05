#pragma once

#include "wimage_t.h"

// for matrix operation

// plus

template<typename T, int C>
cv::MatExpr operator + (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator + (WInputImageT<T, C>& a, const cv::Scalar& s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator + (const cv::Scalar& s, WInputImageT<T, C>& a)
{
	return s + a.matrix;
}

template<typename T, int C>
cv::MatExpr operator + (const cv::MatExpr& e, WInputImageT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator + (WInputImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

//--


template<typename T, int C>
cv::MatExpr operator + (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator + (const WImageT<T, C>& a, const cv::Scalar& s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator + (const cv::Scalar& s, const WImageT<T, C>& a)
{
	return s + a.matrix;
}

template<typename T, int C>
cv::MatExpr operator + (const cv::MatExpr& e, const WImageT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator + (const WImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}


// minus

template<typename T, int C>
cv::MatExpr operator - (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a.matrix() - b.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (WInputImageT<T, C>& a, const cv::Scalar& s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator - (const cv::Scalar& s, WInputImageT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (const cv::MatExpr& e, WInputImageT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (WInputImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

template<typename T, int C>
cv::MatExpr operator - (WInputImageT<T, C>& m)
{
	return operator - (m.matrix())
}

template<typename T, int C>
cv::MatExpr operator - (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a.matrix() - b.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (const WImageT<T, C>& a, const cv::Scalar& s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator - (const cv::Scalar& s, const WImageT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (const cv::MatExpr& e, const WImageT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (const WImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

template<typename T, int C>
cv::MatExpr operator - (const WImageT<T, C>& m)
{
	return operator - (m.matrix())
}

// multiply

template<typename T, int C>
cv::MatExpr operator * (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (WInputImageT<T, C>& a, double s)
{
	return a.matrix() + b;
}

template<typename T, int C>
cv::MatExpr operator * (double s, WInputImageT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (const cv::MatExpr& e, WInputImageT<T, C>& m)
{
	return e * m.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (WInputImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

// --

template<typename T, int C>
cv::MatExpr operator * (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (const WImageT<T, C>& a, double s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator * (double s, const WImageT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (const cv::MatExpr& e, const WImageT<T, C>& m)
{
	return e * m.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (const WImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

// divide

template<typename T, int C>
cv::MatExpr operator / (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (WInputImageT<T, C>& a, double s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator / (double s, WInputImageT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (const cv::MatExpr& e, WInputImageT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (WInputImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

// --

template<typename T, int C>
cv::MatExpr operator / (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (const WImageT<T, C>& a, double s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator / (double s, const WImageT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (const cv::MatExpr& e, const WImageT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (const WImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}


// comparison

template<typename T, int C>
cv::MatExpr operator < (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a.matrix() < b.matrix();
}

template<typename T, int C>
cv::MatExpr operator < (WInputImageT<T, C>& a, double s)
{
	return a.matrix() < s;
}

template<typename T, int C>
cv::MatExpr operator < (double s, WInputImageT<T, C>& a)
{
	return s < a.matrix()

}

// --
template<typename T, int C>
cv::MatExpr operator < (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a.matrix() < b.matrix();
}

template<typename T, int C>
cv::MatExpr operator < (const WImageT<T, C>& a, double s)
{
	return a.matrix() < s;
}

template<typename T, int C>
cv::MatExpr operator < (double s, const WImageT<T, C>& a)
{
	return s < a.matrix()

}

template<typename T, int C>
cv::MatExpr operator <= (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a.matrix() <= b.matrix();
}

template<typename T, int C>
cv::MatExpr operator <= (WInputImageT<T, C>& a, double s)
{
	return a.matrix() <= s;
}

template<typename T, int C>
cv::MatExpr operator <= (double s, WInputImageT<T, C>& a)
{
	return s <= a.matrix();
}

template<typename T, int C>
cv::MatExpr operator <= (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a.matrix() <= b.matrix();
}

template<typename T, int C>
cv::MatExpr operator <= (const WImageT<T, C>& a, double s)
{
	return a.matrix() <= s;
}

template<typename T, int C>
cv::MatExpr operator <= (double s, const WImageT<T, C>& a)
{
	return s <= a.matrix();
}


template<typename T, int C>
cv::MatExpr operator == (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a.matrix() == b.matrix();
}

template<typename T, int C>
cv::MatExpr operator == (WInputImageT<T, C>& a, double s)
{
	return a.matrix() == b;
}

template<typename T, int C>
cv::MatExpr operator == (double s, WInputImageT<T, C>& a)
{
	return s == a.matrix();
}

template<typename T, int C>
cv::MatExpr operator == (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a.matrix() == b.matrix();
}

template<typename T, int C>
cv::MatExpr operator == (const WImageT<T, C>& a, double s)
{
	return a.matrix() == b;
}

template<typename T, int C>
cv::MatExpr operator == (double s, const WImageT<T, C>& a)
{
	return s == a.matrix();
}


template<typename T, int C>
cv::MatExpr operator != (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a + b;
}

template<typename T, int C>
cv::MatExpr operator != (WInputImageT<T, C>& a, double s)
{
	return a.matrix() != s;
}

template<typename T, int C>
cv::MatExpr operator != (double s, WInputImageT<T, C>& a)
{
	return s != a.matrix();

}

template<typename T, int C>
cv::MatExpr operator != (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a + b;
}

template<typename T, int C>
cv::MatExpr operator != (const WImageT<T, C>& a, double s)
{
	return a.matrix() != s;
}

template<typename T, int C>
cv::MatExpr operator != (double s, const WImageT<T, C>& a)
{
	return s != a.matrix();

}


template<typename T, int C>
cv::MatExpr operator >= (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a.matrix() >= b.matrix();
}

template<typename T, int C>
cv::MatExpr operator >= (WInputImageT<T, C>& a, double s)
{
	return a.matrix() >= s;
}

template<typename T, int C>
cv::MatExpr operator >= (double s, WInputImageT<T, C>& a)
{
	return s >= a.matrix();
}

template<typename T, int C>
cv::MatExpr operator >= (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a.matrix() >= b.matrix();
}

template<typename T, int C>
cv::MatExpr operator >= (const WImageT<T, C>& a, double s)
{
	return a.matrix() >= s;
}

template<typename T, int C>
cv::MatExpr operator >= (double s, const WImageT<T, C>& a)
{
	return s >= a.matrix();
}


template<typename T, int C>
cv::MatExpr operator > (WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return a.matrix() > b.matrix();
}

template<typename T, int C>
cv::MatExpr operator > (WInputImageT<T, C>& a, double s)
{
	return a.matrix() > s;
}

template<typename T, int C>
cv::MatExpr operator > (double s, WInputImageT<T, C>& a)
{
	return s > a.matrix();
}

template<typename T, int C>
cv::MatExpr operator > (const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return a.matrix() > b.matrix();
}

template<typename T, int C>
cv::MatExpr operator > (const WImageT<T, C>& a, double s)
{
	return a.matrix() > s;
}

template<typename T, int C>
cv::MatExpr operator > (double s, const WImageT<T, C>& a)
{
	return s > a.matrix();
}


template<typename T, int C>
cv::MatExpr min(WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return min(a.matrix(), b.matrix());
}

template<typename T, int C>
cv::MatExpr min(WInputImageT<T, C>& a, double s)
{
	return min(a.matrix(), s);
}

template<typename T, int C>
cv::MatExpr min(double s, WInputImageT<T, C>& a)
{
	return min(s, a.matrix());
}

template<typename T, int C>
cv::MatExpr min(const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return min(a.matrix(), b.matrix());
}

template<typename T, int C>
cv::MatExpr min(const WImageT<T, C>& a, double s)
{
	return min(a.matrix(), s);
}

template<typename T, int C>
cv::MatExpr min(double s, const WImageT<T, C>& a)
{
	return min(s, a.matrix());
}


template<typename T, int C>
cv::MatExpr max(WInputImageT<T, C>& a, WInputImageT<T, C>& b)
{
	return max(a.matrix(), b.matrix());
}

template<typename T, int C>
cv::MatExpr max(WInputImageT<T, C>& a, double s)
{
	return max(a.matrix(), s);
}

template<typename T, int C>
cv::MatExpr max(double s, WInputImageT<T, C>& a)
{
	return max(s, a.matrix());
}

template<typename T, int C>
cv::MatExpr max(const WImageT<T, C>& a, const WImageT<T, C>& b)
{
	return max(a.matrix(), b.matrix());
}

template<typename T, int C>
cv::MatExpr max(const WImageT<T, C>& a, double s)
{
	return max(a.matrix(), s);
}

template<typename T, int C>
cv::MatExpr max(double s, const WImageT<T, C>& a)
{
	return max(s, a.matrix());
}

