@ECHO  OFF
REM  Gera todos scripts de make pelos arquivos .comp

cls

pushd  .

cd ..\Ferramentas
gmake /b..\Composicao /c..\Composicao\TESTBAR
gmake /b..\Composicao /c..\Composicao\TESTBARDEBUG


popd