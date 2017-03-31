#!/usr/bin/expect
spawn telnet 100.10.19.37
send "\n"
send "\n"
send "Out2.PID.P 15\n"
send "Out1.PID.P 15\n"
send "Out2.PID.I 0.2\n"
send "Out1.PID.I 0.2\n"
send "Out2.PID.D 0\n"
send "Out1.PID.D 0\n"
send "system.other.reset Ports\n"
interact
