Installation de Mydombox
========

Installation de Mydombox
Les paragraphes ci-dessous décrivent comment installer Mydombox sur un raspbery Pi (testé sur Raspbian GNU/Linux 7).

Prérequis

Pour une installation complète sur le Raspberry (Mydombox, Mysql, Apache):

`sudo apt-get install mysql-server libmysqlclient-dev apache2 php5 php5-mysql libcurl4-gnutls-dev`

Pour une installation partielle (juste mydombox, Mysql & Apache sur une autre machine):

`sudo apt-get install libmysqlclient-dev libcurl4-gnutls-dev`

Installation de Mydombox Core

Création d'un user Mydombox

`sudo adduser mydombox`

Entrer un password.

Ajout du user dans le groupe “dialout” (pour avoir acces aux ports USB)

`sudo adduser mydombox dialout`

Création d'un répertoire caché pour les pid de l'application

`su - mydombox
mkdir -p /home/mydombox/.pid/`

Téléchargement de la dernière release

Vous pouvez télécharger la dernière livraison ici, ou la télécharger directement sur le Raspberry :

`su - mydombox
cd /home/mydombox/
wget http://download.mydombox.com/latest.zip`
or
`wget http://download.mydombox.com/mydombox-0.4.0.zip`

Dézipage de la Livraison :

`unzip latest.zip`
or
`unzip mydombox-0.4.0.zip`

Création du lien symbolique vers la version courante :

`cd /home/mydombox/
rm current
ln -s 0.4.0 current `

Création de la BDD Mysql

Création d'un user Mydombox

`cd /home/mydombox/current
mysql -u root -p  < database/Create_mydombox_0-4-0.sql
mysql -u root -p  < database/Populate_mydombox_0-4-0.sql`

Si la bdd est sur la même machine :

`mysql -u root -p  -e "grant all privileges on mydombox.* to mydombox@localhost identified by 'mydomboxpwd';" `
Sinon:

`mysql -u root -p  -e "grant all privileges on mydombox.* to mydombox@'%' identified by 'mydomboxpwd';"`
Migration de la BDD Mysql

Dans le cas ou une version de Mydombox est déja installée , il est possible de migrer la base de donnée pour conserver ses données:

Exemple pour passer de la version 0.2.0 à 0.4.0 :

`cd /home/mydombox/current
mysql -u root -p  < database/Migration_mydombox_0-2-0_to_0-2-1.sql
mysql -u root -p  < database/Migration_mydombox_0-2-1_to_0-3-0.sql
mysql -u root -p  < database/Migration_mydombox_0-3-0_to_0-4-0.sql`

Puis passer la commande suivante pour remplir la Base :

`mysql -u root -p  < database/Populate_mydombox_0-4-0.sql`

Compilation et déploiement

Compilation Pour compiler (attention gcc doit au préalable être installé):

chmod 755 compilation.sh
./compilation.sh

PS: la compilation via make ne fonctionne pas encore.
Scripts de démarrage

Positionner les droits sur le script de démarrage

chmod 755 script/mydombox
Copier le script dans /etc/init.d et l'ajouter au démarrage auto en tant que root:

as root:
cp /home/mydombox/current/script/mydombox /etc/init.d/mydombox
update-rc.d mydombox defaults
Configuration

le fichier de configuration est dans le répertoire conf :

vim /home/mydombox/current/conf/mydombox.conf
Les loglevels disponibles sont les suivants : INFO → ERROR → DEBUG → DEBUG_SQL

Démarrage / Arret

Démarrage de Mydombox:

su - mydombox
service mydombox start 
Arrêt de Mydombox:

su - mydombox
service mydombox stop
Frontend Installation

L'interface web est incluse dans le package, on fait simplement pointer une configuration apache sur le répertoire de l'interface (en tant que root). !!! Cette étape n'est pas nécessaire si elle a déjà été faite une fois. !!!

As root :
cp /home/mydombox/current/frontends/mydombox.conf /etc/apache2/conf.d/
service apache2 restart
Se connecter à Mydombox

Pour se connecter à Mydombox il suffit donc d'ouvrir votre navigateur préféré et taper l'adresse de votre Raspberry:

http://192.168.1.5/mydombox-mobile/