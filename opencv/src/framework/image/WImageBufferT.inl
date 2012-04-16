#pragma once

#include "WImageT.h"

// for matrix operation

// plus

template<typename T, int C>
cv::MatExpr operator + (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator + (WConstImageT<T, C>& a, const cv::Scalar& s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator + (const cv::Scalar& s, WConstImageT<T, C>& a)
{
	return s + a.matrix;
}

template<typename T, int C>
cv::MatExpr operator + (const cv::MatExpr& e, WConstImageT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator + (WConstImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

//--


template<typename T, int C>
cv::MatExpr operator + (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator + (const WImageBufferT<T, C>& a, const cv::Scalar& s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator + (const cv::Scalar& s, const WImageBufferT<T, C>& a)
{
	return s + a.matrix;
}

template<typename T, int C>
cv::MatExpr operator + (const cv::MatExpr& e, const WImageBufferT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator + (const WImageBufferT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}


// minus

template<typename T, int C>
cv::MatExpr operator - (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a.matrix() - b.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (WConstImageT<T, C>& a, const cv::Scalar& s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator - (const cv::Scalar& s, WConstImageT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (const cv::MatExpr& e, WConstImageT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (WConstImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

template<typename T, int C>
cv::MatExpr operator - (WConstImageT<T, C>& m)
{
	return operator - (m.matrix())
}

template<typename T, int C>
cv::MatExpr operator - (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a.matrix() - b.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (const WImageBufferT<T, C>& a, const cv::Scalar& s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator - (const cv::Scalar& s, const WImageBufferT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (const cv::MatExpr& e, const WImageBufferT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator - (const WImageBufferT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

template<typename T, int C>
cv::MatExpr operator - (const WImageBufferT<T, C>& m)
{
	return operator - (m.matrix())
}

// multiply

template<typename T, int C>
cv::MatExpr operator * (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (WConstImageT<T, C>& a, double s)
{
	return a.matrix() + b;
}

template<typename T, int C>
cv::MatExpr operator * (double s, WConstImageT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (const cv::MatExpr& e, WConstImageT<T, C>& m)
{
	return e * m.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (WConstImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

// --

template<typename T, int C>
cv::MatExpr operator * (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (const WImageBufferT<T, C>& a, double s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator * (double s, const WImageBufferT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (const cv::MatExpr& e, const WImageBufferT<T, C>& m)
{
	return e * m.matrix();
}

template<typename T, int C>
cv::MatExpr operator * (const WImageBufferT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

// divide

template<typename T, int C>
cv::MatExpr operator / (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (WConstImageT<T, C>& a, double s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator / (double s, WConstImageT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (const cv::MatExpr& e, WConstImageT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (WConstImageT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}

// --

template<typename T, int C>
cv::MatExpr operator / (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a.matrix() + b.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (const WImageBufferT<T, C>& a, double s)
{
	return a.matrix() + s;
}

template<typename T, int C>
cv::MatExpr operator / (double s, const WImageBufferT<T, C>& a)
{
	return s + a.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (const cv::MatExpr& e, const WImageBufferT<T, C>& m)
{
	return e + m.matrix();
}

template<typename T, int C>
cv::MatExpr operator / (const WImageBufferT<T, C>& m, const cv::MatExpr& e)
{
	return m.matrix() + e;
}


// comparison

template<typename T, int C>
cv::MatExpr operator < (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a.matrix() < b.matrix();
}

template<typename T, int C>
cv::MatExpr operator < (WConstImageT<T, C>& a, double s)
{
	return a.matrix() < s;
}

template<typename T, int C>
cv::MatExpr operator < (double s, WConstImageT<T, C>& a)
{
	return s < a.matrix()

}

// --
template<typename T, int C>
cv::MatExpr operator < (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a.matrix() < b.matrix();
}

template<typename T, int C>
cv::MatExpr operator < (const WImageBufferT<T, C>& a, double s)
{
	return a.matrix() < s;
}

template<typename T, int C>
cv::MatExpr operator < (double s, const WImageBufferT<T, C>& a)
{
	return s < a.matrix()

}

template<typename T, int C>
cv::MatExpr operator <= (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a.matrix() <= b.matrix();
}

template<typename T, int C>
cv::MatExpr operator <= (WConstImageT<T, C>& a, double s)
{
	return a.matrix() <= s;
}

template<typename T, int C>
cv::MatExpr operator <= (double s, WConstImageT<T, C>& a)
{
	return s <= a.matrix();
}

template<typename T, int C>
cv::MatExpr operator <= (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a.matrix() <= b.matrix();
}

template<typename T, int C>
cv::MatExpr operator <= (const WImageBufferT<T, C>& a, double s)
{
	return a.matrix() <= s;
}

template<typename T, int C>
cv::MatExpr operator <= (double s, const WImageBufferT<T, C>& a)
{
	return s <= a.matrix();
}


template<typename T, int C>
cv::MatExpr operator == (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a.matrix() == b.matrix();
}

template<typename T, int C>
cv::MatExpr operator == (WConstImageT<T, C>& a, double s)
{
	return a.matrix() == b;
}

template<typename T, int C>
cv::MatExpr operator == (double s, WConstImageT<T, C>& a)
{
	return s == a.matrix();
}

template<typename T, int C>
cv::MatExpr operator == (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a.matrix() == b.matrix();
}

template<typename T, int C>
cv::MatExpr operator == (const WImageBufferT<T, C>& a, double s)
{
	return a.matrix() == b;
}

template<typename T, int C>
cv::MatExpr operator == (double s, const WImageBufferT<T, C>& a)
{
	return s == a.matrix();
}


template<typename T, int C>
cv::MatExpr operator != (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a + b;
}

template<typename T, int C>
cv::MatExpr operator != (WConstImageT<T, C>& a, double s)
{
	return a.matrix() != s;
}

template<typename T, int C>
cv::MatExpr operator != (double s, WConstImageT<T, C>& a)
{
	return s != a.matrix();

}

template<typename T, int C>
cv::MatExpr operator != (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a + b;
}

template<typename T, int C>
cv::MatExpr operator != (const WImageBufferT<T, C>& a, double s)
{
	return a.matrix() != s;
}

template<typename T, int C>
cv::MatExpr operator != (double s, const WImageBufferT<T, C>& a)
{
	return s != a.matrix();

}


template<typename T, int C>
cv::MatExpr operator >= (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a.matrix() >= b.matrix();
}

template<typename T, int C>
cv::MatExpr operator >= (WConstImageT<T, C>& a, double s)
{
	return a.matrix() >= s;
}

template<typename T, int C>
cv::MatExpr operator >= (double s, WConstImageT<T, C>& a)
{
	return s >= a.matrix();
}

template<typename T, int C>
cv::MatExpr operator >= (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a.matrix() >= b.matrix();
}

template<typename T, int C>
cv::MatExpr operator >= (const WImageBufferT<T, C>& a, double s)
{
	return a.matrix() >= s;
}

template<typename T, int C>
cv::MatExpr operator >= (double s, const WImageBufferT<T, C>& a)
{
	return s >= a.matrix();
}


template<typename T, int C>
cv::MatExpr operator > (WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return a.matrix() > b.matrix();
}

template<typename T, int C>
cv::MatExpr operator > (WConstImageT<T, C>& a, double s)
{
	return a.matrix() > s;
}

template<typename T, int C>
cv::MatExpr operator > (double s, WConstImageT<T, C>& a)
{
	return s > a.matrix();
}

template<typename T, int C>
cv::MatExpr operator > (const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return a.matrix() > b.matrix();
}

template<typename T, int C>
cv::MatExpr operator > (const WImageBufferT<T, C>& a, double s)
{
	return a.matrix() > s;
}

template<typename T, int C>
cv::MatExpr operator > (double s, const WImageBufferT<T, C>& a)
{
	return s > a.matrix();
}


template<typename T, int C>
cv::MatExpr min(WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return min(a.matrix(), b.matrix());
}

template<typename T, int C>
cv::MatExpr min(WConstImageT<T, C>& a, double s)
{
	return min(a.matrix(), s);
}

template<typename T, int C>
cv::MatExpr min(double s, WConstImageT<T, C>& a)
{
	return min(s, a.matrix());
}

template<typename T, int C>
cv::MatExpr min(const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return min(a.matrix(), b.matrix());
}

template<typename T, int C>
cv::MatExpr min(const WImageBufferT<T, C>& a, double s)
{
	return min(a.matrix(), s);
}

template<typename T, int C>
cv::MatExpr min(double s, const WImageBufferT<T, C>& a)
{
	return min(s, a.matrix());
}


template<typename T, int C>
cv::MatExpr max(WConstImageT<T, C>& a, WConstImageT<T, C>& b)
{
	return max(a.matrix(), b.matrix());
}

template<typename T, int C>
cv::MatExpr max(WConstImageT<T, C>& a, double s)
{
	return max(a.matrix(), s);
}

template<typename T, int C>
cv::MatExpr max(double s, WConstImageT<T, C>& a)
{
	return max(s, a.matrix());
}

template<typename T, int C>
cv::MatExpr max(const WImageBufferT<T, C>& a, const WImageBufferT<T, C>& b)
{
	return max(a.matrix(), b.matrix());
}

template<typename T, int C>
cv::MatExpr max(const WImageBufferT<T, C>& a, double s)
{
	return max(a.matrix(), s);
}

template<typename T, int C>
cv::MatExpr max(double s, const WImageBufferT<T, C>& a)
{
	return max(s, a.matrix());
}

