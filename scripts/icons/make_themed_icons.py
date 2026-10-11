"""Write SciDAVis' themed icon set (scidavis/icons/themed).

Usage: make_themed_icons.py <tabler-icons outline dir> <output dir>
  e.g. download https://registry.npmjs.org/@tabler/icons/-/icons-3.49.0.tgz, extract it and run
  scripts/icons/make_themed_icons.py package/icons/outline scidavis/icons/themed
Afterwards regenerate scidavis/themedicons.qrc if icons were added or removed.


Tabler icons (MIT) are copied under SciDAVis' historical icon names; the scientific icons
Tabler lacks are drawn here in the same style (24x24 grid, 2px round strokes in
currentColor). "#ACCENT" is replaced by the palette highlight color at run time.
"""
import os
import re
import shutil
import sys

here = os.path.dirname(os.path.abspath(__file__))
exec(open(os.path.join(here, 'icon_mapping.py')).read())
tabler = sys.argv[1]
out = sys.argv[2]
os.makedirs(out, exist_ok=True)

HEAD = ('<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" '
        'fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" '
        'stroke-linejoin="round">\n')


def svg(name, body):
    with open(os.path.join(out, name + '.svg'), 'w') as f:
        f.write(HEAD + body.strip() + '\n</svg>\n')


def shade(d, opacity=.3, color='currentColor'):
    return f'<path d="{d}" fill="{color}" fill-opacity="{opacity}" stroke="none"/>'


def dot(x, y, r=1.1):
    return f'<circle cx="{x}" cy="{y}" r="{r}" fill="currentColor" stroke="none"/>'


AXES = '<path d="M4 4v16h16"/>'

# ---- 2D plot types -----------------------------------------------------------------------
svg('hBars', '<path d="M4 4v16"/><rect x="4" y="6" width="9" height="3" rx="1"/>'
             '<rect x="4" y="11" width="15" height="3" rx="1"/><rect x="4" y="16" width="11" height="3" rx="1"/>')
svg('stacked_hist', '<path d="M3 20h18"/>'
    + shade('M5 15h4v5h-4z', .35) + shade('M10 12h4v8h-4z', .35) + shade('M15 14h4v6h-4z', .35)
    + '<rect x="5" y="11" width="4" height="9"/><path d="M5 15h4"/>'
      '<rect x="10" y="5" width="4" height="15"/><path d="M10 12h4"/>'
      '<rect x="15" y="9" width="4" height="11"/><path d="M15 14h4"/>')
svg('boxPlot', '<path d="M8 3v4M8 15v4M6.5 3h3M6.5 19h3"/><rect x="5.5" y="7" width="5" height="8" rx="1"/>'
               '<path d="M5.5 11h5"/><path d="M16 6v4M16 15v3M14.5 6h3M14.5 18h3"/>'
               '<rect x="13.5" y="10" width="5" height="5" rx="1"/><path d="M13.5 12.5h5"/>')
ARROWS = ('<path d="M4 12l5 -5M9 7h-3.5M9 7v3.5"/><path d="M13 20l6 -6M19 14h-3.5M19 14v3.5"/>'
          '<path d="M12 9h8M20 9l-3 -3M20 9l-3 3"/><path d="M6 21v-6M6 15l-2.5 2.5M6 15l2.5 2.5"/>')
svg('vectXYXY', ARROWS)
svg('vectXYAM', ARROWS + dot(4, 12) + dot(13, 20) + dot(12, 9) + dot(6, 21))
svg('vert_steps', AXES + '<path d="M7 17v-4h4v-4h4v-4h4"/>')
svg('hor_steps', AXES + '<path d="M7 17h4v-4h4v-4h4v-3"/>')
svg('spline', AXES + '<path d="M6 17c2.5 0 2.5 -10 5.5 -10s3 7 7.5 5"/>')
svg('yerror', '<path d="M3 21h18"/><path d="M7 5v8M5.5 5h3M5.5 13h3"/><path d="M12 10v8M10.5 10h3M10.5 18h3"/>'
              '<path d="M17 4v7M15.5 4h3M15.5 11h3"/>' + dot(7, 9, 1.6) + dot(12, 14, 1.6) + dot(17, 7.5, 1.6))
svg('y_error', open(os.path.join(out, 'yerror.svg')).read().split('\n', 1)[1].rsplit('</svg>', 1)[0])
svg('x_error', '<path d="M3 3v18"/><path d="M5 7h8M5 5.5v3M13 5.5v3"/><path d="M10 12h8M10 10.5v3M18 10.5v3"/>'
               '<path d="M4 17h7M4 15.5v3M11 15.5v3"/>' + dot(9, 7, 1.6) + dot(14, 12, 1.6) + dot(7.5, 17, 1.6))
svg('dropLines', AXES + '<path d="M8 11v9M13 7.5v12.5M17 13v7" stroke-dasharray="2 2.5"/>'
    + '<circle cx="8" cy="9.5" r="1.5"/><circle cx="13" cy="6" r="1.5"/><circle cx="17" cy="11.5" r="1.5"/>')
