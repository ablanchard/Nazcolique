#script bash qui écrit l'adresse de l'hote puis son adresse de Bcast
shopt -s extglob

addr="`ifconfig | grep "inet "`"

set $addr
for i in $*
do
        if [ ${i:0:3} = adr ]
        then
                echo ${i:4}
        fi
        if [ ${i:0:5} = Bcast ]
        then
                echo ${i:6}
        fi

done

