find_package(Ipp REQUIRED) 		# version 7.0 IPP is needed. see FindIpp.cmake

if (IPC_BUILD)
  set(IPP_LIB_SUFFIX "")
else(IPC_BUILD)
  set(IPP_LIB_SUFFIX "")
endif(IPC_BUILD)

include_directories(${IPP_H_DIR})

set(IPP_LIBRARIES "general;${IPP_LIB_DIR}/ippi${IPP_LIB_SUFFIX}.lib;general;${IPP_LIB_DIR}/ippcore${IPP_LIB_SUFFIX}.lib;general;${IPP_LIB_DIR}/ippcv${IPP_LIB_SUFFIX}.lib;general;${IPP_LIB_DIR}/ipps${IPP_LIB_SUFFIX}.lib;general;${IPP_LIB_DIR}/ippm${IPP_LIB_SUFFIX}.lib")

