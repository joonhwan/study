#pragma once

#include <vld.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

const char* moduleList[] =
{
	"opencv_calib3d233.dll",
	"opencv_calib3d233d.dll",
	"opencv_contrib233.dll",
	"opencv_contrib233d.dll",
	"opencv_core233.dll",
	"opencv_core233d.dll",
	"opencv_features2d233.dll",
	"opencv_features2d233d.dll",
	"opencv_ffmpeg.dll",
	"opencv_flann233.dll",
	"opencv_flann233d.dll",
	"opencv_gpu233.dll",
	"opencv_gpu233d.dll",
	"opencv_highgui233.dll",
	"opencv_highgui233d.dll",
	"opencv_imgproc233.dll",
	"opencv_imgproc233d.dll",
	"opencv_legacy233.dll",
	"opencv_legacy233d.dll",
	"opencv_ml233.dll",
	"opencv_ml233d.dll",
	"opencv_nonfree233.dll",
	"opencv_nonfree233d.dll",
	"opencv_objdetect233.dll",
	"opencv_objdetect233d.dll",
	"opencv_photo233.dll",
	"opencv_photo233d.dll",
	"opencv_stitching233.dll",
	"opencv_stitching233d.dll",
	"opencv_ts233.dll",
	"opencv_ts233d.dll",
	"opencv_video233.dll",
	"opencv_video233d.dll",
	"opencv_videostab233.dll",
	"opencv_videostab233d.dll",
	0,
};

struct vld_enabler {
	vld_enabler()
	{
		VLDEnable();
		const char** module = &moduleList[0];
		while (*module) {
			HMODULE h = ::GetModuleHandle(*module);
			if (h) {
				VLDEnableModule(h);
			}
			++module;
		}
	}
}___image_vld_enabler_instance;
