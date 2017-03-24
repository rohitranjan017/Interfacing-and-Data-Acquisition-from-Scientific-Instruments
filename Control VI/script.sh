#!/usr/bin/expect
spawn telnet 100.10.19.37
sleep 0.2
send "\n"
send "\n"
send "outputEnable = off\n"
sleep 0.2
send "\x1D\n"
send "quit\n"
send "\x1D\n"
expect "telnet> "
send "quit\n"
interact
