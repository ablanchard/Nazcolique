# Nazcolique 2.345d
# Bouchut Sophiane & Blanchard Alexandre
1. INSTALLATION
Ce programme utilise la librairie SDL pour afficher des graphisme époustouflants.
Aussi avant de le lancer assurer vous d'avoir la librairie SDL ainsi que la librairie SDL_image d'installée sur votre PC.
Placer vous dans le dossier du programme puis executer simplement la commande make.
Le fichier executable s'appelle Nazcolique. Assurer vous d'avoir les droits en execution mais normalement le makefile les a mis pour vous.
Vous pouvez lancer le jeu.

2. OPTIONS
./Nazcolique [ADRESSE IP] [OPTIONS] [PARAMETRE]

ADRESSE IP (pour jouer en mode client)
Pour rejoindre un serveur entrez l'adresse ip de celui-ci apres le nom du jeu

OPTIONS
-v
Choisir la vague a laquelle commencer pour le mode solo et le mode serveur Ex: ./Nazcolique -v 12


3. JEU SOLO
Le but du jeu est de resister à des vagues de plus en plus puissantes d'ennemis.
Vous pouvez vous deplacez à l'aide des touches directionnelles et attaquer les ennemis avec espace.

4. HEBERGER UNE PARTIE
En hebergeant une partie sur creez un serveur sur votre PC permettant a d'autre joueur de jouer avec vous pour cela donnez leur simplement votre adresse IP. 
Pour que le jeu fonctionne correctement le broadcast doit etre activé sur le réseau sur lequel vous jouez.
Le logiciel calcul l'adresse d'hébergement la plus adaptée mais si vous voulez la définir manuellement éditez le fichier addr la première ligne correspond à l'adresse IP de votre machine et la seconde à l\'adresse de broadcast du réseau. Puis mettez ce fichier en lecture uniquement pour empecher le programme de modifier vos paramètres.

5. REJOINDRE UNE PARTIE
Vous permet de rejoindre une partie avec d'autre joueurs. Vous devez pour cela connaitre l'adresse IP d'un serveur et lorsque vous lancer le jeu simplement taper ./Nazcolique AdresseIP.

6. EDITER LA MAP
Fonction en cours de développement

