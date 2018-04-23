#!/bin/bash

if [[ $# -lt 2 ]]; then
    echo "USAGE: deploy_contract.sh <ACCOUNT NAME> <Contract Name> <Contracts Dir (optional)> from within the directory"
    exit 1
fi

ACCOUNT=$1
CONTRACT=$2
CONTRACTS_DIR=$3

eosiocpp -o ${CONTRACTS_DIR}/${CONTRACT}/${CONTRACT}.wast ${CONTRACTS_DIR}/${CONTRACT}/${CONTRACT}.cpp &&
eosiocpp -g ${CONTRACTS_DIR}/${CONTRACT}/${CONTRACT}.abi ${CONTRACTS_DIR}/${CONTRACT}/${CONTRACT}.cpp &&
cleos set contract ${ACCOUNT} ${CONTRACTS_DIR}/${CONTRACT}
