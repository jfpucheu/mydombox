#!/bin/sh

DATABASE_EXIST=$(mysql -u root  -e "show databases;" | grep "^mydombox" | wc -l)

if [ $DATABASE_EXIST -eq 0 ]
then
	mysql -u root  < /etc/mydombox/database/Create_mydombox_0-6-2.sql
fi

VERSION=$( mysql -u root mydombox  -e "SELECT MAX(db_version)  FROM database_version;" |awk -F\| '{ print $1 }' | grep -v db_version)

if [ "${VERSION}" = "0.5.0" ]
then
	mysql -u root  < /etc/mydombox/database/Migration_mydombox_0-5-0_to_0-6-0.sql
fi
if [ "${VERSION}" = "0.6.0" ]
then
	mysql -u root  < /etc/mydombox/database/Migration_mydombox_0-6-0_to_0-6-1.sql
fi

if [ "${VERSION}" = "0.6.1" ]
then
	mysql -u root  < /etc/mydombox/database/Migration_mydombox_0-6-1_to_0-6-2.sql
fi


mysql -u root  < /etc/mydombox/database/Populate_mydombox_0-6-0.sql
mysql -u root  -e "grant all privileges on mydombox.* to mydombox@localhost identified by 'mydomboxpwd';"

/usr/sbin/mydombox /etc/mydombox/mydombox.conf