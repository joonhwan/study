cmake_minimum_required(VERSION 2.8.0)

project(qtpropertybrowser)

include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# link_libraries(${QT_QTMAIN_LIBRARY}) # for WinMain wrapper.

set(${PROJECT_NAME}_CPP
  qtpropertybrowserutils.cpp
  )

set(${PROJECT_NAME}_H
  QtAbstractEditorFactoryBase
  QtAbstractPropertyBrowser
  QtAbstractPropertyManager
  QtBoolPropertyManager
  QtBrowserItem
  QtButtonPropertyBrowser
  QtCharEditorFactory
  QtCharPropertyManager
  QtCheckBoxFactory
  QtColorEditorFactory
  QtColorPropertyManager
  QtCursorEditorFactory
  QtCursorPropertyManager
  QtDateEditFactory
  QtDatePropertyManager
  QtDateTimeEditFactory
  QtDateTimePropertyManager
  QtDoublePropertyManager
  QtDoubleSpinBoxFactory
  QtEnumEditorFactory
  QtEnumPropertyManager
  QtFlagPropertyManager
  QtFontEditorFactory
  QtFontPropertyManager
  QtGroupBoxPropertyBrowser
  QtGroupPropertyManager
  QtIntPropertyManager
  QtKeySequenceEditorFactory
  QtKeySequencePropertyManager
  QtLineEditFactory
  QtLocalePropertyManager
  QtPointFPropertyManager
  QtPointPropertyManager
  QtProperty
  QtRectFPropertyManager
  QtRectPropertyManager
  QtScrollBarFactory
  QtSizeFPropertyManager
  QtSizePolicyPropertyManager
  QtSizePropertyManager
  QtSliderFactory
  QtSpinBoxFactory
  QtStringPropertyManager
  QtTimeEditFactory
  QtTimePropertyManager
  QtTreePropertyBrowser
  QtVariantEditorFactory
  QtVariantProperty
  QtVariantPropertyManager
  )

set(${PROJECT_NAME}_MOC_H
  qtpropertybrowserutils_p.h
  )

set(${PROJECT_NAME}_QRC
  qtpropertybrowser.qrc
  )

set(${PROJECT_NAME}_MOC_H_INCLUDED_BY_SOURCE
  qtbuttonpropertybrowser.h
  qteditorfactory.h
  qtgroupboxpropertybrowser.h
  qtpropertybrowser.h
  qtpropertymanager.h
  qttreepropertybrowser.h
  qtvariantproperty.h
  )

set(${PROJECT_NAME}_MOC_CPP_INCLUDED_BY_SOURCE "")
foreach(moc_from_cpp ${${PROJECT_NAME}_MOC_H_INCLUDED_BY_SOURCE})
  get_filename_component(moc_from_cpp_filetitle ${moc_from_cpp} NAME_WE)
  set(target_moc_name "moc_${moc_from_cpp_filetitle}.cpp")
  message("generating ${target_moc_name}")
  qt4_generate_moc(${moc_from_cpp} ${target_moc_name})
  set(${PROJECT_NAME}_MOC_CPP_INCLUDED_BY_SOURCE ${${PROJECT_NAME}_MOC_CPP_INCLUDED_BY_SOURCE} ${target_moc_name})
endforeach(moc_from_cpp)

set(${PROJECT_NAME}_CPP_WITH_MOC
  qtbuttonpropertybrowser.cpp
  qteditorfactory.cpp
  qtgroupboxpropertybrowser.cpp
  qtpropertybrowser.cpp
  qtpropertymanager.cpp
  qttreepropertybrowser.cpp
  qtvariantproperty.cpp
  )

set(${PROJECT_NAME}_MOC_FROM_CPP "")
foreach(moc_from_cpp ${${PROJECT_NAME}_CPP_WITH_MOC})
  get_filename_component(moc_from_cpp_filetitle ${moc_from_cpp} NAME_WE)
  set(target_moc_name "${moc_from_cpp_filetitle}.moc")
  message("generating ${target_moc_name}")
  qt4_generate_moc(${moc_from_cpp} ${target_moc_name})
  set(${PROJECT_NAME}_MOC_FROM_CPP ${${PROJECT_NAME}_MOC_FROM_CPP} ${target_moc_name})
endforeach(moc_from_cpp)

# not to re-include source file to be compiled
set_source_files_properties(${${PROJECT_NAME}_MOC_CPP_INCLUDED_BY_SOURCE}
  PROPERTIES
  HEADER_FILE_ONLY ON
  )
# set_source_files_properties(${${PROJECT_NAME}_MOC_FROM_CPP}
#   PROPERTIES
#   HEADER_FILE_ONLY ON
#   )

qt4_wrap_cpp(${PROJECT_NAME}_MOC_CPP ${${PROJECT_NAME}_MOC_H})
qt4_add_resources(${PROJECT_NAME}_QRC_CPP ${${PROJECT_NAME}_QRC})

include_directories(${CMAKE_BIN_DIR})

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_CPP}
  ${${PROJECT_NAME}_MOC_CPP}
  ${${PROJECT_NAME}_MOC_H}
  ${${PROJECT_NAME}_CPP_WITH_MOC}
  ${${PROJECT_NAME}_MOC_FROM_CPP}
  ${${PROJECT_NAME}_QRC_CPP}
  ${${PROJECT_NAME}_MOC_CPP_INCLUDED_BY_SOURCE}
  )

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  FOLDER "externals"
  )

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
  ${QT_LIBRARIES}
  )

