# Guia para Novos Desenvolvedores — Melhorias no SciDAVis

Este documento é um roteiro prático para quem está começando a contribuir com o SciDAVis (C++/Qt5). Ele cobre 4 frentes de trabalho, em ordem recomendada de dificuldade para um iniciante: comece pelo item 4 (bug pontual, baixo risco), depois o item 3 (feature pequena e isolada), e deixe os itens 1 e 2 (organização e UI) para quando já tiver mais confiança no código, pois afetam o projeto inteiro.

> Leia também o `.clang-format` na raiz do projeto — ele já define o estilo de código (WebKit/Qt) que o `clang-format` aplica automaticamente. Rode `clang-format -i <arquivo>` antes de abrir um PR.

---

## 1. Organização de pastas e legibilidade do projeto — ✅ CONCLUÍDO

Feito na branch `reorganize-project-structure`. O código de `libscidavis/src/` foi separado em
`app/`, `project/`, `analysis/` (+ `fit/`), `plot/` (+ `3d/`, `tools/`), `scripting/`, `dialogs/`,
`widgets/` e `io/`; `future/` ficou como estava. Todas as pastas estão no include path (CMake e qmake),
então `#include "Arquivo.h"` continua funcionando sem caminho. Scripts da raiz foram para `scripts/` e
`packaging/`. A descrição de cada módulo e a tabela "onde estão os cálculos" estão no `README.md`.

Ao criar arquivos novos: coloque na pasta do módulo e adicione em `libscidavis/CMakeLists.txt` **e**
`libscidavis/sourcefiles.pri`.

## 2. Modernização da parte gráfica (Qt)

> ✅ **Base atualizada**: na branch `qt6-cpp20` o projeto foi migrado para **Qt 6.8 LTS + C++20**
> (Qwt 5 portada e incluída em `3rdparty/qwt5`). Ver "Notas da migração para Qt 6" no `README.md`.
> Scripts Python (PyQt6) portados; build legado qmake removido.

### Situação atual

- Qt5 puro (Widgets), sem `QStyleSheet` global — cada diálogo monta sua própria paleta manualmente (ex.: `Table.cpp` usa `QPalette` direto, `FitDialog.cpp` idem).
- A maioria dos diálogos é montada 100% em C++ (`new QLabel(...)`, `new QGridLayout(...)`), não em arquivos `.ui`. Só a pasta `future/` usa Qt Designer (`TableConfigPage.ui`, `matrixcontroltabs.ui`, `DimensionsDialog.ui`).
- Ícones são bitmap (`IconLoader` carrega de recurso `.qrc`), não SVG.

### Recomendação (incremental, sem reescrever tudo)

Não é necessário trocar de tecnologia (ex. migrar para QML) — o ganho não compensa o risco em uma base de 230+ arquivos com lógica científica sensível. Modernize a camada Qt Widgets existente:

1. **Tema único via QSS**: criar `resources/styles/light.qss` e `dark.qss`, carregar em `main.cpp`/`ApplicationWindow` com `qApp->setStyleSheet(...)`. Permite trocar tema sem recompilar.
2. **Detectar tema do sistema operacional**: Qt 5.15+ expõe `QPalette` do SO; combine com a opção manual em `ConfigDialog`.
3. **Ícones SVG**: o projeto já linka o módulo `Svg` no `CMakeLists.txt` (`find_package(Qt5 ... Svg ...)`), mas a maior parte dos ícones ainda é bitmap. Trocar por SVG dá ícones nítidos em qualquer DPI (suporte a HiDPI/4K).
4. **Migrar diálogos grandes para `.ui`** seguindo o exemplo de `future/table/TableConfigPage.ui`: comece pelo `AxesDialog` ou `ConfigDialog`, que hoje são só código C++ (`AxesDialog.cpp`, 66 KB de criação manual de widgets). Isso facilita revisão visual e reduz boilerplate.
5. Sempre teste com `QT_SCALE_FACTOR=2 ./scidavis` para garantir que nada quebra em telas de alta densidade.

Comece pelo item 1 (QSS) — é o que dá retorno visual imediato com menor risco, e não exige tocar em lógica de nenhum diálogo existente.

---

## 3. Parênteses coloridos ao escrever fórmulas — ✅ CONCLUÍDO

> Implementado em `libscidavis/src/widgets/BracketHighlighter.*` (cores por nível, erro para fechamento
> sem abertura, destaque do par junto ao cursor, também em campos de uma linha). O texto abaixo é o plano original.

