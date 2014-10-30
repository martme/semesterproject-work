#!/bin/bash

# uses the cpuburn cli, see http://www.hecticgeek.com/2012/03/cpuburn-cpu-stress-test-ubuntu-linux/
# install using sudo-apt-get install cpuburn, for documentation see `$ man cpuburn`

CORES=1
REPITITIONS=3
SLEEPTIME=1
i=0

function usage
{
    echo "usage: cpuload [-c cores]"
}

function do_kill
{
    echo "killing burn threads ..."
    killall burnP6
    #echo "all cpuburn processes were killed"
}


while [ "$1" != "" ]; do
    case $1 in
        -c | --cores )          shift
                                CORES=$1
                                ;;
        -k | --kill )           do_kill
                                exit 1
                                ;;
        -h | --help )           usage
                                exit 1
                                ;;
        * )                     usage
                                exit 1
    esac
    shift
done

until [ $REPITITIONS -lt 1 ]; do
    sleep $SLEEPTIME
    i=$CORES
    until [ $i -lt 1 ]; do
        burnP6 &
        echo "starting burn thread ..."
        let i=i-1
    done
    sleep $SLEEPTIME
    do_kill
    let REPITITIONS=REPITITIONS-1

done


