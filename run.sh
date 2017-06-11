#!/bin/bash
set -e

fail() {
    echo $1 >&2    
    exit 1
}

NUMBER_OF_ARGUMENTS=$#

LINUX_VOLUME="$PWD/../linux:/home/student/src/linux"
INITRAMFS_VOLUME="$PWD:/home/student/src/initramfs"
VOLUMES="-v $LINUX_VOLUME -v $INITRAMFS_VOLUME"

BUILD_COMMAND="docker build -t so ./docker"
DEFAULT_COMMAND="docker run -ti $VOLUMES so"
DEBUG_COMMAND="docker exec -ti $(docker ps -q) bash"
INTERACTIVE_COMMAND="docker run -it $VOLUMES so bash"

if [ $NUMBER_OF_ARGUMENTS -eq 0 ]
then
    echo "Running default program..."
    eval $DEFAULT_COMMAND
    # docker run -v "$PWD"/../linux:/home/student/src/linux -v "$PWD":/home/student/src/initramfs so
else
    if [ $NUMBER_OF_ARGUMENTS -gt 1 ]
    then
        fail "You must supply only one argument, run the command with --help or -h to see the options."
    else
        case $1 in
            -i) echo "Running in interactive"
                eval $INTERACTIVE_COMMAND
                ;;
            -b) echo "Building image"
                eval $BUILD_COMMAND
                ;;
            -h) echo "help - to be developed"
                ;;
            --debuger) echo "debug - to be developed"
                eval $DEBUG_COMMAND
                ;;
            *) echo "default"
               eval $DEFAULT_COMMAND
                ;;
        esac
    fi
fi