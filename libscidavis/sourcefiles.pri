#############################################################################
###################### PROJECT FILES SECTION ################################
#############################################################################


###################### HEADERS ##############################################

HEADERS  += src/app/ApplicationWindow.h \
            src/app/IconLoader.h \
            src/app/globals.h\
            src/plot/Graph.h \
            src/plot/3d/Graph3D.h \
            src/project/Table.h \
            src/dialogs/CurvesDialog.h \
            src/dialogs/PlotDialog.h \
            src/dialogs/Plot3DDialog.h \
            src/dialogs/PlotWizard.h \
            src/dialogs/ExportDialog.h \
            src/dialogs/AxesDialog.h \
            src/dialogs/PolynomFitDialog.h \
            src/dialogs/ExpDecayDialog.h \
            src/dialogs/FunctionDialog.h \
            src/dialogs/FitDialog.h \
            src/dialogs/SurfaceDialog.h \
            src/dialogs/TextDialog.h \
            src/dialogs/LineDialog.h \
            src/plot/tools/ScalePicker.h \
            src/plot/tools/TitlePicker.h \
            src/plot/tools/CanvasPicker.h \
            src/plot/PlotCurve.h \
            src/plot/QwtErrorPlotCurve.h \
            src/plot/QwtPieCurve.h \
            src/dialogs/ErrDialog.h \
            src/plot/Legend.h \
            src/plot/ArrowMarker.h \
            src/plot/ImageMarker.h \
            src/dialogs/ImageDialog.h \
            src/analysis/fit/fit_gsl.h \
            src/plot/MultiLayer.h\
            src/dialogs/LayerDialog.h \
            src/dialogs/IntDialog.h \
            src/plot/3d/Bar.h \
            src/plot/3d/Cone3D.h \
            src/dialogs/ConfigDialog.h \
            src/plot/QwtBarCurve.h \
            src/plot/BoxCurve.h \
            src/plot/QwtHistogram.h \
            src/plot/VectorCurve.h \
            src/plot/ScaleDraw.h \
            src/project/Matrix.h \
            src/dialogs/DataSetDialog.h \
            src/scripting/MyParser.h \
            src/widgets/SymbolBox.h \
            src/widgets/PatternBox.h \
            src/dialogs/SymbolDialog.h \
            src/plot/Plot.h \
            src/widgets/ColorButton.h \
            src/dialogs/AssociationsDialog.h \
            src/dialogs/RenameWindowDialog.h \
            src/project/MyWidget.h \
            src/dialogs/InterpolationDialog.h\
            src/dialogs/ImportASCIIDialog.h \
            src/dialogs/ImageExportDialog.h\
            src/dialogs/SmoothCurveDialog.h\
            src/dialogs/FilterDialog.h\
            src/dialogs/FFTDialog.h\
            src/project/Note.h\
            src/project/Folder.h\
            src/dialogs/FindDialog.h\
            src/scripting/ScriptingEnv.h\
            src/scripting/Script.h\
            src/scripting/ScriptEdit.h\
            src/plot/FunctionCurve.h\
            src/analysis/fit/Fit.h\
            src/analysis/fit/MultiPeakFit.h\
            src/analysis/fit/ExponentialFit.h\
            src/analysis/fit/PolynomialFit.h\
            src/analysis/fit/NonLinearFit.h\
            src/analysis/fit/PluginFit.h\
            src/analysis/fit/SigmoidalFit.h\
            src/app/customevents.h\
            src/dialogs/ScriptingLangDialog.h\
            src/widgets/TextFormatButtons.h\
            src/project/TableStatistics.h\
            src/plot/Spectrogram.h\
            src/widgets/ColorMapEditor.h\
            src/plot/SelectionMoveResizer.h\
            src/analysis/Filter.h\
            src/analysis/Differentiation.h\
            src/analysis/Integration.h\
            src/analysis/Interpolation.h\
            src/analysis/SmoothFilter.h\
            src/analysis/FFTFilter.h\
            src/analysis/FFT.h\
            src/analysis/Convolution.h\
            src/analysis/Correlation.h\
            src/plot/tools/PlotToolInterface.h\
            src/plot/tools/ScreenPickerTool.h\
            src/plot/tools/DataPickerTool.h\
            src/plot/tools/RangeSelectorTool.h\
            src/plot/tools/TranslateCurveTool.h\
            src/plot/tools/MultiPeakFitTool.h\
            src/dialogs/CurveRangeDialog.h\
            src/plot/tools/LineProfileTool.h\
            src/plot/PlotEnrichement.h\
            src/dialogs/ExtensibleFileDialog.h\
            src/dialogs/OpenProjectDialog.h\
        src/plot/Grid.h\
            src/plot/tools/DataPointPicker.h \
            src/io/TeXTableSettings.h \
            src/widgets/TeXTableSettingsWidget.h \
            src/dialogs/TeXTableExportDialog.h \
            src/widgets/PenWidget.h \
            src/app/QStringStdString.h

