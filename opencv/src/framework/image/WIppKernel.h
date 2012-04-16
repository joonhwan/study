#pragma once

#include <ippi.h>

//
// initialization method for WIppIntKernel is simpler here but need
// more labour to implement than cv::Mat's cv::Mat_ matrix initialization method
// see & compare following example
//
// cv::Mat kernel2 = (cv::Mat_<float>(3,3) <<
//  				    0, -1,  0,
//  				   -1,  5, -1,
// 	     			    0, -1,  0);
//
// or even better idea is using boost::asign and boost::array together.

class WIppIntKernelProperty
{
public:
	WIppIntKernelProperty()
		: m_divisor(1)
	{
		m_size.width = m_size.height = 0;
	}
	WIppIntKernelProperty(int w, int h,
						  int anchorx, int anchory)
		: m_divisor(1)
	{
		m_size.width = w;
		m_size.height = h;
		m_anchor.x = anchorx;
		m_anchor.y = anchory;
	}
	void setAnchor(int x, int y)
	{
		m_anchor.x = x;
		m_anchor.y = y;
	}
	const IppiPoint& ippAnchor() const
	{
		return m_anchor;
	}
	void setDivisor(int divisor)
	{
		m_divisor = divisor;
	}
	int divisor() const
	{
		return m_divisor;
	}
	const IppiSize& ippSize() const
	{
		return m_size;
	}
protected:
	IppiPoint m_anchor;
	IppiSize m_size;
	int m_divisor;
};

template<int C, int N>
class WIppIntKernel;

template<>
class WIppIntKernel<1,3> : public WIppIntKernelProperty
{
public:
	WIppIntKernel(int _v00, int _v01, int _v02,
				  int _v10, int _v11, int _v12,
				  int _v20, int _v21, int _v22)
		: WIppIntKernelProperty(3,3,1,1)
	{
		v[0] = _v00;
		v[1] = _v01;
		v[2] = _v02;
		v[3] = _v10;
		v[4] = _v11;
		v[5] = _v12;
		v[6] = _v20;
		v[7] = _v21;
		v[8] = _v22;

		m_size.width = 3;
		m_size.height = 3;
	}
	operator const int* () const
	{
		return &v[0];
	}
protected:
	int v[3*3];
};

template<>
class WIppIntKernel<1,5> : public WIppIntKernelProperty
{
public:
	WIppIntKernel(int _v00, int _v01, int _v02, int _v03, int _v04,
				  int _v10, int _v11, int _v12, int _v13, int _v14,
				  int _v20, int _v21, int _v22, int _v23, int _v24,
				  int _v30, int _v31, int _v32, int _v33, int _v34,
				  int _v40, int _v41, int _v42, int _v43, int _v44)
		: WIppIntKernelProperty(5,5,2,2)
	{
		int i = 0;
		v[i++] = _v00; v[i++] = _v01; v[i++] = _v02; v[i++] = _v03; v[i++] = _v04;
		v[i++] = _v10; v[i++] = _v11; v[i++] = _v12; v[i++] = _v13; v[i++] = _v14;
		v[i++] = _v20; v[i++] = _v21; v[i++] = _v22; v[i++] = _v23; v[i++] = _v24;
		v[i++] = _v30; v[i++] = _v31; v[i++] = _v32; v[i++] = _v33; v[i++] = _v34;
		v[i++] = _v40; v[i++] = _v41; v[i++] = _v42; v[i++] = _v43; v[i++] = _v44;
	}
	operator const int* () const
	{
		return &v[0];
	}
protected:
	int v[5*5];
};

