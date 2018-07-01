@ECHO  OFF
REM  Testa um programa Formato  Testa  <NomePrograma> <NomeScript> [l]

if ""=="%1" goto erro
if ""=="%2" goto erro
if ""=="%3" goto console

..\Produto\%1 /s..\Scripts\%2 /l..\Produto\%2
goto sai

:console
..\Produto\%1 /s..\Scripts\%2 
goto sai

:erro
ECHO >>> Comando errado deveria ser
ECHO
ECHO  Testa <NomePrograma> <NomeScript> [*]
ECHO     se * existe e' gerado em /produto um log com o mesmo nome do script
ECHO

:sai
