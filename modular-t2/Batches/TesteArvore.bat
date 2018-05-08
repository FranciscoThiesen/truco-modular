rem testa o modulo arvore

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TesteArvore      /s..\scripts\TesteArvore         /l..\produto\testearvore             /a..\scripts\estatisticas
