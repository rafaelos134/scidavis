# SciDAVis

**SciDAVis** (*Sci*entific *D*ata *A*nalysis and *Vis*ualization) é um aplicativo
livre (GPL v2+) para análise e visualização de dados científicos, escrito em
C++20 com Qt 6 (6.8 LTS). Roda em Linux, Windows e macOS.

- Manual do usuário: <https://highperformancecoder.github.io/scidavis-handbook/>
- Site: <http://scidavis.sourceforge.net>
- Compilação e instalação: [INSTALL.md](INSTALL.md)
- Licença, créditos e política de versões: [CREDITS.md](CREDITS.md) · [gpl.txt](gpl.txt)
- Histórico de mudanças: [ChangeLog.md](ChangeLog.md)

---

## Sumário

1. [Funcionalidades](#1-funcionalidades)
2. [Estrutura do repositório](#2-estrutura-do-repositório)
3. [Organização do código-fonte (`libscidavis/src`)](#3-organização-do-código-fonte-libscidavissrc)
4. [Onde estão os cálculos](#4-onde-estão-os-cálculos)
5. [Arquitetura em uma página](#5-arquitetura-em-uma-página)
6. [Compilando e testando](#6-compilando-e-testando)
7. [Como contribuir](#7-como-contribuir)

---

## 1. Funcionalidades

| Funcionalidade | O que faz | Onde fica (pasta em `libscidavis/src/`) |
|---|---|---|
| **Tabelas** | Planilhas com colunas numéricas, texto, data/hora, mês e dia da semana; fórmulas por coluna ("Set Column Values"); ordenação; estatísticas | `project/Table.*`, `future/table/`, `future/core/column/` |
| **Matrizes** | Dados 2D (z = f(x, y)) com fórmulas; base para gráficos 3D e espectrogramas | `project/Matrix.*`, `future/matrix/` |
| **Gráficos 2D** | Linhas, pontos, barras, histogramas, pizza, box-plot, vetores, barras de erro, espectrogramas, curvas de função; múltiplas camadas por janela | `plot/` |
| **Gráficos 3D** | Superfícies, barras 3D, cones, dispersão 3D (via QwtPlot3D/OpenGL) | `plot/3d/` |
| **Ferramentas interativas** | Leitura de pontos, seleção de intervalo, mover curvas, perfil de linha, ajuste de múltiplos picos com o mouse | `plot/tools/` |
| **Ajuste de curvas (fit)** | Linear, polinomial, exponencial (1, 2 e 3 termos), sigmoidal (Boltzmann), Gauss, Lorentz, multi-picos, função definida pelo usuário e plugins | `analysis/fit/` |
| **Análise numérica** | Derivada, integral, interpolação, suavização, FFT, filtros FFT, convolução/deconvolução, correlação | `analysis/` |
| **Estatística** | Estatísticas de linhas/colunas (média, desvio-padrão, variância, soma, min/max) | `project/TableStatistics.*` |
| **Scripting** | Fórmulas com muParser; scripts Python (SIP/PyQt) ainda não disponíveis no Qt 6 | `scripting/` |
| **Notas** | Janelas de texto/script dentro do projeto | `project/Note.*` |
| **Importar/Exportar** | ASCII/CSV, projetos do Origin (`.opj`), tabelas em LaTeX, exportação de imagens (PNG, SVG, PDF, EPS…) | `io/`, `dialogs/ImportASCIIDialog.*`, `dialogs/ImageExportDialog.*` |
| **Projetos** | Arquivo `.sciprj` com pastas, tabelas, matrizes, gráficos e notas | `app/ApplicationWindow.*`, `project/Folder.*`, `future/core/Project.*` |

---

## 2. Estrutura do repositório

```
scidavis/
├── CMakeLists.txt          # Build (CMake) — único suportado
├── scidavis.pro, config.pri# Build legado (qmake, Qt 5) — NÃO funciona mais, só histórico
├── libscidavis/            # >>> Biblioteca com TODA a lógica do programa <<<
│   ├── CMakeLists.txt      #   lista de fontes para o CMake
│   ├── sourcefiles.pri     #   lista de fontes do qmake legado
│   ├── python.pri          #   bindings Python (qmake legado)
│   └── src/                #   código-fonte (ver seção 3)
├── scidavis/               # Executável: main.cpp, ícones, traduções, .desktop, scidavisrc.py
│   ├── src/main.cpp        #   ponto de entrada
│   ├── icons/              #   ícones (.qrc)
│   └── translations/       #   arquivos .ts do Qt Linguist
├── fitPlugins/             # Exemplos de plugins de ajuste (bibliotecas carregadas em tempo de execução)
├── test/                   # Testes unitários (GoogleTest) e projetos de exemplo
├── 3rdparty/               # Bibliotecas externas
│   ├── qwt5/               #   Qwt 5.2 portada para Qt 6 (código incluído no repositório)
│   ├── qwtplot3d/          #   gráficos 3D (submódulo git)
│   ├── liborigin/          #   leitura de projetos do Origin (submódulo git)
│   └── minigzip/           #   compressão de arquivos .sciprj.gz
├── cmake/                  # Módulos CMake (FindSIP, FindPyQt, Windeployqt)
├── manual/                 # Manual em LaTeX
├── doc/                    # Extras de documentação
├── scripts/                # Scripts de desenvolvimento (release, traduções, cobertura, hook de commit)
├── packaging/              # Empacotamento (MSI Windows, bundle macOS, MacPorts, MXE)
│   └── legacy-win32/       #   build antigo Win32/Qt4 (histórico, não usado pelo CI)
├── obsCheck/               # Dockerfiles para testar pacotes do openSUSE Build Service
├── screenshots/            # Capturas de tela
├── .github/workflows/      # CI (Ubuntu, MSVC, MinGW, macOS) e empacotamento
├── Doxyfile, Doxyprogrammers # Geração de documentação da API (doxygen)
└── _clang-format           # Estilo de código (aplique com clang-format -i)
```

---

## 3. Organização do código-fonte (`libscidavis/src`)

Os arquivos estão agrupados por responsabilidade. **Todas as pastas abaixo estão
no include path** do CMake, então os `#include` usam apenas o nome do
arquivo — ex.: `#include "Graph.h"` — independentemente da pasta.

```
libscidavis/src/
├── app/            Janela principal e infraestrutura
├── project/        Objetos do projeto (janelas filhas)
├── analysis/       Operações numéricas sobre curvas
│   └── fit/        Ajuste de curvas (regressão)
├── plot/           Gráficos 2D: camadas, curvas, eixos, legendas
│   ├── 3d/         Gráficos 3D
│   └── tools/      Ferramentas interativas do mouse
├── scripting/      muParser, Python, editor de scripts, bindings SIP
├── dialogs/        Caixas de diálogo
├── widgets/        Componentes visuais reutilizáveis
├── io/             Importação/exportação de formatos externos
└── future/         Framework "aspect" (nova camada de dados, ver abaixo)
    ├── core/       AbstractAspect, Project, Column, filtros de tipo de dado
    ├── table/      Modelo/visão da tabela (MVC)
    ├── matrix/     Modelo/visão da matriz (MVC)
    └── lib/        Utilitários (Interval, XmlStreamReader, ActionManager)
```

### `app/` — aplicação

| Arquivo | Responsabilidade |
|---|---|
| `ApplicationWindow.*` | Janela principal (MDI): menus, barras de ferramentas, abrir/salvar `.sciprj`, criação de tabelas/gráficos, ligação entre todos os módulos. É o maior arquivo do projeto (~13,7 mil linhas). |
| `globals.*`, `version.cpp` | Número de versão, diálogo "Sobre" (`SciDAVisAbout.ui`). `version.cpp` é reescrito por `scripts/makeRelease.sh`. |
| `IconLoader.*` | Carrega ícones claros ou escuros conforme a luminosidade do tema. |
| `customevents.h`, `SciDAVisObject.h`, `QStringStdString.h` | Eventos Qt próprios, classe-base para objetos scriptáveis, conversões de string. |

### `project/` — objetos que aparecem na árvore do projeto

| Arquivo | Responsabilidade |
|---|---|
| `MyWidget.*` | Classe-base de toda sub-janela (Table, Matrix, MultiLayer, Note, Graph3D). |
| `Folder.*` | Pastas do projeto (árvore do "Project Explorer"). |
| `Table.*` | Janela de tabela; delega os dados para `future/table/future_Table`. |
| `Matrix.*` | Janela de matriz; delega para `future/matrix/future_Matrix`. |
| `TableStatistics.*` | Tabela derivada com estatísticas de linhas/colunas. |
| `Note.*` | Janela de notas/scripts. |

### `plot/` — gráficos 2D (baseados em Qwt 5)

| Arquivo | Responsabilidade |
|---|---|
| `MultiLayer.*` | Janela de gráfico; contém uma ou mais camadas (`Graph`). |
| `Graph.*` | Uma camada de gráfico: curvas, eixos, escalas, marcadores, exportação. |
| `Plot.*` | Subclasse de `QwtPlot` usada por `Graph`. |
| `PlotCurve.*` | Classe-base das curvas ligadas a colunas de tabela. |
| `QwtBarCurve`, `QwtHistogram`, `QwtPieCurve`, `BoxCurve`, `VectorCurve`, `QwtErrorPlotCurve`, `FunctionCurve`, `Spectrogram` | Tipos específicos de curva. |
| `ScaleDraw.*`, `Grid.*`, `Legend.*` | Eixos/rótulos de escala, grade e legenda. |
| `ArrowMarker.*`, `ImageMarker.*`, `PlotEnrichement.*` | Setas, imagens e anotações sobre o gráfico. |
| `SelectionMoveResizer.*` | Mover/redimensionar elementos selecionados. |
| `3d/Graph3D.*`, `3d/Bar.*`, `3d/Cone3D.*` | Gráficos 3D (QwtPlot3D + OpenGL). |
| `tools/*` | `DataPickerTool`, `RangeSelectorTool`, `TranslateCurveTool`, `MultiPeakFitTool`, `LineProfileTool`, `ScreenPickerTool` (todos implementam `PlotToolInterface`) e os "pickers" de canvas/escala/título. |

### `scripting/`

| Arquivo | Responsabilidade |
|---|---|
| `ScriptingEnv.*`, `Script.*` | Interface abstrata de linguagem de script. |
| `MuParserScripting.*`, `MuParserScript.*` | Avaliador de fórmulas muParser; tabela de funções embutidas (`math_functions[]`) e funções `col()`, `cell()` etc. |
| `PythonScripting.*`, `PythonScript.*` | Interpretador Python embutido (opcional; ainda não portado para Qt 6, ver seção 6). |
| `scidavis.sip`, `project.py`, `pyproject.toml` | Definição dos bindings Python gerados pelo SIP. |
| `MyParser.*` | Avaliador muParser simples usado em diálogos (ex.: limites de função). |
| `ScriptEdit.*` | Editor de texto usado em notas e no "Set Column Values". |

### `dialogs/` e `widgets/`

`dialogs/` contém todas as caixas de diálogo (`*Dialog`, `PlotWizard`,
`ExtensibleFileDialog`). Os nomes indicam a função: `FitDialog` (assistente de
ajuste), `AxesDialog`, `PlotDialog`, `ConfigDialog` (preferências),
`ImportASCIIDialog`, `FFTDialog`, `IntDialog` (integração), etc.

`widgets/` contém componentes reutilizados pelos diálogos: `ColorButton`,
`ColorBox`, `PatternBox`, `SymbolBox`, `PenWidget`, `ColorMapEditor`,
`TextFormatButtons`, `TeXTableSettingsWidget`.

### `io/`

| Arquivo | Responsabilidade |
|---|---|
| `importOPJ.*` | Importa projetos do Origin (`.opj`) usando `liborigin` (`-DORIGIN_IMPORT=ON`). |
| `TeXTableSettings.*` | Opções de exportação de tabela em LaTeX. |

A importação ASCII em si fica em `future/table/AsciiTableImportFilter.*`.

### `future/` — framework de dados ("aspects")

Camada mais nova, em estilo MVC, que guarda os dados de verdade:
`AbstractAspect` é a base de tudo que fica na árvore do projeto (com undo/redo
via `QUndoStack`); `Column` guarda os valores de uma coluna; os filtros em
`core/datatypes/` convertem entre tipos (texto ↔ número ↔ data). `Table` e
`Matrix` em `project/` são "cascas" de compatibilidade (macro
`LEGACY_CODE_0_2_x`) que encapsulam `future_Table` e `future_Matrix`.

---

## 4. Onde estão os cálculos

Quase toda a matemática usa a **GNU Scientific Library (GSL)**. Todas as
operações sobre curvas herdam de `Filter` (`analysis/Filter.*`), que lê os
pontos da curva/colunas, chama o método virtual `calculateOutputData()` e
gera a tabela/curva de resultado.

| Cálculo | Arquivo | Método / algoritmo |
|---|---|---|
| Classe-base de toda análise | `analysis/Filter.cpp` | Coleta dados da curva no intervalo [x<sub>início</sub>, x<sub>fim</sub>], ordena, cria saída |
| Derivada | `analysis/Differentiation.cpp` | Diferenças finitas centrais: média das inclinações à esquerda e à direita de cada ponto (`output()`) |
| Integral | `analysis/Integration.cpp` | Regra do trapézio (`trapezoid()`); interpolação Linear, Cúbica (spline) ou Akima via `gsl_interp`/`gsl_spline` |
| Interpolação | `analysis/Interpolation.cpp` | `gsl_interp_linear`, `gsl_interp_cspline`, `gsl_interp_akima` |
| Suavização | `analysis/SmoothFilter.cpp` | Savitzky-Golay (mínimos quadrados locais com `gsl_linalg`/`gsl_blas`), FFT, média móvel |
| FFT | `analysis/FFT.cpp` | `gsl_fft_real/complex` (transformada direta e inversa, amplitude, fase) |
| Filtros FFT | `analysis/FFTFilter.cpp` | Passa-baixa, passa-alta, passa-banda, rejeita-banda (`gsl_fft_real_radix2`) |
| Convolução / Deconvolução | `analysis/Convolution.cpp` | Via FFT radix-2 (`gsl_fft_real_radix2_transform`) |
| Correlação | `analysis/Correlation.cpp` | Correlação cruzada via FFT |
| Motor de ajuste não linear | `analysis/fit/Fit.cpp` | Levenberg-Marquardt (`gsl_multifit_fdfsolver_lmsder`/`lmder`) ou Simplex de Nelder-Mead (`gsl_multimin_fminimizer_nmsimplex`); erros dos parâmetros por `gsl_multifit_covar`; χ², R² |
| Funções-modelo e Jacobianas | `analysis/fit/fit_gsl.cpp` | `exp_f/df`, `expd2_*`, `expd3_*`, `boltzmann_*`, `gauss_*`, `gauss_multi_peak_*`, `lorentz_multi_peak_*`, `user_*` (fórmula do usuário avaliada com muParser) |
| Ajuste linear / polinomial | `analysis/fit/PolynomialFit.cpp` | Mínimos quadrados lineares (`gsl_multifit_linear`, ponderado: `gsl_multifit_wlinear`) |
| Exponencial (1, 2, 3 termos) | `analysis/fit/ExponentialFit.cpp` | Classes `ExponentialFit`, `TwoExpFit`, `ThreeExpFit` |
| Sigmoidal | `analysis/fit/SigmoidalFit.cpp` | Boltzmann |
| Gauss / Lorentz / multi-picos | `analysis/fit/MultiPeakFit.cpp` | `GaussFit`, `LorentzFit`, `GaussAmpFit`, `MultiPeakFit` |
| Fórmula do usuário | `analysis/fit/NonLinearFit.cpp` | Expressão digitada no `FitDialog` |
| Plugins de ajuste | `analysis/fit/PluginFit.cpp` + `fitPlugins/` | Carrega funções de bibliotecas dinâmicas |
| Estatísticas | `project/TableStatistics.cpp` | `gsl_stats_mean`, `gsl_stats_sd`, `gsl_stats_variance`, soma, min/max |
| Fórmulas de colunas/matrizes | `scripting/MuParserScript.cpp`, `scripting/MuParserScripting.cpp` | muParser + funções embutidas; `col("A")`, `cell(i,j)` |
| Curvas de função f(x), paramétricas e polares | `plot/FunctionCurve.cpp` | Amostragem da expressão com o ambiente muParser (`ScriptingLangManager`) |
| Histogramas | `plot/QwtHistogram.cpp` | Contagem por classes (bins) com `gsl_histogram` |
| Box-plot | `plot/BoxCurve.cpp` | Quartis, percentis e whiskers com `gsl_stats_quantile_from_sorted_data` |
| Perfil de linha em imagem | `plot/tools/LineProfileTool.cpp` | Amostragem de pixels ao longo de uma linha |

**Fluxo típico de uma análise** (ex.: menu *Analysis → Fit Exponential Decay*):

```
ApplicationWindow (ação do menu)
   └── ExpDecayDialog            (dialogs/)       — usuário escolhe curva e chute inicial
         └── ExponentialFit      (analysis/fit/)  — herda Fit → Filter
               ├── Filter::setDataFromCurve()     — lê pontos da curva
               ├── Fit::fit()                     — GSL Levenberg-Marquardt
               │     └── exp_f / exp_df           (analysis/fit/fit_gsl.cpp)
               └── Filter::addResultCurve()       — desenha o resultado no Graph e
                                                    escreve o log em ApplicationWindow
```

---

## 5. Arquitetura em uma página

```
                         ┌───────────────────────────┐
  scidavis/src/main.cpp ─▶   ApplicationWindow (app) │  janela MDI, menus, salvar/abrir
                         └──────────┬────────────────┘
                                    │ cria e gerencia
          ┌─────────────┬───────────┼─────────────┬──────────────┐
          ▼             ▼           ▼             ▼              ▼
       Folder        Table       Matrix      MultiLayer        Note       (project/, plot/)
     (árvore)          │           │          └─ Graph (camadas)
                       ▼           ▼              └─ PlotCurve, eixos, legenda
                 future_Table  future_Matrix
                       └─ Column ─ filtros de tipo (future/core)

   Análises (analysis/) leem curvas do Graph ou colunas da Table, calculam com GSL
   e devolvem novas colunas/curvas.  Scripts (scripting/) acessam tudo isso via
   muParser ou Python.
```

Pontos importantes:

- **Formato de projeto (`.sciprj`)**: texto com marcadores tipo `<table>`,
  `<graph>`, `<note>` lidos linha a linha em `ApplicationWindow.cpp`
  (`openProject`, `saveProject`) e nos métodos `saveToString()`/`restore()` de
  cada janela.
- **Undo/redo**: implementado na camada `future/` com comandos em
  `aspectcommands.h`, `columncommands.*`, `tablecommands.*`, `matrixcommands.*`.
- **Bindings Python**: `scripting/scidavis.sip` expõe `ApplicationWindow`,
  `Table`, `Matrix`, `Graph`, os fits e filtros para Python; o módulo de
  inicialização é `scidavis/scidavisrc.py`.

---

## 6. Compilando e testando

Requisitos: **Qt 6.8 LTS** (módulos Core, Gui, Widgets, Svg, PrintSupport, Xml,
OpenGL, OpenGLWidgets e LinguistTools), compilador com **C++20** (GCC 11+, Clang 14+,
MSVC 2022), CMake 3.16+, GSL, muParser e zlib. A Qwt 5 e a QwtPlot3D são compiladas
junto com o projeto (não use os pacotes `libqwt*` da distribuição, que são para Qt 5).

Exemplo para Linux (Debian/Ubuntu/Pop!_OS). O Qt 6 das distribuições costuma ser
mais antigo que o 6.8, então ele é instalado em `~/Qt` com o
[aqtinstall](https://github.com/miurahr/aqtinstall), sem precisar de `sudo`:

```bash
sudo apt install build-essential cmake ninja-build libgl1-mesa-dev libglu1-mesa-dev \
                 libxkbcommon-dev libxcb-cursor0 libmuparser-dev libgsl-dev zlib1g-dev libgtest-dev
pip install --user aqtinstall
python3 -m aqt install-qt linux desktop 6.8.3 linux_gcc_64 -O ~/Qt

git submodule update --init --recursive      # qwtplot3d, liborigin

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_PREFIX_PATH=$HOME/Qt/6.8.3/gcc_64 \
      -DSEARCH_FOR_UPDATES=OFF -DDOWNLOAD_LINKS=OFF   # opcional: -DORIGIN_IMPORT=ON
cmake --build build -j$(nproc)
./build/scidavis/scidavis
```

Testes (GoogleTest):

```bash
cmake -S . -B build -DBUILD_TESTS=ON && cmake --build build -j$(nproc)
cd build && ctest --output-on-failure        # em servidor sem tela: xvfb-run ctest ...
```

Opções do CMake: `SCRIPTING_MUPARSER` (ON), `ORIGIN_IMPORT` (OFF), `BUILD_TESTS` (OFF),
`SEARCH_FOR_UPDATES` (ON), `DOWNLOAD_LINKS` (ON). `SCRIPTING_PYTHON` ainda **não** foi
portado para Qt 6/PyQt6 e gera erro se ativado.

### Notas da migração para Qt 6

- **Fontes em projetos**: o Qt 6 mudou a escala de peso das fontes (negrito 75 → 700).
  Os arquivos `.sciprj` e as configurações continuam na escala antiga, para manter
  compatibilidade; a conversão fica em `SciDAVis::fontWeightToLegacy()` /
  `fontWeightFromLegacy()` (`app/globals.cpp`).
- **Caixas de mensagem com botões personalizados**: use `SciDAVis::choice()`
  (`app/globals.cpp`) no lugar das sobrecargas antigas de `QMessageBox`.
- **Conexões `SIGNAL()`/`SLOT()` em texto** não são verificadas pelo compilador: um sinal
  removido no Qt 6 só aparece como aviso `No such signal` ao rodar. Em código novo,
  prefira a sintaxe com ponteiros (`&Classe::sinal`).

### Scripts auxiliares

| Script | Uso |
|---|---|
| `scripts/makeRelease.sh <versão>` | Atualiza `app/version.cpp`, `Doxyversion`, appdata; cria commit e tag |
| `scripts/makeDist.sh` | Gera o tarball de código-fonte (inclui submódulos) |
| `scripts/update_translations.sh` (`.bat`) | Atualiza os `.ts` preservando traduções existentes |
| `scripts/pre-commit.py` | Hook de git que aplica `clang-format` (`ln -s ../../scripts/pre-commit.py .git/hooks/pre-commit`) |
| `scripts/run-coverage.sh`, `scripts/compileTest.sh` | Cobertura de testes e teste de compilação (qmake legado, não funcionam com Qt 6) |
| `packaging/makeMsi.sh`, `packaging/mkMacDist.sh` | Instalador MSI (Windows) e bundle `.app`/`.pkg` (macOS) |

Todos os scripts podem ser chamados de qualquer diretório — eles mudam para a
raiz do repositório antes de executar.

---

## 7. Como contribuir

- **Adicionando um arquivo novo**: coloque-o na pasta do módulo correspondente e
  adicione-o em `libscidavis/CMakeLists.txt` (listas `HEADERS`/`SRCS`). Não é
  preciso mexer em include paths.
- **Nova pasta de módulo**: inclua-a em `target_include_directories` no
  `libscidavis/CMakeLists.txt`.
- **Nova análise**: herde de `Filter` (ou de `Fit` para ajustes) em `analysis/`,
  implemente `calculateOutputData()` (ou as funções-modelo em `fit_gsl.cpp`) e
  crie o diálogo em `dialogs/`.
- **Estilo**: rode `clang-format -i <arquivo>` (regras em `_clang-format`).
- **Mover arquivos**: use `git mv` para preservar o histórico (`git log --follow`).
