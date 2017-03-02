#!/bin/sh

set -e

echo 'Check for mydombox.conf'
if [ -f /etc/mydombox/mydombox.conf ]
then
    echo 'Editing /etc/mydombox/mydombox.conf...'
    sed -i "s,mysqlhostname,${MYSQL_HOSTNAME:-localhost}," /etc/mydombox/mydombox.conf
    sed -i "s,mysqlport,${MYSQL_PORT:-3306}," /etc/mydombox/mydombox.conf
    sed -i "s,mysqluser,${MYSQL_USER:-mydombox}," /etc/mydombox/mydombox.conf
    sed -i "s,mysqlpassword,${MYSQL_PASSWORD:-mydomboxpwd}," /etc/mydombox/mydombox.conf
    
fi

echo 'Check for db.php'
if [ -f /var/www/html/mydombox-mobile/inc/db.php ]
then
    echo 'Editing /var/www/html/mydombox-mobile/inc/db.php...'
    sed -i "s,mysqlhostname,${MYSQL_HOSTNAME:-localhost}," /var/www/html/mydombox-mobile/inc/db.php
    sed -i "s,mysqlport,${MYSQL_PORT:-3306}," /var/www/html/mydombox-mobile/inc/db.php
    sed -i "s,mysqluser,${MYSQL_USER:-mydombox}," /var/www/html/mydombox-mobile/inc/db.php
    sed -i "s,mysqlpassword,${MYSQL_PASSWORD:-mydomboxpwd}," /var/www/html/mydombox-mobile/inc/db.php
    
fi

#DATABASE_EXIST=$(mysql -u ${MYSQL_HOSTNAME:-localhost} -pmydomboxpwd -e "show databases;" | grep "^mydombox" | wc -l)
#
#if [ $DATABASE_EXIST -eq 0 ]
#then
#	mysql -u root  -pmydomboxpwd < /etc/mydombox/database/Create_mydombox_0-6-2.sql
#fi

#VERSION=$( mysql -u root mydombox -pmydomboxpwd -e "SELECT MAX(db_version)  FROM database_version;" |awk -F\| '{ print $1 }' | grep -v db_version)

#if [ "${VERSION}" = "0.5.0" ]
#then
#	mysql -u root  -pmydomboxpwd < /etc/mydombox/database/Migration_mydombox_0-5-0_to_0-6-0.sql
#fi
#if [ "${VERSION}" = "0.6.0" ]
#then
#	mysql -u root  -pmydomboxpwd < /etc/mydombox/database/Migration_mydombox_0-6-0_to_0-6-1.sql
#fi

#if [ "${VERSION}" = "0.6.1" ]
#then
#	mysql -u root  -pmydomboxpwd < /etc/mydombox/database/Migration_mydombox_0-6-1_to_0-6-2.sql
#fi


#mysql -u root  -pmydomboxpwd < /etc/mydombox/database/Populate_mydombox_0-6-0.sql
#mysql -u root  -pmydomboxpwd -e "grant all privileges on mydombox.* to mydombox@localhost identified by 'mydomboxpwd';"

/usr/sbin/mydombox /etc/mydombox/mydombox.conf