svg('fit', '<path d="M4 19c4 -8 8 -11 16 -13" stroke="#ACCENT"/>'
    + dot(5, 15.5) + dot(7.5, 15) + dot(9, 11) + dot(11.5, 11.5) + dot(13.5, 8.5) + dot(16, 9) + dot(18.5, 5.5))
LINESYMBOL = ('<path d="M5.4 15.3l2.2 -2.6M10.4 11.2l1.3 1M15.3 12.5l3.4 -4"/>'
              '<circle cx="4" cy="17" r="1.8"/><circle cx="9" cy="11" r="1.8"/>'
              '<circle cx="13" cy="14" r="1.8"/><circle cx="20" cy="6.5" r="1.8"/>')
svg('lpPlot', LINESYMBOL)
svg('lineSymbol', LINESYMBOL)

# ---- 3D plots ----------------------------------------------------------------------------
BARS3D = ('<path d="M4 10h4v9h-4z"/><path d="M4 10l2 -2h4l-2 2"/><path d="M8 10l2 -2v9l-2 2"/>'
          '<path d="M10 5h4v14h-4z"/><path d="M10 5l2 -2h4l-2 2"/><path d="M14 5l2 -2v14l-2 2"/>'
          '<path d="M16 12h4v7h-4z"/><path d="M16 12l2 -2h4l-2 2"/><path d="M20 12l2 -2v7l-2 2"/>')
svg('bars', BARS3D)
svg('plot_bars', BARS3D)
svg('cones', '<path d="M3 18l3.5 -12l3.5 12"/><ellipse cx="6.5" cy="18" rx="3.5" ry="1.4"/>'
             '<path d="M13 16l3.5 -12l3.5 12"/><ellipse cx="16.5" cy="16" rx="3.5" ry="1.4"/>')
FLOOR = '<path d="M2 17l8 4l12 -5"/>'
svg('crosses', FLOOR + ''.join(f'<path d="M{x-1.5} {y-1.5}l3 3M{x+1.5} {y-1.5}l-3 3"/>'
                                for x, y in ((6, 10), (13, 5), (18, 11), (10, 15))))
svg('pointsMesh', ''.join(dot(x, y, 1) for y, xs in ((6, (9, 13, 17)), (10, (6.5, 11, 15.5, 20)),
                                                   (14, (4, 9, 14, 19)), (18, (6.5, 11.5, 16.5)))
                          for x in xs))
ROWS = ('<path d="M6 6c4 2 9 -2 14 2"/><path d="M4.5 10.5c4 2 9 -2 14.5 2.5"/>'
        '<path d="M3 15c4 2 9 -2 15 3"/>')
COLS = ('<path d="M6 6c-1 3 -2 6 -3 9"/><path d="M10.7 6.4c-.6 3 -1.4 6.2 -2 9.5"/>'
        '<path d="M15.3 6.3c-.2 3.2 -.7 6.4 -1.2 10"/><path d="M20 8c-.5 3.3 -1 6.8 -2 10"/>')
svg('grid_only', ROWS + COLS)
svg('grid_poly', shade('M6 6c4 2 9 -2 14 2c-.5 3.3 -1 6.8 -2 10c-6 -5 -11 -1 -15 -3c1 -3 2 -6 3 -9z', .3, '#ACCENT')
    + ROWS + COLS)
svg('lineMesh', ROWS + '<path d="M5.3 8.2c4 2 9 -2 14.3 2.3"/><path d="M3.8 12.8c4 2 9 -2 14.8 2.7"/>')
svg('ribbon', '<path d="M3 6c3 -3 6 3 9 0s6 -3 9 0"/><path d="M3 9c3 -3 6 3 9 0s6 -3 9 0"/><path d="M3 6v3M21 6v3"/>'
              '<path d="M3 15c3 -3 6 3 9 0s6 -3 9 0"/><path d="M3 18c3 -3 6 3 9 0s6 -3 9 0"/><path d="M3 15v3M21 15v3"/>')
svg('trajectory', '<path d="M12 3c4 0 6 1.5 6 3s-2.5 3 -6 3s-6 1.5 -6 3s2.5 3 6 3s6 1.5 6 3s-2.5 3 -6 3"/>'
    + dot(12, 21, 1.4))

# ---- maps --------------------------------------------------------------------------------
FRAME = '<rect x="3" y="3" width="18" height="18" rx="2"/>'
svg('contour_map', FRAME + '<path d="M7 12c0 -3.5 3.5 -5.5 7 -4.5s4.5 4.5 2.5 6.5s-9.5 2 -9.5 -2z"/>'
                           '<path d="M10.5 12c0 -1.5 1.7 -2.5 3.3 -2s2 2 1 3s-4.3 1 -4.3 -1z"/>')
CELLS = [(.15, .35, .6), (.35, .6, .85), (.6, .85, .35)]


