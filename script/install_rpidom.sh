#!/bin/bash

# RETURN CODES
SUCCESS_CODE=0
HELP_RETURN_CODE=$SUCCESS_CODE
USAGE_ERROR_CODE=1

{
red="\E[31m"
green="\E[32m"
orange="\E[33m"
normal="\E[39m"
}

function mess ()
{
        echo -e "`date \"+%F %T %Z\"` : ${orange}$*${normal}"
}

function info ()
{
        echo -e "${green}$*${normal}"
}

function success ()
{
        echo -e "`date \"+%F %T %Z\"` : ${green}$*${normal}"
}

function error ()
{
        echo -e "`date \"+%F %T %Z\"` : ${red}$*${normal}"
}


####################################################
# Add modules to load in /etc/modules
###################################################

MODULES=("wire" "w1_therm" "i2c_bcm2708" "ds2482")

for ((i=0; i<${#MODULES[*]} ; i++)); 
do
	if [ $(cat /etc/modules | grep -w "${MODULES[i]}" | wc -l) -eq 0 ];then
		echo ${MODULES[i]} >> /etc/modules
		if [ $? -ne 0 ]; then
                        error "Impossible to add module ${MODULES[i]} to /etc/modules "
                        exit $USAGE_ERROR_CODE
                else
                        success "Module ${MODULES[i]} Successflully add in /etc/modules"
                fi
	else
		mess "Module ${MODULES[i]} Already in /etc/modules"
	fi
done

####################################################
# Add command to register i2c device to /etc/rc.local 
###################################################

CMD=("#Command to enable Rpidom card devices:" "echo ds2482 0x18 | sudo tee /sys/bus/i2c/devices/i2c-1/new_device" "echo ds1338 0x68 | sudo tee /sys/bus/i2c/devices/i2c-1/new_device")

cp /etc/rc.local /etc/rc.local-bkp
cat /etc/rc.local | grep -v "exit 0" > /etc/rc.local-tmp
cat /etc/rc.local-tmp > /etc/rc.local
rm /etc/rc.local-tmp
chmod 755 /etc/rc.local

for ((i=0; i<${#CMD[*]} ; i++));
do
        if [ $(cat /etc/rc.local | grep -w "${CMD[i]}" | wc -l) -eq 0 ];then
                echo ${CMD[i]} >> /etc/rc.local
                if [ $? -ne 0 ]; then
                        error "Impossible to add command ${CMD[i]} to /etc/rc.local "
                        exit $USAGE_ERROR_CODE
                else
                        success "Command ${CMD[i]} Successflully add in /etc/rc.local"
                fi
        else
                mess "Module ${CMD[i]} Already in /etc/rc.local"
        fi
done

echo "exit 0" >> /etc/rc.local

####################################################
# Change /boot/cmdline.txt 
###################################################

CMD_OLD="dwc_otg.lpm_enable=0 console=ttyAMA0,115200 kgdboc=ttyAMA0,115200 console=tty1 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline rootwait"
CMD_NEW="dwc_otg.lpm_enable=0 console=tty1 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline rootwait"

if [ $(cat /boot/cmdline.txt | grep -w "$CMD_NEW" | wc -l) -eq 0 ];then

	cp /boot/cmdline.txt /boot/cmdline.txt-bkp
	cat /boot/cmdline.txt | grep -v "$CMD_OLD" > /boot/cmdline.txt-tmp
	mv /boot/cmdline.txt-tmp /boot/cmdline.txt
	chmod 755 /boot/cmdline.txt
	echo $CMD_NEW >> /boot/cmdline.txt	

	if [ $? -ne 0 ]; then
		error "Impossible to upload configuration in /boot/cmdline.txt"
		exit $USAGE_ERROR_CODE
	else
                success "Configuration for Rpidom added in /boot/cmdline.txt"
	fi
else
	mess "Configuration for Rpidom already added in /boot/cmdline.txt"
fi

####################################################
# Change /etc/inittab
###################################################

CMD_OLD="T0:23:respawn:/sbin/getty -L ttyAMA0 115200 vt100"
CMD_NEW="#T0:23:respawn:/sbin/getty -L ttyAMA0 115200 vt100"

if [ $(cat /etc/inittab | grep -w "$CMD_NEW" | wc -l) -eq 0 ];then

        cp /etc/inittab /etc/inittab-bkp
        cat /etc/inittab | grep -v "$CMD_OLD" > /etc/inittab-tmp
        mv /etc/inittab-tmp /etc/inittab
        chmod 644 /etc/inittab
        echo $CMD_NEW >> /etc/inittab

        if [ $? -ne 0 ]; then
                error "Impossible to upload configuration in /etc/inittab"
                exit $USAGE_ERROR_CODE
        else
                success "Configuration for Rpidom change in /etc/inittab"
        fi
else
        mess "Configuration for Rpidom already change in /etc/inittab"
fi

