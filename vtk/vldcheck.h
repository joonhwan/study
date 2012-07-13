#pragma once

#include <vld.h>
// #define WIN32_LEAN_AND_MEAN
// #include <windows.h>

// const char* moduleList[] =
// {
// 	"LSDyna.dll"
// 	"QVTK.dll",
// 	"vtkCommon.dll",
// 	"vtkDICOMParser.dll",
// 	"vtkFiltering.dll",
// 	"vtkGraphics.dll",
// 	"vtkHybrid.dll",
// 	"vtkIO.dll",
// 	"vtkImaging.dll",
// 	"vtkInfovis.dll",
// 	"vtkNetCDF.dll",
// 	"vtkNetCDF_cxx.dll",
// 	"vtkQtChart.dll",
// 	"vtkRendering.dll",
// 	"vtkViews.dll",
// 	"vtkVolumeRendering.dll",
// 	"vtkWidgets.dll",
// 	"vtkalglib.dll",
// 	"vtkexoIIc.dll",
// 	"vtkexpat.dll",
// 	"vtkfreetype.dll",
// 	"vtkftgl.dll",
// 	"vtkhdf5.dll",
// 	"vtkhdf5_hl.dll",
// 	"vtkjpeg.dll",
// 	"vtklibxml2.dll",
// 	"vtkmetaio.dll",
// 	"vtkpng.dll",
// 	"vtksys.dll",
// 	"vtktiff.dll",
// 	"vtkverdict.dll",
// 	"vtkzlib.dll",
// 	"QtGuid4.dll",
// 	// "QtCored4.dll",
// 	// "QtSqld4.dll",
// 	0,
// };

// struct vld_enabler {
// 	vld_enabler()
// 	{
// 		VLDEnable();
// 		const char** module = &moduleList[0];
// 		while (*module) {
// 			HMODULE h = ::GetModuleHandle(*module);
// 			if (h) {
// 				VLDEnableModule(h);
// 			}
// 			++module;
// 		}
// 	}
// }___image_vld_enabler_instance;
