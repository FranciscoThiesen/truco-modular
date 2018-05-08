##################################################
###
### Diretivas de MAKE para o construto: TesteBaralho
### Gerado a partir de: TesteBaralho.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteBaralho


### Nomes de paths

Pdef                 = ..\Tabelas
Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diretórios para geração

Fdef                 = ..\Tabelas
Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox  /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\lista.obj   $(Fobj)\baralho.obj   $(Fobj)\testbaralho.obj \
   Construto

### Limpar arquivos

limpa :
   ..\..\Ferramnt\CompileBanner /c$(NOME)
   ..\..\Ferramnt\CompileBanner /c$(NOME) >$(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\baralho.obj :  {$(Pc)}\baralho.c \
    {$(Ph)}baralho.h            {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\testbaralho.obj :  {$(Pc)}\testbaralho.c \
    {$(Ph)}baralho.h            {$(Ph)}generico.h           {$(Ph)}lerparm.h            \
    {$(Ph)}lista.h              {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\lista.obj   $(Fobj)\baralho.obj   $(Fobj)\testbaralho.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteBaralho
###
##################################################

