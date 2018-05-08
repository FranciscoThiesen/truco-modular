rem testa o modulo lista

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TesteLista     /s..\scripts\TesteLista         /l..\produto\testelist         /a..\scripts\estatisticas
