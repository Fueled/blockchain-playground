pragma solidity ^0.4.19;

contract Ownable {
    address public owner;

    function Ownable() public {
        owner = msg.sender;
    }

    /**
     * Checks if sender is owner of contract
     */
    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}
