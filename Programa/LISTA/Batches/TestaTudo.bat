REM executa os testes dos exemplos simples

del estatisticas.estat

..\Produto\TESTLIS	/s..\Scripts\TesteLista.script /l..\Produto\TESTLIS /a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\Produto\TESTLISDEBUGCONT	/s..\Scripts\TesteListaCont	/l..\Produto\TESTLISDEBUGCONT	/a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\Ferramentas\exbestat /e..\Scripts\estatisticas
:sai