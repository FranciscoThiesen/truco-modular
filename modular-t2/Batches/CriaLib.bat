ECHO Cria a biblioteca a ser utilizada no exemplo \simples
ECHO assume o arcabouco todo construído e correto

pushd  .

cd    ..\Objetos
del    *.obj
del    *.lib
nmake /F..\Composicao\crialib.make  "PRD="
copy  ArcaboucoTeste.lib  ..\Objetos

popd
