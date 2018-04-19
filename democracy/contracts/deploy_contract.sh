#!/bin/bash

if [[ $# -ne 2 ]]; then
    echo "USAGE: deploy_contract.sh <ACCOUNT NAME> <Contract Name> from within the directory"
    exit 1
fi

ACCOUNT=$1
CONTRACT=$2

eosiocpp -o ${CONTRACT}/${CONTRACT}.wast ${CONTRACT}/${CONTRACT}.cpp && 
eosiocpp -g ${CONTRACT}/${CONTRACT}.abi ${CONTRACT}/${CONTRACT}.cpp && 
cleos set contract ${ACCOUNT} ./${CONTRACT}