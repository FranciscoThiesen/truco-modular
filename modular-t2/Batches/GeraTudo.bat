@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\..\ferramnt

gmake  /b..\composicao  /cTesteAleatorio
gmake  /b..\composicao  /cTesteFuncoes
gmake  /b..\composicao  /cTesteControleEspaco
gmake  /b..\composicao  /cTesteTabelaSimbolos
gmake  /b..\composicao  /cTesteContadores
gmake  /b..\composicao  /cTesteLerParametros
gmake  /b..\composicao  /cCriaLib

popd
