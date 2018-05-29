REM  Compila todos os .makes
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio

cls

del ..\Objetos\*.obj
del ..\Produto\*.err
del ..\Produto\*.exe

REM compila para producao sem otimizacoes
pushd .
cd ../Ferramentas
nmake /F..\Composicao\TESTBAR.make 
popd

copy ..\Produto\*.err ..\Produto\tudo.err

notepad ..\Produto\tudo.err