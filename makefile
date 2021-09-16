#Nom du programme
PROG=Programme

#Compilation
CC=gcc

#Copie des fichiers
CP=cp -v

#Options de compilation
CFLAGS=-Wall -ansi -pedantic
#Options d edition de liens
LDFLAGS=-lm

#Repertoire des sources et entete du projet
srcdir=./src/
#Repertoire qui contient les fichiers objets et executable
bindir=./bin/
#Repertoire qui contient la documentation technique du projet
docdir=./doc/
#Repertoire qui contient les fichiers de sauvegarde du projet
savedir=./save

#Fichiers source
SRC=$(wildcard $(srcdir)*.c)
#Fichiers objet
OBJ=$(subst $(srcdir), $(bindir),$(SRC:.c=.o))
#Fichier d entete
HEAD=(wildcard $(srcdir)*.h)

#Commande pour effacer des fichiers
RM=find . -name "*.bak" -type f -delete && find . -name "*.o" -type f -delete && find . -name "*.old" -type f -delete && find . -name "*~" -type f -delete

all : $(PROG)

$(PROG) : $(OBJ)
	$(CC) $^ -o $(bindir)$@ $(LDFLAGS)

./bin/%.o : ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean save doxygen create restore give execute

clean : 
	$(RM)

#Creation des fichier de documentation
doxygen : 
	doxygen -g
	echo "INPUT = src" >> Doxyfile
	echo "OUTPUT_DIRECTORY = doc" >> Doxyfile
	doxygen Doxyfile
	rm -i Doxyfile

#Creation initiale des dossiers
create : 
	@mkdir -pv doc save src bin
	@touch readme.md
	@echo "Se placer avec le terminal dans le dossier où se trouve le fichier Makefile.\n\n" > readme.md
	@echo "# Création des dossiers:\n### make create\n\n" >> readme.md
	@echo "# Compilation:\n### make\n\n" >> readme.md
	@echo "# Executer:\n### make execute\n\n" >> readme.md
	@echo "# Creer une documentation:\n### make doxygen\n###### *necessite un dossier doc et src\n\n" >> readme.md
	@echo "# Sauvegarde des fichiers sources\n### make save\n\n" >> readme.md
	@echo "# Restauration des fichiers de sauvegarde\n### make restore\n\n" >> readme.md
	@echo "# Creation du rendu\n### make give\n###### Fichiers du .zip : src, doc, bin" >> readme.md

#Sauvegarde des fichiers sources
save : 
	$(CP) $(srcdir)* $(savedir)

#Restauration des fichiers sources
restore : 
	$(CP) $(savedir)/* $(srcdir)

#Compression des fichiers dans une archive zip
give : 
	zip -r julien_theo.zip $(srcdir) $(docdir) $(bindir)

#Executer le programme
execute :
	@$(bindir)$(PROG)
