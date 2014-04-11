#!/bin/sh
if [ $# != 3 ]; then
    echo 'Usage: addr2line.sh executefile addressfile functionfile'
    exit;
fi;
echo "begin"
cat $2 |while read line
do
    if [ "$line" = 'enter' ]; then
        read line1
        read line2
#       echo $line >> $3
        addr2line -e $1 -f $line1 -s >>$3
        echo "--->" >> $3
        addr2line -e $1 -f $line2 -s | sed 's/^/  /' >> $3
        echo  >> $3
    elif [ "$line" = 'exit' ]; then
        read line1
        read line2
        addr2line -e $1 -f $line2 -s | sed 's/^/  /' >> $3
        echo "<---" >> $3
        addr2line -e $1 -f $line1 -s  >> $3
#       echo $line >> $3
        echo >> $3
    fi;
done
echo "end"