###################### SOURCES ##############################################

SOURCES  += src/app/ApplicationWindow.cpp \
            src/app/IconLoader.cpp \
            src/plot/Graph.cpp \
            src/plot/3d/Graph3D.cpp \
            src/project/Table.cpp \
            src/dialogs/CurvesDialog.cpp \
            src/dialogs/PlotDialog.cpp \
            src/dialogs/Plot3DDialog.cpp \
            src/dialogs/PlotWizard.cpp \
            src/dialogs/ExportDialog.cpp \
            src/dialogs/AxesDialog.cpp \
            src/dialogs/PolynomFitDialog.cpp \
            src/dialogs/TextDialog.cpp \
            src/plot/tools/ScalePicker.cpp\
            src/plot/tools/TitlePicker.cpp \
            src/plot/tools/CanvasPicker.cpp \
            src/dialogs/ExpDecayDialog.cpp \
            src/dialogs/FunctionDialog.cpp \
            src/dialogs/FitDialog.cpp \
            src/dialogs/SurfaceDialog.cpp \
            src/dialogs/LineDialog.cpp \
            src/plot/PlotCurve.cpp \
            src/plot/QwtErrorPlotCurve.cpp \
            src/plot/QwtPieCurve.cpp \
            src/dialogs/ErrDialog.cpp \
            src/plot/Legend.cpp \
            src/plot/ArrowMarker.cpp \
            src/plot/ImageMarker.cpp \
            src/dialogs/ImageDialog.cpp \
            src/plot/MultiLayer.cpp\
            src/dialogs/LayerDialog.cpp \
            src/dialogs/IntDialog.cpp \
            src/plot/3d/Bar.cpp \
            src/plot/3d/Cone3D.cpp \
            src/dialogs/DataSetDialog.cpp \
            src/dialogs/ConfigDialog.cpp \
            src/plot/QwtBarCurve.cpp \
            src/plot/BoxCurve.cpp \
            src/plot/QwtHistogram.cpp \
            src/plot/VectorCurve.cpp \
            src/project/Matrix.cpp \
            src/scripting/MyParser.cpp\
            src/widgets/SymbolBox.cpp \
            src/widgets/PatternBox.cpp \
            src/dialogs/SymbolDialog.cpp \
            src/plot/Plot.cpp \
            src/widgets/ColorButton.cpp \
            src/dialogs/AssociationsDialog.cpp \
            src/dialogs/RenameWindowDialog.cpp \
            src/project/MyWidget.cpp\
            src/dialogs/InterpolationDialog.cpp\
            src/analysis/fit/fit_gsl.cpp\
            src/dialogs/SmoothCurveDialog.cpp\
            src/dialogs/FilterDialog.cpp\
            src/dialogs/FFTDialog.cpp\
            src/project/Note.cpp\
            src/project/Folder.cpp\
            src/dialogs/FindDialog.cpp\
            src/widgets/TextFormatButtons.cpp\
            src/scripting/ScriptEdit.cpp\
            src/dialogs/ImportASCIIDialog.cpp\
            src/dialogs/ImageExportDialog.cpp\
            src/plot/ScaleDraw.cpp\
            src/plot/FunctionCurve.cpp\
            src/analysis/fit/Fit.cpp\
            src/analysis/fit/MultiPeakFit.cpp\
            src/analysis/fit/ExponentialFit.cpp\
            src/analysis/fit/PolynomialFit.cpp\
            src/analysis/fit/PluginFit.cpp\
            src/analysis/fit/NonLinearFit.cpp\
            src/analysis/fit/SigmoidalFit.cpp\
            src/scripting/ScriptingEnv.cpp\
            src/scripting/Script.cpp\
            src/dialogs/ScriptingLangDialog.cpp\
            src/project/TableStatistics.cpp\
            src/plot/Spectrogram.cpp\
            src/widgets/ColorMapEditor.cpp\
            src/plot/SelectionMoveResizer.cpp\
            src/analysis/Filter.cpp\
            src/analysis/Differentiation.cpp\
            src/analysis/Integration.cpp\
            src/analysis/Interpolation.cpp\
            src/analysis/SmoothFilter.cpp\
            src/analysis/FFTFilter.cpp\
            src/analysis/FFT.cpp\
            src/analysis/Convolution.cpp\
            src/analysis/Correlation.cpp\
            src/plot/tools/ScreenPickerTool.cpp\
            src/plot/tools/DataPickerTool.cpp\
            src/plot/tools/RangeSelectorTool.cpp\
            src/plot/tools/TranslateCurveTool.cpp\
            src/plot/tools/MultiPeakFitTool.cpp\
            src/dialogs/CurveRangeDialog.cpp\
            src/plot/tools/LineProfileTool.cpp\
            src/plot/PlotEnrichement.cpp\
            src/dialogs/ExtensibleFileDialog.cpp\
            src/dialogs/OpenProjectDialog.cpp\
            src/plot/Grid.cpp\
            src/app/globals.cpp \
            src/plot/tools/DataPointPicker.cpp \
            src/io/TeXTableSettings.cpp \
            src/widgets/TeXTableSettingsWidget.cpp \
            src/dialogs/TeXTableExportDialog.cpp \
            src/app/version.cpp \
            src/widgets/PenWidget.cpp

