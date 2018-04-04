pragma solidity ^0.4.19;

import "./Ownable.sol";

contract Event is Ownable {
    string public name;
    uint public totalSupply;
    uint public ticketsSold;
    uint public price;

    mapping (address => uint256) public ticketOwners;

    // Mapping of
    mapping (address => mapping (uint => uint)) public ticketOffers;

    function Event(string _name, uint _totalSupply) public {
        name = _name;
        ticketsSold = 0;
        totalSupply = _totalSupply;
    }

    /**
     * Buy ticket for Event
     * @param amount Name of the owner
     * @return ticket newly owned ticket.
    */
    function buyTickets(uint amount)
    public
    payable {
        // Check if there is availability for amount
        require(totalSupply < (ticketsSold + amount));
        require(msg.value <= price);
        ticketOwners[msg.sender] += amount;
        ticketsSold += amount;
    }

    function setTotalSupply(uint availability) public onlyOwner {
        totalSupply = availability;
    }
}