### Onde as fórmulas são digitadas hoje

Encontrei dois pontos de entrada de texto relevantes:

- **`ScriptEdit`** (`libscidavis/src/scripting/ScriptEdit.h` / `.cpp`) — editor usado para scripts Python/muParser. É reutilizado em:
  - `Note.cpp` (janelas de "Nota"/script)
  - `Table.cpp` (diálogo "Set Column Values", onde se digitam fórmulas de coluna)
  - `Matrix.cpp` (fórmulas de matriz)
- **`FunctionDialog`** (`libscidavis/src/dialogs/FunctionDialog.cpp:65`) — usa um `QTextEdit` simples (`boxFunction`) para digitar a função `f(x)` ao criar curvas de função.

O próprio cabeçalho do `ScriptEdit` já lista isso como dívida técnica conhecida:

```cpp
// ScriptEdit.h, linha 43-48
/*!\brief Editor widget with support for evaluating expressions and executing code.
 *
 * \section future_plans Future Plans
 * - Display line numbers.
 * - syntax highlighting, indentation, auto-completion etc. (maybe using QScintilla)
 */
```

Ou seja: não existe nenhum `QSyntaxHighlighter` hoje. É a forma certa de implementar isso em Qt — não precisa de QScintilla para algo tão focado.

### Como implementar

1. Crie uma nova classe `ParenthesisHighlighter : public QSyntaxHighlighter` (novo par de arquivos `ParenthesisHighlighter.h`/`.cpp` em `libscidavis/src/scripting/`, adicionados a `sourcefiles.pri` **e** `CMakeLists.txt`).
2. Estratégia simples e robusta: colorir por **nível de profundidade** (estilo VSCode "Rainbow Brackets"), usando uma pilha:

```cpp
// ParenthesisHighlighter.h
#ifndef PARENTHESISHIGHLIGHTER_H
#define PARENTHESISHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QVector>
#include <QColor>

class ParenthesisHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit ParenthesisHighlighter(QTextDocument *parent);

protected:
    void highlightBlock(const QString &text) override;

private:
    QVector<QColor> m_colors;
};

#endif
```

```cpp
// ParenthesisHighlighter.cpp
#include "ParenthesisHighlighter.h"

ParenthesisHighlighter::ParenthesisHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent),
      m_colors({ QColor("#d19a66"), QColor("#c678dd"), QColor("#56b6c2"),
                 QColor("#98c379"), QColor("#e06c75") })
{
}

void ParenthesisHighlighter::highlightBlock(const QString &text)
{
    // O nível inicial do bloco vem do estado salvo no bloco anterior,
    // para que a contagem de profundidade seja consistente entre linhas.
    int depth = previousBlockState() > 0 ? previousBlockState() : 0;

    for (int i = 0; i < text.length(); ++i) {
        QChar c = text.at(i);
        if (c == '(' || c == '[' || c == '{') {
            QColor color = m_colors[depth % m_colors.size()];
            setFormat(i, 1, color);
            depth++;
        } else if (c == ')' || c == ']' || c == '}') {
            depth = qMax(0, depth - 1);
            QColor color = m_colors[depth % m_colors.size()];
            setFormat(i, 1, color);
        }
    }
    setCurrentBlockState(depth);
}
```

3. Anexe o highlighter onde o texto é editado:
   - Em `ScriptEdit::ScriptEdit(...)` (`ScriptEdit.cpp`, perto da linha 47, no construtor): `new ParenthesisHighlighter(document());`
   - Em `FunctionDialog.cpp`, logo após `boxFunction = new QTextEdit();` (linha 65): `new ParenthesisHighlighter(boxFunction->document());`

   Não precisa guardar o ponteiro: ao passar o `QTextDocument*` como `parent`, o Qt cuida do `delete` automaticamente.

4. **Não pinte os parênteses dentro de uma fórmula matemática de forma diferente da semântica de cores de erro já existente.** `ScriptEdit` já usa `QTextBlockFormat` (`d_fmt_success`/`d_fmt_failure`) para marcar linha executada com sucesso/erro (veja `ScriptEdit.cpp:242-248`). Seu highlighter atua em `QTextCharFormat` (caractere), então não há conflito — mas teste visualmente para confirmar que as duas camadas de cor não ficam ilegíveis juntas.

### Como validar

