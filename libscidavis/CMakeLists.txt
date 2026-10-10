###################### HEADERS ##############################################
set( HEADERS
  "src/app/ApplicationWindow.h"
  "src/app/IconLoader.h"
  "src/app/globals.h"
  "src/plot/Graph.h"
  "src/plot/3d/Graph3D.h"
  "src/project/Table.h"
  "src/dialogs/CurvesDialog.h"
  "src/dialogs/PlotDialog.h"
  "src/dialogs/Plot3DDialog.h"
  "src/dialogs/PlotWizard.h"
  "src/dialogs/ExportDialog.h"
  "src/dialogs/AxesDialog.h"
  "src/dialogs/PolynomFitDialog.h"
  "src/dialogs/ExpDecayDialog.h"
  "src/dialogs/FunctionDialog.h"
  "src/dialogs/FitDialog.h"
  "src/dialogs/SurfaceDialog.h"
  "src/dialogs/TextDialog.h"
  "src/dialogs/LineDialog.h"
  "src/plot/tools/ScalePicker.h"
  "src/plot/tools/TitlePicker.h"
  "src/plot/tools/CanvasPicker.h"
  "src/plot/PlotCurve.h"
  "src/plot/QwtErrorPlotCurve.h"
  "src/plot/QwtPieCurve.h"
  "src/dialogs/ErrDialog.h"
  "src/plot/Legend.h"
  "src/plot/ArrowMarker.h"
  "src/plot/ImageMarker.h"
  "src/dialogs/ImageDialog.h"
  "src/analysis/fit/fit_gsl.h"
  "src/plot/MultiLayer.h"
  "src/dialogs/LayerDialog.h"
  "src/dialogs/IntDialog.h"
  "src/plot/3d/Bar.h"
  "src/plot/3d/Cone3D.h"
  "src/dialogs/ConfigDialog.h"
  "src/plot/QwtBarCurve.h"
  "src/plot/BoxCurve.h"
  "src/plot/QwtHistogram.h"
  "src/plot/VectorCurve.h"
  "src/plot/ScaleDraw.h"
  "src/project/Matrix.h"
  "src/dialogs/DataSetDialog.h"
  "src/scripting/MyParser.h"
  "src/widgets/SymbolBox.h"
  "src/widgets/PatternBox.h"
  "src/dialogs/SymbolDialog.h"
  "src/plot/Plot.h"
  "src/widgets/ColorButton.h"
  "src/dialogs/AssociationsDialog.h"
  "src/dialogs/RenameWindowDialog.h"
  "src/project/MyWidget.h"
  "src/dialogs/InterpolationDialog.h"
  "src/dialogs/ImportASCIIDialog.h"
  "src/dialogs/ImageExportDialog.h"
  "src/dialogs/SmoothCurveDialog.h"
  "src/dialogs/FilterDialog.h"
  "src/dialogs/FFTDialog.h"
  "src/project/Note.h"
  "src/project/Folder.h"
  "src/dialogs/FindDialog.h"
  "src/scripting/ScriptingEnv.h"
  "src/scripting/Script.h"
  "src/scripting/ScriptEdit.h"
  "src/plot/FunctionCurve.h"
  "src/analysis/fit/Fit.h"
  "src/analysis/fit/MultiPeakFit.h"
  "src/analysis/fit/ExponentialFit.h"
  "src/analysis/fit/PolynomialFit.h"
  "src/analysis/fit/NonLinearFit.h"
  "src/analysis/fit/PluginFit.h"
  "src/analysis/fit/SigmoidalFit.h"
  "src/app/customevents.h"
  "src/dialogs/ScriptingLangDialog.h"
  "src/widgets/TextFormatButtons.h"
  "src/project/TableStatistics.h"
  "src/plot/Spectrogram.h"
  "src/widgets/ColorMapEditor.h"
  "src/plot/SelectionMoveResizer.h"
  "src/analysis/Filter.h"
  "src/analysis/Differentiation.h"
  "src/analysis/Integration.h"
  "src/analysis/Interpolation.h"
  "src/analysis/SmoothFilter.h"
  "src/analysis/FFTFilter.h"
  "src/analysis/FFT.h"
  "src/analysis/Convolution.h"
  "src/analysis/Correlation.h"
  "src/plot/tools/PlotToolInterface.h"
  "src/plot/tools/ScreenPickerTool.h"
  "src/plot/tools/DataPickerTool.h"
  "src/plot/tools/RangeSelectorTool.h"
  "src/plot/tools/TranslateCurveTool.h"
  "src/plot/tools/MultiPeakFitTool.h"
  "src/dialogs/CurveRangeDialog.h"
  "src/plot/tools/LineProfileTool.h"
  "src/plot/PlotEnrichement.h"
  "src/dialogs/ExtensibleFileDialog.h"
  "src/dialogs/OpenProjectDialog.h"
  "src/plot/Grid.h"
  "src/plot/tools/DataPointPicker.h"
  "src/io/TeXTableSettings.h"
  "src/widgets/TeXTableSettingsWidget.h"
  "src/dialogs/TeXTableExportDialog.h"
  "src/widgets/PenWidget.h"
  "src/app/QStringStdString.h"
  "src/future/core/AbstractAspect.h"
  "src/future/core/AbstractPart.h"
  "src/future/core/AspectPrivate.h"
  "src/future/core/aspectcommands.h"
  "src/future/core/future_Folder.h"
  "src/future/core/Project.h"
  "src/future/core/ProjectConfigPage.h"
  "src/future/core/PartMdiView.h"
  "src/future/core/AbstractColumn.h"
  "src/future/core/column/Column.h"
  "src/future/core/column/ColumnPrivate.h"
  "src/future/core/column/columncommands.h"
  "src/future/core/AbstractFilter.h"
  "src/future/core/AbstractSimpleFilter.h"
  "src/future/core/datatypes/SimpleCopyThroughFilter.h"
  "src/future/core/datatypes/DateTime2DoubleFilter.h"
  "src/future/core/datatypes/DateTime2StringFilter.h"
  "src/future/core/datatypes/DayOfWeek2DoubleFilter.h"
  "src/future/core/datatypes/Double2DateTimeFilter.h"
  "src/future/core/datatypes/Double2DayOfWeekFilter.h"
  "src/future/core/datatypes/Double2MonthFilter.h"
  "src/future/core/datatypes/Double2StringFilter.h"
  "src/future/core/datatypes/NumericDateTimeBaseFilter.h"
  "src/future/core/datatypes/Month2DoubleFilter.h"
  "src/future/core/datatypes/String2DateTimeFilter.h"
  "src/future/core/datatypes/String2DayOfWeekFilter.h"
  "src/future/core/datatypes/String2DoubleFilter.h"
  "src/future/core/datatypes/String2MonthFilter.h"
  "src/future/lib/macros.h"
  "src/future/lib/XmlStreamReader.h"
  "src/future/lib/ActionManager.h"
  "src/future/lib/ConfigPageWidget.h"
  "src/future/lib/Interval.h"
  "src/future/lib/IntervalAttribute.h"
  "src/future/matrix/future_Matrix.h"
  "src/future/matrix/MatrixModel.h"
  "src/future/matrix/MatrixView.h"
  "src/future/matrix/matrixcommands.h"
  "src/future/table/future_Table.h"
  "src/future/table/TableModel.h"
  "src/future/table/TableView.h"
  "src/future/table/tablecommands.h"
  "src/future/table/TableDoubleHeaderView.h"
  "src/future/table/TableItemDelegate.h"
  "src/future/table/TableCommentsHeaderModel.h"
  "src/future/table/future_SortDialog.h"
  "src/future/table/AsciiTableImportFilter.h"
  "src/future/core/AbstractImportFilter.h"
  "src/future/core/interfaces.h"
  "src/scripting/MuParserScript.h"
  "src/scripting/MuParserScripting.h"
)