###################### FORMS ##############################################
FORMS +=   src/app/SciDAVisAbout.ui

########### Future code backported from the aspect framework ##################
DEFINES += LEGACY_CODE_0_2_x
INCLUDEPATH  += src
INCLUDEPATH  += src/app
INCLUDEPATH  += src/project
INCLUDEPATH  += src/io
INCLUDEPATH  += src/analysis
INCLUDEPATH  += src/analysis/fit
INCLUDEPATH  += src/plot
INCLUDEPATH  += src/plot/3d
INCLUDEPATH  += src/plot/tools
INCLUDEPATH  += src/scripting
INCLUDEPATH  += src/dialogs
INCLUDEPATH  += src/widgets
INCLUDEPATH  += src/future

FORMS += src/future/matrix/matrixcontroltabs.ui \
         src/future/core/ProjectConfigPage.ui \
		 src/future/table/controltabs.ui \
		 src/future/table/DimensionsDialog.ui

HEADERS += src/future/core/AbstractAspect.h \
           src/future/core/AbstractPart.h \
           src/future/core/AspectPrivate.h \
           src/future/core/aspectcommands.h \
           src/future/core/future_Folder.h \
           src/future/core/Project.h \
           src/future/core/ProjectConfigPage.h \
           src/future/core/PartMdiView.h \
           src/future/core/AbstractColumn.h \
           src/future/core/column/Column.h \
           src/future/core/column/ColumnPrivate.h \
           src/future/core/column/columncommands.h \
           src/future/core/AbstractFilter.h \
           src/future/core/AbstractSimpleFilter.h \
           src/future/core/datatypes/SimpleCopyThroughFilter.h \
           src/future/core/datatypes/DateTime2DoubleFilter.h \
           src/future/core/datatypes/DateTime2StringFilter.h \
           src/future/core/datatypes/DayOfWeek2DoubleFilter.h \
           src/future/core/datatypes/Double2DateTimeFilter.h \
           src/future/core/datatypes/NumericDateTimeBaseFilter.h \
           src/future/core/datatypes/Double2DayOfWeekFilter.h \
           src/future/core/datatypes/Double2MonthFilter.h \
           src/future/core/datatypes/Double2StringFilter.h \
           src/future/core/datatypes/Month2DoubleFilter.h \
           src/future/core/datatypes/String2DateTimeFilter.h \
           src/future/core/datatypes/String2DayOfWeekFilter.h \
           src/future/core/datatypes/String2DoubleFilter.h \
           src/future/core/datatypes/String2MonthFilter.h \
           src/future/lib/macros.h \
           src/future/lib/XmlStreamReader.h \
           src/future/lib/ActionManager.h \
           src/future/lib/ConfigPageWidget.h \
           src/future/lib/Interval.h \
           src/future/lib/IntervalAttribute.h \
           src/future/matrix/future_Matrix.h \
           src/future/matrix/MatrixModel.h \
           src/future/matrix/MatrixView.h \
           src/future/matrix/matrixcommands.h \
           src/future/table/future_Table.h \
           src/future/table/TableModel.h \
           src/future/table/TableView.h \
           src/future/table/tablecommands.h \
           src/future/table/TableDoubleHeaderView.h \
           src/future/table/TableItemDelegate.h \
           src/future/table/TableCommentsHeaderModel.h \
           src/future/table/future_SortDialog.h \
           src/future/table/AsciiTableImportFilter.h \
           src/future/core/AbstractImportFilter.h \
           src/future/core/interfaces.h \