- Abra uma Tabela → botão direito numa coluna → "Set Column Values" → digite `sin(x*(2+cos(y)))` e confira que cada nível de parênteses tem cor diferente, mesmo movendo o cursor.
- Repita em Plot → "Add Function" (usa `FunctionDialog`).
- Teste parênteses desbalanceados (ex. só `(`) para garantir que não trava nem buga o resto do documento.

---

## 4. Bug: indentação corrompida ao reabrir o projeto após gerar imagem

### Causa raiz mais provável

Achei o suspeito principal em `libscidavis/src/project/Note.cpp`, função `saveToString`:

```cpp
// Note.cpp, linha 70-80
QString Note::saveToString(const QString &info)
{
    QString s = "<note>\n";
    s += QString(name()) + "\t" + birthDate() + "\n";
    s += info;
    s += "WindowLabel\t" + windowLabel() + "\t" + QString::number(captionPolicy()) + "\n";
    s += "AutoExec\t" + QString(autoExec ? "1" : "0") + "\n";
    s += "<content>\n" + te->toPlainText().trimmed() + "\n</content>";
    s += "\n</note>\n";
    return s;
}
```

`QString::trimmed()` remove espaços/tabs/quebras de linha do **início e do fim de toda a string**, não linha por linha. Se o conteúdo da Nota/Script começa com uma linha indentada (ex. um script Python colado começando com espaços, ou simplesmente uma linha vazia antes do código), o `trimmed()` apaga essa indentação **da primeira linha** antes mesmo de salvar no arquivo de projeto. No próximo carregamento, o texto já está salvo sem a indentação original — não é o carregamento que está errado, é o salvamento.

Função correspondente de leitura, para referência (parece correta, só devolve o que foi salvo):

```cpp
// Note.cpp, linha 82-97
void Note::restore(const QStringList &data)
{
    ...
    if (*line == "<content>")
        line++;
    while (line != data.end() && *line != "</content>")
        te->insertPlainText((*line++) + "\n");
}
```

### Por que parece ligado a "gerar uma imagem"

O formato de projeto do SciDAVis (`.sciprj`) não é XML real — `<note>`, `<content>` etc. são apenas marcadores de texto lidos linha a linha (veja os vários `t.readLine().split("\t", ...)` em `ApplicationWindow.cpp`). Gerar/exportar uma imagem de um gráfico no mesmo projeto não corrompe o parser por si só, mas é comum que o fluxo de trabalho que dispara o bug seja: escrever um script numa Nota → gerar o gráfico/imagem a partir dele → salvar o projeto. O `trimmed()` ataca nesse exato salvamento, então o efeito "só aparece depois de gerar a imagem" é provavelmente coincidência de fluxo, não causalidade direta. **Confirme isso comparando o conteúdo de uma Nota antes/depois do save sem nenhuma imagem envolvida** — se a indentação já se perder nesse caso simples, a causa é mesmo o `trimmed()` e o passo da imagem é irrelevante para o bug.

### Suspeito secundário (efeito colateral ao digitar, não ao salvar)

`ScriptEdit::updateIndentation()` (`ScriptEdit.cpp`, linha 391-402), chamada a cada Enter (linha 106-111, `keyPressEvent`):

```cpp
void ScriptEdit::updateIndentation()
{
    QTextCursor cursor = textCursor();
    QTextBlock para = cursor.block();
    QString prev = para.previous().text();
    int i;
    for (i = 0; prev[i].isSpace(); i++)
        ;
    QString indent = prev.mid(0, i);
    cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cursor.insertText(indent);
}
```

Isso só copia a indentação da linha anterior — não trata Tab/4-espaços nem aumenta indentação após `:` (Python) ou `{` , e o acesso `prev[i]` quando a linha anterior é só espaços ou vazia depende do comportamento de `QString::operator[]` fora dos limites (em Qt5 retorna um `QChar()` padrão, então não trava, mas é um código frágil que vale reescrever com `prev.length()` explícito no `for`). Não é a causa do bug relatado, mas é a mesma área de código e vale corrigir junto.

### Plano de correção

1. Trocar o `trimmed()` por algo que não toque na indentação:
   ```cpp
   s += "<content>\n" + te->toPlainText() + "\n</content>";
   ```
   e, se for preciso remover linhas vazias extras no início/fim do documento (era provavelmente a intenção original do `trimmed()`), faça isso explicitamente removendo blocos vazios nas pontas, **sem** usar uma função que afeta espaços internos da primeira linha.