def cells(color):
    body = ''
    for row, opacities in enumerate(CELLS):
        for col, opacity in enumerate(opacities):
            body += f'<rect x="{4 + col * 5.5}" y="{4 + row * 5.5}" width="5" height="5" fill="{color}" ' \
                    f'fill-opacity="{opacity}" stroke="none"/>'
    return body


svg('color_map', cells('#ACCENT') + FRAME)
svg('gray_map', cells('currentColor') + FRAME)

# ---- 3D frame, grids and axes ------------------------------------------------------------
CUBE = '<path d="M5 9h10v10h-10z"/><path d="M9 5h10v10"/><path d="M5 9l4 -4M15 9l4 -4M15 19l4 -4"/>'
HIDDEN = '<path d="M9 5v10h10M9 15l-4 4" stroke-dasharray="1.5 2"/>'
FACES = {
    'floorGrid': ((5, 19), (15, 19), (19, 15), (9, 15)),
    'ceilGrid': ((5, 9), (15, 9), (19, 5), (9, 5)),
    'leftGrid': ((5, 9), (9, 5), (9, 15), (5, 19)),
    'rightGrid': ((15, 9), (19, 5), (19, 15), (15, 19)),
    'frontGrid': ((5, 9), (15, 9), (15, 19), (5, 19)),
    'backGrid': ((9, 5), (19, 5), (19, 15), (9, 15)),
}


def lerp(p, q, t):
    return (round(p[0] + (q[0] - p[0]) * t, 2), round(p[1] + (q[1] - p[1]) * t, 2))


def face(quad, opacity=.3, grid=True):
    p0, p1, p2, p3 = quad
    body = shade('M{} {}L{} {}L{} {}L{} {}z'.format(*p0, *p1, *p2, *p3), opacity, '#ACCENT')
    if grid:
        for t in (1 / 3, 2 / 3):
            a, b = lerp(p0, p1, t), lerp(p3, p2, t)
            c, d = lerp(p0, p3, t), lerp(p1, p2, t)
            body += f'<path d="M{a[0]} {a[1]}L{b[0]} {b[1]}M{c[0]} {c[1]}L{d[0]} {d[1]}" stroke-width="1"/>'
    return body


for name, quad in FACES.items():
    svg(name, (HIDDEN if name == 'backGrid' else '') + face(quad) + CUBE)
svg('no_grid', HIDDEN + CUBE)
svg('floor', face(FACES['floorGrid'], .3, False) + CUBE
    + '<path d="M7 17.5c2 -1.5 4 .5 6 -1s3 -.5 4 -1" stroke-width="1.5"/>')
svg('no_floor', CUBE + '<path d="M5 19l4 -4h10" stroke-dasharray="1.5 2"/>')
svg('free_axes', '<path d="M8 15v-12M8 3l-2 2.5M8 3l2 2.5"/><path d="M8 15h13M21 15l-2.5 -2M21 15l-2.5 2"/>'
                 '<path d="M8 15l-5 5M3 20h3M3 20v-3"/>')
svg('no_axes', '<path d="M5 9h10v10h-10zM9 5h10v10M5 9l4 -4M15 9l4 -4M15 19l4 -4" stroke-dasharray="1.5 2"/>')

# ---- axis (scale) position ---------------------------------------------------------------
SCALE_FRAME = '<rect x="5" y="5" width="14" height="14" rx="1.5" stroke-width="1.5" stroke-dasharray="1.5 2"/>'
SIDES = {
    'bottom_scl': '<path d="M5 19h14M8 19v-3M12 19v-3M16 19v-3"/>',
    'top_scl': '<path d="M5 5h14M8 5v3M12 5v3M16 5v3"/>',
    'left_scl': '<path d="M5 5v14M5 8h3M5 12h3M5 16h3"/>',
    'right_scl': '<path d="M19 5v14M19 8h-3M19 12h-3M19 16h-3"/>',
}
for name, body in SIDES.items():
    svg(name, SCALE_FRAME + body)

# ---- grid direction (axes dialog) ---------------------------------------------------------
svg('grid_horizontal', FRAME + '<path d="M3 9h18M3 15h18" stroke-width="1.5"/>')
svg('grid_vertical', FRAME + '<path d="M9 3v18M15 3v18" stroke-width="1.5"/>')

missing = [n for n in CUSTOM if not os.path.exists(os.path.join(out, n + '.svg'))]
assert not missing, missing

# ---- Tabler icons ------------------------------------------------------------------------
for name, src in TABLER.items():
    text = open(os.path.join(tabler, src + '.svg')).read()
    text = re.sub(r'\s*class="[^"]*"', '', text)           # drop Tabler's CSS classes
    text = re.sub(r'<path stroke="none" d="M0 0h24v24H0z" fill="none" />\s*', '', text)
    with open(os.path.join(out, name.replace('.png', '') + '.svg'), 'w') as f:
        f.write(text)
shutil.copy(os.path.join(tabler, '..', '..', 'LICENSE'), os.path.join(out, 'LICENSE-tabler-icons.txt'))
print(len(TABLER) + len(CUSTOM), 'icons written to', out)
