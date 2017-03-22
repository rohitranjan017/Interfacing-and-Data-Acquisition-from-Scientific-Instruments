#!/usr/bin/expect
spawn telnet 100.10.19.37
sleep 0.2
send "\n"
send "\n"
send "Out1.selected?\n"
send "Out2.selected?\n"
send "Out1.PID.Input?\n"
send "Out2.PID.Input?\n"
send "In1.value?\n"
send "In2.value?\n"
send "In3.value?\n"
send "In4.value?\n"
sleep 0.2
send "\x1D\n"
send "quit\n"
send "\x1D\n"
expect "telnet> "
send "quit\n"
interact
