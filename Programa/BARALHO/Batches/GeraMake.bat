@ECHO  OFF
REM  Gera script de make
REM    Sintaxe   GeraMake <NomeArquivoComposicao>

pushd  .

if ""=="%1" goto erro

cd ..\Ferramentas
gmake /c..\Composicao\%1 /b..\Composicao

goto sai

:erro
echo Falta nome do arquivo de diretivas de composicao

:sai
popd