###################### SOURCES ##############################################
set( SRCS
  "src/app/ApplicationWindow.cpp"
  "src/app/IconLoader.cpp"
  "src/plot/Graph.cpp"
  "src/plot/3d/Graph3D.cpp"
  "src/project/Table.cpp"
  "src/dialogs/CurvesDialog.cpp"
  "src/dialogs/PlotDialog.cpp"
  "src/dialogs/Plot3DDialog.cpp"
  "src/dialogs/PlotWizard.cpp"
  "src/dialogs/ExportDialog.cpp"
  "src/dialogs/AxesDialog.cpp"
  "src/dialogs/PolynomFitDialog.cpp"
  "src/dialogs/TextDialog.cpp"
  "src/plot/tools/ScalePicker.cpp"
  "src/plot/tools/TitlePicker.cpp"
  "src/plot/tools/CanvasPicker.cpp"
  "src/dialogs/ExpDecayDialog.cpp"
  "src/dialogs/FunctionDialog.cpp"
  "src/dialogs/FitDialog.cpp"
  "src/dialogs/SurfaceDialog.cpp"
  "src/dialogs/LineDialog.cpp"
  "src/plot/PlotCurve.cpp"
  "src/plot/QwtErrorPlotCurve.cpp"
  "src/plot/QwtPieCurve.cpp"
  "src/dialogs/ErrDialog.cpp"
  "src/plot/Legend.cpp"
  "src/plot/ArrowMarker.cpp"
  "src/plot/ImageMarker.cpp"
  "src/dialogs/ImageDialog.cpp"
  "src/plot/MultiLayer.cpp"
  "src/dialogs/LayerDialog.cpp"
  "src/dialogs/IntDialog.cpp"
  "src/plot/3d/Bar.cpp"
  "src/plot/3d/Cone3D.cpp"
  "src/dialogs/DataSetDialog.cpp"
  "src/dialogs/ConfigDialog.cpp"
  "src/plot/QwtBarCurve.cpp"
  "src/plot/BoxCurve.cpp"
  "src/plot/QwtHistogram.cpp"
  "src/plot/VectorCurve.cpp"
  "src/project/Matrix.cpp"
  "src/scripting/MyParser.cpp"
  "src/widgets/SymbolBox.cpp"
  "src/widgets/PatternBox.cpp"
  "src/dialogs/SymbolDialog.cpp"
  "src/plot/Plot.cpp"
  "src/widgets/ColorButton.cpp"
  "src/dialogs/AssociationsDialog.cpp"
  "src/dialogs/RenameWindowDialog.cpp"
  "src/project/MyWidget.cpp"
  "src/dialogs/InterpolationDialog.cpp"
  "src/analysis/fit/fit_gsl.cpp"
  "src/dialogs/SmoothCurveDialog.cpp"
  "src/dialogs/FilterDialog.cpp"
  "src/dialogs/FFTDialog.cpp"
  "src/project/Note.cpp"
  "src/project/Folder.cpp"
  "src/dialogs/FindDialog.cpp"
  "src/widgets/TextFormatButtons.cpp"
  "src/scripting/ScriptEdit.cpp"
  "src/dialogs/ImportASCIIDialog.cpp"
  "src/dialogs/ImageExportDialog.cpp"
  "src/plot/ScaleDraw.cpp"
  "src/plot/FunctionCurve.cpp"
  "src/analysis/fit/Fit.cpp"
  "src/analysis/fit/MultiPeakFit.cpp"
  "src/analysis/fit/ExponentialFit.cpp"
  "src/analysis/fit/PolynomialFit.cpp"
  "src/analysis/fit/PluginFit.cpp"
  "src/analysis/fit/NonLinearFit.cpp"
  "src/analysis/fit/SigmoidalFit.cpp"
  "src/scripting/ScriptingEnv.cpp"
  "src/scripting/Script.cpp"
  "src/dialogs/ScriptingLangDialog.cpp"
  "src/project/TableStatistics.cpp"
  "src/plot/Spectrogram.cpp"
  "src/widgets/ColorMapEditor.cpp"
  "src/plot/SelectionMoveResizer.cpp"
  "src/analysis/Filter.cpp"
  "src/analysis/Differentiation.cpp"
  "src/analysis/Integration.cpp"
  "src/analysis/Interpolation.cpp"
  "src/analysis/SmoothFilter.cpp"
  "src/analysis/FFTFilter.cpp"
  "src/analysis/FFT.cpp"
  "src/analysis/Convolution.cpp"
  "src/analysis/Correlation.cpp"
  "src/plot/tools/ScreenPickerTool.cpp"
  "src/plot/tools/DataPickerTool.cpp"
  "src/plot/tools/RangeSelectorTool.cpp"
  "src/plot/tools/TranslateCurveTool.cpp"
  "src/plot/tools/MultiPeakFitTool.cpp"
  "src/dialogs/CurveRangeDialog.cpp"
  "src/plot/tools/LineProfileTool.cpp"
  "src/plot/PlotEnrichement.cpp"
  "src/dialogs/ExtensibleFileDialog.cpp"
  "src/dialogs/OpenProjectDialog.cpp"
  "src/plot/Grid.cpp"
  "src/app/globals.cpp"
  "src/plot/tools/DataPointPicker.cpp"
  "src/io/TeXTableSettings.cpp"
  "src/widgets/TeXTableSettingsWidget.cpp"
  "src/dialogs/TeXTableExportDialog.cpp"
  "src/app/version.cpp"
  "src/widgets/PenWidget.cpp"
  "src/future/core/AbstractAspect.cpp"
  "src/future/core/AbstractPart.cpp"
  "src/future/core/AspectPrivate.cpp"
  "src/future/core/future_Folder.cpp"
  "src/future/core/PartMdiView.cpp"
  "src/future/core/Project.cpp"
  "src/future/core/column/Column.cpp"
  "src/future/core/column/ColumnPrivate.cpp"
  "src/future/core/column/columncommands.cpp"
  "src/future/core/datatypes/DateTime2StringFilter.cpp"
  "src/future/core/datatypes/String2DateTimeFilter.cpp"
  "src/future/core/datatypes/Double2StringFilter.cpp"
  "src/future/core/datatypes/NumericDateTimeBaseFilter.cpp"
  "src/future/core/AbstractSimpleFilter.cpp"
  "src/future/core/AbstractFilter.cpp"
  "src/future/core/ProjectConfigPage.cpp"
  "src/future/lib/XmlStreamReader.cpp"
  "src/future/lib/ActionManager.cpp"
  "src/future/lib/ConfigPageWidget.cpp"
  "src/future/matrix/future_Matrix.cpp"
  "src/future/matrix/MatrixModel.cpp"
  "src/future/matrix/MatrixView.cpp"
  "src/future/matrix/matrixcommands.cpp"
  "src/future/table/future_Table.cpp"
  "src/future/table/TableModel.cpp"
  "src/future/table/TableView.cpp"
  "src/future/table/tablecommands.cpp"
  "src/future/table/TableDoubleHeaderView.cpp"
  "src/future/table/TableItemDelegate.cpp"
  "src/future/table/TableCommentsHeaderModel.cpp"
  "src/future/table/future_SortDialog.cpp"
  "src/future/table/AsciiTableImportFilter.cpp"
  "src/scripting/MuParserScript.cpp"
  "src/scripting/MuParserScripting.cpp"
  )

