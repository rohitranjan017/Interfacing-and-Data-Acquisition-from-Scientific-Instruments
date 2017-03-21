#!/usr/bin/expect
spawn su - controlx
expect "Password: "
send "123\n"
send "sudo gpib_config\n"
expect "password for controlx: "
send "123\n"
sleep 0.1
send "exit\n"
interact  
