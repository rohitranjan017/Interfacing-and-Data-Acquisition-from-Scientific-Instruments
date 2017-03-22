#!/usr/bin/expect
spawn ibtest
send "d\n"
send "2\n"
send "w\n"
send "SENS:DATA:FRES?\n"
send "r\n"
send "200\n"
send "q\n"
interact
