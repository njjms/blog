#!/bin/sh

GIT=`which git`
DATELOG=`date +'%Y-%m-%d-%H-%M-%S'`
LOG="/tmp/${DATELOG}.txt"
REPO="/home/deploy/mysite"

if [ ! -d ${REPO}/.git ]; then
	echo "${REPO} is not a valid git repo! Aborting..." >> ${LOG}
	exit 0
else
    echo "${REPO} is a valid git repo! Proceeding..." >> ${LOG}
fi

${GIT} add --all . >> ${LOG}
${GIT} commit -m "Automated commit on ${COMMIT_TIMESTAMP}" >> ${LOG}
${GIT} push origin master >> ${LOG}
