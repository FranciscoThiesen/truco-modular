ECHO compila o modulo baralho
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft
cls

del ..\produto\*.err
del ..\objetos\*.obj

REM compila para producao
pushd .
nmake /F..\composicao\testebaralho.make 
popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

