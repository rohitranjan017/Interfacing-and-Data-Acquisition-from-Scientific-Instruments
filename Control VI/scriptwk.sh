#!/usr/bin/expect
spawn ibtest
send "d\n"
send "6\n"
send "w\n"
send "SOUR:CURR 0.01\n"
send "q\n"
interact