###################### FORMS ##############################################
set( FORMS "src/app/SciDAVisAbout.ui"
  "src/future/matrix/matrixcontroltabs.ui"
  "src/future/core/ProjectConfigPage.ui"
  "src/future/table/controltabs.ui"
  "src/future/table/DimensionsDialog.ui"
  )

if( ORIGIN_IMPORT )
  list( APPEND HEADERS "src/io/importOPJ.h" )
  list( APPEND SRCS "src/io/importOPJ.cpp" )
endif()

add_library( libscidavis STATIC
  ${SRCS}
  ${HEADERS}
  ${FORMS}
  )
  
if( MSVC )
	foreach(_source IN ITEMS ${SRCS})
		get_filename_component(_source_path "${_source}" PATH)
		string(REGEX REPLACE "^src/?([^/]*)" "\\1" _source_path ${_source_path})
		if (NOT ${_source_path} STREQUAL "")
			source_group("Source Files/${_source_path}" FILES "${_source}")
		endif()
	endforeach()

	foreach(_source IN ITEMS ${HEADERS})
		get_filename_component(_source_path "${_source}" PATH)
		string(REGEX REPLACE "^src/?([^/]*)" "\\1" _source_path ${_source_path})
		if (NOT ${_source_path} STREQUAL "")
			source_group("Header Files/${_source_path}" FILES "${_source}")
		endif()
	endforeach()

	foreach(_source IN ITEMS ${FORMS})
		get_filename_component(_source_path "${_source}" PATH)
		string(REGEX REPLACE "^src/?([^/]*)" "\\1" _source_path ${_source_path})
		if (NOT ${_source_path} STREQUAL "")
			source_group("Forms/${_source_path}" FILES "${_source}")
		else()
			source_group("Forms" FILES "${_source}")
		endif()
		
	endforeach()
