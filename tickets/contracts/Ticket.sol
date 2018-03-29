pragma solidity ^0.4.17;


contract Ticket {
    address public owner;

    function Ticket() public {
        owner = msg.sender;
    }

    function setOwner(address _owner) public {
        require(msg.sender == owner);

        owner = _owner;
    }

}
