#pragma once

template<typename T>
struct WLookupTableTraits;


template<>
struct WLookupTableTraits<uchar>
{
	// default table data type
	typedef int TableDataType;
};


template<>
struct WLookupTableTraits<ushort>
{
	// default table data type
	typedef int TableDataType;
};


template<>
struct WLookupTableTraits<short>
{
	// default table data type
	typedef int TableDataType;
};

template<>
struct WLookupTableTraits<float>
{
	typedef float TableDataType;
};

