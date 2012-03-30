set(OPENCV_DIR d:/prj/oss/not-mine/opencv/build/install)
set(OPENCV_H_DIR ${OPENCV_DIR}/include)
set(OPENCV_LIB_DIR ${OPENCV_DIR}/lib)

include_directories(${OPENCV_H_DIR})
include_directories(${OPENCV_H_DIR}/opencv)

set(OPENCV_CORE_LIBRARY "debug;${OPENCV_LIB_DIR}/opencv_core233d.lib;optimized;${OPENCV_LIB_DIR}/opencv_core233.lib")
set(OPENCV_HIGHGUI_LIBRARY "debug;${OPENCV_LIB_DIR}/opencv_highgui233d.lib;optimized;${OPENCV_LIB_DIR}/opencv_highgui233.lib")
set(OPENCV_IMAGEPROC_LIBRARY "debug;${OPENCV_LIB_DIR}/opencv_imgproc233d.lib;optimized;${OPENCV_LIB_DIR}/opencv_imgproc233.lib")
set(OPENCV_ML_LIBRARY "debug;${OPENCV_LIB_DIR}/opencv_ml233d.lib;optimized;${OPENCV_LIB_DIR}/opencv_ml233.lib")
set(OPENCV_LEGACY_LIBRARY "debug;${OPENCV_LIB_DIR}/opencv_legacy233d.lib;optimized;${OPENCV_LIB_DIR}/opencv_legacy233.lib")
set(OPENCV_FEATURES_LIBRARY "debug;${OPENCV_LIB_DIR}/opencv_features2d233d.lib;optimized;${OPENCV_LIB_DIR}/opencv_features2d233.lib")
set(OPENCV_OBJECT_LIBRARY "debug;${OPENCV_LIB_DIR}/opencv_objdetect233d.lib;optimized;${OPENCV_LIB_DIR}/opencv_objdetect233.lib")
set(OPENCV_CONTRIB_LIBRARY "debug;${OPENCV_LIB_DIR}/opencv_contrib233d.lib;optimized;${OPENCV_LIB_DIR}/opencv_contrib233.lib")

set(OPENCV_LIBRARIES 
  ${OPENCV_CORE_LIBRARY}
  ${OPENCV_HIGHGUI_LIBRARY}
  ${OPENCV_IMAGEPROC_LIBRARY}
  ${OPENCV_ML_LIBRARY}
  ${OPENCV_LEGACY_LIBRARY}
  ${OPENCV_FEATURES_LIBRARY}
  ${OPENCV_OBJECT_LIBRARY}
  ${OPENCV_CONTRIB_LIBRARY}
  )
