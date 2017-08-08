#!/bin/csh -f
# CLASSIFICATION: UNCLASSIFIED

set dir=`dirname $0`

setenv LD_LIBRARY_PATH ${dir}:${dir}/../../CCS/linux
setenv MSPCCS_DATA ${dir}/../../data
setenv JAVA_HOME /usr/jdk1.5.0_18

${JAVA_HOME}/bin/java -Xss1024k -jar ${dir}/MSPCCS.jar
