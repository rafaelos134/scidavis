# old icon name -> Tabler outline icon, or None for a custom SVG drawn in the same style
TABLER = {
 '3dplots':'cube-3d-sphere','area':'chart-area','arrangeLayers':'layout-board-split','arrow':'arrow-up-right',
 'auto_layout':'layout-dashboard','box':'box','clock':'clock','close':'trash','col_stat':'table-column',
 'config_curves':'chart-line','configTable':'table-options','copy':'copy','cursors':'focus-centered',
 'cursor_16':'target','curves':'chart-line','cut':'cut','datetype.png':'calendar','duplicate':'copy-plus',
 'equals.png':'equal','erase':'eraser','exp':'superscript','fileopen':'folder-open','fileprint':'printer',
 'filesave':'device-floppy','fit_frame':'arrows-maximize','folder_closed':'folder','folder_open':'folder-open',
 'folder':'folder-search','fx':'math-function','general':'settings','gomme':'eraser','graph':'chart-line',
 'graph_disabled':'chart-line','hand':'hand-move','histogram':'chart-histogram','import':'file-import',
 'index':'subscript','layer_disabled':'square','layer_enabled':'square-check','legend':'list-details',
 'lock':'lock','log':'file-text','lPlot':'chart-line','matrix':'grid-dots','monalisa':'photo','movie':'movie',
 'mask':'eye-off','new_aspect':'file-plus','newfolder':'folder-plus','newF':'math-function',
 'newFxy':'math-function-y','new_graph':'presentation-analytics','newLayer':'stack-push','new_matrix':'grid-dots',
 'new_note':'note','new':'file','next':'arrow-right','note':'notes','numerictype.png':'number-123',
 'open_template':'template','palette':'palette','panel_4':'layout-grid','panel_h2':'layout-columns',
 'panel_v2':'layout-rows','stacked':'stack-2','paste':'clipboard','pdf':'file-type-pdf','perspective':'perspective',
 'pie':'chart-pie','pointer':'pointer','pPlot':'chart-scatter','prev':'arrow-left','quit':'logout',
 'randomNumbers':'dice-5','reset_rotation':'rotate-360','resize':'resize','rowNumbers':'list-numbers',
 'save_template':'file-download','scatter':'chart-scatter-3d','select':'crosshair','stat_rows':'table-row',
 'table':'table','texttype.png':'letter-case','text':'typography','unlock':'lock-open','unmask':'eye',
 'unzoom':'zoom-reset','vertBars':'chart-bar','wizard':'wand','worksheet':'table','zoomOut':'zoom-out',
 'zoom':'zoom-in','pixelProfile':'chart-ppf','isolines':'ripple',
 # icons previously loaded through IconLoader::load()
 'edit-copy':'copy','edit-cut':'cut','edit-paste':'clipboard','edit-undo':'arrow-back-up','edit-redo':'arrow-forward-up',
}
CUSTOM = ['backGrid','bars','plot_bars','bottom_scl','boxPlot','ceilGrid','color_map','cones','contour_map','crosses',
 'dropLines','fit','floorGrid','floor','free_axes','frontGrid','gray_map','grid_only','grid_poly','hBars','hor_steps',
 'leftGrid','left_scl','lineMesh','lineSymbol','lpPlot','no_axes','no_floor','no_grid','pointsMesh','ribbon',
 'rightGrid','right_scl','spline','stacked_hist','top_scl','trajectory','vectXYAM','vectXYXY','vert_steps','yerror']
# kept as bitmaps: mouse cursors and the axis illustrations of the axes dialog
KEEP = ['lens','cursor','vizor']

# table/matrix action icons (formerly :/16x16/*.png and :/32x32/*.png)
TABLER.update({
 'add_column':'column-insert-right','add_columns':'columns-3','add_rows':'row-insert-bottom','clear':'eraser',
 'clear_column':'eraser','clear_row':'eraser','clear_table':'clear-all','column_description':'file-description',
 'column_format_type':'adjustments-horizontal','formula_editor':'pencil','go_to_cell':'focus-2',
 'insert_column':'column-insert-left','insert_row':'row-insert-top','normalize':'arrows-vertical',
 'recalculate':'refresh','remove_column':'column-remove','remove_row':'row-remove','select_all':'select-all',
 'sort':'sort-ascending','table_header':'heading','table_options':'table-options','TeX':'tex',
})
CUSTOM += ['x_error', 'y_error', 'grid_horizontal', 'grid_vertical']