endif()

set_target_properties(libscidavis PROPERTIES OUTPUT_NAME scidavis)

target_link_libraries( libscidavis
  ZLIB::ZLIB
  GSL::gsl
  GSL::gslcblas
  OpenGL::GL
  OpenGL::GLU
  ${MUPARSER_LIB}
  minigzip
  Qt6::Core
  Qt6::Gui
  Qt6::Widgets
  Qt6::PrintSupport
  Qt6::OpenGL
  Qt6::OpenGLWidgets
  Qt6::Svg
  Qt6::Xml
  m
  )

target_include_directories( libscidavis PUBLIC ${MUPARSER_INCLUDE_DIR} )

# bundled Qwt 5 (ported to Qt 6) and QwtPlot3D, see 3rdparty/CMakeLists.txt
target_link_libraries( libscidavis qwt5 qwtplot3d )


if( SCRIPTING_PYTHON )
  target_include_directories( libscidavis PUBLIC ${Python3_INCLUDE_DIRS} )
  target_link_libraries( libscidavis  ${Python3_LIBRARIES} )

  # add sip generated files' directory to include path
  target_include_directories( libscidavis PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
endif()

target_compile_definitions( libscidavis PUBLIC
  LEGACY_CODE_0_2_x
  SCRIPTING_CONSOLE
  SCRIPTING_DIALOG
  )

if( WIN32 )
  target_compile_definitions( libscidavis PUBLIC
    TS_PATH="${CMAKE_INSTALL_PREFIX}/translations"
    DOC_PATH="${CMAKE_INSTALL_PREFIX}"
    PLUGIN_PATH="${CMAKE_INSTALL_PREFIX}/fitPlugins"
    )
else()
  target_compile_definitions( libscidavis PUBLIC
     TS_PATH="${CMAKE_INSTALL_FULL_DATAROOTDIR}/scidavis/translations"
     DOC_PATH="${CMAKE_INSTALL_DOCDIR}/scidavis"
     PLUGIN_PATH="${CMAKE_INSTALL_LIBDIR}/scidavis/plugins"
    )
endif()

if( WIN32 )
  target_compile_definitions( libscidavis PUBLIC
    DYNAMIC_MANUAL_PATH
    DYNAMIC_PLUGIN_PATH
    )
endif()

if( SEARCH_FOR_UPDATES )
  target_compile_definitions( libscidavis PUBLIC SEARCH_FOR_UPDATES )
endif()

if( DOWNLOAD_LINKS )
  target_compile_definitions( libscidavis PUBLIC DOWNLOAD_LINKS )
endif()

if( SCRIPTING_MUPARSER )
  target_compile_definitions( libscidavis PUBLIC SCRIPTING_MUPARSER )
endif()

if( ORIGIN_IMPORT )
  target_compile_definitions( libscidavis PUBLIC ORIGIN_IMPORT )
  if( LIBORIGIN_FOUND )
    target_link_libraries( libscidavis PkgConfig::LIBORIGIN )
  else()
    target_link_libraries( libscidavis origin_static )
    target_include_directories( libscidavis PUBLIC
      "${CMAKE_SOURCE_DIR}/3rdparty/liborigin" )
  endif()
endif()

if( SCRIPTING_PYTHON )
  target_compile_definitions( libscidavis PUBLIC
    PYTHON_CONFIG_PATH="${CMAKE_INSTALL_PREFIX}/etc"
    PYTHON_UTIL_PATH="${CMAKE_INSTALL_PREFIX}/share/scidavis"
    SCRIPTING_PYTHON
    )
  if( MINGW )
    get_filename_component( PYTHON_DIR ${Python3_EXECUTABLE} DIRECTORY )
    file( REAL_PATH "${PYTHON_DIR}/.." PYTHON_ROOT_DIR )
    set( PYTHONHOME "${PYTHON_ROOT_DIR}" CACHE PATH "Python Home" )
    message( STATUS "PYTHONHOME = ${PYTHONHOME}" )
    set_property( SOURCE "src/scripting/PythonScripting.cpp"
      APPEND
      PROPERTY COMPILE_DEFINITIONS
      PYTHONHOME=${PYTHONHOME}
      )
  endif()
endif()

if( SEARCH_FOR_UPDATES OR DOWNLOAD_LINKS )
  target_link_libraries( libscidavis Qt6::Network )
endif()

# Every module folder is on the include path, so headers are included by
# file name only (e.g. #include "Graph.h") regardless of where they live.
target_include_directories( libscidavis PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/app"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/project"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/io"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/analysis"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/analysis/fit"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/plot"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/plot/3d"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/plot/tools"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/scripting"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/dialogs"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/widgets"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/future"
  )

if( SCRIPTING_PYTHON )

  if( SIP_VERSION VERSION_GREATER_EQUAL 5 )
    set( scidavis_SIP_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/python/scidavis )
  else()
    set( scidavis_SIP_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR} )
  endif()

  set(scidavis_PyQt_HDR ${scidavis_SIP_OUTPUT_DIR}/sipAPIscidavis.h)
  if( SIP_VERSION VERSION_GREATER_EQUAL 5 )
    set( scidavis_SIP_HDR ${CMAKE_CURRENT_BINARY_DIR}/python/sip.h )
    target_include_directories( libscidavis BEFORE PUBLIC
      "${CMAKE_CURRENT_BINARY_DIR}/python"
      "${scidavis_SIP_OUTPUT_DIR}"
    )
  endif()

  set_source_files_properties(
    ${scidavis_PyQt_HDR}
    PROPERTIES
    GENERATED ON
    )

  set(scidavis_PyQt_SRC
    ${scidavis_SIP_OUTPUT_DIR}/sipscidaviscmodule.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisApplicationWindow.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisGraph.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisArrowMarker.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisImageMarker.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisLegend.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisMultiLayer.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisTable.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisMatrix.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisMyWidget.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisScriptEdit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisNote.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisPythonScript.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisPythonScripting.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisFolder.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisExponentialFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisTwoExpFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisThreeExpFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisSigmoidalFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisGaussAmpFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisLorentzFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisNonLinearFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisPluginFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisMultiPeakFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisPolynomialFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisLinearFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisGaussFit.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisFilter.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisDifferentiation.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisIntegration.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisInterpolation.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisSmoothFilter.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisFFTFilter.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisFFT.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisCorrelation.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisConvolution.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisDeconvolution.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisAbstractAspect.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisColumn.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisQwtSymbol.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisQwtPlotCurve.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisQwtPlot.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisGrid.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisQList0100QDateTime.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisQList0101Folder.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisQList0101MyWidget.cpp
    ${scidavis_SIP_OUTPUT_DIR}/sipscidavisQList0101QwtPlotCurve.cpp
    )

  set_source_files_properties(
    ${scidavis_PyQt_SRC}
    PROPERTIES
    GENERATED ON
    )

  if( SIP_VERSION VERSION_GREATER_EQUAL 5 )
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    add_custom_command(
      OUTPUT ${scidavis_PyQt_HDR} ${scidavis_PyQt_SRC} ${scidavis_SIP_HDR}
      COMMAND ${SIP_EXECUTABLE} --no-make --qmake=${_qmake_executable}
        --include-dir=${PyQt_INCLUDE_DIRS}
        --build-dir=${CMAKE_CURRENT_BINARY_DIR}/python
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/scripting/scidavis.sip
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/scripting
      )
  else()
    add_custom_command(
      OUTPUT ${scidavis_PyQt_HDR} ${scidavis_PyQt_SRC}
      COMMAND ${SIP_EXECUTABLE} -c . -I${PyQt_INCLUDE_DIRS} ${PyQt_FLAGS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scripting/scidavis.sip
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/scripting/scidavis.sip
      )
  endif()

  if( SIP_VERSION VERSION_GREATER_EQUAL 5 )
    add_custom_target(generate_PyQt_source
      DEPENDS ${scidavis_PyQt_HDR} ${scidavis_PyQt_SRC} ${scidavis_SIP_HDR}
      )
  else()
    add_custom_target(generate_PyQt_source
      DEPENDS ${scidavis_PyQt_HDR} ${scidavis_PyQt_SRC}
      )
  endif()

  target_sources( libscidavis PRIVATE
    "src/scripting/PythonScript.h"
    "src/scripting/PythonScripting.h"
    ${scidavis_PyQt_HDR}
    "src/scripting/PythonScript.cpp"
    "src/scripting/PythonScripting.cpp"
    ${scidavis_PyQt_SRC}
    )

  add_dependencies(libscidavis generate_PyQt_source)

endif()
