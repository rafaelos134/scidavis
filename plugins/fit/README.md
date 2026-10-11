# Plugins de ajuste de curvas

Exemplos de funções de ajuste carregadas pelo assistente de ajuste (Análise → Assistente de ajuste)
a partir de bibliotecas dinâmicas. Cada subpasta é um plugin independente, em C ou C++, que usa a
GSL; o carregamento fica em `libscidavis/src/analysis/fit/PluginFit.cpp`.

Para criar um plugin, copie um dos exemplos (por exemplo `explin/`), ajuste a função e acrescente
um `add_subdirectory(...)` e o alvo correspondente em `plugins/fit/CMakeLists.txt`.
