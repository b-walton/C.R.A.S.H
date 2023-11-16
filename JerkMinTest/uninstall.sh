#!/bin/bash

echo "=========================="
echo "Removing App JerkMinTest"


LIBPANDA_USER=$(cat /etc/libpanda.d/libpanda_usr)

# Disable the installed services:
echo " - Disabling startup scripts..."
systemctl disable C.R.A.S.H


# Here is where we remove scripts, services, etc.
echo " - Removing scripts..."
cd
if [ "x"`systemctl list-units | grep -c C.R.A.S.H.service` = "x1" ]; then
    echo "Uninstalling C.R.A.S.H.service"

    source /home/$LIBPANDA_USER/catkin_ws/devel/setup.bash
    rosrun robot_upstart uninstall C.R.A.S.H
fi

systemctl daemon-reload # if needed
