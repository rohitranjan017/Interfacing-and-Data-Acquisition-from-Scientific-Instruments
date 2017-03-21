#!/usr/bin/expect
spawn ibtest
send "d\n"
send "6\n"
send "w\n"
send "SOUR:CURR 89.00e-6\n"
send "q\n"
interact
