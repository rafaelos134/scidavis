# Testes

- `*.cpp` — testes em C++ com GoogleTest (executável `unittest`); `utils.h` e
  `ApplicationWindowTest.h` têm as funções auxiliares.
- `python/` — scripts executados dentro do SciDAVis (`scidavis -x script.py`) quando o projeto é
  configurado com `-DSCRIPTING_PYTHON=ON`.
- `data/` — projetos (`.sciprj`) e arquivos do Origin (`.opj`) abertos pelos testes; copiados para
  a pasta de build pelo `CMakeLists.txt`.
- `reference/menus/` — menus esperados; o teste compara com os menus gerados pela execução.

Rodar: configure com `-DBUILD_TESTS=ON` e use `ctest --output-on-failure` na pasta de build
(em servidores sem tela, `xvfb-run ctest ...`).
