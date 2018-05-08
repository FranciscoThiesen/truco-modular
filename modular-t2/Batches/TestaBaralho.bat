rem testa o modulo baralho

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TesteBaralho.exe        /s..\scripts\TesteBaralho         /a..\scripts\estatisticas
