
if [[ $# -ne 1 ]]; then
    echo "USAGE: deploy.sh <ACCOUNT NAME>    - Deploys all realated projects in project"
    exit 1
fi

ACCOUNT=$1

./contracts/deploy_contract.sh ${ACCOUNT} ballot ./contracts
