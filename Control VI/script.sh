#!/usr/bin/expect
spawn telnet 100.10.19.37
send "\n"
send "\n"
send "outputEnable = off\n"
send "system.other.reset Ports\n"
interact
