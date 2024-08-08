# can2tcp
This is a CAN2TCP client/server tunnel e.g. for SSH tunnel usage. First you
start the application on the server site. It uses the any host socket
0.0.0.0 on port 7000 and additionally connects to the CAN device vcan0. If
you add the -s option it connects to a remote host using the port 7000. You
can use another CAN device using the -d option. If you want to use another
socket port you have to use the -p option.