2. Escreva um teste de regressão em `test/` (existe `test/readWriteProject.cpp`, é o lugar certo): criar uma Nota com texto contendo indentação (`"    linha_indentada\noutra"`), salvar projeto, recarregar, comparar string exata.
3. Reescrever `updateIndentation()` com limites explícitos:
   ```cpp
   void ScriptEdit::updateIndentation()
   {
       QTextCursor cursor = textCursor();
       QString prev = cursor.block().previous().text();
       int i = 0;
       while (i < prev.length() && prev.at(i).isSpace())
           i++;
       cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
       cursor.insertText(prev.left(i));
   }
   ```

### Como validar manualmente

1. Abra uma Nota, cole um script com indentação (ex. um `if/for` em Python com 4 espaços).
2. Gere/exporte uma imagem de qualquer gráfico no mesmo projeto.
3. Salve o projeto (`.sciprj`), feche o SciDAVis.
4. Reabra o projeto e confira se a indentação da Nota é idêntica à original (comparação de string, não só visual).
5. Repita sem o passo 2 (sem gerar imagem) para confirmar que o bug independe disso.

---

## 5. Futuro: reescrita em Rust (a explorar)

> Decisão atual: seguir com a **modernização em Qt (item 2)**. Esta seção registra a alternativa de
> longo prazo para estudo futuro.

### Referência: FilmCraft

[FilmCraft](https://github.com/storytold/filmcraft) (reimplementação do Premiere em Rust puro, MIT/Apache-2.0)
é o modelo a seguir:

- Interface em **egui**, isolada num único crate (`ui-egui`); nada abaixo dela depende de toolkit de UI.
- Motor (`engine`) com registro de comandos, sessão, undo/redo e jobs — separado da interface.
- Renderização na GPU via **wgpu** (Metal/Vulkan/DX12/WebGPU), com caminho CPU equivalente testado contra a GPU.
- Roda nativo em Linux/Windows/macOS e no navegador via WebAssembly.
- O projeto se declara *alpha*: é um bom exemplo de arquitetura, não de maturidade.

### O que seria (opção 1: reescrita completa)

Não existe conversão automática C++/Qt → Rust: seria um projeto novo, reaproveitando apenas o
conhecimento (algoritmos, formato `.sciprj`). Tamanho atual a ser substituído: **~96 mil linhas de C++**.

| Módulo atual | Linhas | Equivalente em Rust | Dificuldade |
|---|---|---|---|
| `analysis/` (cálculos) | 6,2k | `rustfft`, `nalgebra`, `statrs`, `levenberg-marquardt`, `argmin` | Baixa |
| `future/` + `project/` (dados, colunas, undo) | 26k | Rust puro (structs + padrão Command) | Média |
| `scripting/` | 3,4k | `evalexpr`/`fasteval` (muParser), `pyo3` (Python) | Média — manter sintaxe das fórmulas |
| `plot/` (2D/3D) | 22k | `egui_plot` ou plot próprio sobre `wgpu` | **Alta** — Qwt dá eixos log, barras de erro, export PDF/EPS/SVG prontos |
| `dialogs/` + `widgets/` + `app/` | 36k | `egui` | Alta (volume) |
| `io/` (Origin `.opj`) | 1,4k + liborigin | sem crate; ponte C++ via `cxx` | Alta |
| Leitor de `.sciprj` | — | parser novo | Média — obrigatório para compatibilidade |

### Caminho sugerido quando for explorar

1. Workspace Cargo separado (`rust/`) no estilo do FilmCraft: `scidavis-core` (dados + cálculos),
   `scidavis-engine` (comandos/undo), `scidavis-ui-egui`, `apps/scidavis`.
2. Começar por `scidavis-core` portando `analysis/` e validar **numericamente** contra a versão C++
   (mesmos dados de entrada → mesmos resultados dos fits/FFT/integrais).
3. Protótipo egui: tabela + gráfico 2D + ajuste de curva + leitura de `.sciprj`.
4. Só então decidir se vale migrar o resto. Pré-requisito: instalar o Rust (`curl https://sh.rustup.rs -sSf | sh`).

---

## Ordem sugerida de trabalho

1. **Item 4** (bug de indentação) — escopo pequeno, 1 arquivo, fácil de testar e de revisar em PR.
2. **Item 3** (parênteses coloridos) — classe nova e isolada, baixo risco de regressão no resto do app.
3. **Item 2** (QSS/tema) — primeiro passo de UI, sem tocar em lógica.
4. ~~**Item 1** (reorganização de pastas)~~ — ✅ concluído.
5. **Item 5** (Rust) — exploração futura, depois do item 2.