SOURCES += src/future/core/AbstractAspect.cpp \
           src/future/core/AbstractPart.cpp \
           src/future/core/AspectPrivate.cpp \
           src/future/core/future_Folder.cpp \
           src/future/core/PartMdiView.cpp \
           src/future/core/Project.cpp \
           src/future/core/column/Column.cpp \
           src/future/core/column/ColumnPrivate.cpp \
           src/future/core/column/columncommands.cpp \
           src/future/core/datatypes/DateTime2StringFilter.cpp \
           src/future/core/datatypes/String2DateTimeFilter.cpp \
           src/future/core/datatypes/Double2StringFilter.cpp \
           src/future/core/datatypes/NumericDateTimeBaseFilter.cpp \
           src/future/core/AbstractSimpleFilter.cpp \
           src/future/core/AbstractFilter.cpp \
           src/future/core/ProjectConfigPage.cpp \
           src/future/lib/XmlStreamReader.cpp \
           src/future/lib/ActionManager.cpp \
           src/future/lib/ConfigPageWidget.cpp \
           src/future/matrix/future_Matrix.cpp \
           src/future/matrix/MatrixModel.cpp \
           src/future/matrix/MatrixView.cpp \
           src/future/matrix/matrixcommands.cpp \
           src/future/table/future_Table.cpp \
           src/future/table/TableModel.cpp \
           src/future/table/TableView.cpp \
           src/future/table/tablecommands.cpp \
           src/future/table/TableDoubleHeaderView.cpp \
           src/future/table/TableItemDelegate.cpp \
           src/future/table/TableCommentsHeaderModel.cpp \
           src/future/table/future_SortDialog.cpp \
           src/future/table/AsciiTableImportFilter.cpp \

###############################################################
##################### Compression #############################
############### (mini gzip implementation) ####################
################# requires zlib >= 1.2.3 ######################
###############################################################

SOURCES += ../3rdparty/minigzip/minigzip.c

###############################################################
#### Origin OPJ import via liborigin
###############################################################
liborigin {
	HEADERS += src/io/importOPJ.h
	SOURCES += src/io/importOPJ.cpp
}