template<>
class WIppIntKernel<3,3> : public WIppIntKernelProperty
{
public:
	typedef WPixelValue<int,3> V;
	WIppIntKernel(int _v00, int _v01, int _v02,
				  int _v10, int _v11, int _v12,
				  int _v20, int _v21, int _v22)
		: WIppIntKernelProperty(3,3,1,1)
	{
		int i = 0;
		v[i] = v[i+1] = v[i+2] = _v00; i+=3;
		v[i] = v[i+1] = v[i+2] = _v01; i+=3;
		v[i] = v[i+1] = v[i+2] = _v02; i+=3;
		v[i] = v[i+1] = v[i+2] = _v10; i+=3;
		v[i] = v[i+1] = v[i+2] = _v11; i+=3;
		v[i] = v[i+1] = v[i+2] = _v12; i+=3;
		v[i] = v[i+1] = v[i+2] = _v20; i+=3;
		v[i] = v[i+1] = v[i+2] = _v21; i+=3;
		v[i] = v[i+1] = v[i+2] = _v22; i+=3;
	}
	WIppIntKernel(const V& _v00, const V& _v01, const V& _v02,
				  const V& _v10, const V& _v11, const V& _v12,
				  const V& _v20, const V& _v21, const V& _v22)
		: WIppIntKernelProperty(3,3,1,1)
	{
		int i = 0;
		_v00.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v01.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v02.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v10.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v11.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v12.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v20.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v21.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v22.getValue(v[i],v[i+1],v[i+2]); i+=3;
	}
	operator const int* () const
	{
		return &v[0];
	}
protected:
	int v[3*3*3];
};

template<>
class WIppIntKernel<3,5> : public WIppIntKernelProperty
{
public:
	typedef WPixelValue<int,3> V;
	WIppIntKernel(int _v00, int _v01, int _v02, int _v03, int _v04,
				  int _v10, int _v11, int _v12, int _v13, int _v14,
				  int _v20, int _v21, int _v22, int _v23, int _v24,
				  int _v30, int _v31, int _v32, int _v33, int _v34,
				  int _v40, int _v41, int _v42, int _v43, int _v44)
		: WIppIntKernelProperty(5,5,2,2)
	{
		int i = 0;
		v[i] = v[i+1] = v[i+2] = v[i+3] = v[i+4] = _v00; i+=5;
		v[i] = v[i+1] = v[i+2] = v[i+3] = v[i+4] = _v01; i+=5;
		v[i] = v[i+1] = v[i+2] = v[i+3] = v[i+4] = _v02; i+=5;
		v[i] = v[i+1] = v[i+2] = v[i+3] = v[i+4] = _v10; i+=5;
		v[i] = v[i+1] = v[i+2] = v[i+3] = v[i+4] = _v11; i+=5;
		v[i] = v[i+1] = v[i+2] = v[i+3] = v[i+4] = _v12; i+=5;
		v[i] = v[i+1] = v[i+2] = v[i+3] = v[i+4] = _v20; i+=5;
		v[i] = v[i+1] = v[i+2] = v[i+3] = v[i+4] = _v21; i+=5;
		v[i] = v[i+1] = v[i+2] = v[i+3] = v[i+4] = _v22; i+=5;
	}
	WIppIntKernel(const V& _v00, const V& _v01, const V& _v02, const V& _v03, const V& _v04,
				  const V& _v10, const V& _v11, const V& _v12, const V& _v13, const V& _v14,
				  const V& _v20, const V& _v21, const V& _v22, const V& _v23, const V& _v24,
				  const V& _v30, const V& _v31, const V& _v32, const V& _v33, const V& _v34,
				  const V& _v40, const V& _v41, const V& _v42, const V& _v43, const V& _v44)
		: WIppIntKernelProperty(5,5,2,2)
	{
		int i = 0;
		_v00.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v01.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v02.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v03.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v04.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v10.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v11.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v12.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v13.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v14.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v20.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v21.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v22.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v23.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v24.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v30.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v31.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v32.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v33.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v34.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v40.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v41.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v42.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v43.getValue(v[i],v[i+1],v[i+2]); i+=3;
		_v44.getValue(v[i],v[i+1],v[i+2]); i+=3;
	}
	operator const int* () const
	{
		return &v[0];
	}
protected:
	int v[3*3*3];
};

