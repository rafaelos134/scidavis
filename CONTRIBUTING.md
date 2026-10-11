# Como contribuir com o SciDAVis

Obrigado pelo interesse! Este guia mostra o caminho mais curto do zero até a sua primeira
contribuição. Para entender o projeto por dentro (módulos, arquitetura, onde estão os cálculos),
veja o [README.md](README.md).

## 1. Preparar o ambiente

Requisitos: Qt 6.8 LTS, compilador com C++20 (GCC 11+, Clang 14+ ou MSVC 2022), CMake 3.16+,
GSL, muParser e zlib. O passo a passo completo para Linux está na seção 6 do README; em resumo:

```bash
git clone --recursive <url-do-repositório> scidavis
cd scidavis
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=$HOME/Qt/6.8.3/gcc_64 -DBUILD_TESTS=ON
cmake --build build -j$(nproc)
./build/scidavis/scidavis
```

Já clonou sem `--recursive`? Rode `git submodule update --init --recursive`.

## 2. Encontrar algo para fazer

- [docs/ROADMAP.md](docs/ROADMAP.md) lista melhorias planejadas, com o passo a passo e os
  arquivos envolvidos em cada uma.
- Bugs e pedidos ficam nas issues do GitHub.

## 3. Onde fica cada coisa

| Quero mexer em... | Pasta |
|---|---|
| Cálculos (ajustes, FFT, integração, estatística) | `libscidavis/src/analysis/` |
| Gráficos 2D e 3D | `libscidavis/src/plot/` |
| Tabelas, matrizes, notas, pastas do projeto | `libscidavis/src/project/` e `libscidavis/src/future/` |
| Janelas de diálogo | `libscidavis/src/dialogs/` |
| Componentes visuais reutilizáveis | `libscidavis/src/widgets/` |
| Fórmulas e scripts (muParser/Python) | `libscidavis/src/scripting/` |
| Janela principal, temas, ícones | `libscidavis/src/app/` e `scidavis/resources/` |
| Traduções | `scidavis/translations/` |
| Testes | `test/` |
| Documentação | `docs/` |

## 4. Regras do código

- **Arquivo novo**: coloque na pasta do módulo e acrescente nas listas `HEADERS`/`SRCS` de
  `libscidavis/CMakeLists.txt`. Os `#include` usam só o nome do arquivo (`#include "Graph.h"`):
  todas as pastas de módulo já estão no include path.
- **Estilo**: rode `clang-format -i <arquivo>` antes do commit (regras em `.clang-format`).
  Para fazer isso automaticamente: `ln -s ../../scripts/pre-commit.py .git/hooks/pre-commit`.
- **Ícones**: sempre `IconLoader::load("nome")`, com o SVG em `scidavis/resources/icons/themed/`
  (veja "Interface: temas e ícones" no README). Não use bitmaps nem cores fixas na interface.
- **Campos de fórmula**: chame `BracketHighlighter::attach(campo)` para colorir os parênteses.
- **Sinais e slots**: prefira `connect(obj, &Classe::sinal, ...)`. A forma com `SIGNAL()`/`SLOT()`
  não é verificada pelo compilador.
- **Textos da interface**: sempre dentro de `tr("...")`, em inglês. As traduções ficam nos `.ts`.
- **Mover arquivos**: use `git mv` para preservar o histórico.

## 5. Testar

```bash
cd build && ctest --output-on-failure     # em servidor sem tela: xvfb-run ctest ...
```

Mudou algo visível? Teste nos temas claro e escuro (Editar → Preferências → Tema). Mexeu em
números? Teste com o programa em português (vírgula decimal) e em inglês (ponto decimal).

## 6. Enviar a contribuição

1. Crie uma branch a partir de `master` (`git checkout -b minha-melhoria`).
2. Faça commits pequenos, cada um com uma mensagem que explique *o que* e *por quê*.
3. Abra um pull request descrevendo a mudança e como você testou. O CI compila e testa em Linux,
   Windows e macOS automaticamente.
