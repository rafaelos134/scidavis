# Documentação

| Pasta | Conteúdo |
|---|---|
| `manual/` | Manual do usuário em LaTeX (`scidavis.tex` é o arquivo principal; `pics/` e `icons/` são as figuras). A versão publicada fica em <https://highperformancecoder.github.io/scidavis-handbook/>. |
| `api/` | Configuração do Doxygen para a documentação do código: `cd docs/api && doxygen` gera `API/html/`. `Doxyversion` é atualizado por `scripts/makeRelease.sh`. |
| `screenshots/` | Capturas de tela usadas no README e na ficha do aplicativo (`scidavis/data/scidavis.appdata.xml`). |
| `ROADMAP.md` | Melhorias planejadas, com o passo a passo de cada uma. |

A visão geral do código (módulos, arquitetura, onde estão os cálculos) está no
[README.md](../README.md) da raiz; o guia para colaboradores, em [CONTRIBUTING.md](../CONTRIBUTING.md).
