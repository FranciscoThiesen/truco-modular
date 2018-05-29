REM executa os testes dos exemplos simples

del estatisticas.estat

..\Produto\TESTLIS	/s..\Scripts\TesteLista.script /l..\Produto\TESTLIS /a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\Ferramentas\exbestat /e..\Scripts\estatisticas
