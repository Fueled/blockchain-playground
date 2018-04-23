# Democracy EOS Smart Contract

Simple example of the usual ETH in a EOS smart contract.

## Requirements

- [eosiocpp](https://github.com/EOSIO/eos/wiki/Programs-&-Tools#eosiocpp)



## Deploying

To push the contract onto the EOS blockchain we have to do the following things:

- [Allocate Wallet Address](#setting-up-eos-wallet)
- [Run deploy script](#generate-webassembly-file)

You can use a simple script in contracts called `deploy_contract.sh` that will 


### Deploy script
We've created a quick deploy script that does the following steps:
- Creates the WebAssembly file
- Creates the ABI file
- Deploys contract with given account

**Usage:**

In the root folder of the project, run:

```
./contracts/deploy_contract.sh <ACCOUNT> <CONTRACT>
```

This script assumes the following contract structure, lets say we have `HelloWorld`:
```
contracts/
    HelloWorld/
        HelloWorld.cpp
        Helloworld.hpp

    deploy_contract.sh
```

## Setting up EOS wallet

In order to deploy a contract you will have to push the code onto an account. This account is created with your public key you created through `cleos`.

To get a new public key you simply run:
```
cleos create key
```

This will give you a Public and Private key, note that *only the public key is shared* and is used to create your wallet. From there, verification is done with your Private key you have locally.

A small indicator that distinct these two keys is that the public key starts with the `EOS` prefix.

### Structure of Wallets and Accounts
Similar to other Distributed Apps Blockchain networks such as Ethereum the EOS blockchain uses Wallets to store your assets and sending and receiving transactions. It uses a client called `cleos` to sign your transactions and keeps your private keys safe by encryption.

The difference of EOS and Ethereum is that EOS goes a little further and associates Accounts to these Wallets. An account is a human readable identifier that is stored on the blockchain. These accounts on itself can have specific permissions that are validated upon the transaction to see if this account is permissioned to do so.

```
- Wallet 1 <Public/Secret Key>
    - Account laura
        - Permission read
        - Permission custom_permission
    - Account paul
        - Permission write
        - Permission read

- Wallet 2 <Public/Secret Key>
    - Account henk
    - Account julien
```

### Creating your account
When you retrieved your public key you can start creating an account. These accounts are identified with a name that you can choose, note that the name does not contain any spaces.

Before you can create an account with a specific Public key, make sure that you have imported the private key inside Cleos:
```
cleos create key

>> Private Key: ...
>> Public Key: EOS...
```
```
cleos import <Private key>
```

```
cleos create account eosio hello.code <OWNER PUBLIC KEY> <YOUR PUBLIC KEY>
```

*Note the `PUBLIC OWNER KEY`*: Accounts can be created as sort of a `subaccount`, this basically gives the `owner` certain permissions to control the transactions of that sub account.




# Notes


## Understanding EOS Smart contract

- Smart contracts are written in C++
- Smart Contracts is bascially a class, inheriting the EOSIO `contract` class

- Creating an ABI
	- `eosiocpp` can read through annotations and use it to generate ABI functions
	- These comments can only be read through with the double shash `//` format
	- You can persist mutliple `@abi` in front of the annotation to generate multiple naming in the ABI
		- The `@abi` annotation accepts the type of abi definition is as the first argument, e.g. `action` or `table`
			- the `table` type accepts 2 *optional* parameters, first is possibly a different table name and second one is the type of indexing you want (optional), such as `i64`, make sure to have an `id` property on your struct.
	- `_self` is used globally inside the contract as the contract instance
	- `multi_index` is scoped by the `contract` on initiation


- Database thoughts
	- `emplace` is creating a new item inside the table
	- `multi_index` is indexed by `primary_key()` method in struct, which in itself returns the field to be indexed and unique by
	- Querying the database is done by the `.find` method of the `multi_index` database property
		- `auto iter = table_name.find(YourPrimaryKeyValue)`
		- Updating these rows in the iteration value is done by referencing back the table instance (e.g. `table_name`) and passing the iteration as argument ```table_name.modify(iter, 0, [&]( auto& row) {
               // Do your changes here
              row.value = "New Value"
            });)```

    - `struct` needs to have the `EOSLIB_SERIALIZE` macro to assign what fields have to be serialized in the database
    	- Format is `EOSLIB_SERIALIZE(N(table_name), (field1)(field2)(field3))`
    - `N()` is a macro to `eosio::string_to_name` method that basically takes a string and returns back a 64 bit integer.

    - Use the `available_primary_key` method when you have `i64` setup as `id`


### Generate WebAssembly file

To generate Wast file you can run the following command:
```
eosiocpp -o hello.wast hello.cpp
```

### Generate ABI

In order to push to the blockchain we create an Application Binary Interface, which is a json file that maps your actions and data structures.


## Intro into EOS database

The EOS database is a special feature that enabled you to store data into the blockchain in a structural way. Under the hood EOS uses the Boost `multi_index_container` library.

### Structuring your tables
The EOS database tables can be formatted by `struct` data type, in these structures you are able to define the naming and type definition of your properties of that table.

### Working with vectors
Todo

### Querying your data
Todo

### Persisting & Modifying
Todo

### Under the hood 
Todo


