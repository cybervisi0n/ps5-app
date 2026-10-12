#!/bin/bash
PROJECT=ps5app

#Parse args
if [ "$#" -lt 1 ]; then
    echo "Usage: ./drun.sh {command}"
    echo "use --interactive instead of {command} for an interactive shell."
    exit 1
fi

FIRSTARG=1
INTERACTIVE=0
DOCKERFILENAME=docker/Dockerfile

# Interactive shell
if [ "${!FIRSTARG}" = "--interactive" ]; then
    FIRSTARG=$FIRSTARG+1
    INTERACTIVE=1
fi

IMAGENAME=$PROJECT-build

# Build command variable
COMMAND=""
for (( i=$FIRSTARG; i<=$#; i+=1 ))
do
    COMMAND=$COMMAND"${!i} "
done

# Check if container image needs to be built
if [ "$(docker images -q $IMAGENAME)" == "" ]
then
    echo "Building container image $IMAGENAME"
    docker build -t $IMAGENAME -f $DOCKERFILENAME .
fi

mkdir -p ./.fontconfig_cache

CWD=$(pwd)

# Start an interactive shell
if [ $INTERACTIVE -eq 1 ]; then
docker run -it --user $(id -u):$(id -g) \
           --env DISPLAY=$DISPLAY \
           --env GITHUB_ACTIONS=$GITHUB_ACTIONS \
           -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
           --privileged \
           --device /dev/fuse \
           --cap-add SYS_ADMIN \
           --mount type=bind,src=./,target=$CWD \
           $IMAGENAME \
           bash -c "cd $CWD && source ./scripts/env_vars.sh && bash"
exit 0
fi

# Run command in container
docker run --user $(id -u):$(id -g) \
           --env DISPLAY=$DISPLAY \
           --env GITHUB_ACTIONS=$GITHUB_ACTIONS \
           -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
           --privileged \
           --device /dev/fuse \
           --cap-add SYS_ADMIN \
           -i \
           --mount type=bind,src=./,target=$CWD \
           $IMAGENAME bash -c "cd $CWD && source ./scripts/env_vars.sh &&  $COMMAND"

